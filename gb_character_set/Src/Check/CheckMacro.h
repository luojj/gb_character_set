// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：CheckMacro.h
// 创建日期：2014-08-22
// 创建人：罗俊杰
// 文件说明：检测宏定义
// $_FILEHEADER_END ***********************************************************

#ifndef CHECK_MACRO_H
#define CHECK_MACRO_H

#include "TypeDef.h"
#include "Log/LogMacro.h"

#define CHECK_OBJECT_NO_RETURN(object, module_name, ...)														\
	if (object == nullptr)																						\
	{																											\
		LogSKV(Error, module_name, "object == nullptr!", "Func", __FUNCTION__, "Line", __LINE__, ##__VA_ARGS__);\
	}

#define CHECK_OBJECT_NO_RETURN_VALUE(object, module_name, ...)													\
	if (object == nullptr)																						\
	{																											\
		LogSKV(Error, module_name, "object == nullptr!", "Func", __FUNCTION__, "Line", __LINE__, ##__VA_ARGS__);\
		return;																									\
	}

#define CHECK_OBJECT_RETURN_VALUE(object, return_value, module_name, ...)										\
	if (object == nullptr)																						\
	{																											\
		LogSKV(Error, module_name, "object == nullptr!", "Func", __FUNCTION__, "Line", __LINE__, ##__VA_ARGS__);\
		return return_value;																					\
	}

#define CHECK_OBJECT_BREAK(object, module_name, ...)															\
	if (object == nullptr)																						\
	{																											\
		LogSKV(Error, module_name, "object == nullptr!", "Func", __FUNCTION__, "Line", __LINE__, ##__VA_ARGS__);\
		break;																									\
	}

#define CHECK_OBJECT_CONTINUE(object, module_name, ...)															\
	if (object == nullptr)																						\
	{																											\
		LogSKV(Error, module_name, "object == nullptr!", "Func", __FUNCTION__, "Line", __LINE__, ##__VA_ARGS__);\
		continue;																								\
	}

#define CHECK_OBJECT_AND_LEN_NO_RETURN_VALUE(object, len, module_name, ...)													\
	if (object == nullptr || len == 0)																						\
	{																														\
		LogSKV(Error, module_name, "object == nullptr || len == 0", "Func", __FUNCTION__, "Line", __LINE__, ##__VA_ARGS__);	\
		return;																												\
	}

#define CHECK_OBJECT_AND_LEN_RETURN_VALUE(object, len, return_value, module_name, ...)										\
	if (object == nullptr || len == 0)																						\
	{																														\
		LogSKV(Error, module_name, "object == nullptr || len == 0", "Func", __FUNCTION__, "Line", __LINE__, ##__VA_ARGS__);	\
		return return_value;																								\
	}

#define CHECK_OBJECT_AND_LEN_BREAK(object, len, module_name, ...)															\
	if (object == nullptr || len == 0)																						\
	{																														\
		LogSKV(Error, module_name, "object == nullptr || len == 0", "Func", __FUNCTION__, "Line", __LINE__, ##__VA_ARGS__);	\
		break;																												\
	}

#define CHECK_OBJECT_AND_LEN_CONTINUE(object, len, module_name, ...)														\
	if (object == nullptr || len == 0)																						\
	{																														\
		LogSKV(Error, module_name, "object == nullptr || len == 0", "Func", __FUNCTION__, "Line", __LINE__, ##__VA_ARGS__);	\
		continue;																											\
	}

#define CHECK_VALUE_NOT_EQUAL_NO_RETURN(value, expect_value, module_name, ...)																				\
	if (value != expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value not equal!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);	\
	}

#define CHECK_VALUE_NOT_EQUAL_NO_RETURN_VALUE(value, expect_value, module_name, ...)																		\
	if (value != expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value not equal!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);	\
		return;																																				\
	}

#define CHECK_VALUE_NOT_EQUAL_RETURN_VALUE(value, expect_value, return_value, module_name, ...)																\
	if (value != expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value not equal!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);	\
		return return_value;																																\
	}

#define CHECK_VALUE_NOT_EQUAL_BREAK(value, expect_value, module_name, ...)																					\
	if (value != expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value not equal!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);	\
		break;																																				\
	}

#define CHECK_VALUE_EQUAL_NO_RETURN_VALUE(value, expect_value, module_name, ...)																			\
	if (value == expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value equal!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);		\
		return;																																				\
	}

#define CHECK_VALUE_EQUAL_RETURN_VALUE(value, expect_value, return_value, module_name, ...)																	\
	if (value == expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value equal!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);		\
		return return_value;																																\
	}

#define CHECK_VALUE_EQUAL_BREAK(value, expect_value, module_name, ...)																						\
	if (value == expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value equal!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);		\
		break;																																				\
	}

#define CHECK_VALUE_EQUAL_CONTINUE(value, expect_value, module_name, ...)																					\
	if (value == expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value equal!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);		\
		continue;																																			\
	}

#define CHECK_VALUE_LESS_NO_RETURN_VALUE(value, expect_value, module_name, ...)																				\
	if (value < expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value too small!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);	\
		return;																																				\
	}

#define CHECK_VALUE_LESS_RETURN_VALUE(value, expect_value, return_value, module_name, ...)																	\
	if (value < expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value too small!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);	\
		return return_value;																																\
	}

#define CHECK_VALUE_LESS_BREAK(value, expect_value, module_name, ...)																						\
	if (value < expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value too small!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);	\
		break;																																				\
	}

#define CHECK_VALUE_LESS_EQUAL_NO_RETURN_VALUE(value, expect_value, module_name, ...)																		\
	if (value <= expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value too small!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);	\
		return;																																				\
	}

#define CHECK_VALUE_LESS_EQUAL_RETURN_VALUE(value, expect_value, return_value, module_name, ...)															\
	if (value <= expect_value)																																\
	{																																						\
		LogSKV(Error, module_name, "value too small!", "Func", __FUNCTION__, "Line", __LINE__, "Value", value, "ExpectValue", expect_value, ##__VA_ARGS__);	\
		return return_value;																																\
	}

#define CLOSE_FILE(file)	\
	if (file != nullptr)	\
	{						\
		fclose(file);		\
		file = nullptr;		\
	}

#endif