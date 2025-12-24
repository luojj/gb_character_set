// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：LogConfig.h
// 创建日期：2012-07-06
// 创建人：罗俊杰
// 文件说明：日志配置
// $_FILEHEADER_END ***********************************************************

#ifndef LOG_CONFIG_H
#define LOG_CONFIG_H

#include <string>
#include <functional>
#include "TypeDef.h"

// 日志级别
enum class ENUM_LOG_LEVEL : MyUInt16
{
	Debug = 0,
	Info = 1,
	Warn = 2,
	Error = 3,
};

// 日志选项
enum class ENUM_LOG_OPTION : MyUInt16
{
	Timestamp = 1,			// 打印时间戳
	LogLevel = 2,			// 打印日志级别
	ThreadID = 4,			// 打印线程ID
	PrintToFile = 8,		// 打印到文件
	PrintToConsole = 16,	// 打印到控制台
};

// 日志切割方式
enum class ENUM_LOG_SLICING_TYPE : MyUInt16
{
	Time = 0,	// 按时间切割
	Size = 1,	// 按大小切割
};

// 日志配置
struct STRUCT_LOG_CONFIG
{
	// 进程名称
	std::string									m_strProcessName{};
	// 日志级别
	ENUM_LOG_LEVEL								m_LogLevel = ENUM_LOG_LEVEL::Info;
	// 日志选项,见ENUM_LOG_OPTION
	MyUInt16									m_iLogOption = 0;
	// 日志切割方式
	ENUM_LOG_SLICING_TYPE						m_iLogSlicingType = ENUM_LOG_SLICING_TYPE::Time;
	// 日志切割参数
	// 按时间切割的话,单位为小时
	// 按大小切割的话,单位为K
	MyUInt64									m_iLogSlicingParam = 0;
	// 每次提交到硬盘前的日志缓存大小,单位为K
	MyUInt32									m_iLogCacheSize = 1024 * 10;
	// 是否以进程的方式启动
	// true:按进程方式启动
	// false:按服务方式启动
	bool										m_bByProcess = true;
	// 支持将日志输出给外层,以便输出到其它地方
	std::function<void(const char*, MyUInt32)>	m_OutputFunc = nullptr;
};

#endif