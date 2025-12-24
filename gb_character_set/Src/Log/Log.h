// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：Log.h
// 创建日期：2012-07-06
// 创建人：罗俊杰
// 文件说明：日志类
// $_FILEHEADER_END ***********************************************************

#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <string.h>
#include <ctime>
#include <mutex>
#include <string>
#include <sstream>
#include <memory>
#include "TypeDef.h"
#include "LogConfig.h"
#include "Memory/AutoFreeBuffer.h"
#include "Queue/RecyclingObjectPool.h"

class CLog
{
public:
	CLog() = default;
	~CLog() = default;

public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：InitLog
	// 函数参数：aLogConfig			[输入]		日子配置
	// 返 回 值：调用是否成功
	// 函数说明：初始化日志
	// $_FUNCTION_END *********************************************************
	bool InitLog(const STRUCT_LOG_CONFIG& aLogConfig);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：SetLogCacheSize
	// 函数参数：aiLogCacheSize		[输入]		日志缓存大小
	// 返 回 值：
	// 函数说明：设置日志缓存大小
	// $_FUNCTION_END ****************************************************
	void SetLogCacheSize(MyUInt32 aiLogCacheSize);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetLogLevel
	// 函数参数：aLogLevel			[输入]		日志等级
	// 返 回 值：
	// 函数说明：设置日志等级
	// $_FUNCTION_END *********************************************************
	void SetLogLevel(ENUM_LOG_LEVEL aLogLevel);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：FormatLog
	// 函数参数：aLogLevel			[输入]		每条日志记录的日志等级,如果这个日志等级低于SetLogLevel设置的等级,将不打印到文件中,但可以打印到控制台
	//			 astrModuleName		[输入]		模块名
	//			 apFormat			[输入]		日志记录的格式化字符串
	//			 ...				[输入]		日志记录格式化参数
	// 返 回 值：
	// 函数说明：格式化日志(日志长度不可以超过3K大小,不然会崩溃)
	// $_FUNCTION_END ****************************************************
	void FormatLog(ENUM_LOG_LEVEL aLogLevel, const std::string& astrModuleName, const char* apFormat, ...);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：StreamLog
	// 函数参数：aLogLevel			[输入]		每条日志记录的日志等级,如果这个日志等级低于SetLogLevel设置的等级,将不打印到文件中,但可以打印到控制台
	//			 astrModuleName		[输入]		模块名
	//			 params				[输入]		日志记录的扩展参数
	// 返 回 值：
	// 函数说明：流式日志(没有日志长度的限制)
	// $_FUNCTION_END ****************************************************
	template <typename ...Params>
	void StreamLog(ENUM_LOG_LEVEL aLogLevel, const std::string& astrModuleName, Params&&... params);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：StreamKeyValueLog
	// 函数参数：aLogLevel			[输入]		每条日志记录的日志等级,如果这个日志等级低于SetLogLevel设置的等级,将不打印到文件中,但可以打印到控制台
	//			 astrModuleName		[输入]		模块名
	//			 apContent			[输入]		日志记录的内容
	//			 params				[输入]		日志记录的扩展参数
	// 返 回 值：
	// 函数说明：基于Key-Value的流式日志(没有日志长度的限制)
	// $_FUNCTION_END ****************************************************
	template <typename ...Params>
	void StreamKeyValueLog(ENUM_LOG_LEVEL aLogLevel, const std::string& astrModuleName, const char* apContent, Params&&... params);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Flush
	// 函数参数：
	// 返 回 值：
	// 函数说明：提交日志
	// $_FUNCTION_END *********************************************************
	void Flush();
	
private:
	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：IsPrint
	// 函数参数：aLogLevel			[输入]		每条日志记录的日志等级
	// 返 回 值：是否打印日志
	// 函数说明：是否打印日志
	// $_FUNCTION_END ****************************************************
	bool IsPrint(ENUM_LOG_LEVEL aLogLevel);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：AddTimestamp
	// 函数参数：apConsoleInfo		[输入|输出]	控制台信息
	// 返 回 值：
	// 函数说明：添加时间戳
	// $_FUNCTION_END ****************************************************
	void AddTimestamp(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const;
	
	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：AddLogLevel
	// 函数参数：aLogLevel			[输入]		每条日志记录的日志等级
	//			 apConsoleInfo		[输入|输出]	控制台信息
	// 返 回 值：
	// 函数说明：添加日志级别
	// $_FUNCTION_END ****************************************************
	void AddLogLevel(ENUM_LOG_LEVEL aLogLevel, std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const;
	
	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：AddThreadID
	// 函数参数：apConsoleInfo		[输入|输出]	控制台信息
	// 返 回 值：
	// 函数说明：添加线程ID
	// $_FUNCTION_END ****************************************************
	void AddThreadID(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const;

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：AddModuleName
	// 函数参数：astrModuleName		[输入]		模块名
	//			 apConsoleInfo		[输入|输出]	控制台信息
	// 返 回 值：
	// 函数说明：添加模块名
	// $_FUNCTION_END ****************************************************
	void AddModuleName(const std::string& astrModuleName, std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const;
	
	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：AddLog
	// 函数参数：apFormat			[输入]		日志记录的格式化字符串
	//			 argptr				[输入]		日志记录格式化参数
	//			 apConsoleInfo		[输入|输出]	控制台信息
	// 返 回 值：
	// 函数说明：添加日志记录
	// $_FUNCTION_END ****************************************************
	void AddLog(const char* apFormat, va_list& argptr, std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const;
	
	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：PrintToConsole
	// 函数参数：apConsoleInfo		[输入]		控制台信息
	// 返 回 值：
	// 函数说明：打印到控制台
	// $_FUNCTION_END ****************************************************
	void PrintToConsole(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const;

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：PrintToFile
	// 函数参数：
	// 返 回 值：调用是否成功
	// 函数说明：打印到文件
	// $_FUNCTION_END ****************************************************
	bool PrintToFile();

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：PrintFileStrategy
	// 函数参数：apConsoleInfo		[输入]		控制台信息
	// 返 回 值：
	// 函数说明：打印文件的策略
	// $_FUNCTION_END ****************************************************
	void PrintFileStrategy(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ChangeLog
	// 函数参数：
	// 返 回 值：
	// 函数说明：切换日志
	// $_FUNCTION_END *********************************************************
	void ChangeLog();

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：PrintContent
	// 函数参数：apContent			[输入]		日志记录的内容
	//			 apConsoleInfo		[输入|输出]	控制台信息
	// 返 回 值：
	// 函数说明：打印日志内容
	// $_FUNCTION_END ****************************************************
	void PrintContent(const char* apContent, std::shared_ptr<CAutoFreeBuffer> apConsoleInfo) const;

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：PrintParam
	// 函数参数：apConsoleInfo		[输入|输出]	控制台信息
	//			 param1				[输入]		参数1
	//			 params				[输入]		参数包
	// 返 回 值：
	// 函数说明：打印参数
	// $_FUNCTION_END ****************************************************
	template <typename Param1, typename ... Params>
	void PrintParam(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo, Param1 param1, Params&&... params) const;

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：PrintParam
	// 函数参数：apConsoleInfo		[输入|输出]	控制台信息
	//			 param				[输入]		参数
	// 返 回 值：
	// 函数说明：打印参数(作为递归的结束)
	// $_FUNCTION_END ****************************************************
	template <typename Param>
	void PrintParam(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo, Param&& param) const;

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：PrintKeyValueParam
	// 函数参数：apConsoleInfo		[输入|输出]	控制台信息
	//			 params				[输入]		参数包
	// 返 回 值：
	// 函数说明：打印KeyValue参数
	// $_FUNCTION_END ****************************************************
	template <typename ... Params>
	void PrintKeyValueParam(std::shared_ptr<CAutoFreeBuffer> apConsoleInfo, Params&&... params) const;

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：GetKeyValueParam
	// 函数参数：aOutput			[输入]		输出流
	//			 object				[输入]		参数
	//			 aiParamCount		[输入]		参数总个数
	//			 aiValueCount		[输入]		Value个数
	//			 abIsKey			[输入|输出]	是否为Key
	// 返 回 值：
	// 函数说明：获取KeyValue参数
	// $_FUNCTION_END ****************************************************
	template <typename Param>
	void GetKeyValueParam(std::ostringstream& aOutput, Param object, std::size_t aiParamCount, std::size_t& aiValueCount, bool& abIsKey) const;

private:
	// 锁
	std::mutex									m_Lock;
	// 日志配置
	STRUCT_LOG_CONFIG							m_LogConfig{};
	// 日志文件路径
	std::string									m_strLogFilePath = "";
	// 内存池
	CRecyclingObjectPool<CAutoFreeBuffer, void>	m_MemoryPool{};
	// 文件日志缓存
	CAutoFreeBuffer								m_FileLogBuff{};
	// 日志上次写入时间
	std::time_t									m_iLogWriteTime = 0;
	// 日志生成时间
	std::time_t									m_iCreateTime = 0;
	// 日志写入大小
	MyUInt64									m_iLogWriteSize = 0;
	// 日志缓存最大上限
	MyUInt32									m_iLogCacheMaxSize = 1024 * 100;
};

#include "Log.inl"

#endif