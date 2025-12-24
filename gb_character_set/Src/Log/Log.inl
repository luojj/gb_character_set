// 流式日志(没有日志长度的限制)
template <typename ...Params>
void CLog::StreamLog(ENUM_LOG_LEVEL aLogLevel, const std::string& astrModuleName, Params&&... params)
{
	// 是否打印日志
	if (!IsPrint(aLogLevel))
		return;
	auto pConsoleInfo = m_MemoryPool.GetSharedObject();
	if (pConsoleInfo == nullptr)
		return;
	pConsoleInfo->Resize(0);
	// 添加时间戳
	AddTimestamp(pConsoleInfo);
	// 添加日志级别
	AddLogLevel(aLogLevel, pConsoleInfo);
	// 添加线程ID
	AddThreadID(pConsoleInfo);
	// 添加模块名
	AddModuleName(astrModuleName, pConsoleInfo);
	// 打印参数
	*pConsoleInfo += "[";
	PrintParam(pConsoleInfo, std::forward<Params>(params)...);
	*pConsoleInfo += "]";
	// 添加换行符号
	*pConsoleInfo += "\n";
	// 打印到控制台
	PrintToConsole(pConsoleInfo);
	// 输出日志
	// 注意:外层不能执行耗时的处理,否则会影响整体性能.外层应该直接将日志数据放入队列后返回.
	if (m_LogConfig.m_OutputFunc != nullptr)
		m_LogConfig.m_OutputFunc(pConsoleInfo->GetMultiData(), pConsoleInfo->GetMultiDataLen());
	
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	// 检测是否需要将日志写入文件
	PrintFileStrategy(pConsoleInfo);
	// 切换日志
	ChangeLog();
}

// 基于Key-Value的流式日志(没有日志长度的限制)
template <typename ...Params>
void CLog::StreamKeyValueLog(ENUM_LOG_LEVEL aLogLevel, const std::string& astrModuleName, const char* apContent, Params&&... params)
{
	// 是否打印日志
	if (!IsPrint(aLogLevel))
		return;
	auto pConsoleInfo = m_MemoryPool.GetSharedObject();
	if (pConsoleInfo == nullptr)
		return;
	pConsoleInfo->Resize(0);
	// 添加时间戳
	AddTimestamp(pConsoleInfo);
	// 添加日志级别
	AddLogLevel(aLogLevel, pConsoleInfo);
	// 添加线程ID
	AddThreadID(pConsoleInfo);
	// 添加模块名
	AddModuleName(astrModuleName, pConsoleInfo);
	// 打印日志内容
	PrintContent(apContent, pConsoleInfo);
	// 打印参数
	*pConsoleInfo += "[";
	PrintKeyValueParam(pConsoleInfo, std::forward<Params>(params)...);
	*pConsoleInfo += "]";
	// 添加换行符号
	*pConsoleInfo += "\n";
	// 打印到控制台
	PrintToConsole(pConsoleInfo);
	// 输出日志
	// 注意:外层不能执行耗时的处理,否则会影响整体性能.外层应该直接将日志数据放入队列后返回.
	if (m_LogConfig.m_OutputFunc != nullptr)
		m_LogConfig.m_OutputFunc(pConsoleInfo->GetMultiData(), pConsoleInfo->GetMultiDataLen());

	std::lock_guard<std::mutex> AutoLock(m_Lock);
	// 检测是否需要将日志写入文件
	PrintFileStrategy(pConsoleInfo);
	// 切换日志
	ChangeLog();
}

// 打印参数
template <typename Param1, typename ... Params>
void CLog::PrintParam(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo, Param1 param1, Params&&... params) const
{
	// 将数据写入缓存
	std::ostringstream os;
	os << param1 << ", ";
	*apConsoleInfo += os.str();
	PrintParam(apConsoleInfo, std::forward<Params>(params)...);
}

// 打印参数(作为递归的结束)
template <typename Param>
void CLog::PrintParam(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo, Param&& param) const
{
	// 将数据写入缓存
	std::ostringstream os;
	os << param;
	*apConsoleInfo += os.str();
}

// 打印KeyValue参数
template <typename ... Params>
void CLog::PrintKeyValueParam(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo, Params&&... params) const
{
	std::ostringstream os;
	bool bIsKey = true;
	std::size_t iParamCount = sizeof...(params);
	std::size_t iValueCount = 0;
	using Expander = int[];
	Expander{ (GetKeyValueParam(os, params, iParamCount, iValueCount, bIsKey), 0)... };
	if (!bIsKey)	// 如果发现输入的Key和Value不配对,则添加以下内容
		os << " (Key Value Not Pair!)";
	*apConsoleInfo += os.str();
}

// 获取KeyValue参数
template <typename Param>
void CLog::GetKeyValueParam(std::ostringstream& aOutput, Param object, std::size_t aiParamCount, std::size_t& aiValueCount, bool& abIsKey) const
{
	++aiValueCount;
	if (abIsKey)
	{
		aOutput << object << ":";
	}
	else
	{
		if (aiValueCount == aiParamCount)
			aOutput << object;
		else
			aOutput << object << ", ";
	}
	abIsKey = !abIsKey;
}