// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：AutoFreeBuffer.h
// 创建日期：2014-08-22
// 创建人：罗俊杰
// 文件说明：自动释放缓存,以内存形式存储数据,如果要存放字符串,需要在Resize时将字符结束符计算在内
// 否则向GetMultiData和GetWideData返回的缓存做字符串操作时(如strcpy)会出错
// 另外尽量用strncpy等带长度的操作,不要用strcpy等操作
// $_FILEHEADER_END ***********************************************************

#ifndef AUTO_FREE_BUFFER_H
#define AUTO_FREE_BUFFER_H

#include <string>
#include "TypeDef.h"

// 自动释放缓存类型
enum class ENUM_AUTO_FREE_BUFFER_TYPE : MyUInt16
{
	Default = 0,	// 默认
	Multi_Char = 1,	// 多字节
	Wide_Char = 2,	// 宽字节
};

class CAutoFreeBuffer
{
public:
	CAutoFreeBuffer();
	CAutoFreeBuffer(MyUInt32 aiDefaultSize, MyUInt32 aiMallocSize);
	CAutoFreeBuffer(const CAutoFreeBuffer& aAutoFreeBuffer);
	CAutoFreeBuffer(CAutoFreeBuffer&& aAutoFreeBuffer) noexcept;
	CAutoFreeBuffer& operator=(const CAutoFreeBuffer& aAutoFreeBuffer);
	CAutoFreeBuffer& operator=(CAutoFreeBuffer&& aAutoFreeBuffer) noexcept;
	~CAutoFreeBuffer();

	CAutoFreeBuffer& operator+=(const CAutoFreeBuffer& astrData);

	CAutoFreeBuffer& operator+=(char acData);
	CAutoFreeBuffer& operator+=(const char* apData);
	CAutoFreeBuffer& operator+=(const std::string& astrData);

	CAutoFreeBuffer& operator+=(wchar_t acData);
	CAutoFreeBuffer& operator+=(const wchar_t* apData);
	CAutoFreeBuffer& operator+=(const std::wstring& astrData);

public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Resize
	// 函数参数：aiSize					[输入]	数据大小,注:这里的大小指的是数据个数,不是内存大小
	//			 aAutoFreeBufferType	[输入]	自动释放缓存类型
	// 返 回 值：调用是否成功
	// 函数说明：调整大小,会根据传入的数据大小计算内存大小,如果现有缓存过小,会重新分配,并清除现有缓存内的内容
	// $_FUNCTION_END *********************************************************
	bool Resize(MyUInt32 aiSize, ENUM_AUTO_FREE_BUFFER_TYPE aAutoFreeBufferType = ENUM_AUTO_FREE_BUFFER_TYPE::Multi_Char);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Reserve
	// 函数参数：aiSize					[输入]	数据大小,注:这里的大小指的是数据个数,不是内存大小
	//			 aAutoFreeBufferType	[输入]	自动释放缓存类型
	// 返 回 值：调用是否成功
	// 函数说明：预留大小,会根据传入的数据大小计算内存大小,如果现有缓存过小,会重新分配,但不清除现有缓存内的内容
	// $_FUNCTION_END *********************************************************
	bool Reserve(MyUInt32 aiSize, ENUM_AUTO_FREE_BUFFER_TYPE aAutoFreeBufferType = ENUM_AUTO_FREE_BUFFER_TYPE::Multi_Char);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：AppendDataBuffer
	// 函数参数：apData					[输入]	要追加到缓存中的数据
	//			 aiDataLen				[输入]	要追加到缓存中的数据长度,注:这里的长度指的是内存大小,不是数据个数
	// 返 回 值：调用是否成功
	// 函数说明：向缓存中追加数据,如果缓存没有分配空间会自动分配,如果现有缓存过小,会重新分配
	// $_FUNCTION_END *********************************************************
	bool AppendDataBuffer(const char* apData, MyUInt32 aiDataLen);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：AppendDataBuffer
	// 函数参数：apData					[输入]	要追加到缓存中的数据
	//			 aiDataLen				[输入]	要追加到缓存中的数据长度,注:这里的长度指的是内存大小,不是数据个数
	// 返 回 值：调用是否成功
	// 函数说明：向缓存中追加数据,如果缓存没有分配空间会自动分配,如果现有缓存过小,会重新分配
	// $_FUNCTION_END *********************************************************
	bool AppendDataBuffer(const wchar_t* apData, MyUInt32 aiDataLen);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：RemoveDataBuffer
	// 函数参数：aiDataLen				[输入]	要移动的缓存长度,注:这里的长度指的是内存大小,不是数据个数
	//			 aAutoFreeBufferType	[输入]	自动释放缓存类型
	// 返 回 值：
	// 函数说明：将缓存向前移动
	// $_FUNCTION_END *********************************************************
	void RemoveDataBuffer(MyUInt32 aiDataLen, ENUM_AUTO_FREE_BUFFER_TYPE aAutoFreeBufferType = ENUM_AUTO_FREE_BUFFER_TYPE::Multi_Char);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetMultiData
	// 函数参数：
	// 返 回 值：多字节缓存
	// 函数说明：获取多字节缓存
	// $_FUNCTION_END *********************************************************
	auto GetMultiData() { return m_pMultiDataBuffer; };

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetMultiDataBufferLen
	// 函数参数：
	// 返 回 值：多字节缓存大小
	// 函数说明：获取多字节缓存大小
	// $_FUNCTION_END *********************************************************
	auto GetMultiDataBufferLen() const { return m_iMultiDataBufferLen; };

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetMultiDataLen
	// 函数参数：
	// 返 回 值：多字节数据长度
	// 函数说明：获取多字节数据长度
	// $_FUNCTION_END *********************************************************
	auto GetMultiDataLen() const { return m_iMultiDataLen; };

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：MultiDataEmpty
	// 函数参数：
	// 返 回 值：多字节数据是否为空
	// 函数说明：多字节数据是否为空
	// $_FUNCTION_END *********************************************************
	auto MultiDataEmpty() const { return (m_iMultiDataLen == 0 ? true : false); };

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ToString
	// 函数参数：
	// 返 回 值：std::string
	// 函数说明：转为std::string
	// $_FUNCTION_END *********************************************************
	std::string ToString() const;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetWideData
	// 函数参数：
	// 返 回 值：宽字节缓存
	// 函数说明：获取宽字节缓存
	// $_FUNCTION_END *********************************************************
	auto GetWideData() { return m_pWideDataBuffer; };

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetWideDataBufferLen
	// 函数参数：
	// 返 回 值：宽字节缓存大小
	// 函数说明：获取宽字节缓存大小
	// $_FUNCTION_END *********************************************************
	auto GetWideDataBufferLen() const { return m_iWideDataBufferLen; };

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetWideDataLen
	// 函数参数：
	// 返 回 值：宽字节数据长度
	// 函数说明：获取宽字节数据长度
	// $_FUNCTION_END *********************************************************
	auto GetWideDataLen() const { return m_iWideDataLen; };

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：WideDataEmpty
	// 函数参数：
	// 返 回 值：宽字节数据是否为空
	// 函数说明：宽字节数据是否为空
	// $_FUNCTION_END *********************************************************
	auto WideDataEmpty() const { return (m_iWideDataLen == 0 ? true : false); };

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ToWString
	// 函数参数：
	// 返 回 值：std::wstring
	// 函数说明：转为std::wstring
	// $_FUNCTION_END *********************************************************
	std::wstring ToWString() const;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Clear
	// 函数参数：
	// 返 回 值：
	// 函数说明：清除本地缓存
	// $_FUNCTION_END *********************************************************
	void Clear();

private:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：MultiDataAllocate
	// 函数参数：aiSize					[输入]	数据大小,注:这里的大小指的是数据个数,不是内存大小
	//			 abSaveData				[输入]	是否保存数据
	// 返 回 值：调用是否成功
	// 函数说明：多字节分配
	// $_FUNCTION_END *********************************************************
	bool MultiDataAllocate(MyUInt32 aiSize, bool abSaveData);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：WideDataAllocate
	// 函数参数：aiSize					[输入]	数据大小,注:这里的大小指的是数据个数,不是内存大小
	//			 abSaveData				[输入]	是否保存数据
	// 返 回 值：调用是否成功
	// 函数说明：宽字节分配
	// $_FUNCTION_END *********************************************************
	bool WideDataAllocate(MyUInt32 aiSize, bool abSaveData);

private:
	// 多字节缓存
	char*		m_pMultiDataBuffer = nullptr;
	// 多字节缓存大小
	MyUInt32	m_iMultiDataBufferLen = 0;
	// 多字节数据大小,即strlen的大小
	MyUInt32	m_iMultiDataLen = 0;
	// 宽字节缓存
	wchar_t*	m_pWideDataBuffer = nullptr;
	// 宽字节缓存大小
	MyUInt32	m_iWideDataBufferLen = 0;
	// 宽字节数据大小,即wcslen的大小
	MyUInt32	m_iWideDataLen = 0;
	// 默认大小
	MyUInt32	m_iDefaultSize = 0;
	// 内存分配分界大小
	MyUInt32	m_iMallocSize = 0;
};

#endif