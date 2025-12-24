// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：ByteOrderUtils.h
// 创建日期：2020-05-25
// 创建人：罗俊杰
// 文件说明：字节序工具类
// $_FILEHEADER_END ***********************************************************

#ifndef BYTE_ORDER_UTILS_H
#define BYTE_ORDER_TUILS_H

#include <bitset>
#include <string.h>
#include "TypeDef.h"
#include "TypeTraits/sfinae_is_xxx.h"

enum class ENUM_SHIFT_TYPE : MyUInt16
{
	Default = 0,	// 默认,不移位
	Left = 1,		// 左移
	Right = 2,		// 右移
};

class CByteOrderUtils
{
public:
	CByteOrderUtils() = default;
	~CByteOrderUtils() = default;

public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：IsBigEndian
	// 函数参数：
	// 返 回 值：是否为大端字节序
	// 函数说明：是否为大端字节序
	// $_FUNCTION_END *********************************************************
	static bool IsBigEndian();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Store32
	// 函数参数：aiValue		[输入]			32位值
	//			 apArray		[输入]			字符数组
	//			 aiBitPos		[输入]			字符数组的开始位置
	//			 abBigEndian	[输入]			是否为大端字节序
	// 返 回 值：
	// 函数说明：将32位值保存到字符数组
	// $_FUNCTION_END *********************************************************
	static void Store32(MyUInt32 aiValue, MyUInt8* apArray, MyUInt32 aiBitPos, bool abBigEndian);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Load32
	// 函数参数：aiValue		[输入|输出]		32位值
	//			 apArray		[输入]			字符数组
	//			 aiBitPos		[输入]			字符数组的开始位置
	//			 abBigEndian	[输入]			是否为大端字节序
	// 返 回 值：
	// 函数说明：从字符数组加载32位值
	// $_FUNCTION_END *********************************************************
	static void Load32(MyUInt32& aiValue, const MyUInt8* apArray, MyUInt32 aiBitPos, bool abBigEndian);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Store64
	// 函数参数：aiValue		[输入]			32位值
	//			 apArray		[输入]			字符数组
	//			 aiBitPos		[输入]			字符数组的开始位置
	//			 abBigEndian	[输入]			是否为大端字节序
	// 返 回 值：
	// 函数说明：将64位值保存到字符数组
	// $_FUNCTION_END *********************************************************
	static void Store64(MyUInt64 aiValue, MyUInt8* apArray, MyUInt32 aiBitPos, bool abBigEndian);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Load64
	// 函数参数：aiValue		[输入|输出]		32位值
	//			 apArray		[输入]			字符数组
	//			 aiBitPos		[输入]			字符数组的开始位置
	//			 abBigEndian	[输入]			是否为大端字节序
	// 返 回 值：
	// 函数说明：从字符数组加载64位值
	// $_FUNCTION_END *********************************************************
	static void Load64(MyUInt64& aiValue, const MyUInt8* apArray, MyUInt32 aiBitPos, bool abBigEndian);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：ByteOrderTrans
	// 函数参数：aValue			[输入]			数值
	// 返 回 值：
	// 函数说明：字节序转换
	// $_FUNCTION_END ****************************************************
	template <typename T>
	static T ByteOrderTrans(T aValue);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：GetValue
	// 函数参数：aSrcValue		[输入]			源数值
	//			 aDstValue		[输入]			目标数值
	//			 aMask			[输入]			掩码
	//			 aType			[输入]			移位类型
	//			 aiShiftCount	[输入]			移几位
	// 返 回 值：数值
	// 函数说明：获取8位数值中的数据
	// $_FUNCTION_END ****************************************************
	template <typename Src, typename Dst>
	static Dst GetValue(Src aSrcValue, Dst aDstValue, const std::bitset<8>& aMask, ENUM_SHIFT_TYPE aType, MyUInt16 aiShiftCount);

	// $_FUNCTION_BEGIN **************************************************
	// 函数名称：GetValue
	// 函数参数：aValue			[输入]			数值
	//			 aMask			[输入]			掩码
	//			 aType			[输入]			移位类型
	//			 aiShiftCount	[输入]			移几位
	// 返 回 值：数值
	// 函数说明：获取16位数值中的数据
	// $_FUNCTION_END ****************************************************
	template <typename T>
	static T GetValue(T aValue, const std::bitset<16>& aMask, ENUM_SHIFT_TYPE aType, MyUInt16 aiShiftCount);
};

#include "ByteOrderUtils.inl"

#endif