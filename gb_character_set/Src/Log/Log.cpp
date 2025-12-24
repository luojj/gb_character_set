#if defined (ANDROID) || defined (__ANDROID__)	// Android平台
#include <android/log.h>
#endif
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <thread>
#include "Log/Log.h"
#include "Chrono/ChronoWrapper.h"
#include "Utils/SyncStreamUtils.h"
#include "File/FileSystem.h"

constexpr MyUInt16 DEF_FORMAT_MAX_LEN = 2048;
////////////////////////////////////////////////////////////////////////////////////////////////////
// CLog
// 初始化日志
bool CLog::InitLog(const STRUCT_LOG_CONFIG& aLogConfig)
{
	if (aLogConfig.m_strProcessName.empty())
		return false;
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	// 设置Log路径
	m_strLogFilePath = CFileSystem::GetCurrentPath(aLogConfig.m_bByProcess);
	m_strLogFilePath += "/Log";
	// 检测日志文件夹,如果没有则创建
	if (!CFileSystem::IsExists(m_strLogFilePath))
		CFileSystem::CreateSystemDirectory(m_strLogFilePath);
	// 保存日志配置
	m_LogConfig = aLogConfig;
	// 生成日志文件路径
	m_strLogFilePath += "/" + m_LogConfig.m_strProcessName + "_" + CChronoWrapper::GetFormatTime(ENUM_TIME_FORMAT_TYPE::Time1) + ".log";
	// 检查日志选项
	if (m_LogConfig.m_iLogOption == 0)
#if defined (_DEBUG) || defined(DEBUG)
		m_LogConfig.m_iLogOption = ((MyUInt16)ENUM_LOG_OPTION::Timestamp | (MyUInt16)ENUM_LOG_OPTION::LogLevel | (MyUInt16)ENUM_LOG_OPTION::ThreadID | (MyUInt16)ENUM_LOG_OPTION::PrintToFile | (MyUInt16)ENUM_LOG_OPTION::PrintToConsole);
#else
		m_LogConfig.m_iLogOption = ((MyUInt16)ENUM_LOG_OPTION::Timestamp | (MyUInt16)ENUM_LOG_OPTION::LogLevel | (MyUInt16)ENUM_LOG_OPTION::ThreadID | (MyUInt16)ENUM_LOG_OPTION::PrintToFile);
#endif
	// 检查日志切割参数
	if (m_LogConfig.m_iLogSlicingType == ENUM_LOG_SLICING_TYPE::Time)
	{
		if (m_LogConfig.m_iLogSlicingParam == 0)
			m_LogConfig.m_iLogSlicingParam = 24;
	}
	else if (m_LogConfig.m_iLogSlicingType == ENUM_LOG_SLICING_TYPE::Size)
	{
		if (m_LogConfig.m_iLogSlicingParam == 0)
			m_LogConfig.m_iLogSlicingParam = m_iLogCacheMaxSize;
	}
	// 检查日志缓存大小
	if (m_LogConfig.m_iLogCacheSize > m_iLogCacheMaxSize)
		m_LogConfig.m_iLogCacheSize = m_iLogCacheMaxSize;
	// 内存池
	m_MemoryPool.SetRecyclingObjectType(ENUM_RECYCLING_OBJECT_TYPE::Shared);
	// 给文件日志缓存分配内存
	m_FileLogBuff.Reserve(m_iLogCacheMaxSize);
	// 保存日志写入时间
	m_iLogWriteTime = CChronoWrapper::MS_Time(ENUM_CLOCK_TYPE::Steady);
	// 保存日志生成时间
	m_iCreateTime = CChronoWrapper::H_Time(ENUM_CLOCK_TYPE::System);
	return true;
}

// 设置日志缓存大小
void CLog::SetLogCacheSize(MyUInt32 aiLogCacheSize)
{
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	if (aiLogCacheSize > m_iLogCacheMaxSize)
		m_LogConfig.m_iLogCacheSize = m_iLogCacheMaxSize;
	else
		m_LogConfig.m_iLogCacheSize = aiLogCacheSize;
}

// 设置日志等级
void CLog::SetLogLevel(ENUM_LOG_LEVEL aLogLevel)
{
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	m_LogConfig.m_LogLevel = aLogLevel;
}

// 格式化日志(日志长度不可以超过3K大小,不然会崩溃)
void CLog::FormatLog(ENUM_LOG_LEVEL aLogLevel, const std::string& astrModuleName, const char* apFormat, ...)
{
	// 不能输出空字符串
	if (apFormat == nullptr)
		return;
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
	// 添加日志记录
	va_list argptr;
	va_start(argptr, apFormat);
	AddLog(apFormat, argptr, pConsoleInfo);
	va_end(argptr);
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

// 提交日志
void CLog::Flush()
{
	// 将剩下的日志写入文件
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	PrintToFile();
}

// 是否打印日志
bool CLog::IsPrint(ENUM_LOG_LEVEL aLogLevel)
{
	std::lock_guard<std::mutex> AutoLock(m_Lock);
	return ((m_LogConfig.m_LogLevel <= aLogLevel) ? true : false);
}

// 添加时间戳
void CLog::AddTimestamp(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const
{
	if (m_LogConfig.m_iLogOption & (MyUInt16)ENUM_LOG_OPTION::Timestamp) // 打印时间戳
		*apConsoleInfo += std::format("[{}]", CChronoWrapper::GetFormatTime(ENUM_TIME_FORMAT_TYPE::Time3));
}

// 添加日志级别
void CLog::AddLogLevel(ENUM_LOG_LEVEL aLogLevel, std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const
{
	if (m_LogConfig.m_iLogOption & (MyUInt16)ENUM_LOG_OPTION::LogLevel)	// 打印日志级别
	{
		// 将数据写入缓存
		if (aLogLevel == ENUM_LOG_LEVEL::Debug)
			*apConsoleInfo += std::format("[{:^7}]", "Debug");
		else if (aLogLevel == ENUM_LOG_LEVEL::Info)
			*apConsoleInfo += std::format("[{:^7}]", "Info");
		else if (aLogLevel == ENUM_LOG_LEVEL::Warn)
			*apConsoleInfo += std::format("[{:^7}]", "Warn");
		else if (aLogLevel == ENUM_LOG_LEVEL::Error)
			*apConsoleInfo += std::format("[{:^7}]", "Error");
		else
			*apConsoleInfo += std::format("[{:^7}]", "Unknown");
	}
}

// 添加线程ID
void CLog::AddThreadID(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const
{
	if (m_LogConfig.m_iLogOption & (MyUInt16)ENUM_LOG_OPTION::ThreadID)	// 打印线程ID
	{
		// 将数据写入缓存
		std::ostringstream os;
		os << std::this_thread::get_id();
		// linux下最长的线程ID为15位字符串
		*apConsoleInfo += std::format("[{:^15}]", os.str());
	}
}

// 添加模块名
void CLog::AddModuleName(const std::string& astrModuleName, std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const
{
	if (!astrModuleName.empty())
		*apConsoleInfo += std::format("[{:^30}]", astrModuleName);
}

// 添加日志记录
void CLog::AddLog(const char* apFormat, va_list& argptr, std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const
{
#if defined (_WIN32)
	// 把szFormat追加到apConsoleInfo中
	// 注意格式化字符串的长度不能超过DEF_FORMAT_MAX_LEN
	char szTemp[DEF_FORMAT_MAX_LEN]{};
	auto iLen = _vsnprintf_s(szTemp, DEF_FORMAT_MAX_LEN, apFormat, argptr);
	*apConsoleInfo += "[";
	apConsoleInfo->AppendDataBuffer(szTemp, iLen);
	*apConsoleInfo += "]";
#else
	// 把szFormat追加到apConsoleInfo中
	// 注意格式化字符串的长度不能超过DEF_FORMAT_MAX_LEN
	char szTemp[DEF_FORMAT_MAX_LEN]{};
	auto iLen = vsnprintf(szTemp, DEF_FORMAT_MAX_LEN, apFormat, argptr);
	*apConsoleInfo += "[";
	apConsoleInfo->AppendDataBuffer(szTemp, iLen);
	*apConsoleInfo += "]";
#endif
	// 添加换行符号
	* apConsoleInfo += "\n";
}

// 打印到控制台
void CLog::PrintToConsole(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const
{
	if (m_LogConfig.m_iLogOption & (MyUInt16)ENUM_LOG_OPTION::PrintToConsole)	// 打印到控制台
	{
#if defined (ANDROID) || defined (__ANDROID__)	// Android平台
		__android_log_print(ANDROID_LOG_INFO, "Android Platform", "%s", apConsoleInfo->ToString().c_str());
#else
		CSyncStreamUtils() << apConsoleInfo->ToString();
#endif
	}
}

// 打印到文件
bool CLog::PrintToFile()
{
	bool bReturn = true;
	if (m_LogConfig.m_iLogOption & (MyUInt16)ENUM_LOG_OPTION::PrintToFile)	// 打印到文件
	{
		if (!m_strLogFilePath.empty())	// 有文件名,并且有可打印标志,则打印到文件
		{
			FILE* pFile = nullptr;
			pFile = fopen(m_strLogFilePath.c_str(), "a");
			if (pFile != nullptr)
			{
				setlocale(LC_ALL, "");
				fwrite(m_FileLogBuff.GetMultiData(), sizeof(char), m_FileLogBuff.GetMultiDataLen(), pFile);
				fclose(pFile);

				m_iLogWriteSize += m_FileLogBuff.GetMultiDataLen();
			}
			else
			{
				m_FileLogBuff += "CLog::PrintToFile _tfopen Failed!";
				// 为防止日志缓存一直不能写入磁盘而造成的内存疯涨情况,当缓存大于日志缓存最大上限则清除缓存
				if (m_FileLogBuff.GetMultiDataLen() < m_iLogCacheMaxSize)
					bReturn = false;
			}
		}
	}
	return bReturn;
}

// 打印文件的策略
void CLog::PrintFileStrategy(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo)
{
	m_FileLogBuff += *apConsoleInfo;
	if (m_FileLogBuff.GetMultiDataLen() > m_LogConfig.m_iLogCacheSize)
	{
		// 当日志缓存大于设置的日志缓存大小时直接写入文件
		if (PrintToFile())
			m_FileLogBuff.Resize(0);
	}
	else
	{
		// 当日志缓存小于等于设置的日志缓存大小时,检测日志上次写入时间
		// 如果超过3秒则直接写入文件
		if (CChronoWrapper::MS_Time(ENUM_CLOCK_TYPE::Steady) - m_iLogWriteTime > 3000)
		{
			if (PrintToFile())
				m_FileLogBuff.Resize(0);
			m_iLogWriteTime = CChronoWrapper::MS_Time(ENUM_CLOCK_TYPE::Steady);
		}
	}
}

// 切换日志
void CLog::ChangeLog()
{
	if (m_LogConfig.m_iLogSlicingType == ENUM_LOG_SLICING_TYPE::Time)
	{
		// 取得当前时间
		auto iNow = CChronoWrapper::H_Time(ENUM_CLOCK_TYPE::System);
		if (MyUInt64(iNow - m_iCreateTime) > m_LogConfig.m_iLogSlicingParam)
		{
			// 修改日志文件路径
			m_strLogFilePath = CFileSystem::GetCurrentPath(m_LogConfig.m_bByProcess);
			m_strLogFilePath += "/Log";
			m_strLogFilePath += "/" + m_LogConfig.m_strProcessName + "_" + CChronoWrapper::GetFormatTime(ENUM_TIME_FORMAT_TYPE::Time1) + ".log";
			// 修改时间
			m_iCreateTime = CChronoWrapper::H_Time(ENUM_CLOCK_TYPE::System);
		}
	}
	else if (m_LogConfig.m_iLogSlicingType == ENUM_LOG_SLICING_TYPE::Size)
	{
		if (m_iLogWriteSize > m_LogConfig.m_iLogSlicingParam * 1024)
		{
			// 修改日志文件路径
			m_strLogFilePath = CFileSystem::GetCurrentPath(m_LogConfig.m_bByProcess);
			m_strLogFilePath += "/Log";
			m_strLogFilePath += "/" + m_LogConfig.m_strProcessName + "_" + CChronoWrapper::GetFormatTime(ENUM_TIME_FORMAT_TYPE::Time1) + ".log";
			// 修改日志写入大小
			m_iLogWriteSize = 0;
		}
	}
}

// 打印日志内容
void CLog::PrintContent(const char* apContent, std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const
{
	*apConsoleInfo += std::format("[{:^10}]", apContent);
}