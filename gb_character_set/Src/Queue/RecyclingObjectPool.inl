namespace recycling_object
{

template <typename Base, typename Derive, typename = void>
struct get_ptr_type
{
	typedef Base type;
};

template <typename Base, typename Derive>
struct get_ptr_type<Base, Derive, std::enable_if_t<sfinae::is_derive<Base, Derive>::value>>
{
	typedef Derive type;
};

}

// 设置回收对象类型
template <typename Base, typename Derive>
void CRecyclingObjectPool<Base, Derive>::SetRecyclingObjectType(ENUM_RECYCLING_OBJECT_TYPE aRecyclingObjectType)
{
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	m_RecyclingObjectType = aRecyclingObjectType;
}

// 设置池大小
template <typename Base, typename Derive>
void CRecyclingObjectPool<Base, Derive>::SetPoolSize(std::size_t aiMaxSize)
{
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	if (aiMaxSize != 0)
		m_iMaxCount = aiMaxSize;
}

// 是否为空
template <typename Base, typename Derive>
bool CRecyclingObjectPool<Base, Derive>::IsEmpty()
{
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	if (m_RecyclingObjectType == ENUM_RECYCLING_OBJECT_TYPE::Unique)
		return m_UniqueList.empty();
	else if (m_RecyclingObjectType == ENUM_RECYCLING_OBJECT_TYPE::Shared)
		return m_SharedList.empty();
	return false;
}

// 池使用大小
template <typename Base, typename Derive>
std::size_t CRecyclingObjectPool<Base, Derive>::Size()
{
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	if (m_RecyclingObjectType == ENUM_RECYCLING_OBJECT_TYPE::Unique)
		return m_UniqueList.size();
	else if (m_RecyclingObjectType == ENUM_RECYCLING_OBJECT_TYPE::Shared)
		return m_SharedList.size();
	return 0;
}

// 获取Unique对象
template <typename Base, typename Derive> template <typename... Args>
std::unique_ptr<Base, std::function<void(Base*)>> CRecyclingObjectPool<Base, Derive>::GetUniqueObject(Args&&... args)
{
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	if (m_RecyclingObjectType != ENUM_RECYCLING_OBJECT_TYPE::Unique)
		return nullptr;
	if (m_UniqueList.empty())
	{
		std::unique_ptr<Base, std::function<void(Base*)>> Object(new typename recycling_object::get_ptr_type<Base, Derive>::type(std::forward<Args>(args)...), std::move(std::bind(&CRecyclingObjectPool<Base, Derive>::Delete, this, std::placeholders::_1)));
		return Object;
	}
	else
	{
		std::unique_ptr<Base, std::function<void(Base*)>> Object(m_UniqueList.front().release(), std::move(std::bind(&CRecyclingObjectPool<Base, Derive>::Delete, this, std::placeholders::_1)));
		m_UniqueList.pop_front();
		return Object;
	}
}

// 获取Shared对象
template <typename Base, typename Derive> template <typename... Args>
std::shared_ptr<Base> CRecyclingObjectPool<Base, Derive>::GetSharedObject(Args&&... args)
{
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	if (m_RecyclingObjectType != ENUM_RECYCLING_OBJECT_TYPE::Shared)
		return nullptr;
	if (m_SharedList.empty())
	{
		std::shared_ptr<Base> Object(new typename recycling_object::get_ptr_type<Base, Derive>::type(std::forward<Args>(args)...), std::bind(&CRecyclingObjectPool<Base, Derive>::Delete, this, std::placeholders::_1));
		return Object;
	}
	else
	{
		auto Object = m_SharedList.front();
		m_SharedList.pop_front();
		return Object;
	}
}

// 释放器
template <typename Base, typename Derive>
void CRecyclingObjectPool<Base, Derive>::Delete(Base* apObject)
{
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	if (m_RecyclingObjectType == ENUM_RECYCLING_OBJECT_TYPE::Unique)
	{
		if (m_UniqueList.size() <= m_iMaxCount)
			m_UniqueList.emplace_back(std::unique_ptr<Base>(apObject));
		else
			delete apObject;
	}
	else if (m_RecyclingObjectType == ENUM_RECYCLING_OBJECT_TYPE::Shared)
	{
		if (m_SharedList.size() <= m_iMaxCount)
			m_SharedList.emplace_back(std::shared_ptr<Base>(apObject, std::bind(&CRecyclingObjectPool<Base, Derive>::Delete, this, std::placeholders::_1)));
		else
			delete apObject;
	}
}