// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：TypeDef.h
// 创建日期：2012-06-23
// 创建人：罗俊杰
// 文件说明：为平台重新定义基本数据类型
// $_FILEHEADER_END ***********************************************************

#ifndef TYPE_DEF_H
#define TYPE_DEF_H

#include <stdint.h>
typedef	int8_t				MyInt8;
typedef	uint8_t				MyUInt8;
typedef int16_t				MyInt16;
typedef uint16_t			MyUInt16;
typedef int32_t				MyInt32;
typedef uint32_t			MyUInt32;
typedef int64_t				MyInt64;
typedef uint64_t			MyUInt64;
typedef int32_t				MyLong32;
typedef uint32_t			MyULong32;
typedef int64_t				MyLong64;
typedef uint64_t			MyULong64;

// 定义LINUX宏
#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__) || defined(__GNUC__)
#define LINUX
#endif

// WIN32只判断32位平台
// _WIN32判断32位和64位平台
// _WIN64只判断64位平台
#if defined (_WIN32)
#include <BaseTsd.h>						// for UINT_PTR
#define INVALID_MY_SOCKET	(UINT_PTR)(~0)	// 无效的Socket
typedef UINT_PTR			MY_SOCKET_TYPE;	// Windows下Socket的类型

#elif defined (LINUX)
#define INVALID_MY_SOCKET	-1				// 无效的Socket
typedef int					MY_SOCKET_TYPE;	// Linux下Socket的类型

#endif

#endif	// TYPE_DEF_H