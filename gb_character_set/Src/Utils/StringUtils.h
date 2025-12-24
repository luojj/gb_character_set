// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：StringUtils.h
// 创建日期：2020-05-25
// 创建人：罗俊杰
// 文件说明：字符串工具类
// $_FILEHEADER_END ***********************************************************

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <tuple>
#include <vector>
#include <sstream>
#include <algorithm>
#include <charconv>
#include <iomanip>
#include "TypeDef.h"
#include "CommonMacro.h"
#include "TypeTraits/sfinae_is_xxx.h"
#include "Check/CheckMacro.h"

class CStringUtils
{
public:
	CStringUtils() = default;
	~CStringUtils() = default;

public:
	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：TrimLeft
	// 函数参数：astrValue			[输入|输出]		字符串
	//			 astrDelimiter		[输入]			分隔符
	// 返 回 值：
	// 函数说明：去除字符串首位的指定字符
	// $_FUNCTION_END ****************************************************
	static void TrimLeft(std::string& astrValue, const std::string& astrDelimiter = " ");

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：TrimRight
	// 函数参数：astrValue			[输入|输出]		字符串
	//			 astrDelimiter		[输入]			分隔符
	// 返 回 值：
	// 函数说明：去除字符串末位的指定字符
	// $_FUNCTION_END ****************************************************
	static void TrimRight(std::string& astrValue, const std::string& astrDelimiter = " ");

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：Trim
	// 函数参数：astrValue			[输入|输出]		字符串
	//			 astrDelimiter		[输入]			分隔符
	// 返 回 值：
	// 函数说明：去除字符串首末位指定字符
	// $_FUNCTION_END ****************************************************
	static void Trim(std::string& astrValue, const std::string& astrDelimiter = " ");

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：ToLower
	// 函数参数：astrValue			[输入|输出]		字符串
	// 返 回 值：
	// 函数说明：字符串转小写
	// $_FUNCTION_END ****************************************************
	static void ToLower(std::string& astrValue);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：ToUpper
	// 函数参数：astrValue			[输入|输出]		字符串
	// 返 回 值：
	// 函数说明：字符串转大写
	// $_FUNCTION_END ****************************************************
	static void ToUpper(std::string& astrValue);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：SplitString
	// 函数参数：astrValue			[输入]			要拆分的字符串
	//			 astrSplit			[输入]			拆分字符
	// 返 回 值：调用是否成功
	// 函数说明：按拆分字符拆分一个字符串
	// $_FUNCTION_END ****************************************************
	static std::tuple<bool, std::string, std::string> SplitString(const std::string& astrValue, const std::string& astrSplit);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：SplitString
	// 函数参数：astrValue			[输入]			要拆分的字符串
	//			 astrSplit			[输入]			拆分字符
	//			 aResult			[输入|输出]		结果
	// 返 回 值：调用是否成功
	// 函数说明：按拆分字符拆分一个字符串
	// $_FUNCTION_END ****************************************************
	static bool SplitString(const std::string& astrValue, const std::string& astrSplit, std::vector<std::string>& aResult);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：String2CharArray
	// 函数参数：astrValue			[输入]			源字符串
	//			 apValue			[输入|输出]		目标字符串
	//			 aiValueLen			[输入]			目标字符串长度
	// 返 回 值：
	// 函数说明：从string转char*
	// $_FUNCTION_END ****************************************************
	static void String2CharArray(const std::string& astrValue, char* apValue, MyUInt32 aiValueLen);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：CharArray2CharArray
	// 函数参数：apSrcValue			[输入]			源字符串
	//			 aiSrcValueLen		[输入]			源字符串长度
	//			 apDstValue			[输入|输出]		目标字符串
	//			 aiDstValueLen		[输入]			目标字符串长度
	// 返 回 值：
	// 函数说明：从char*转char*
	// $_FUNCTION_END ****************************************************
	static void CharArray2CharArray(const char* apSrcValue, MyUInt32 aiSrcValueLen, char* apDstValue, MyUInt32 aiDstValueLen);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：Replace
	// 函数参数：astrValue			[输入]			字符串
	//			 astrBefore			[输入]			要替换的字符
	//			 astrAfter			[输入]			新字符
	// 返 回 值：替换后的字符串
	// 函数说明：替换字符串
	// $_FUNCTION_END ****************************************************
	static std::string Replace(const std::string& astrValue, const std::string& astrBefore, const std::string& astrAfter);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：IsNumber
	// 函数参数：astrValue			[输入]			值
	// 返 回 值：是否为数字
	// 函数说明：是否为数字
	// $_FUNCTION_END ****************************************************
	static bool IsNumber(const std::string& astrValue);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：IsHaveSubString
	// 函数参数：astrValue			[输入]			值
	//			 astrSubValue		[输入]			子值
	// 返 回 值：是否存在子值
	// 函数说明：是否存在子值
	// $_FUNCTION_END ****************************************************
	static bool IsHaveSubString(const std::string& astrValue, const std::string& astrSubValue);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：String2Value
	// 函数参数：astrValue			[输入]			字符串
	//			 aValue				[输入|输出]		结果
	// 返 回 值：
	// 函数说明：从string转值
	// $_FUNCTION_END ****************************************************
	template <typename T>
	static void String2Value(const std::string& astrValue, T& aValue);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：String2Value
	// 函数参数：apValue			[输入]			字符串
	//			 aiValueLen			[输入]			字符串长度
	//			 aValue				[输入|输出]		结果
	//			 aBase				[输入]			进制
	//			 aFmt				[输入]			格式
	// 返 回 值：
	// 函数说明：从string转值
	// $_FUNCTION_END ****************************************************
	template <typename T>
	static void String2Value(const char* apValue, MyUInt32 aiValueLen, T& aValue, int aBase = 10, std::chars_format aFmt = std::chars_format::general);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：Value2String
	// 函数参数：aValue				[输入]			值
	// 返 回 值：字符串
	// 函数说明：从值转string
	// $_FUNCTION_END ****************************************************
	template <typename T>
	static std::string Value2String(const T& aValue);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：Value2String
	// 函数参数：apValue			[输入|输出]		结果,不保证有结束符
	//			 aiValueLen			[输入]			存放结果的大小
	//			 aValue				[输入]			值
	//			 aBase				[输入]			进制
	//			 aFmt				[输入]			格式
	//			 aPrecision			[输入]			小数点后几位
	// 返 回 值：
	// 函数说明：从值转string
	// $_FUNCTION_END ****************************************************
	template <typename T>
	static void Value2String(char* apValue, MyUInt32 aiValueLen, const T& aValue, int aBase = 10, std::chars_format aFmt = std::chars_format::general, int aPrecision = 3);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：Value2HexString
	// 函数参数：aValue				[输入]			值
	//			 abNeedHeader		[输入]			是否需要0x
	//			 abUpcase			[输入]			是否为大写
	// 返 回 值：16进制字符串
	// 函数说明：从值转16进制string
	// $_FUNCTION_END ****************************************************
	template <typename T>
	static std::string Value2HexString(const T& aValue, bool abNeedHeader = true, bool abUpcase = true);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：HexString2Value
	// 函数参数：astrValue			[输入]			字符串("0x11"->17或"11"->17)
	// 返 回 值：值
	// 函数说明：从16进制string转值
	// $_FUNCTION_END ****************************************************
	template <typename T>
	static T HexString2Value(const std::string& astrValue);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：BytesToHex
	// 函数参数：apData				[输入]			数据
	//			 aiDataLen			[输入]			数据长度
	//			 abUpcase			[输入]			是否为大写
	// 返 回 值：字符串
	// 函数说明：将字节数组转为16进制的文本
	// $_FUNCTION_END ****************************************************
	template <typename T>
	static std::string BytesToHex(const T* apData, MyUInt32 aiDataLen, bool abUpcase);
};

#include "StringUtils.inl"

#endif