// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：LogMacro.h
// 创建日期：2012-07-06
// 创建人：罗俊杰
// 文件说明：日志宏
// $_FILEHEADER_END ***********************************************************

#ifndef LOG_MACRO_H
#define LOG_MACRO_H

#include "Log.h"
#include "Single/Single.h"

// 格式化日志
// 日志方式:
// LogF(Info, "Test", "Test1:%d, Test2:%s", 100, "aaa")
// 输出:
// [2012-07-06 10:00:00][Info][1234][Test][Test1:100, Test2:aaa]
#define LogF(level, module_name, content, ...) (CSingle<CLog>::GetInstance().FormatLog(ENUM_LOG_LEVEL::level, module_name, content, ##__VA_ARGS__))

// 流式日志
// 日志方式:
// LogS(Info, "Test", "List", 100, "aaa", 0.111)
// 输出:
// [2012-07-06 10:00:00][Info][1234][Test][List, 100, aaa, 0.111]
#define LogS(level, module_name, ...) (CSingle<CLog>::GetInstance().StreamLog(ENUM_LOG_LEVEL::level, module_name, ##__VA_ARGS__))

// 流式Key-Value日志
// 日志方式:
// LogSKV(Info, "Test", "Log!", "Test1:", 100, "Test2:", "aaa")
// 输出:
// [2012-07-06 10:00:00][Info][1234][Test][Log!][Test1:100, Test2:0.111]
#define LogSKV(level, module_name, content, ...) (CSingle<CLog>::GetInstance().StreamKeyValueLog(ENUM_LOG_LEVEL::level, module_name, content, ##__VA_ARGS__))

#endif