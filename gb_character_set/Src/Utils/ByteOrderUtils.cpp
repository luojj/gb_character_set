#include <bit>
#include "Utils/ByteOrderUtils.h"

namespace byte_order
{

	namespace c20_before
	{
		union ByteOrderInfo
		{
			int		m_iTest;
			char	m_cTest;
		};

		static bool IsBigEndian()
		{
			ByteOrderInfo Info{};
			Info.m_iTest = 1;
			if (Info.m_cTest == 1)
				return false;
			return true;
		}
	}

	inline namespace c20
	{
		static bool IsBigEndian()
		{
			if constexpr (std::endian::native == std::endian::big)
				return true;
			else
				return false;
		}
	}
}

// 是否为大端字节序
bool CByteOrderUtils::IsBigEndian()
{
	return byte_order::IsBigEndian();
}

// 将32位值保存到字符数组
void CByteOrderUtils::Store32(MyUInt32 aiValue, MyUInt8* apArray, MyUInt32 aiBitPos, bool abBigEndian)
{
	if (apArray == nullptr)
		return;

	if (abBigEndian)
	{
		apArray[aiBitPos + 0] = (MyUInt8)((aiValue >> 24) & 255);
		apArray[aiBitPos + 1] = (MyUInt8)((aiValue >> 16) & 255);
		apArray[aiBitPos + 2] = (MyUInt8)((aiValue >> 8) & 255);
		apArray[aiBitPos + 3] = (MyUInt8)(aiValue & 255);
	}
	else
	{
		apArray[aiBitPos + 0] = (MyUInt8)(aiValue);
		apArray[aiBitPos + 1] = (MyUInt8)(aiValue >> 8);
		apArray[aiBitPos + 2] = (MyUInt8)(aiValue >> 16);
		apArray[aiBitPos + 3] = (MyUInt8)(aiValue >> 24);
	}
}

// 从字符数组加载32位值
void CByteOrderUtils::Load32(MyUInt32& aiValue, const MyUInt8* apArray, MyUInt32 aiBitPos, bool abBigEndian)
{
	if (apArray == nullptr)
		return;

	if (abBigEndian)
	{
		aiValue = ((MyUInt32)(apArray[aiBitPos + 0] & 255) << 24) | \
			((MyUInt32)(apArray[aiBitPos + 1] & 255) << 16) | \
			((MyUInt32)(apArray[aiBitPos + 2] & 255) << 8) | \
			((MyUInt32)(apArray[aiBitPos + 3] & 255));
	}
	else
	{
		aiValue = ((MyUInt32)(apArray[aiBitPos + 0])) | \
			((MyUInt32)(apArray[aiBitPos + 1]) << 8) | \
			((MyUInt32)(apArray[aiBitPos + 2]) << 16) | \
			((MyUInt32)(apArray[aiBitPos + 3]) << 24);
	}
}

// 将64位值保存到字符数组
void CByteOrderUtils::Store64(MyUInt64 aiValue, MyUInt8* apArray, MyUInt32 aiBitPos, bool abBigEndian)
{
	if (apArray == nullptr)
		return;

	if (abBigEndian)
	{
		apArray[aiBitPos + 0] = (MyUInt8)((aiValue >> 56) & 255);
		apArray[aiBitPos + 1] = (MyUInt8)((aiValue >> 48) & 255);
		apArray[aiBitPos + 2] = (MyUInt8)((aiValue >> 40) & 255);
		apArray[aiBitPos + 3] = (MyUInt8)((aiValue >> 32) & 255);
		apArray[aiBitPos + 4] = (MyUInt8)((aiValue >> 24) & 255);
		apArray[aiBitPos + 5] = (MyUInt8)((aiValue >> 16) & 255);
		apArray[aiBitPos + 6] = (MyUInt8)((aiValue >> 8) & 255);
		apArray[aiBitPos + 7] = (MyUInt8)(aiValue & 255);
	}
	else
	{
		apArray[aiBitPos + 0] = (MyUInt8)(aiValue);
		apArray[aiBitPos + 1] = (MyUInt8)(aiValue >> 8);
		apArray[aiBitPos + 2] = (MyUInt8)(aiValue >> 16);
		apArray[aiBitPos + 3] = (MyUInt8)(aiValue >> 24);
		apArray[aiBitPos + 4] = (MyUInt8)(aiValue >> 32);
		apArray[aiBitPos + 5] = (MyUInt8)(aiValue >> 40);
		apArray[aiBitPos + 6] = (MyUInt8)(aiValue >> 48);
		apArray[aiBitPos + 7] = (MyUInt8)(aiValue >> 56);
	}
}

// 从字符数组加载64位值
void CByteOrderUtils::Load64(MyUInt64& aiValue, const MyUInt8* apArray, MyUInt32 aiBitPos, bool abBigEndian)
{
	if (apArray == nullptr)
		return;

	if (abBigEndian)
	{
		aiValue = (((MyUInt64)(apArray[aiBitPos + 0] & 255)) << 56) | \
			(((MyUInt64)(apArray[aiBitPos + 1] & 255)) << 48) | \
			(((MyUInt64)(apArray[aiBitPos + 2] & 255)) << 40) | \
			(((MyUInt64)(apArray[aiBitPos + 3] & 255)) << 32) | \
			(((MyUInt64)(apArray[aiBitPos + 4] & 255)) << 24) | \
			(((MyUInt64)(apArray[aiBitPos + 5] & 255)) << 16) | \
			(((MyUInt64)(apArray[aiBitPos + 6] & 255)) << 8) | \
			(((MyUInt64)(apArray[aiBitPos + 7] & 255)));
	}
	else
	{
		aiValue = ((MyUInt64)(apArray[aiBitPos + 0])) | \
			((MyUInt64)(apArray[aiBitPos + 1]) << 8) | \
			((MyUInt64)(apArray[aiBitPos + 2]) << 16) | \
			((MyUInt64)(apArray[aiBitPos + 3]) << 24) | \
			((MyUInt64)(apArray[aiBitPos + 4]) << 32) | \
			((MyUInt64)(apArray[aiBitPos + 5]) << 40) | \
			((MyUInt64)(apArray[aiBitPos + 6]) << 48) | \
			((MyUInt64)(apArray[aiBitPos + 7]) << 56);
	}
}