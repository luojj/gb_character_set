#include "Charset/Charset.h"
#include <memory>
#include <cuchar>
#include <sstream>
#include "CommonMacro.h"
#include "Charset/GB2312Table.h"
#include "Charset/GBKTable.h"
#include "Charset/GB18030Table.h"
#include "Utils/ByteOrderUtils.h"
#include "Check/CheckMacro.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
CCharset::CCharset()
{
	InitGBTable();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// C++
// UTF-8转Unicode
std::tuple<bool, std::vector<wchar_t>> CCharset::UTF8_2_Unicode_Cpp(const char* apUTF8)
{
	CHECK_OBJECT_RETURN_VALUE(apUTF8, std::make_tuple(false, std::vector<wchar_t>{}), CharsetMod);

	std::setlocale(LC_CTYPE, "en_US.utf8");

	std::mbstate_t State{};
	std::size_t iCount = std::mbsrtowcs(nullptr, &apUTF8, 0, &State);
	CHECK_VALUE_EQUAL_RETURN_VALUE(iCount, static_cast<std::size_t>(-1), std::make_tuple(false, std::vector<wchar_t>{}), CharsetMod);

	std::vector<wchar_t> Result{};
	Result.resize(iCount + 1);

	iCount = std::mbsrtowcs(&Result[0], &apUTF8, Result.size(), &State);
	CHECK_VALUE_EQUAL_RETURN_VALUE(iCount, static_cast<std::size_t>(-1), std::make_tuple(false, std::vector<wchar_t>{}), CharsetMod);

	return std::make_tuple(true, Result);
}

// Unicode转UTF-8
std::tuple<bool, std::vector<char>> CCharset::Unicode_2_UTF8_Cpp(const wchar_t* apUnicode)
{
	CHECK_OBJECT_RETURN_VALUE(apUnicode, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	std::setlocale(LC_CTYPE, "en_US.utf8");

	std::mbstate_t State{};
	std::size_t iCount = std::wcsrtombs(nullptr, &apUnicode, 0, &State);
	CHECK_VALUE_EQUAL_RETURN_VALUE(iCount, static_cast<std::size_t>(-1), std::make_tuple(false, std::vector<char>{}), CharsetMod);

	std::vector<char> Result{};
	Result.resize(iCount + 1);

	iCount = std::wcsrtombs(&Result[0], &apUnicode, Result.size(), &State);
	CHECK_VALUE_EQUAL_RETURN_VALUE(iCount, static_cast<std::size_t>(-1), std::make_tuple(false, std::vector<char>{}), CharsetMod);

	return std::make_tuple(true, Result);
}

// UTF-8转UTF-16
std::tuple<bool, std::vector<char16_t>> CCharset::UTF8_2_UTF16_Cpp(const char* apUTF8, MyUInt32 aiUTF8Len, bool abBigEndian)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF8, aiUTF8Len, std::make_tuple(false, std::vector<char16_t>{}), CharsetMod);

	std::setlocale(LC_ALL, "en_US.utf8");

	const char* pStart = apUTF8;
	const char* pEnd = apUTF8 + aiUTF8Len;

	std::size_t iCount = 0;
	std::vector<char16_t> Result{};
	Result.resize(aiUTF8Len);

	char16_t cValue{};
	std::mbstate_t State{};
	while (std::size_t rc = std::mbrtoc16(&cValue, pStart, pEnd - pStart, &State))
	{
		if (rc == static_cast<std::size_t>(-1) || rc == static_cast<std::size_t>(-2) || rc == static_cast<std::size_t>(-3))
			break;

		if (!abBigEndian)
			cValue = (char16_t)CByteOrderUtils::ByteOrderTrans((MyUInt16)cValue);
		Result[iCount++] = cValue;
		pStart += rc;
	}
	Result.resize(iCount + 1);
	return std::make_tuple(true, Result);
}

// UTF-16转UTF-8
std::tuple<bool, std::vector<char>> CCharset::UTF16_2_UTF8_Cpp(const char16_t* apUTF16, MyUInt32 aiUTF16Len)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF16, aiUTF16Len, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	std::setlocale(LC_ALL, "en_US.utf8");

	std::size_t iCount = 0;
	std::vector<char> Result{};
	Result.resize((size_t)aiUTF16Len * MB_LEN_MAX);

	char cValue[MB_LEN_MAX]{};
	std::mbstate_t State{};
	for (MyUInt32 i = 0; i < aiUTF16Len; ++i)
	{
		std::size_t rc = std::c16rtomb(&cValue[0], apUTF16[i], &State);
		CHECK_VALUE_EQUAL_RETURN_VALUE(rc, static_cast<std::size_t>(-1), std::make_tuple(false, std::vector<char>{}), CharsetMod, "Char", (std::size_t)apUTF16[i]);
		for (std::size_t j = 0; j < rc; ++j)
			Result[iCount++] = cValue[j];
	}
	Result.resize(iCount + 1);
	return std::make_tuple(true, Result);
}

// UTF-8转UTF-32
std::tuple<bool, std::vector<char32_t>> CCharset::UTF8_2_UTF32_Cpp(const char* apUTF8, MyUInt32 aiUTF8Len, bool abBigEndian)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF8, aiUTF8Len, std::make_tuple(false, std::vector<char32_t>{}), CharsetMod);

	std::setlocale(LC_ALL, "en_US.utf8");

	const char* pStart = apUTF8;
	const char* pEnd = apUTF8 + aiUTF8Len;

	std::size_t iCount = 0;
	std::vector<char32_t> Result{};
	Result.resize(aiUTF8Len);

	char32_t cValue{};
	std::mbstate_t State{};
	while (std::size_t rc = std::mbrtoc32(&cValue, pStart, pEnd - pStart, &State))
	{
		if (rc == static_cast<std::size_t>(-1) || rc == static_cast<std::size_t>(-2) || rc == static_cast<std::size_t>(-3))
			break;

		if (!abBigEndian)
			cValue = (char32_t)CByteOrderUtils::ByteOrderTrans((MyUInt32)cValue);
		Result[iCount++] = cValue;
		pStart += rc;
	}
	Result.resize(iCount + 1);
	return std::make_tuple(true, Result);
}

// UTF32转UTF-8
std::tuple<bool, std::vector<char>> CCharset::UTF32_2_UTF8_Cpp(const char32_t* apUTF32, MyUInt32 aiUTF32Len)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF32, aiUTF32Len, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	std::setlocale(LC_ALL, "en_US.utf8");

	std::size_t iCount = 0;
	std::vector<char> Result{};
	Result.resize((size_t)aiUTF32Len * MB_LEN_MAX);

	char cValue[MB_LEN_MAX]{};
	std::mbstate_t State{};
	for (MyUInt32 i = 0; i < aiUTF32Len; ++i)
	{
		std::size_t rc = std::c32rtomb(&cValue[0], apUTF32[i], &State);
		CHECK_VALUE_EQUAL_RETURN_VALUE(rc, static_cast<std::size_t>(-1), std::make_tuple(false, std::vector<char>{}), CharsetMod, "Char", (std::size_t)apUTF32[i]);
		for (std::size_t j = 0; j < rc; ++j)
			Result[iCount++] = cValue[j];
	}
	Result.resize(iCount + 1);
	return std::make_tuple(true, Result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// C
// UTF-8转Unicode
std::tuple<bool, std::vector<MyUInt16>> CCharset::UTF8_2_Unicode_C(const char* apUTF8, MyUInt32 aiUTF8Len)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF8, aiUTF8Len, std::make_tuple(false, std::vector<MyUInt16>{}), CharsetMod);

	MyUInt32 iUnicodeLen = UTF8_2_Unicode(apUTF8, aiUTF8Len, nullptr);
	if (iUnicodeLen == 0)
	{
		LogF(Error, CharsetMod, "CCharset::UTF8_2_Unicode_C Get Len Failed.");
		return std::make_tuple(false, std::vector<MyUInt16>{});
	}

	std::vector<MyUInt16> Result{};
	Result.resize((size_t)iUnicodeLen + 1);

	MyUInt16* pUnicode = &Result[0];
	UTF8_2_Unicode(apUTF8, aiUTF8Len, pUnicode);
	return std::make_tuple(true, Result);
}

// Unicode转UTF-8
std::tuple<bool, std::vector<char>> CCharset::Unicode_2_UTF8_C(const MyUInt16* apUnicode, MyUInt32 aiUnicodeLen)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUnicode, aiUnicodeLen, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	MyUInt32 iUTF8Len = Unicode_2_UTF8(apUnicode, aiUnicodeLen, nullptr);
	if (iUTF8Len == 0)
	{
		LogF(Error, CharsetMod, "CCharset::Unicode_2_UTF8_C Get Len Failed.");
		return std::make_tuple(false, std::vector<char>{});
	}

	std::vector<char> Result{};
	Result.resize((size_t)iUTF8Len + 1);

	char* pUTF8 = &Result[0];
	Unicode_2_UTF8(apUnicode, aiUnicodeLen, pUTF8);
	return std::make_tuple(true, Result);
}

// UTF-8转UTF-16
std::tuple<bool, std::vector<MyUInt16>> CCharset::UTF8_2_UTF16_C(const char* apUTF8, MyUInt32 aiUTF8Len, bool abBigEndian)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF8, aiUTF8Len, std::make_tuple(false, std::vector<MyUInt16>{}), CharsetMod);

	MyUInt32 iUTF16Len = UTF8_2_UTF16(apUTF8, aiUTF8Len, nullptr);
	if (iUTF16Len == 0)
	{
		LogF(Error, CharsetMod, "CCharset::UTF8_2_UTF16_C Get Len Failed.");
		return std::make_tuple(false, std::vector<MyUInt16>{});
	}

	std::vector<MyUInt16> Result{};
	Result.resize((size_t)iUTF16Len + 1);

	MyUInt16* pUTF16 = &Result[0];
	UTF8_2_UTF16(apUTF8, aiUTF8Len, pUTF16);

	if (!abBigEndian)
	{
		for (auto& pos : Result)
			pos = CByteOrderUtils::ByteOrderTrans(pos);
	}
	return std::make_tuple(true, Result);
}

// UTF-16转UTF-8
std::tuple<bool, std::vector<char>> CCharset::UTF16_2_UTF8_C(const MyUInt16* apUTF16, MyUInt32 aiUTF16Len, bool abBigEndian)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF16, aiUTF16Len, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	MyUInt16* pUTF16 = (MyUInt16*)apUTF16;
	std::vector<MyUInt16> Temp{};
	if (!abBigEndian)
	{
		Temp.resize(aiUTF16Len);
		std::copy(apUTF16, apUTF16 + aiUTF16Len, Temp.begin());
		for (auto& pos : Temp)
			pos = CByteOrderUtils::ByteOrderTrans(pos);
		pUTF16 = &Temp[0];
	}

	MyUInt32 iUTF8Len = UTF16_2_UTF8(pUTF16, aiUTF16Len, nullptr);
	if (iUTF8Len == 0)
	{
		LogF(Error, CharsetMod, "CCharset::UTF16_2_UTF8_C Get Len Failed.");
		return std::make_tuple(false, std::vector<char>{});
	}

	std::vector<char> Result{};
	Result.resize((size_t)iUTF8Len + 1);

	char* pUTF8 = &Result[0];
	UTF16_2_UTF8(pUTF16, aiUTF16Len, pUTF8);

	return std::make_tuple(true, Result);
}

// UTF-8转UTF-32
std::tuple<bool, std::vector<MyUInt32>> CCharset::UTF8_2_UTF32_C(const char* apUTF8, MyUInt32 aiUTF8Len, bool abBigEndian)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF8, aiUTF8Len, std::make_tuple(false, std::vector<MyUInt32>{}), CharsetMod);

	MyUInt32 iUTF32Len = UTF8_2_UTF32(apUTF8, aiUTF8Len, nullptr);
	if (iUTF32Len == 0)
	{
		LogF(Error, CharsetMod, "CCharset::UTF8_2_UTF32_C Get Len Failed.");
		return std::make_tuple(false, std::vector<MyUInt32>{});
	}

	std::vector<MyUInt32> Result{};
	Result.resize((size_t)iUTF32Len + 1);

	MyUInt32* pUTF32 = &Result[0];
	UTF8_2_UTF32(apUTF8, aiUTF8Len, pUTF32);

	if (!abBigEndian)
	{
		for (auto& pos : Result)
			pos = CByteOrderUtils::ByteOrderTrans((MyUInt32)pos);
	}
	return std::make_tuple(true, Result);
}

// UTF32转UTF-8
std::tuple<bool, std::vector<char>> CCharset::UTF32_2_UTF8_C(const MyUInt32* apUTF32, MyUInt32 aiUTF32Len, bool abBigEndian)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF32, aiUTF32Len, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	MyUInt32* pUTF32 = (MyUInt32*)apUTF32;
	std::vector<MyUInt32> Temp{};
	if (!abBigEndian)
	{
		Temp.resize(aiUTF32Len);
		std::copy(apUTF32, apUTF32 + aiUTF32Len, Temp.begin());
		for (auto& pos : Temp)
			pos = CByteOrderUtils::ByteOrderTrans((MyUInt32)pos);
		pUTF32 = &Temp[0];
	}

	MyUInt32 iUTF8Len = UTF32_2_UTF8(pUTF32, aiUTF32Len, nullptr);
	if (iUTF8Len == 0)
	{
		LogF(Error, CharsetMod, "CCharset::UTF32_2_UTF8_C Get Len Failed.");
		return std::make_tuple(false, std::vector<char>{});
	}

	std::vector<char> Result{};
	Result.resize((size_t)iUTF8Len + 1);

	char* pUTF8 = &Result[0];
	UTF32_2_UTF8(pUTF32, aiUTF32Len, pUTF8);

	return std::make_tuple(true, Result);
}

// GB2312转Unicode
std::tuple<bool, std::vector<MyUInt16>> CCharset::GB2312_2_Unicode(const char* apGB2312, MyUInt32 aiGB2312Len)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apGB2312, aiGB2312Len, std::make_tuple(false, std::vector<MyUInt16>{}), CharsetMod);

	std::vector<MyUInt16> Result{};
	Result.resize(aiGB2312Len);

	MyUInt32 iUnicodeLen = 0;
	MyUInt8* pGB2312 = (MyUInt8*)apGB2312;
	for (MyUInt32 i = 0; i < aiGB2312Len; i += 2)
	{
		// GB2312为大端字节序
		MyUInt16 iGB2312 = (pGB2312[i] << 8 | pGB2312[i + 1]);

		auto pos = m_GB2312_2_Unicode_Tables.find(iGB2312);
		if (pos == m_GB2312_2_Unicode_Tables.end())
		{
			LogSKV(Error, CharsetMod, "CCharset::GB2312_2_Unicode Not Find GB2312.", "i", i, "GB2312", iGB2312);
			return std::make_tuple(false, std::vector<MyUInt16>{});
		}
		else
		{
			Result[iUnicodeLen++] = pos->second;
		}
	}
	Result.resize((size_t)iUnicodeLen + 1);

	return std::make_tuple(true, Result);
}

// Unicode转GB2312
std::tuple<bool, std::vector<char>> CCharset::Unicode_2_GB2312(const MyUInt16* apUnicode, MyUInt32 aiUnicodeLen)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUnicode, aiUnicodeLen, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	std::vector<char> Result{};
	Result.resize((size_t)aiUnicodeLen * MB_LEN_MAX);

	MyUInt32 iGB2312Len = 0;
	for (MyUInt32 i = 0; i < aiUnicodeLen; ++i)
	{
		auto pos = m_Unicode_2_GB2312_Tables.find(apUnicode[i]);
		if (pos == m_Unicode_2_GB2312_Tables.end())
		{
			LogSKV(Error, CharsetMod, "CCharset::Unicode_2_GB2312 Not Find Unicode.", "i", i, "Unicode", apUnicode[i]);
			return std::make_tuple(false, std::vector<char>{});
		}
		else
		{
			MyUInt16 iGB2312 = pos->second;
			Result[iGB2312Len++] = (char)(iGB2312 >> 8);
			Result[iGB2312Len++] = (char)(iGB2312 & 0x00FF);
		}
	}
	Result.resize((size_t)iGB2312Len + 1);

	return std::make_tuple(true, Result);
}

// GB2312转UTF-8
std::tuple<bool, std::vector<char>> CCharset::GB2312_2_UTF8(const char* apGB2312, MyUInt32 aiGB2312Len)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apGB2312, aiGB2312Len, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	auto UnicodeResult = GB2312_2_Unicode(apGB2312, aiGB2312Len);
	if (!std::get<0>(UnicodeResult))
	{
		LogF(Error, CharsetMod, "CCharset::GB2312_2_UTF8 GB2312_2_Unicode Failed.");
		return std::make_tuple(false, std::vector<char>{});
	}

	return Unicode_2_UTF8_C(&std::get<1>(UnicodeResult)[0], (MyUInt32)std::get<1>(UnicodeResult).size() - 1);
}

// UTF-8转GB2312
std::tuple<bool, std::vector<char>> CCharset::UTF8_2_GB2312(const char* apUTF8, MyUInt32 aiUTF8Len)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF8, aiUTF8Len, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	auto UnicodeResult = UTF8_2_Unicode_C(apUTF8, aiUTF8Len);
	if (!std::get<0>(UnicodeResult))
	{
		LogF(Error, CharsetMod, "CCharset::UTF8_2_GB2312 UTF8_2_Unicode_C Failed.");
		return std::make_tuple(false, std::vector<char>{});
	}

	return Unicode_2_GB2312(&std::get<1>(UnicodeResult)[0], (MyUInt32)std::get<1>(UnicodeResult).size() - 1);
}

// GBK转Unicode
std::tuple<bool, std::vector<MyUInt16>> CCharset::GBK_2_Unicode(const char* apGBK, MyUInt32 aiGBKLen)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apGBK, aiGBKLen, std::make_tuple(false, std::vector<MyUInt16>{}), CharsetMod);

	std::vector<MyUInt16> Result{};
	Result.resize(aiGBKLen);

	MyUInt32 iUnicodeLen = 0;
	MyUInt8* pGBK = (MyUInt8*)apGBK;
	for (MyUInt32 i = 0; i < aiGBKLen; i += 2)
	{
		// GBK为大端字节序
		MyUInt16 iGBK = (pGBK[i] << 8 | pGBK[i + 1]);

		auto pos = m_GBK_2_Unicode_Tables.find(iGBK);
		if (pos == m_GBK_2_Unicode_Tables.end())
		{
			LogSKV(Error, CharsetMod, "CCharset::GBK_2_Unicode Not Find GBK.", "i", i, "GBK", iGBK);
			return std::make_tuple(false, std::vector<MyUInt16>{});
		}
		else
		{
			Result[iUnicodeLen++] = pos->second;
		}
	}
	Result.resize((size_t)iUnicodeLen + 1);

	return std::make_tuple(true, Result);
}

// Unicode转GBK
std::tuple<bool, std::vector<char>> CCharset::Unicode_2_GBK(const MyUInt16* apUnicode, MyUInt32 aiUnicodeLen)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUnicode, aiUnicodeLen, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	std::vector<char> Result{};
	Result.resize((size_t)aiUnicodeLen * MB_LEN_MAX);

	MyUInt32 iGBKLen = 0;
	for (MyUInt32 i = 0; i < aiUnicodeLen; ++i)
	{
		auto pos = m_Unicode_2_GBK_Tables.find(apUnicode[i]);
		if (pos == m_Unicode_2_GBK_Tables.end())
		{
			LogSKV(Error, CharsetMod, "CCharset::Unicode_2_GBK Not Find Unicode.", "i", i, "Unicode", apUnicode[i]);
			return std::make_tuple(false, std::vector<char>{});
		}
		else
		{
			MyUInt16 iGBK = pos->second;
			Result[iGBKLen++] = (char)(iGBK >> 8);
			Result[iGBKLen++] = (char)(iGBK & 0x00FF);
		}
	}
	Result.resize((size_t)iGBKLen + 1);

	return std::make_tuple(true, Result);
}

// GBK转UTF-8
std::tuple<bool, std::vector<char>> CCharset::GBK_2_UTF8(const char* apGBK, MyUInt32 aiGBKLen)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apGBK, aiGBKLen, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	auto UnicodeResult = GBK_2_Unicode(apGBK, aiGBKLen);
	if (!std::get<0>(UnicodeResult))
	{
		LogF(Error, CharsetMod, "CCharset::GBK_2_UTF8 GBK_2_Unicode Failed.");
		return std::make_tuple(false, std::vector<char>{});
	}

	return Unicode_2_UTF8_C(&std::get<1>(UnicodeResult)[0], (MyUInt32)std::get<1>(UnicodeResult).size() - 1);
}

// UTF-8转GBK
std::tuple<bool, std::vector<char>> CCharset::UTF8_2_GBK(const char* apUTF8, MyUInt32 aiUTF8Len)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF8, aiUTF8Len, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	auto UnicodeResult = UTF8_2_Unicode_C(apUTF8, aiUTF8Len);
	if (!std::get<0>(UnicodeResult))
	{
		LogF(Error, CharsetMod, "CCharset::UTF8_2_GBK UTF8_2_Unicode_C Failed.");
		return std::make_tuple(false, std::vector<char>{});
	}

	return Unicode_2_GBK(&std::get<1>(UnicodeResult)[0], (MyUInt32)std::get<1>(UnicodeResult).size() - 1);
}

// GB18030转Unicode
std::tuple<bool, std::vector<MyUInt16>> CCharset::GB18030_2_Unicode(const char* apGB18030, MyUInt32 aiGB18030Len)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apGB18030, aiGB18030Len, std::make_tuple(false, std::vector<MyUInt16>{}), CharsetMod);

	auto gb18030_byte = [](const MyUInt8* apGB18030)->MyUInt32 {
		MyUInt32 iGB18030Len = 0;
		if (apGB18030[0] >= 0x00 && apGB18030[0] <= 0x7F)
		{
			iGB18030Len = 1;
		}
		else if (apGB18030[0] >= 0x81 && apGB18030[0] <= 0xFE)
		{
			if (apGB18030[1] >= 0x30 && apGB18030[1] <= 0x39)
				iGB18030Len = 4;
			else
				iGB18030Len = 2;
		}
		return iGB18030Len;
	};

	std::vector<MyUInt16> Result{};
	Result.resize(aiGB18030Len);

	MyUInt32 iUnicodeLen = 0;
	MyUInt32 iOffset = 0;
	MyUInt8* pGB18030 = (MyUInt8*)apGB18030;

	do
	{
		MyUInt32 iLen = gb18030_byte(pGB18030 + iOffset);
		if (iLen == 1)
		{
			MyUInt16 iUnicode = pGB18030[iOffset];
			Result[iUnicodeLen++] = iUnicode;
		}
		else if (iLen == 2)
		{
			MyUInt16 iGB18030 = (pGB18030[iOffset] << 8 | pGB18030[iOffset + 1]);

			auto pos = m_GB18030_2Byte_2_Unicode_Tables.find(iGB18030);
			if (pos == m_GB18030_2Byte_2_Unicode_Tables.end())
			{
				LogSKV(Error, CharsetMod, "CCharset::GB18030_2_Unicode Not Find GB18030.", "i", iLen, "GB18030", iGB18030);
				return std::make_tuple(false, std::vector<MyUInt16>{});
			}
			else
			{
				Result[iUnicodeLen++] = pos->second;
			}
		}
		else if (iLen == 4)
		{
			MyUInt32 iGB18030 = (pGB18030[iOffset] << 24 | pGB18030[iOffset + 1] << 16 | pGB18030[iOffset + 2] << 8 | pGB18030[iOffset + 3]);
			if (iGB18030 >= 0x81308130 && iGB18030 <= 0x8439FE39)
			{
				auto pos = m_GB18030_4Byte_2_Unicode_Tables.find(iGB18030);
				if (pos == m_GB18030_4Byte_2_Unicode_Tables.end())
				{
					LogSKV(Error, CharsetMod, "CCharset::GB18030_2_Unicode Not Find GB18030.", "i", iLen, "GB18030", iGB18030);
					return std::make_tuple(false, std::vector<MyUInt16>{});
				}
				Result[iUnicodeLen++] = pos->second;
			}
			else
			{
				MyUInt16 iUnicode = 0x10000 + (pGB18030[iOffset] - 0x90) * 12600 + (pGB18030[iOffset + 1] - 0x30) * 1260 + (pGB18030[iOffset + 2] - 0x81) * 10 + pGB18030[iOffset + 3] - 0x30;
				Result[iUnicodeLen++] = iUnicode;
			}
		}

		iOffset += iLen;
		aiGB18030Len -= iLen;
	} while (aiGB18030Len != 0);
	Result.resize((size_t)iUnicodeLen + 1);

	return std::make_tuple(true, Result);
}

// Unicode转GB18030
std::tuple<bool, std::vector<char>> CCharset::Unicode_2_GB18030(const MyUInt16* apUnicode, MyUInt32 aiUnicodeLen)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUnicode, aiUnicodeLen, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	std::vector<char> Result{};
	Result.resize((size_t)aiUnicodeLen * MB_LEN_MAX);

	MyUInt32 iGB18030Len = 0;
	for (MyUInt32 i = 0; i < aiUnicodeLen; ++i)
	{
		if (apUnicode[i] >= 0x00 && apUnicode[i] <= 0x7F)
		{
			Result[iGB18030Len++] = (MyUInt8)apUnicode[i];
		}
		else
		{
			auto pos_16 = m_Unicode_2_GB18030_2Byte_Tables.find(apUnicode[i]);
			if (pos_16 == m_Unicode_2_GB18030_2Byte_Tables.end())
			{
				auto pos = m_Unicode_2_GB18030_4Byte_Tables.find(apUnicode[i]);
				if (pos == m_Unicode_2_GB18030_4Byte_Tables.end())
				{
					MyUInt16 U = apUnicode[i] - 0x10000;
					MyUInt16 M1 = U / 12600;
					MyUInt16 N1 = U % 12600;
					MyUInt16 M2 = N1 / 1260;
					MyUInt16 N2 = N1 % 1260;
					MyUInt16 M3 = N2 / 10;
					MyUInt16 N3 = N2 % 10;

					Result[iGB18030Len++] = (char)(M1 + 0x90);
					Result[iGB18030Len++] = (char)(M2 + 0x30);
					Result[iGB18030Len++] = (char)(M3 + 0x81);
					Result[iGB18030Len++] = (char)(N3 + 0x30);
				}
				else
				{
					MyUInt32 iGB18030_32 = pos->second;

					Result[iGB18030Len++] = (char)(iGB18030_32 >> 24);
					Result[iGB18030Len++] = (char)((iGB18030_32 >> 16) & 0x00FF);
					Result[iGB18030Len++] = (char)((iGB18030_32 >> 8) & 0x0000FF);
					Result[iGB18030Len++] = (char)(iGB18030_32 & 0x000000FF);
				}
			}
			else
			{
				MyUInt16 iGB18030_16 = pos_16->second;
				Result[iGB18030Len++] = (char)(iGB18030_16 >> 8);
				Result[iGB18030Len++] = (char)(iGB18030_16 & 0x00FF);
			}
		}
	}
	Result.resize((size_t)iGB18030Len + 1);

	return std::make_tuple(true, Result);
}

// GB18030转UTF-8
std::tuple<bool, std::vector<char>> CCharset::GB18030_2_UTF8(const char* apGB18030, MyUInt32 aiGB18030Len)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apGB18030, aiGB18030Len, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	auto UnicodeResult = GB18030_2_Unicode(apGB18030, aiGB18030Len);
	if (!std::get<0>(UnicodeResult))
	{
		LogF(Error, CharsetMod, "CCharset::GB18030_2_UTF8 GB18030_2_Unicode Failed.");
		return std::make_tuple(false, std::vector<char>{});
	}

	return Unicode_2_UTF8_C(&std::get<1>(UnicodeResult)[0], (MyUInt32)std::get<1>(UnicodeResult).size() - 1);
}

// UTF-8转GB18030
std::tuple<bool, std::vector<char>> CCharset::UTF8_2_GB18030(const char* apUTF8, MyUInt32 aiUTF8Len)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF8, aiUTF8Len, std::make_tuple(false, std::vector<char>{}), CharsetMod);

	auto UnicodeResult = UTF8_2_Unicode_C(apUTF8, aiUTF8Len);
	if (!std::get<0>(UnicodeResult))
	{
		LogF(Error, CharsetMod, "CCharset::UTF8_2_GB18030 UTF8_2_Unicode_C Failed.");
		return std::make_tuple(false, std::vector<char>{});
	}

	return Unicode_2_GB18030(&std::get<1>(UnicodeResult)[0], (MyUInt32)std::get<1>(UnicodeResult).size() - 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Unicode转UTF-8
MyUInt32 CCharset::Unicode_2_UTF8(MyUInt32 aiUnicode, char* apUTF8)
{
	MyUInt32 iUTF8Len = 0;
	if (aiUnicode <= 0x0000007F)
	{
		// U-00000000 - U-0000007F:0xxxxxxx
		if (apUTF8 != nullptr)
			*apUTF8 = (aiUnicode & 0x7F);
		iUTF8Len = 1;
	}
	else if (aiUnicode >= 0x00000080 && aiUnicode <= 0x000007FF)
	{
		// U-00000080 - U-000007FF:110xxxxx 10xxxxxx
		if (apUTF8 != nullptr)
		{
			*(apUTF8 + 1) = (aiUnicode & 0x3F) | 0x80;
			*apUTF8 = ((aiUnicode >> 6) & 0x1F) | 0xC0;
		}
		iUTF8Len = 2;
	}
	else if (aiUnicode >= 0x00000800 && aiUnicode <= 0x0000FFFF)
	{
		// U-00000800 - U-0000FFFF:1110xxxx 10xxxxxx 10xxxxxx
		if (apUTF8 != nullptr)
		{
			*(apUTF8 + 2) = (aiUnicode & 0x3F) | 0x80;
			*(apUTF8 + 1) = ((aiUnicode >> 6) & 0x3F) | 0x80;
			*apUTF8 = ((aiUnicode >> 12) & 0x0F) | 0xE0;
		}
		iUTF8Len = 3;
	}
	else if (aiUnicode >= 0x00010000 && aiUnicode <= 0x001FFFFF)
	{
		// U-00010000 - U-001FFFFF:11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		if (apUTF8 != nullptr)
		{
			*(apUTF8 + 3) = (aiUnicode & 0x3F) | 0x80;
			*(apUTF8 + 2) = ((aiUnicode >> 6) & 0x3F) | 0x80;
			*(apUTF8 + 1) = ((aiUnicode >> 12) & 0x3F) | 0x80;
			*apUTF8 = ((aiUnicode >> 18) & 0x07) | 0xF0;
		}
		iUTF8Len = 4;
	}
	else if (aiUnicode >= 0x00200000 && aiUnicode <= 0x03FFFFFF)
	{
		// U-00200000 - U-03FFFFFF:111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		if (apUTF8 != nullptr)
		{
			*(apUTF8 + 4) = (aiUnicode & 0x3F) | 0x80;
			*(apUTF8 + 3) = ((aiUnicode >> 6) & 0x3F) | 0x80;
			*(apUTF8 + 2) = ((aiUnicode >> 12) & 0x3F) | 0x80;
			*(apUTF8 + 1) = ((aiUnicode >> 18) & 0x3F) | 0x80;
			*apUTF8 = ((aiUnicode >> 24) & 0x03) | 0xF8;
		}
		iUTF8Len = 5;
	}
	else if (aiUnicode >= 0x04000000 && aiUnicode <= 0x7FFFFFFF)
	{
		// U-04000000 - U-7FFFFFFF:1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		if (apUTF8 != nullptr)
		{
			*(apUTF8 + 5) = (aiUnicode & 0x3F) | 0x80;
			*(apUTF8 + 4) = ((aiUnicode >> 6) & 0x3F) | 0x80;
			*(apUTF8 + 3) = ((aiUnicode >> 12) & 0x3F) | 0x80;
			*(apUTF8 + 2) = ((aiUnicode >> 18) & 0x3F) | 0x80;
			*(apUTF8 + 1) = ((aiUnicode >> 24) & 0x3F) | 0x80;
			*apUTF8 = ((aiUnicode >> 30) & 0x01) | 0xFC;
		}
		iUTF8Len = 6;
	}
	return iUTF8Len;
}

// UTF-8转Unicode
std::tuple<MyUInt32, MyUInt32> CCharset::UTF8_2_Unicode(const char* apUTF8, MyUInt16* apUnicode)
{
	CHECK_OBJECT_RETURN_VALUE(apUTF8, std::make_tuple(0, 0), CharsetMod);

	auto get_utf8_size = [](MyUInt8 utf8)->MyUInt32 {
		MyUInt32 iUTF8Len = 0;
		if (utf8 < 0x80)
			iUTF8Len = 1;
		else if ((utf8 >> 5) == 0x06)
			iUTF8Len = 2;
		else if ((utf8 >> 4) == 0x0E)
			iUTF8Len = 3;
		else if ((utf8 >> 3) == 0x1E)
			iUTF8Len = 4;
		else if ((utf8 >> 2) == 0x3E)
			iUTF8Len = 5;
		else if ((utf8 >> 1) == 0x7E)
			iUTF8Len = 6;
		return iUTF8Len;
	};

	// b1表示UTF-8编码的apUTF8中的高字节,b2表示次高字节,...
	char b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0, b6 = 0;
	MyUInt32 iUTF8Len = get_utf8_size((MyUInt8)apUTF8[0]);
	MyUInt32 iUnicodeLen = 0;
	MyUInt8* pOutput = (MyUInt8*)apUnicode;

	switch (iUTF8Len)
	{
	case 1:
		if (pOutput != nullptr)
			*pOutput = *apUTF8;
		iUnicodeLen = 1;
		break;
	case 2:
		b1 = *apUTF8;
		b2 = *(apUTF8 + 1);
		if ((b2 & 0xC0) != 0x80)
		{
			LogF(Error, CharsetMod, "CCharset::UTF8_2_Unicode UTF8 Len 2 Failed.");
			return std::make_tuple(0, 0);
		}

		if (pOutput != nullptr)
		{
			*pOutput = (b1 << 6) + (b2 & 0x3F);
			*(pOutput + 1) = (b1 >> 2) & 0x07;
		}
		iUnicodeLen = 1;
		break;
	case 3:
		b1 = *apUTF8;
		b2 = *(apUTF8 + 1);
		b3 = *(apUTF8 + 2);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80))
		{
			LogF(Error, CharsetMod, "CCharset::UTF8_2_Unicode UTF8 Len 3 Failed.");
			return std::make_tuple(0, 0);
		}

		if (pOutput != nullptr)
		{
			*pOutput = (b2 << 6) + (b3 & 0x3F);
			*(pOutput + 1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
		}
		iUnicodeLen = 1;
		break;
	case 4:
		b1 = *apUTF8;
		b2 = *(apUTF8 + 1);
		b3 = *(apUTF8 + 2);
		b4 = *(apUTF8 + 3);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) || ((b4 & 0xC0) != 0x80))
		{
			LogF(Error, CharsetMod, "CCharset::UTF8_2_Unicode UTF8 Len 4 Failed.");
			return std::make_tuple(0, 0);
		}

		if (pOutput != nullptr)
		{
			*pOutput = (b3 << 6) + (b4 & 0x3F);
			*(pOutput + 1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
			*(pOutput + 2) = ((b1 << 2) & 0x1C) + ((b2 >> 4) & 0x03);
		}
		iUnicodeLen = 2;
		break;
	case 5:
		b1 = *apUTF8;
		b2 = *(apUTF8 + 1);
		b3 = *(apUTF8 + 2);
		b4 = *(apUTF8 + 3);
		b5 = *(apUTF8 + 4);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80))
		{
			LogF(Error, CharsetMod, "CCharset::UTF8_2_Unicode UTF8 Len 5 Failed.");
			return std::make_tuple(0, 0);
		}

		if (pOutput != nullptr)
		{
			*pOutput = (b4 << 6) + (b5 & 0x3F);
			*(pOutput + 1) = (b3 << 4) + ((b4 >> 2) & 0x0F);
			*(pOutput + 2) = (b2 << 2) + ((b3 >> 4) & 0x03);
			*(pOutput + 3) = (b1 << 6);
		}
		iUnicodeLen = 2;
		break;
	case 6:
		b1 = *apUTF8;
		b2 = *(apUTF8 + 1);
		b3 = *(apUTF8 + 2);
		b4 = *(apUTF8 + 3);
		b5 = *(apUTF8 + 4);
		b6 = *(apUTF8 + 5);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80) || ((b6 & 0xC0) != 0x80))
		{
			LogF(Error, CharsetMod, "CCharset::UTF8_2_Unicode UTF8 Len 6 Failed.");
			return std::make_tuple(0, 0);
		}

		if (pOutput != nullptr)
		{
			*pOutput = (b5 << 6) + (b6 & 0x3F);
			*(pOutput + 1) = (b5 << 4) + ((b6 >> 2) & 0x0F);
			*(pOutput + 2) = (b3 << 2) + ((b4 >> 4) & 0x03);
			*(pOutput + 3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);
		}
		iUnicodeLen = 2;
		break;
	default:
		break;
	}

	return std::make_tuple(iUTF8Len, iUnicodeLen);
}

// UTF-32转UTF-8
MyUInt32 CCharset::UTF32_2_UTF8(MyUInt32 aiUTF32, char* apUTF8)
{
	constexpr MyUInt8 PREFIX[] = { 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
	constexpr MyUInt32 CODE_UP[] =
	{
		0x80,		// U+00000000 - U+0000007F
		0x800,		// U+00000080 - U+000007FF
		0x10000,	// U+00000800 - U+0000FFFF
		0x200000,	// U+00010000 - U+001FFFFF
		0x4000000,	// U+00200000 - U+03FFFFFF
		0x80000000	// U+04000000 - U+7FFFFFFF
	};

	// 根据UCS4编码范围确定对应的UTF-8编码字节数
	MyUInt32 i = 0;
	MyUInt32 iSize = sizeof(CODE_UP) / sizeof(MyUInt32);
	for (i = 0; i < iSize; ++i)
	{
		if (aiUTF32 < CODE_UP[i])
			break;
	}

	// 无效的UCS4编码
	if (i == iSize)
	{
		LogSKV(Error, CharsetMod, "CCharset::UTF32_2_UTF8 Invalid UTF-32.", "UTF32", aiUTF32);
		return 0;
	}

	// UTF-8编码字节数
	MyUInt32 iUTF8Len = i + 1;
	if (apUTF8 != nullptr)
	{
		// 转换为UTF-8编码
		for (; i > 0; --i)
		{
			apUTF8[i] = (char)((aiUTF32 & 0x3F) | 0x80);
			aiUTF32 >>= 6;
		}
		apUTF8[0] = (char)(aiUTF32 | PREFIX[iUTF8Len - 1]);
	}
	return iUTF8Len;
}

// UTF-8转UTF-32
MyUInt32 CCharset::UTF8_2_UTF32(const char* apUTF8, MyUInt32& aiUTF32)
{
	CHECK_OBJECT_RETURN_VALUE(apUTF8, 0, CharsetMod);

	MyUInt32 iUTF8Len = 0;
	MyUInt8 iTemp = (MyUInt8)(*apUTF8++);
	if (iTemp < 0x80)
	{
		aiUTF32 = iTemp;
		iUTF8Len = 1;
		return iUTF8Len;
	}

	// 非法UTF8
	if (iTemp < 0xC0 || iTemp > 0xFD)
	{
		LogSKV(Error, CharsetMod, "CCharset::UTF8_2_UTF32 Invalid UTF-8.", "Temp", iTemp);
		return iUTF8Len;
	}

	if (iTemp < 0xE0)
	{
		aiUTF32 = iTemp & 0x1F;
		iUTF8Len = 2;
	}
	else if (iTemp < 0xF0)
	{
		aiUTF32 = iTemp & 0x0F;
		iUTF8Len = 3;
	}
	else if (iTemp < 0xF8)
	{
		aiUTF32 = iTemp & 0x07;
		iUTF8Len = 4;
	}
	else if (iTemp < 0xFC)
	{
		aiUTF32 = iTemp & 0x03;
		iUTF8Len = 5;
	}
	else
	{
		aiUTF32 = iTemp & 0x01;
		iUTF8Len = 6;
	}

	MyUInt32 i = 0;
	for (i = 1; i < iUTF8Len; ++i)
	{
		iTemp = (MyUInt8)(*apUTF8++);
		// 非法UTF8
		if (iTemp < 0x80 || iTemp > 0xBF)
		{
			LogSKV(Error, CharsetMod, "CCharset::UTF8_2_UTF32 Invalid UTF-8.", "Temp", iTemp);
			return 0;
		}

		aiUTF32 = (aiUTF32 << 0x06) + (iTemp & 0x3F);
	}
	return iUTF8Len;
}

// UTF-32转UTF-16
MyUInt32 CCharset::UTF32_2_UTF16(MyUInt32 aiUTF32, MyUInt16* apUTF16)
{
	MyUInt32 iUTF16Len = 0;
	if (aiUTF32 <= 0xFFFF)
	{
		if (apUTF16 != nullptr)
			*apUTF16 = (MyUInt16)(aiUTF32);
		iUTF16Len = 1;
	}
	else if (aiUTF32 <= 0xEFFFF)
	{
		if (apUTF16 != nullptr)
		{
			// 高10位
			apUTF16[0] = (MyUInt16)(0xD800 + (aiUTF32 >> 10) - 0x40);
			// 低10位
			apUTF16[1] = (MyUInt16)(0xDC00 + (aiUTF32 & 0x03FF));
		}
		iUTF16Len = 2;
	}
	return iUTF16Len;
}

// UTF-16转UTF-32
MyUInt32 CCharset::UTF16_2_UTF32(const MyUInt16* apUTF16, MyUInt32& aiUTF32)
{
	CHECK_OBJECT_RETURN_VALUE(apUTF16, 0, CharsetMod);

	MyUInt32 iUTF16Len = 0;
	MyUInt16 iHigh = apUTF16[0];
	if (iHigh >= 0xD800 && iHigh <= 0xDFFF)
	{
		if (iHigh < 0xDC00)
		{
			MyUInt16 iLow = apUTF16[1];
			if (iLow >= 0xDC00 && iLow <= 0xDFFF)
			{
				aiUTF32 = (iLow & 0x03FF) + (((iHigh & 0x03FF) + 0x40) << 10);
				iUTF16Len = 2;
			}
		}

		// 非法UTF16编码
		LogF(Error, CharsetMod, "CCharset::UTF16_2_UTF32 Invalid UTF-16.");
	}
	else
	{
		aiUTF32 = iHigh;
		iUTF16Len = 1;
	}
	return iUTF16Len;
}

// UTF-8转Unicode(字符串)
MyUInt32 CCharset::UTF8_2_Unicode(const char* apUTF8, MyUInt32 aiUTF8Len, MyUInt16* apUnicode)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF8, aiUTF8Len, 0, CharsetMod);

	MyUInt32 iUnicodeLen = 0;
	while (aiUTF8Len != 0)
	{
		// UTF8转Unicode
		auto Result = UTF8_2_Unicode(apUTF8, apUnicode);
		// 非法的UTF8编码
		if (std::get<0>(Result) == 0)
			return 0;

		apUTF8 += std::get<0>(Result);
		aiUTF8Len -= std::get<0>(Result);

		if (apUnicode != nullptr)
			apUnicode += std::get<1>(Result);
		iUnicodeLen += std::get<1>(Result);
	}
	return iUnicodeLen;
}

// Unicode转UTF-8(字符串)
MyUInt32 CCharset::Unicode_2_UTF8(const MyUInt16* apUnicode, MyUInt32 aiUnicodeLen, char* apUTF8)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUnicode, aiUnicodeLen, 0, CharsetMod);

	MyUInt32 iLen = 0, iUTF8Len = 0;
	while (aiUnicodeLen != 0)
	{
		MyUInt32 iUnicode = *apUnicode;
		// Unicode转UTF-8
		iLen = Unicode_2_UTF8(iUnicode, apUTF8);
		// 非法的Unicode编码
		if (iLen == 0)
			return 0;

		++apUnicode;
		--aiUnicodeLen;

		if (apUTF8 != nullptr)
			apUTF8 += iLen;

		iUTF8Len += iLen;
	}
	return iUTF8Len;
}

// UTF-8转UTF-16(字符串)
MyUInt32 CCharset::UTF8_2_UTF16(const char* apUTF8, MyUInt32 aiUTF8Len, MyUInt16* apUTF16)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF8, aiUTF8Len, 0, CharsetMod);

	MyUInt32 iTemp = 0, iLen = 0, iUTF16Len = 0;
	while (aiUTF8Len != 0)
	{
		// UTF-8转UTF-32
		iLen = UTF8_2_UTF32(apUTF8, iTemp);
		// 非法的UTF8编码
		if (iLen == 0)
			return 0;

		apUTF8 += iLen;
		aiUTF8Len -= iLen;

		// UTF-32转UTF-16
		iLen = UTF32_2_UTF16(iTemp, apUTF16);
		if (iLen == 0)
			return 0;

		if (apUTF16 != nullptr)
			apUTF16 += iLen;
		iUTF16Len += iLen;
	}

	return iUTF16Len;
}

// UTF-16转UTF-8(字符串)
MyUInt32 CCharset::UTF16_2_UTF8(const MyUInt16* apUTF16, MyUInt32 aiUTF16Len, char* apUTF8)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF16, aiUTF16Len, 0, CharsetMod);

	MyUInt32 iTemp = 0, iLen = 0, iUTF8Len = 0;
	while (aiUTF16Len != 0)
	{
		// UTF-16转UTF-32
		iLen = UTF16_2_UTF32(apUTF16, iTemp);
		// 非法的UTF16编码
		if (iLen == 0)
			return 0;

		apUTF16 += iLen;
		aiUTF16Len -= iLen;

		// UTF-32转UTF-8
		iLen = UTF32_2_UTF8(iTemp, apUTF8);
		if (iLen == 0)
			return 0;

		if (apUTF8 != nullptr)
			apUTF8 += iLen;
		iUTF8Len += iLen;
	}

	return iUTF8Len;
}

// UTF-8转UTF-32(字符串)
MyUInt32 CCharset::UTF8_2_UTF32(const char* apUTF8, MyUInt32 aiUTF8Len, MyUInt32* apUTF32)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF8, aiUTF8Len, 0, CharsetMod);

	MyUInt32 iTemp = 0, iLen = 0, iUTF32Len = 0;
	while (aiUTF8Len != 0)
	{
		// UTF-8转UTF-32
		iLen = UTF8_2_UTF32(apUTF8, iTemp);
		// 非法的UTF8编码
		if (iLen == 0)
			return 0;

		apUTF8 += iLen;
		aiUTF8Len -= iLen;

		if (apUTF32 != nullptr)
		{
			*apUTF32 = iTemp;
			++apUTF32;
		}
		++iUTF32Len;
	}
	return iUTF32Len;
}

// UTF-32转UTF-8(字符串)
MyUInt32 CCharset::UTF32_2_UTF8(const MyUInt32* apUTF32, MyUInt32 aiUTF32Len, char* apUTF8)
{
	CHECK_OBJECT_AND_LEN_RETURN_VALUE(apUTF32, aiUTF32Len, 0, CharsetMod);

	MyUInt32 iLen = 0, iUTF8Len = 0;
	while (aiUTF32Len != 0)
	{
		// UTF-32转UTF-8
		iLen = UTF32_2_UTF8(*apUTF32, apUTF8);
		// 非法的UTF32编码
		if (iLen == 0)
			return 0;

		++apUTF32;
		--aiUTF32Len;

		if (apUTF8 != nullptr)
			apUTF8 += iLen;
		iUTF8Len += iLen;
	}
	return iUTF8Len;
}

// 初始化GB编码表
void CCharset::InitGBTable()
{
	auto fun1 = [](std::string_view aTables, std::unordered_map<MyUInt16, MyUInt16>& aMap)->bool {
		std::string strTables(aTables);
		std::stringstream ss(strTables);
		std::string strLine;
		while (std::getline(ss, strLine))
		{
			if (strLine.empty())
				continue;

			MyUInt16 iValue1 = 0, iValue2 = 0;
			std::istringstream is(strLine);
			is >> std::hex >> iValue1 >> iValue2;
			aMap.insert({ iValue1, iValue2 });
		}
		return true;
	};

	auto fun2 = [](std::string_view aTables, std::unordered_map<MyUInt32, MyUInt16>& aMap)->bool {
		std::string strTables(aTables);
		std::stringstream ss(strTables);
		std::string strLine;
		while (std::getline(ss, strLine))
		{
			if (strLine.empty())
				continue;

			MyUInt32 iValue1 = 0;
			MyUInt16 iValue2 = 0;
			std::istringstream is(strLine);
			is >> std::hex >> iValue1 >> iValue2;
			aMap.insert({ iValue1, iValue2 });
		}
		return true;
	};

	// GB2312
	if (!fun1(GB2312_2_Unicode_Tables, m_GB2312_2_Unicode_Tables))
	{
		LogF(Error, CharsetMod, "Init GB2312 Failed.");
		return;
	}

	for (auto& [gb2312, unicode] : m_GB2312_2_Unicode_Tables)
		m_Unicode_2_GB2312_Tables.insert({ unicode, gb2312 });

	// GBK
	if (!fun1(GBK_2_Unicode_Tables, m_GBK_2_Unicode_Tables))
	{
		LogF(Error, CharsetMod, "Init GBK Failed.");
		return;
	}

	for (auto& [gbk, unicode] : m_GBK_2_Unicode_Tables)
		m_Unicode_2_GBK_Tables.insert({ unicode, gbk });

	// GB18030
	if (!fun1(GB18030_2Byte_2_Unicode_Tables, m_GB18030_2Byte_2_Unicode_Tables))
	{
		LogF(Error, CharsetMod, "Init GB18030 2Byte Failed.");
		return;
	}

	for (auto& [gb18030, unicode] : m_GB18030_2Byte_2_Unicode_Tables)
		m_Unicode_2_GB18030_2Byte_Tables.insert({ unicode, gb18030 });

	if (!fun2(GB18030_4Byte_2_Unicode_Tables, m_GB18030_4Byte_2_Unicode_Tables))
	{
		LogF(Error, CharsetMod, "Init GB18030 4Byte Failed.");
		return;
	}

	for (auto& [gb18030, unicode] : m_GB18030_4Byte_2_Unicode_Tables)
		m_Unicode_2_GB18030_4Byte_Tables.insert({ unicode, gb18030 });
}