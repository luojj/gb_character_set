// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：RecyclingObjectPool.h
// 创建日期：2014-12-03
// 创建人：罗俊杰
// 文件说明：回收对象池
// $_FILEHEADER_END ***********************************************************

#ifndef RECYCLING_OBJECT_POOL_H
#define RECYCLING_OBJECT_POOL_H

#include <mutex>
#include <list>
#include <memory>
#include <functional>
#include "TypeDef.h"
#include "CommonMacro.h"
#include "TypeTraits/sfinae_is_xxx.h"

// 池中可存放的最大对象个数(默认值)
constexpr std::size_t DEF_RECYCLING_OBJECT_POOL_MAX_COUNT = 1024;

// 回收对象类型
enum class ENUM_RECYCLING_OBJECT_TYPE : MyUInt16
{
	Default = 0,// 默认值
	Unique = 1,	// std::unique_ptr对象
	Shared = 2,	// std::shared_ptr对象
};

template <typename Base, typename Derive>
class CRecyclingObjectPool
{
public:
	CRecyclingObjectPool() = default;
	~CRecyclingObjectPool() { m_iMaxCount = 0; };

public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetRecyclingObjectType
	// 函数参数：aRecyclingObjectType	[输入]	回收对象类型
	// 返 回 值：
	// 函数说明：设置回收对象类型
	// $_FUNCTION_END *********************************************************
	void SetRecyclingObjectType(ENUM_RECYCLING_OBJECT_TYPE aRecyclingObjectType);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetPoolSize
	// 函数参数：aiMaxSize				[输入]	最大大小
	// 返 回 值：
	// 函数说明：设置池大小
	// $_FUNCTION_END *********************************************************
	void SetPoolSize(std::size_t aiMaxSize);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：IsEmpty
	// 函数参数：
	// 返 回 值：是否为空
	// 函数说明：是否为空
	// $_FUNCTION_END *********************************************************
	bool IsEmpty();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：size
	// 函数参数：
	// 返 回 值：池使用大小
	// 函数说明：池使用大小
	// $_FUNCTION_END *********************************************************
	std::size_t Size();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetUniqueObject
	// 函数参数：
	// 返 回 值：对象
	// 函数说明：获取Unique对象
	// $_FUNCTION_END *********************************************************
	template <typename... Args>
	std::unique_ptr<Base, std::function<void(Base*)>> GetUniqueObject(Args&&... args);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSharedObject
	// 函数参数：
	// 返 回 值：对象
	// 函数说明：获取Shared对象
	// $_FUNCTION_END *********************************************************
	template <typename... Args>
	std::shared_ptr<Base> GetSharedObject(Args&&... args);

private:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Delete
	// 函数参数：apObject				[输入]		对象
	// 返 回 值：
	// 函数说明：释放器
	// $_FUNCTION_END *********************************************************
	void Delete(Base* apObject);

private:
	// 锁
	std::mutex							m_Lock;
	// 回收对象类型
	ENUM_RECYCLING_OBJECT_TYPE			m_RecyclingObjectType = ENUM_RECYCLING_OBJECT_TYPE::Default;
	// 池中可存放的最大对象个数
	std::size_t							m_iMaxCount = DEF_RECYCLING_OBJECT_POOL_MAX_COUNT;
	// Unique缓存对象池
	std::list<std::unique_ptr<Base>>	m_UniqueList{};
	// Shared缓存对象池
	std::list<std::shared_ptr<Base>>	m_SharedList{};
};

#include "RecyclingObjectPool.inl"

#endif