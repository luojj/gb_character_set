// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：LogExtend.h
// 创建日期：2024-03-22
// 创建人：罗俊杰
// 文件说明：日志扩展类
// $_FILEHEADER_END ***********************************************************

#ifndef LOG_EXTEND_H
#define LOG_EXTEND_H

#include <source_location>
#include <format>
#include "Log.h"
#include "Single/Single.h"

namespace log_extend
{

	auto func_format = [](const std::source_location& aLocation)->decltype(auto) {
		return std::format("Func:{}, Line:{}, Column:{}", aLocation.function_name(), aLocation.line(), aLocation.column());
	};

	template <typename ModuleName, typename ...Params>
	struct LogSD
	{
		LogSD(ModuleName aModuleName, Params&&... aParams, const std::source_location& aLocation = std::source_location::current())
		{
			CSingle<CLog>::GetInstance().StreamLog(ENUM_LOG_LEVEL::Debug, aModuleName, func_format(aLocation), std::forward<Params>(aParams)...);
		}
	};
	template <typename ModuleName, typename ...Params>
	LogSD(ModuleName, Params...) -> LogSD<ModuleName, Params...>;

	template <typename ModuleName, typename ...Params>
	struct LogSI
	{
		LogSI(ModuleName aModuleName, Params&&... aParams, const std::source_location& aLocation = std::source_location::current())
		{
			CSingle<CLog>::GetInstance().StreamLog(ENUM_LOG_LEVEL::Info, aModuleName, func_format(aLocation), std::forward<Params>(aParams)...);
		}
	};
	template <typename ModuleName, typename ...Params>
	LogSI(ModuleName, Params...) -> LogSI<ModuleName, Params...>;

	template <typename ModuleName, typename ...Params>
	struct LogSW
	{
		LogSW(ModuleName aModuleName, Params&&... aParams, const std::source_location& aLocation = std::source_location::current())
		{
			CSingle<CLog>::GetInstance().StreamLog(ENUM_LOG_LEVEL::Warn, aModuleName, func_format(aLocation), std::forward<Params>(aParams)...);
		}
	};
	template <typename ModuleName, typename ...Params>
	LogSW(ModuleName, Params...) -> LogSW<ModuleName, Params...>;

	template <typename ModuleName, typename ...Params>
	struct LogSE
	{
		LogSE(ModuleName aModuleName, Params&&... aParams, const std::source_location& aLocation = std::source_location::current())
		{
			CSingle<CLog>::GetInstance().StreamLog(ENUM_LOG_LEVEL::Error, aModuleName, func_format(aLocation), std::forward<Params>(aParams)...);
		}
	};
	template <typename ModuleName, typename ...Params>
	LogSE(ModuleName, Params...) -> LogSE<ModuleName, Params...>;

	template <typename ModuleName, typename Content, typename ...Params>
	struct LogSKVD
	{
		LogSKVD(ModuleName aModuleName, Content aContent, Params&&... aParams, const std::source_location& aLocation = std::source_location::current())
		{
			CSingle<CLog>::GetInstance().StreamKeyValueLog(ENUM_LOG_LEVEL::Debug, aModuleName, aContent, "Func", aLocation.function_name(), "Line", aLocation.line(), "Column", aLocation.column(), std::forward<Params>(aParams)...);
		}
	};
	template <typename ModuleName, typename Content, typename ...Params>
	LogSKVD(ModuleName, Content, Params...) -> LogSKVD<ModuleName, Content, Params...>;

	template <typename ModuleName, typename Content, typename ...Params>
	struct LogSKVI
	{
		LogSKVI(ModuleName aModuleName, Content aContent, Params&&... aParams, const std::source_location& aLocation = std::source_location::current())
		{
			CSingle<CLog>::GetInstance().StreamKeyValueLog(ENUM_LOG_LEVEL::Info, aModuleName, aContent, "Func", aLocation.function_name(), "Line", aLocation.line(), "Column", aLocation.column(), std::forward<Params>(aParams)...);
		}
	};
	template <typename ModuleName, typename Content, typename ...Params>
	LogSKVI(ModuleName, Content, Params...) -> LogSKVI<ModuleName, Content, Params...>;

	template <typename ModuleName, typename Content, typename ...Params>
	struct LogSKVW
	{
		LogSKVW(ModuleName aModuleName, Content aContent, Params&&... aParams, const std::source_location& aLocation = std::source_location::current())
		{
			CSingle<CLog>::GetInstance().StreamKeyValueLog(ENUM_LOG_LEVEL::Warn, aModuleName, aContent, "Func", aLocation.function_name(), "Line", aLocation.line(), "Column", aLocation.column(), std::forward<Params>(aParams)...);
		}
	};
	template <typename ModuleName, typename Content, typename ...Params>
	LogSKVW(ModuleName, Content, Params...) -> LogSKVW<ModuleName, Content, Params...>;

	template <typename ModuleName, typename Content, typename ...Params>
	struct LogSKVE
	{
		LogSKVE(ModuleName aModuleName, Content aContent, Params&&... aParams, const std::source_location& aLocation = std::source_location::current())
		{
			CSingle<CLog>::GetInstance().StreamKeyValueLog(ENUM_LOG_LEVEL::Error, aModuleName, aContent, "Func", aLocation.function_name(), "Line", aLocation.line(), "Column", aLocation.column(), std::forward<Params>(aParams)...);
		}
	};
	template <typename ModuleName, typename Content, typename ...Params>
	LogSKVE(ModuleName, Content, Params...) -> LogSKVE<ModuleName, Content, Params...>;

}

#endif