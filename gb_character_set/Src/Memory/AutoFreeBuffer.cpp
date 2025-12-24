#include <stdlib.h>
#include <string.h>
#include "CommonMacro.h"
#include "Memory/AutoFreeBuffer.h"
#include "Check/CheckMacro.h"

// 默认大小
constexpr MyUInt32 DEF_AUTO_FREE_BUFFER_DEFAULT_SIZE = 32;
// 内存分配分界大小
constexpr MyUInt32 DEF_AUTO_FREE_BUFFER_MALLOC_SIZE = 512;
////////////////////////////////////////////////////////////////////////////////////////////////////
CAutoFreeBuffer::CAutoFreeBuffer()
{
	m_iDefaultSize = DEF_AUTO_FREE_BUFFER_DEFAULT_SIZE;
	m_iMallocSize = DEF_AUTO_FREE_BUFFER_MALLOC_SIZE;
}

CAutoFreeBuffer::CAutoFreeBuffer(MyUInt32 aiDefaultSize, MyUInt32 aiMallocSize)
{
	m_iDefaultSize = aiDefaultSize;
	m_iMallocSize = aiMallocSize;
}

CAutoFreeBuffer::CAutoFreeBuffer(const CAutoFreeBuffer& aAutoFreeBuffer)
{
	Clear();
	if (aAutoFreeBuffer.m_pMultiDataBuffer != nullptr && aAutoFreeBuffer.m_iMultiDataBufferLen != 0)
	{
		m_pMultiDataBuffer = (char*)malloc(aAutoFreeBuffer.m_iMultiDataBufferLen);
		if (m_pMultiDataBuffer != nullptr)
		{
			memcpy(m_pMultiDataBuffer, aAutoFreeBuffer.m_pMultiDataBuffer, aAutoFreeBuffer.m_iMultiDataBufferLen);
			m_iMultiDataBufferLen = aAutoFreeBuffer.m_iMultiDataBufferLen;
			m_iMultiDataLen = aAutoFreeBuffer.m_iMultiDataLen;
		}
	}
	if (aAutoFreeBuffer.m_pWideDataBuffer != nullptr && aAutoFreeBuffer.m_iWideDataBufferLen != 0)
	{
		m_pWideDataBuffer = (wchar_t*)malloc(aAutoFreeBuffer.m_iWideDataBufferLen);
		if (m_pWideDataBuffer != nullptr)
		{
			memcpy(m_pWideDataBuffer, aAutoFreeBuffer.m_pWideDataBuffer, aAutoFreeBuffer.m_iWideDataBufferLen);
			m_iWideDataBufferLen = aAutoFreeBuffer.m_iWideDataBufferLen;
			m_iWideDataLen = aAutoFreeBuffer.m_iWideDataLen;
		}
	}
	m_iDefaultSize = aAutoFreeBuffer.m_iDefaultSize;
	m_iMallocSize = aAutoFreeBuffer.m_iMallocSize;
}

CAutoFreeBuffer::CAutoFreeBuffer(CAutoFreeBuffer&& aAutoFreeBuffer) noexcept
{
	Clear();

	m_pMultiDataBuffer = aAutoFreeBuffer.m_pMultiDataBuffer;
	m_iMultiDataBufferLen = aAutoFreeBuffer.m_iMultiDataBufferLen;
	m_iMultiDataLen = aAutoFreeBuffer.m_iMultiDataLen;

	m_pWideDataBuffer = aAutoFreeBuffer.m_pWideDataBuffer;
	m_iWideDataBufferLen = aAutoFreeBuffer.m_iWideDataBufferLen;
	m_iWideDataLen = aAutoFreeBuffer.m_iWideDataLen;

	m_iDefaultSize = aAutoFreeBuffer.m_iDefaultSize;
	m_iMallocSize = aAutoFreeBuffer.m_iMallocSize;

	aAutoFreeBuffer.m_pMultiDataBuffer = nullptr;
	aAutoFreeBuffer.m_iMultiDataBufferLen = 0;
	aAutoFreeBuffer.m_iMultiDataLen = 0;

	aAutoFreeBuffer.m_pWideDataBuffer = nullptr;
	aAutoFreeBuffer.m_iWideDataBufferLen = 0;
	aAutoFreeBuffer.m_iWideDataLen = 0;
}

CAutoFreeBuffer& CAutoFreeBuffer::operator=(const CAutoFreeBuffer& aAutoFreeBuffer)
{
	if (this != &aAutoFreeBuffer)
	{
		Clear();
		if (aAutoFreeBuffer.m_pMultiDataBuffer != nullptr && aAutoFreeBuffer.m_iMultiDataBufferLen != 0)
		{
			m_pMultiDataBuffer = (char*)malloc(aAutoFreeBuffer.m_iMultiDataBufferLen);
			if (m_pMultiDataBuffer != nullptr)
			{
				memcpy(m_pMultiDataBuffer, aAutoFreeBuffer.m_pMultiDataBuffer, aAutoFreeBuffer.m_iMultiDataBufferLen);
				m_iMultiDataBufferLen = aAutoFreeBuffer.m_iMultiDataBufferLen;
				m_iMultiDataLen = aAutoFreeBuffer.m_iMultiDataLen;
			}
		}
		if (aAutoFreeBuffer.m_pWideDataBuffer != nullptr && aAutoFreeBuffer.m_iWideDataBufferLen != 0)
		{
			m_pWideDataBuffer = (wchar_t*)malloc(aAutoFreeBuffer.m_iWideDataBufferLen);
			if (m_pWideDataBuffer != nullptr)
			{
				memcpy(m_pWideDataBuffer, aAutoFreeBuffer.m_pWideDataBuffer, aAutoFreeBuffer.m_iWideDataBufferLen);
				m_iWideDataBufferLen = aAutoFreeBuffer.m_iWideDataBufferLen;
				m_iWideDataLen = aAutoFreeBuffer.m_iWideDataLen;
			}
		}
		m_iDefaultSize = aAutoFreeBuffer.m_iDefaultSize;
		m_iMallocSize = aAutoFreeBuffer.m_iMallocSize;
	}
	return *this;
}

CAutoFreeBuffer& CAutoFreeBuffer::operator=(CAutoFreeBuffer&& aAutoFreeBuffer) noexcept
{
	if (this != &aAutoFreeBuffer)
	{
		Clear();

		m_pMultiDataBuffer = aAutoFreeBuffer.m_pMultiDataBuffer;
		m_iMultiDataBufferLen = aAutoFreeBuffer.m_iMultiDataBufferLen;
		m_iMultiDataLen = aAutoFreeBuffer.m_iMultiDataLen;

		m_pWideDataBuffer = aAutoFreeBuffer.m_pWideDataBuffer;
		m_iWideDataBufferLen = aAutoFreeBuffer.m_iWideDataBufferLen;
		m_iWideDataLen = aAutoFreeBuffer.m_iWideDataLen;

		m_iDefaultSize = aAutoFreeBuffer.m_iDefaultSize;
		m_iMallocSize = aAutoFreeBuffer.m_iMallocSize;

		aAutoFreeBuffer.m_pMultiDataBuffer = nullptr;
		aAutoFreeBuffer.m_iMultiDataBufferLen = 0;
		aAutoFreeBuffer.m_iMultiDataLen = 0;

		aAutoFreeBuffer.m_pWideDataBuffer = nullptr;
		aAutoFreeBuffer.m_iWideDataBufferLen = 0;
		aAutoFreeBuffer.m_iWideDataLen = 0;
	}
	return *this;
}

CAutoFreeBuffer::~CAutoFreeBuffer()
{
	Clear();
}

CAutoFreeBuffer& CAutoFreeBuffer::operator+=(const CAutoFreeBuffer& astrData)
{
	if (!astrData.MultiDataEmpty())
		AppendDataBuffer(astrData.m_pMultiDataBuffer, astrData.m_iMultiDataLen);
	if (!astrData.WideDataEmpty())
		AppendDataBuffer(astrData.m_pWideDataBuffer, astrData.m_iWideDataLen);
	return *this;
}

CAutoFreeBuffer& CAutoFreeBuffer::operator+=(char acData)
{
	AppendDataBuffer(&acData, 1 * sizeof(char));
	return *this;
}

CAutoFreeBuffer& CAutoFreeBuffer::operator+=(const char* apData)
{
	if (apData != nullptr && strlen(apData) != 0)
		AppendDataBuffer(apData, (MyUInt32)strlen(apData) * sizeof(char));
	return *this;
}

CAutoFreeBuffer& CAutoFreeBuffer::operator+=(const std::string& astrData)
{
	if (!astrData.empty())
		AppendDataBuffer(astrData.c_str(), (MyUInt32)astrData.length() * sizeof(char));
	return *this;
}

CAutoFreeBuffer& CAutoFreeBuffer::operator+=(wchar_t acData)
{
	AppendDataBuffer(&acData, 1 * sizeof(wchar_t));
	return *this;
}

CAutoFreeBuffer& CAutoFreeBuffer::operator+=(const wchar_t* apData)
{
	if (apData != nullptr && wcslen(apData) != 0)
		AppendDataBuffer(apData, (MyUInt32)wcslen(apData) * sizeof(wchar_t));
	return *this;
}

CAutoFreeBuffer& CAutoFreeBuffer::operator+=(const std::wstring& astrData)
{
	if (!astrData.empty())
		AppendDataBuffer(astrData.c_str(), (MyUInt32)astrData.length() * sizeof(wchar_t));
	return *this;
}

// 调整大小,会根据传入的数据大小计算内存大小,如果现有缓存过小,会重新分配,并清除现有缓存内的内容
bool CAutoFreeBuffer::Resize(MyUInt32 aiSize, ENUM_AUTO_FREE_BUFFER_TYPE aAutoFreeBufferType)
{
	if (aAutoFreeBufferType == ENUM_AUTO_FREE_BUFFER_TYPE::Multi_Char)		// 多字节
	{
		if (!MultiDataAllocate(aiSize, false))
			return false;
	}
	else if (aAutoFreeBufferType == ENUM_AUTO_FREE_BUFFER_TYPE::Wide_Char)	// 宽字节
	{
		if (!WideDataAllocate(aiSize, false))
			return false;
	}
	return true;
}

// 预留大小,会根据传入的数据大小计算内存大小,如果现有缓存过小,会重新分配,但不清除现有缓存内的内容
bool CAutoFreeBuffer::Reserve(MyUInt32 aiSize, ENUM_AUTO_FREE_BUFFER_TYPE aAutoFreeBufferType)
{
	if (aAutoFreeBufferType == ENUM_AUTO_FREE_BUFFER_TYPE::Multi_Char)		// 多字节
	{
		if (!MultiDataAllocate(aiSize, true))
			return false;
	}
	else if (aAutoFreeBufferType == ENUM_AUTO_FREE_BUFFER_TYPE::Wide_Char)	// 宽字节
	{
		if (!WideDataAllocate(aiSize, true))
			return false;
	}
	return true;
}

// 向缓存中追加数据,如果缓存没有分配空间会自动分配,如果现有缓存过小,会重新分配
bool CAutoFreeBuffer::AppendDataBuffer(const char* apData, MyUInt32 aiDataLen)
{
	CHECK_OBJECT_RETURN_VALUE(apData, false, MemoryMod_Buffer);
	if (aiDataLen == 0)
		return true;
	// 重新分配大小
	if (m_iMultiDataLen + aiDataLen > m_iMultiDataBufferLen)
	{
		if (!Reserve((m_iMultiDataLen + aiDataLen) / sizeof(char), ENUM_AUTO_FREE_BUFFER_TYPE::Multi_Char))
			return false;
	}
	// 向后追加数据
	if (m_pMultiDataBuffer != nullptr)
	{
		memcpy(m_pMultiDataBuffer + m_iMultiDataLen, apData, aiDataLen);
		m_iMultiDataLen += aiDataLen;
	}
	return true;
}

// 向缓存中追加数据,如果缓存没有分配空间会自动分配,如果现有缓存过小,会重新分配
bool CAutoFreeBuffer::AppendDataBuffer(const wchar_t* apData, MyUInt32 aiDataLen)
{
	CHECK_OBJECT_RETURN_VALUE(apData, false, MemoryMod_Buffer);
	if (aiDataLen == 0)
		return true;
	// 重新分配大小
	if (m_iWideDataLen + aiDataLen > m_iWideDataBufferLen)
	{
		if (!Reserve((m_iWideDataLen + aiDataLen) / sizeof(wchar_t), ENUM_AUTO_FREE_BUFFER_TYPE::Wide_Char))
			return false;
	}
	// 向后追加数据
	if (m_pWideDataBuffer != nullptr)
	{
		memcpy(m_pWideDataBuffer + m_iWideDataLen, apData, aiDataLen);
		m_iWideDataLen += aiDataLen;
	}
	return true;
}

// 将缓存向前移动
void CAutoFreeBuffer::RemoveDataBuffer(MyUInt32 aiDataLen, ENUM_AUTO_FREE_BUFFER_TYPE aAutoFreeBufferType)
{
	if (aiDataLen == 0)
		return;
	if (aAutoFreeBufferType == ENUM_AUTO_FREE_BUFFER_TYPE::Multi_Char)
	{
		CHECK_OBJECT_NO_RETURN_VALUE(m_pMultiDataBuffer, MemoryMod_Buffer);
		// 将缓存向前移动
		MyUInt32 iMoveLen = m_iMultiDataLen - aiDataLen;
		memmove(m_pMultiDataBuffer, m_pMultiDataBuffer + aiDataLen, iMoveLen);
		// 调整缓存数据大小
		m_iMultiDataLen = m_iMultiDataLen - aiDataLen;
	}
	else if (aAutoFreeBufferType == ENUM_AUTO_FREE_BUFFER_TYPE::Wide_Char)
	{
		CHECK_OBJECT_NO_RETURN_VALUE(m_pWideDataBuffer, MemoryMod_Buffer);
		// 将缓存向前移动
		MyUInt32 iMoveLen = m_iWideDataLen - aiDataLen;
		memmove(m_pWideDataBuffer, m_pWideDataBuffer + aiDataLen, iMoveLen);
		// 调整缓存数据大小
		m_iWideDataLen = m_iWideDataLen - aiDataLen;
	}
}

// 转为std::string
std::string CAutoFreeBuffer::ToString() const
{
	if (MultiDataEmpty())
		return std::string{};

	std::string strContent;
	strContent.append(m_pMultiDataBuffer, m_iMultiDataLen);
	return strContent;
}

// 转为std::wstring
std::wstring CAutoFreeBuffer::ToWString() const
{
	if (WideDataEmpty())
		return std::wstring{};

	std::wstring strContent;
	strContent.append(m_pWideDataBuffer, m_iWideDataLen);
	return strContent;
}

// 清除本地缓存
void CAutoFreeBuffer::Clear()
{
	if (m_pMultiDataBuffer != nullptr)
	{
		free((void*)m_pMultiDataBuffer);
		m_pMultiDataBuffer = nullptr;
	}
	m_iMultiDataBufferLen = 0;
	m_iMultiDataLen = 0;

	if (m_pWideDataBuffer != nullptr)
	{
		free((void*)m_pWideDataBuffer);
		m_pWideDataBuffer = nullptr;
	}
	m_iWideDataBufferLen = 0;
	m_iWideDataLen = 0;
}

// 多字节分配
bool CAutoFreeBuffer::MultiDataAllocate(MyUInt32 aiSize, bool abSaveData)
{
	MyUInt32 iOldLen = m_iMultiDataLen;
	if (aiSize * sizeof(char) > m_iMultiDataBufferLen)	// 重新分配大小
	{
		if (m_pMultiDataBuffer == nullptr)	// 从未分配过
		{
			if (aiSize * sizeof(char) > m_iDefaultSize * sizeof(char))
			{
				m_iMultiDataBufferLen = aiSize * sizeof(char);
				m_pMultiDataBuffer = (char*)malloc(m_iMultiDataBufferLen);
				CHECK_OBJECT_RETURN_VALUE(m_pMultiDataBuffer, false, MemoryMod_Buffer);
			}
			else
			{
				m_iMultiDataBufferLen = m_iDefaultSize * sizeof(char);
				m_pMultiDataBuffer = (char*)malloc(m_iMultiDataBufferLen);
				CHECK_OBJECT_RETURN_VALUE(m_pMultiDataBuffer, false, MemoryMod_Buffer);
			}
			memset(m_pMultiDataBuffer, 0, m_iMultiDataBufferLen);
			m_iMultiDataLen = 0;
		}
		else	// 已经分配过
		{
			// 分配大小
			m_iMultiDataBufferLen = (aiSize * 2 * (MyUInt32)sizeof(char) > m_iMallocSize * sizeof(char)) ? (aiSize * 2 * (MyUInt32)sizeof(char)) : (m_iMallocSize * sizeof(char));
			if (!abSaveData)
			{
				// 释放原来的缓存
				if (m_pMultiDataBuffer != nullptr)
				{
					free((void*)m_pMultiDataBuffer);
					m_pMultiDataBuffer = nullptr;
				}
				m_pMultiDataBuffer = (char*)malloc(m_iMultiDataBufferLen);
				CHECK_OBJECT_RETURN_VALUE(m_pMultiDataBuffer, false, MemoryMod_Buffer);
				memset(m_pMultiDataBuffer, 0, m_iMultiDataBufferLen);
				m_iMultiDataLen = 0;
			}
			else
			{
				// 重新分配
				char* pBuffer = (char*)realloc(m_pMultiDataBuffer, m_iMultiDataBufferLen);
				CHECK_OBJECT_RETURN_VALUE(pBuffer, false, MemoryMod_Buffer);
				m_pMultiDataBuffer = pBuffer;
				m_iMultiDataLen = iOldLen;
			}
		}
	}
	else	// 不用重新分配大小
	{
		// 调整数据长度
		if (!abSaveData)
			m_iMultiDataLen = aiSize * sizeof(char);
		else
			m_iMultiDataLen = iOldLen;
	}
	return true;
}

// 宽字节分配
bool CAutoFreeBuffer::WideDataAllocate(MyUInt32 aiSize, bool abSaveData)
{
	MyUInt32 iOldLen = m_iWideDataLen;
	if (aiSize * sizeof(wchar_t) > m_iWideDataBufferLen)	// 重新分配大小
	{
		if (m_pWideDataBuffer == nullptr)	// 从未分配过
		{
			if (aiSize * sizeof(wchar_t) > m_iDefaultSize * sizeof(wchar_t))
			{
				m_iWideDataBufferLen = aiSize * sizeof(wchar_t);
				m_pWideDataBuffer = (wchar_t*)malloc(m_iWideDataBufferLen);
				CHECK_OBJECT_RETURN_VALUE(m_pWideDataBuffer, false, MemoryMod_Buffer);
			}
			else
			{
				m_iWideDataBufferLen = m_iDefaultSize * sizeof(wchar_t);
				m_pWideDataBuffer = (wchar_t*)malloc(m_iWideDataBufferLen);
				CHECK_OBJECT_RETURN_VALUE(m_pWideDataBuffer, false, MemoryMod_Buffer);
			}
			memset(m_pWideDataBuffer, 0, m_iWideDataBufferLen);
			m_iWideDataLen = 0;
		}
		else	// 已经分配过
		{
			// 分配大小
			m_iWideDataBufferLen = (aiSize * 2 * (MyUInt32)sizeof(wchar_t) > m_iMallocSize * sizeof(wchar_t)) ? (aiSize * 2 * (MyUInt32)sizeof(wchar_t)) : (m_iMallocSize * sizeof(wchar_t));
			if (!abSaveData)
			{
				// 释放原来的缓存
				if (m_pWideDataBuffer != nullptr)
				{
					free((void*)m_pWideDataBuffer);
					m_pWideDataBuffer = nullptr;
				}
				m_pWideDataBuffer = (wchar_t*)malloc(m_iWideDataBufferLen);
				CHECK_OBJECT_RETURN_VALUE(m_pWideDataBuffer, false, MemoryMod_Buffer);
				memset(m_pWideDataBuffer, 0, m_iWideDataBufferLen);
				m_iWideDataLen = 0;
			}
			else
			{
				// 重新分配
				wchar_t* pBuffer = (wchar_t*)realloc(m_pWideDataBuffer, m_iWideDataBufferLen);
				CHECK_OBJECT_RETURN_VALUE(pBuffer, false, MemoryMod_Buffer);
				m_pWideDataBuffer = pBuffer;
				m_iWideDataLen = iOldLen;
			}
		}
	}
	else	// 不用重新分配大小
	{
		// 保存数据长度
		if (!abSaveData)
			m_iWideDataLen = aiSize * sizeof(wchar_t);
		else
			m_iWideDataLen = iOldLen;
	}
	return true;
}