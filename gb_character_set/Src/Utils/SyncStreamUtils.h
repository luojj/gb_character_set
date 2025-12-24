// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：SyncStreamUtils.h
// 创建日期：2024-04-03
// 创建人：罗俊杰
// 文件说明：同步流工具类,保证写入std::cout的streambuf时数据的同步
// $_FILEHEADER_END ***********************************************************

#ifndef SYNC_STREAM_UTILS_H
#define SYNC_STREAM_UTILS_H

#include <iostream>
#include <syncstream>

class CSyncStreamUtils
{
public:
	template <typename T>
	std::osyncstream operator <<(const T& value) const;
};

#include "SyncStreamUtils.inl"

#endif