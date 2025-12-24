#include <iostream>
#include <string>
#include <format>
#include <cstdint>
#include <fstream>
#include "CharsetTest.h"
#include "Charset/Charset.h"
#include "Utils/StringUtils.h"
/*
运行结果
windows
C++ Unicode To UTF-8:E68891E698AFE8B081
C++ UTF-8 To Unicode:6211662F8C01
C++ UTF-8 To UTF-16 BE:6211662F8C01
C++ UTF-16 BE To UTF-8:E68891E698AFE8B081
C++ UTF-8 To UTF-16 LE:11622F66018C
C++ UTF-16 LE To UTF-8:E68891E698AFE8B081
C++ UTF-8 To UTF-32 BE:000062110000662F00008C01
C++ UTF-32 BE To UTF-8:E68891E698AFE8B081
C++ UTF-8 To UTF-32 LE:116200002F660000018C0000
C++ UTF-32 LE To UTF-8:E68891E698AFE8B081

C Unicode To UTF-8:E68891E698AFE8B081
C UTF-8 To Unicode:6211662F8C01
C UTF-8 To UTF-16 BE:6211662F8C01
C UTF-16 BE To UTF-8:E68891E698AFE8B081
C UTF-8 To UTF-16 LE:11622F66018C
C UTF-16 LE To UTF-8:E68891E698AFE8B081
C UTF-8 To UTF-32 BE:000062110000662F00008C01
C UTF-32 BE To UTF-8:E68891E698AFE8B081
C UTF-8 To UTF-32 LE:116200002F660000018C0000
C UTF-32 LE To UTF-8:E68891E698AFE8B081

Linux
C++ UTF-8 To Unicode:000062110000662F00008C01
C++ Unicode To UTF-8:E68891E698AFE8B081
C++ UTF-8 To UTF-16 BE:6211662F8C01
C++ UTF-16 BE To UTF-8:E68891E698AFE8B081
C++ UTF-8 To UTF-16 LE:11622F66018C
C++ UTF-16 LE To UTF-8:E68891E698AFE8B081
C++ UTF-8 To UTF-32 BE:000062110000662F00008C01
C++ UTF-32 BE To UTF-8:E68891E698AFE8B081
C++ UTF-8 To UTF-32 LE:116200002F660000018C0000
C++ UTF-32 LE To UTF-8:E68891E698AFE8B081

C UTF-8 To Unicode:6211662F8C01
C Unicode To UTF-8:E68891E698AFE8B081
C UTF-8 To UTF-16 BE:6211662F8C01
C UTF-16 BE To UTF-8:E68891E698AFE8B081
C UTF-8 To UTF-16 LE:11622F66018C
C UTF-16 LE To UTF-8:E68891E698AFE8B081
C UTF-8 To UTF-32 BE:000062110000662F00008C01
C UTF-32 BE To UTF-8:E68891E698AFE8B081
C UTF-8 To UTF-32 LE:116200002F660000018C0000
C UTF-32 LE To UTF-8:E68891E698AFE8B081
*/
void CCharsetTest::TestCharset1()
{
#if defined (_WIN32)
	std::wstring strUnicode_1 = L"我是谁";
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// C++
	CCharset charset;
	auto cpp_utf8_1 = charset.Unicode_2_UTF8_Cpp(strUnicode_1.c_str());
	if (!std::get<0>(cpp_utf8_1))
		std::cout << "C++ Unicode To UTF-8 Failed." << std::endl;
	else
		std::cout << "C++ Unicode To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf8_1)[0], (MyUInt32)std::get<1>(cpp_utf8_1).size() - 1, true) << std::endl;

	auto cpp_unicode_1 = charset.UTF8_2_Unicode_Cpp(&std::get<1>(cpp_utf8_1)[0]);
	if (!std::get<0>(cpp_unicode_1))
		std::cout << "C++ UTF-8 To Unicode Failed." << std::endl;
	else
		std::cout << "C++ UTF-8 To Unicode:" << CStringUtils::BytesToHex(&std::get<1>(cpp_unicode_1)[0], (MyUInt32)std::get<1>(cpp_unicode_1).size() - 1, true) << std::endl;

	auto cpp_utf16_1 = charset.UTF8_2_UTF16_Cpp(&std::get<1>(cpp_utf8_1)[0], (MyUInt32)std::get<1>(cpp_utf8_1).size() - 1, true);
	if (!std::get<0>(cpp_utf16_1))
		std::cout << "C++ UTF-8 To UTF-16 BE Failed." << std::endl;
	else
		std::cout << "C++ UTF-8 To UTF-16 BE:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf16_1)[0], (MyUInt32)std::get<1>(cpp_utf16_1).size() - 1, true) << std::endl;

	auto cpp_utf8_2 = charset.UTF16_2_UTF8_Cpp(&std::get<1>(cpp_utf16_1)[0], (MyUInt32)std::get<1>(cpp_utf16_1).size() - 1);
	if (!std::get<0>(cpp_utf8_2))
		std::cout << "C++ UTF-16 BE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C++ UTF-16 BE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf8_2)[0], (MyUInt32)std::get<1>(cpp_utf8_2).size() - 1, true) << std::endl;

	auto cpp_utf16_2 = charset.UTF8_2_UTF16_Cpp(&std::get<1>(cpp_utf8_1)[0], (MyUInt32)std::get<1>(cpp_utf8_1).size() - 1, false);
	if (!std::get<0>(cpp_utf16_2))
		std::cout << "C++ UTF-8 To UTF-16 LE Failed." << std::endl;
	else
		std::cout << "C++ UTF-8 To UTF-16 LE:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf16_2)[0], (MyUInt32)std::get<1>(cpp_utf16_2).size() - 1, true) << std::endl;

	auto cpp_utf8_3 = charset.UTF16_2_UTF8_Cpp(&std::get<1>(cpp_utf16_1)[0], (MyUInt32)std::get<1>(cpp_utf16_1).size() - 1);
	if (!std::get<0>(cpp_utf8_3))
		std::cout << "C++ UTF-16 LE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C++ UTF-16 LE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf8_3)[0], (MyUInt32)std::get<1>(cpp_utf8_3).size() - 1, true) << std::endl;

	auto cpp_utf32_1 = charset.UTF8_2_UTF32_Cpp(&std::get<1>(cpp_utf8_1)[0], (MyUInt32)std::get<1>(cpp_utf8_1).size() - 1, true);
	if (!std::get<0>(cpp_utf32_1))
		std::cout << "C++ UTF-8 To UTF-32 BE Failed." << std::endl;
	else
		std::cout << "C++ UTF-8 To UTF-32 BE:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf32_1)[0], (MyUInt32)std::get<1>(cpp_utf32_1).size() - 1, true) << std::endl;

	auto cpp_utf8_4 = charset.UTF32_2_UTF8_Cpp(&std::get<1>(cpp_utf32_1)[0], (MyUInt32)std::get<1>(cpp_utf32_1).size() - 1);
	if (!std::get<0>(cpp_utf8_4))
		std::cout << "C++ UTF-32 BE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C++ UTF-32 BE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf8_4)[0], (MyUInt32)std::get<1>(cpp_utf8_4).size() - 1, true) << std::endl;

	auto cpp_utf32_2 = charset.UTF8_2_UTF32_Cpp(&std::get<1>(cpp_utf8_1)[0], (MyUInt32)std::get<1>(cpp_utf8_1).size() - 1, false);
	if (!std::get<0>(cpp_utf32_2))
		std::cout << "C++ UTF-8 To UTF-32 LE Failed." << std::endl;
	else
		std::cout << "C++ UTF-8 To UTF-32 LE:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf32_2)[0], (MyUInt32)std::get<1>(cpp_utf32_2).size() - 1, true) << std::endl;

	auto cpp_utf8_5 = charset.UTF32_2_UTF8_Cpp(&std::get<1>(cpp_utf32_1)[0], (MyUInt32)std::get<1>(cpp_utf32_1).size() - 1);
	if (!std::get<0>(cpp_utf8_5))
		std::cout << "C++ UTF-32 LE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C++ UTF-32 LE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf8_5)[0], (MyUInt32)std::get<1>(cpp_utf8_5).size() - 1, true) << std::endl;

	std::cout << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// C
	auto c_utf8_1 = charset.Unicode_2_UTF8_C((const MyUInt16*)strUnicode_1.c_str(), (MyUInt32)strUnicode_1.size());
	if (!std::get<0>(c_utf8_1))
		std::cout << "C Unicode To UTF-8 Failed." << std::endl;
	else
		std::cout << "C Unicode To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(c_utf8_1)[0], (MyUInt32)std::get<1>(c_utf8_1).size() - 1, true) << std::endl;

	auto c_unicode_1 = charset.UTF8_2_Unicode_C(&std::get<1>(c_utf8_1)[0], (MyUInt32)std::get<1>(c_utf8_1).size() - 1);
	if (!std::get<0>(c_unicode_1))
		std::cout << "C UTF-8 To Unicode Failed." << std::endl;
	else
		std::cout << "C UTF-8 To Unicode:" << CStringUtils::BytesToHex(&std::get<1>(c_unicode_1)[0], (MyUInt32)std::get<1>(c_unicode_1).size() - 1, true) << std::endl;

	auto c_utf16_1 = charset.UTF8_2_UTF16_C(&std::get<1>(c_utf8_1)[0], (MyUInt32)std::get<1>(c_utf8_1).size() - 1, true);
	if (!std::get<0>(c_utf16_1))
		std::cout << "C UTF-8 To UTF-16 BE Failed." << std::endl;
	else
		std::cout << "C UTF-8 To UTF-16 BE:" << CStringUtils::BytesToHex(&std::get<1>(c_utf16_1)[0], (MyUInt32)std::get<1>(c_utf16_1).size() - 1, true) << std::endl;

	auto c_utf8_2 = charset.UTF16_2_UTF8_C(&std::get<1>(c_utf16_1)[0], (MyUInt32)std::get<1>(c_utf16_1).size() - 1, true);
	if (!std::get<0>(c_utf8_2))
		std::cout << "C UTF-16 BE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C UTF-16 BE To UTF-8:" << CStringUtils::BytesToHex((const MyUInt8*)&std::get<1>(c_utf8_2)[0], (MyUInt32)std::get<1>(c_utf8_2).size() - 1, true) << std::endl;

	auto c_utf16_2 = charset.UTF8_2_UTF16_C(&std::get<1>(c_utf8_1)[0], (MyUInt32)std::get<1>(c_utf8_1).size() - 1, false);
	if (!std::get<0>(c_utf16_2))
		std::cout << "C UTF-8 To UTF-16 LE Failed." << std::endl;
	else
		std::cout << "C UTF-8 To UTF-16 LE:" << CStringUtils::BytesToHex(&std::get<1>(c_utf16_2)[0], (MyUInt32)std::get<1>(c_utf16_2).size() - 1, true) << std::endl;

	auto c_utf8_3 = charset.UTF16_2_UTF8_C(&std::get<1>(c_utf16_2)[0], (MyUInt32)std::get<1>(c_utf16_2).size() - 1, false);
	if (!std::get<0>(c_utf8_3))
		std::cout << "C UTF-16 LE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C UTF-16 LE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(c_utf8_3)[0], (MyUInt32)std::get<1>(c_utf8_3).size() - 1, true) << std::endl;

	auto c_utf32_1 = charset.UTF8_2_UTF32_C(&std::get<1>(c_utf8_1)[0], (MyUInt32)std::get<1>(c_utf8_1).size() - 1, true);
	if (!std::get<0>(c_utf32_1))
		std::cout << "C UTF-8 To UTF-32 BE Failed." << std::endl;
	else
		std::cout << "C UTF-8 To UTF-32 BE:" << CStringUtils::BytesToHex(&std::get<1>(c_utf32_1)[0], (MyUInt32)std::get<1>(c_utf32_1).size() - 1, true) << std::endl;

	auto c_utf8_4 = charset.UTF32_2_UTF8_C(&std::get<1>(c_utf32_1)[0], (MyUInt32)std::get<1>(c_utf32_1).size() - 1, true);
	if (!std::get<0>(c_utf8_4))
		std::cout << "C UTF-32 BE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C UTF-32 BE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(c_utf8_4)[0], (MyUInt32)std::get<1>(c_utf8_4).size() - 1, true) << std::endl;

	auto c_utf32_2 = charset.UTF8_2_UTF32_C(&std::get<1>(c_utf8_1)[0], (MyUInt32)std::get<1>(c_utf8_1).size() - 1, false);
	if (!std::get<0>(c_utf32_2))
		std::cout << "C UTF-8 To UTF-32 LE Failed." << std::endl;
	else
		std::cout << "C UTF-8 To UTF-32 LE:" << CStringUtils::BytesToHex(&std::get<1>(c_utf32_2)[0], (MyUInt32)std::get<1>(c_utf32_2).size() - 1, true) << std::endl;

	auto c_utf8_5 = charset.UTF32_2_UTF8_C(&std::get<1>(c_utf32_2)[0], (MyUInt32)std::get<1>(c_utf32_2).size() - 1, false);
	if (!std::get<0>(c_utf8_5))
		std::cout << "C UTF-32 LE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C UTF-32 LE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(c_utf8_5)[0], (MyUInt32)std::get<1>(c_utf8_5).size() - 1, true) << std::endl;

#else
	std::string strGBK = "我是谁";
	std::string strUTF8;
	CCharset charset;
	auto Result = charset.GBK_2_UTF8(strGBK.c_str(), (MyUInt32)strGBK.length());
	if (!std::get<0>(Result))
		std::cout << "CharsetTrans Failed" << std::endl;
	else
		strUTF8.append(&std::get<1>(Result)[0], std::get<1>(Result).size() - 1);
	std::cout << strUTF8 << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// C++
	auto cpp_unicode_1 = charset.UTF8_2_Unicode_Cpp(strUTF8.c_str());
	if (!std::get<0>(cpp_unicode_1))
		std::cout << "C++ UTF-8 To Unicode Failed." << std::endl;
	else
		std::cout << "C++ UTF-8 To Unicode:" << CStringUtils::BytesToHex(&std::get<1>(cpp_unicode_1)[0], (MyUInt32)std::get<1>(cpp_unicode_1).size() - 1, true) << std::endl;

	auto cpp_utf8_1 = charset.Unicode_2_UTF8_Cpp(&std::get<1>(cpp_unicode_1)[0]);
	if (!std::get<0>(cpp_utf8_1))
		std::cout << "C++ Unicode To UTF-8 Failed." << std::endl;
	else
		std::cout << "C++ Unicode To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf8_1)[0], (MyUInt32)std::get<1>(cpp_utf8_1).size() - 1, true) << std::endl;

	auto cpp_utf16_1 = charset.UTF8_2_UTF16_Cpp(&std::get<1>(cpp_utf8_1)[0], (MyUInt32)std::get<1>(cpp_utf8_1).size() - 1, true);
	if (!std::get<0>(cpp_utf16_1))
		std::cout << "C++ UTF-8 To UTF-16 BE Failed." << std::endl;
	else
		std::cout << "C++ UTF-8 To UTF-16 BE:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf16_1)[0], (MyUInt32)std::get<1>(cpp_utf16_1).size() - 1, true) << std::endl;

	auto cpp_utf8_2 = charset.UTF16_2_UTF8_Cpp(&std::get<1>(cpp_utf16_1)[0], (MyUInt32)std::get<1>(cpp_utf16_1).size() - 1);
	if (!std::get<0>(cpp_utf8_2))
		std::cout << "C++ UTF-16 BE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C++ UTF-16 BE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf8_2)[0], (MyUInt32)std::get<1>(cpp_utf8_2).size() - 1, true) << std::endl;

	auto cpp_utf16_2 = charset.UTF8_2_UTF16_Cpp(&std::get<1>(cpp_utf8_1)[0], (MyUInt32)std::get<1>(cpp_utf8_1).size() - 1, false);
	if (!std::get<0>(cpp_utf16_2))
		std::cout << "C++ UTF-8 To UTF-16 LE Failed." << std::endl;
	else
		std::cout << "C++ UTF-8 To UTF-16 LE:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf16_2)[0], (MyUInt32)std::get<1>(cpp_utf16_2).size() - 1, true) << std::endl;

	auto cpp_utf8_3 = charset.UTF16_2_UTF8_Cpp(&std::get<1>(cpp_utf16_1)[0], (MyUInt32)std::get<1>(cpp_utf16_1).size() - 1);
	if (!std::get<0>(cpp_utf8_3))
		std::cout << "C++ UTF-16 LE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C++ UTF-16 LE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf8_3)[0], (MyUInt32)std::get<1>(cpp_utf8_3).size() - 1, true) << std::endl;

	auto cpp_utf32_1 = charset.UTF8_2_UTF32_Cpp(&std::get<1>(cpp_utf8_1)[0], (MyUInt32)std::get<1>(cpp_utf8_1).size() - 1, true);
	if (!std::get<0>(cpp_utf32_1))
		std::cout << "C++ UTF-8 To UTF-32 BE Failed." << std::endl;
	else
		std::cout << "C++ UTF-8 To UTF-32 BE:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf32_1)[0], (MyUInt32)std::get<1>(cpp_utf32_1).size() - 1, true) << std::endl;

	auto cpp_utf8_4 = charset.UTF32_2_UTF8_Cpp(&std::get<1>(cpp_utf32_1)[0], (MyUInt32)std::get<1>(cpp_utf32_1).size() - 1);
	if (!std::get<0>(cpp_utf8_4))
		std::cout << "C++ UTF-32 BE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C++ UTF-32 BE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf8_4)[0], (MyUInt32)std::get<1>(cpp_utf8_4).size() - 1, true) << std::endl;

	auto cpp_utf32_2 = charset.UTF8_2_UTF32_Cpp(&std::get<1>(cpp_utf8_1)[0], (MyUInt32)std::get<1>(cpp_utf8_1).size() - 1, false);
	if (!std::get<0>(cpp_utf32_2))
		std::cout << "C++ UTF-8 To UTF-32 LE Failed." << std::endl;
	else
		std::cout << "C++ UTF-8 To UTF-32 LE:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf32_2)[0], (MyUInt32)std::get<1>(cpp_utf32_2).size() - 1, true) << std::endl;

	auto cpp_utf8_5 = charset.UTF32_2_UTF8_Cpp(&std::get<1>(cpp_utf32_1)[0], (MyUInt32)std::get<1>(cpp_utf32_1).size() - 1);
	if (!std::get<0>(cpp_utf8_5))
		std::cout << "C++ UTF-32 LE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C++ UTF-32 LE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(cpp_utf8_5)[0], (MyUInt32)std::get<1>(cpp_utf8_5).size() - 1, true) << std::endl;

	std::cout << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// C
	auto c_unicode_1 = charset.UTF8_2_Unicode_C(strUTF8.c_str(), (MyUInt32)strUTF8.size());
	if (!std::get<0>(c_unicode_1))
		std::cout << "C UTF-8 To Unicode Failed." << std::endl;
	else
		std::cout << "C UTF-8 To Unicode:" << CStringUtils::BytesToHex(&std::get<1>(c_unicode_1)[0], (MyUInt32)std::get<1>(c_unicode_1).size() - 1, true) << std::endl;

	auto c_utf8_1 = charset.Unicode_2_UTF8_C(&std::get<1>(c_unicode_1)[0], std::get<1>(c_unicode_1).size() - 1);
	if (!std::get<0>(c_utf8_1))
		std::cout << "C Unicode To UTF-8 Failed." << std::endl;
	else
		std::cout << "C Unicode To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(c_utf8_1)[0], (MyUInt32)std::get<1>(c_utf8_1).size() - 1, true) << std::endl;

	auto c_utf16_1 = charset.UTF8_2_UTF16_C(&std::get<1>(c_utf8_1)[0], (MyUInt32)std::get<1>(c_utf8_1).size() - 1, true);
	if (!std::get<0>(c_utf16_1))
		std::cout << "C UTF-8 To UTF-16 BE Failed." << std::endl;
	else
		std::cout << "C UTF-8 To UTF-16 BE:" << CStringUtils::BytesToHex(&std::get<1>(c_utf16_1)[0], (MyUInt32)std::get<1>(c_utf16_1).size() - 1, true) << std::endl;

	auto c_utf8_2 = charset.UTF16_2_UTF8_C(&std::get<1>(c_utf16_1)[0], (MyUInt32)std::get<1>(c_utf16_1).size() - 1, true);
	if (!std::get<0>(c_utf8_2))
		std::cout << "C UTF-16 BE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C UTF-16 BE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(c_utf8_2)[0], (MyUInt32)std::get<1>(c_utf8_2).size() - 1, true) << std::endl;

	auto c_utf16_2 = charset.UTF8_2_UTF16_C(&std::get<1>(c_utf8_1)[0], (MyUInt32)std::get<1>(c_utf8_1).size() - 1, false);
	if (!std::get<0>(c_utf16_2))
		std::cout << "C UTF-8 To UTF-16 LE Failed." << std::endl;
	else
		std::cout << "C UTF-8 To UTF-16 LE:" << CStringUtils::BytesToHex(&std::get<1>(c_utf16_2)[0], (MyUInt32)std::get<1>(c_utf16_2).size() - 1, true) << std::endl;

	auto c_utf8_3 = charset.UTF16_2_UTF8_C(&std::get<1>(c_utf16_2)[0], (MyUInt32)std::get<1>(c_utf16_2).size() - 1, false);
	if (!std::get<0>(c_utf8_3))
		std::cout << "C UTF-16 LE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C UTF-16 LE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(c_utf8_3)[0], (MyUInt32)std::get<1>(c_utf8_3).size() - 1, true) << std::endl;

	auto c_utf32_1 = charset.UTF8_2_UTF32_C(&std::get<1>(c_utf8_1)[0], (MyUInt32)std::get<1>(c_utf8_1).size() - 1, true);
	if (!std::get<0>(c_utf32_1))
		std::cout << "C UTF-8 To UTF-32 BE Failed." << std::endl;
	else
		std::cout << "C UTF-8 To UTF-32 BE:" << CStringUtils::BytesToHex(&std::get<1>(c_utf32_1)[0], (MyUInt32)std::get<1>(c_utf32_1).size() - 1, true) << std::endl;

	auto c_utf8_4 = charset.UTF32_2_UTF8_C(&std::get<1>(c_utf32_1)[0], (MyUInt32)std::get<1>(c_utf32_1).size() - 1, true);
	if (!std::get<0>(c_utf8_4))
		std::cout << "C UTF-32 BE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C UTF-32 BE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(c_utf8_4)[0], (MyUInt32)std::get<1>(c_utf8_4).size() - 1, true) << std::endl;

	auto c_utf32_2 = charset.UTF8_2_UTF32_C(&std::get<1>(c_utf8_1)[0], (MyUInt32)std::get<1>(c_utf8_1).size() - 1, false);
	if (!std::get<0>(c_utf32_2))
		std::cout << "C UTF-8 To UTF-32 LE Failed." << std::endl;
	else
		std::cout << "C UTF-8 To UTF-32 LE:" << CStringUtils::BytesToHex(&std::get<1>(c_utf32_2)[0], (MyUInt32)std::get<1>(c_utf32_2).size() - 1, true) << std::endl;

	auto c_utf8_5 = charset.UTF32_2_UTF8_C(&std::get<1>(c_utf32_2)[0], (MyUInt32)std::get<1>(c_utf32_2).size() - 1, false);
	if (!std::get<0>(c_utf8_5))
		std::cout << "C UTF-32 LE To UTF-8 Failed." << std::endl;
	else
		std::cout << "C UTF-32 LE To UTF-8:" << CStringUtils::BytesToHex(&std::get<1>(c_utf8_5)[0], (MyUInt32)std::get<1>(c_utf8_5).size() - 1, true) << std::endl;
#endif
}

void CCharsetTest::TestCharset2()
{
#if defined (_WIN32)
	std::string strGB2312 = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\gb2312.txt";
	std::string strUnicode = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\unicode_1.txt";
	std::string strUTF8 = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\utf8_1.txt";
	std::string strGB2312_Output = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\gb2312_1.txt";
#else
	std::string strGB2312 = "/home/ljj/self/C++/BaseLibrary/Test/iconv/gb2312.txt";
	std::string strUnicode = "/home/ljj/self/C++/BaseLibrary/Test/iconv/unicode_1.txt";
	std::string strUTF8 = "/home/ljj/self/C++/BaseLibrary/Test/iconv/utf8_1.txt";
	std::string strGB2312_Output = "/home/ljj/self/C++/BaseLibrary/Test/iconv/gb2312_1.txt";
#endif

	std::ifstream file_input;
	file_input.open(strGB2312.c_str(), std::ios::in);
	if (!file_input.is_open())
	{
		std::cout << "open input file failed. input file:" << strGB2312 << std::endl;
		return;
	}

	std::ofstream file_unicode;
	file_unicode.open(strUnicode.c_str(), std::ios::out);
	if (!file_unicode.is_open())
	{
		std::cout << "open output file failed. output file:" << strUnicode << std::endl;
		return;
	}

	std::ofstream file_utf8;
	file_utf8.open(strUTF8.c_str(), std::ios::out);
	if (!file_utf8.is_open())
	{
		std::cout << "open output file failed. output file:" << strUTF8 << std::endl;
		return;
	}

	std::ofstream file_gb2312;
	file_gb2312.open(strGB2312_Output.c_str(), std::ios::out);
	if (!file_gb2312.is_open())
	{
		std::cout << "open output file failed. output file:" << strGB2312_Output << std::endl;
		return;
	}

	CCharset charset;
	std::string strReadLine;
	while (std::getline(file_input, strReadLine))
	{
		MyUInt16 iGB2312 = CStringUtils::HexString2Value<MyUInt16>(strReadLine);

		char GB2312[sizeof(MyUInt16) + 1]{};
		GB2312[0] = (iGB2312 >> 8);
		GB2312[1] = (iGB2312 & 0x00FF);

		auto Result1 = charset.GB2312_2_Unicode(GB2312, sizeof(MyUInt16));
		if (!std::get<0>(Result1))
		{
			file_unicode << "" << std::endl;
		}
		else
		{
			std::string strHexString = CStringUtils::BytesToHex(&std::get<1>(Result1)[0], (MyUInt32)std::get<1>(Result1).size() - 1, true);
			file_unicode << strHexString << std::endl;
		}

		auto Result2 = charset.GB2312_2_UTF8(GB2312, sizeof(MyUInt16));
		if (!std::get<0>(Result2))
		{
			file_utf8 << "" << std::endl;
		}
		else
		{
			std::string strHexString = CStringUtils::BytesToHex(&std::get<1>(Result2)[0], (MyUInt32)std::get<1>(Result2).size() - 1, true);
			file_utf8 << strHexString << std::endl;
		}

		auto Result3 = charset.UTF8_2_GB2312(&std::get<1>(Result2)[0], (MyUInt32)std::get<1>(Result2).size() - 1);
		if (!std::get<0>(Result3))
		{
			file_gb2312 << "" << std::endl;
		}
		else
		{
			std::string strHexString = CStringUtils::BytesToHex(&std::get<1>(Result3)[0], (MyUInt32)std::get<1>(Result3).size() - 1, true);
			file_gb2312 << strHexString << std::endl;
		}
	}
}

void CCharsetTest::TestCharset3()
{
#if defined (_WIN32)
	std::string strGBK = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\gbk.txt";
	std::string strUnicode = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\unicode_2.txt";
	std::string strUTF8 = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\utf8_2.txt";
	std::string strGBK_Output = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\gbk_2.txt";
#else
	std::string strGBK = "/home/ljj/self/C++/BaseLibrary/Test/iconv/gbk.txt";
	std::string strUnicode = "/home/ljj/self/C++/BaseLibrary/Test/iconv/unicode_2.txt";
	std::string strUTF8 = "/home/ljj/self/C++/BaseLibrary/Test/iconv/utf8_2.txt";
	std::string strGBK_Output = "/home/ljj/self/C++/BaseLibrary/Test/iconv/gbk_2.txt";
#endif

	std::ifstream file_input;
	file_input.open(strGBK.c_str(), std::ios::in);
	if (!file_input.is_open())
	{
		std::cout << "open input file failed. input file:" << strGBK << std::endl;
		return;
	}

	std::ofstream file_unicode;
	file_unicode.open(strUnicode.c_str(), std::ios::out);
	if (!file_unicode.is_open())
	{
		std::cout << "open output file failed. output file:" << strUnicode << std::endl;
		return;
	}

	std::ofstream file_utf8;
	file_utf8.open(strUTF8.c_str(), std::ios::out);
	if (!file_utf8.is_open())
	{
		std::cout << "open output file failed. output file:" << strUTF8 << std::endl;
		return;
	}

	std::ofstream file_gbk;
	file_gbk.open(strGBK_Output.c_str(), std::ios::out);
	if (!file_gbk.is_open())
	{
		std::cout << "open output file failed. output file:" << strGBK_Output << std::endl;
		return;
	}

	CCharset charset;
	std::string strReadLine;
	while (std::getline(file_input, strReadLine))
	{
		MyUInt16 iGBK = CStringUtils::HexString2Value<MyUInt16>(strReadLine);

		char GBK[sizeof(MyUInt16) + 1]{};
		GBK[0] = (iGBK >> 8);
		GBK[1] = (iGBK & 0x00FF);

		auto Result1 = charset.GBK_2_Unicode(GBK, sizeof(MyUInt16));
		if (!std::get<0>(Result1))
		{
			file_unicode << "" << std::endl;
		}
		else
		{
			std::string strHexString = CStringUtils::BytesToHex(&std::get<1>(Result1)[0], (MyUInt32)std::get<1>(Result1).size() - 1, true);
			file_unicode << strHexString << std::endl;
		}

		auto Result2 = charset.GBK_2_UTF8(GBK, sizeof(MyUInt16));
		if (!std::get<0>(Result2))
		{
			file_utf8 << "" << std::endl;
		}
		else
		{
			std::string strHexString = CStringUtils::BytesToHex(&std::get<1>(Result2)[0], (MyUInt32)std::get<1>(Result2).size() - 1, true);
			file_utf8 << strHexString << std::endl;
		}

		auto Result3 = charset.UTF8_2_GBK(&std::get<1>(Result2)[0], (MyUInt32)std::get<1>(Result2).size() - 1);
		if (!std::get<0>(Result3))
		{
			file_gbk << "" << std::endl;
		}
		else
		{
			std::string strHexString = CStringUtils::BytesToHex(&std::get<1>(Result3)[0], (MyUInt32)std::get<1>(Result3).size() - 1, true);
			file_gbk << strHexString << std::endl;
		}
	}
}

void CCharsetTest::TestCharset4()
{
#if defined (_WIN32)
	std::string strGB18030 = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\gb18030.txt";
	std::string strUnicode = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\unicode_3.txt";
	std::string strUTF8 = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\utf8_3.txt";
	std::string strGB18030_Output = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\gb18030_3.txt";
#else
	std::string strGB18030 = "/home/ljj/self/C++/BaseLibrary/Test/iconv/gb18030.txt";
	std::string strUnicode = "/home/ljj/self/C++/BaseLibrary/Test/iconv/unicode_3.txt";
	std::string strUTF8 = "/home/ljj/self/C++/BaseLibrary/Test/iconv/utf8_3.txt";
	std::string strGB18030_Output = "/home/ljj/self/C++/BaseLibrary/Test/iconv/gb18030_3.txt";
#endif

	std::ifstream file_input;
	file_input.open(strGB18030.c_str(), std::ios::in);
	if (!file_input.is_open())
	{
		std::cout << "open input file failed. input file:" << strGB18030 << std::endl;
		return;
	}

	std::ofstream file_unicode;
	file_unicode.open(strUnicode.c_str(), std::ios::out);
	if (!file_unicode.is_open())
	{
		std::cout << "open output file failed. output file:" << strUnicode << std::endl;
		return;
	}

	std::ofstream file_utf8;
	file_utf8.open(strUTF8.c_str(), std::ios::out);
	if (!file_utf8.is_open())
	{
		std::cout << "open output file failed. output file:" << strUTF8 << std::endl;
		return;
	}

	std::ofstream file_gb18030;
	file_gb18030.open(strGB18030_Output.c_str(), std::ios::out);
	if (!file_gb18030.is_open())
	{
		std::cout << "open output file failed. output file:" << strGB18030_Output << std::endl;
		return;
	}

	CCharset charset;
	MyUInt32 iLine = 0;
	std::string strReadLine;
	while (std::getline(file_input, strReadLine))
	{
		++iLine;

		if (iLine <= 21897)
		{
			MyUInt16 iGB18030 = CStringUtils::HexString2Value<MyUInt16>(strReadLine);

			char GB18030[sizeof(MyUInt16) + 1]{};
			GB18030[0] = (iGB18030 >> 8);
			GB18030[1] = (iGB18030 & 0x00FF);

			auto Result1 = charset.GB18030_2_Unicode(GB18030, sizeof(MyUInt16));
			if (!std::get<0>(Result1))
			{
				file_unicode << "" << std::endl;
			}
			else
			{
				std::string strHexString = CStringUtils::BytesToHex(&std::get<1>(Result1)[0], (MyUInt32)std::get<1>(Result1).size() - 1, true);
				file_unicode << strHexString << std::endl;
			}

			auto Result2 = charset.GB18030_2_UTF8(GB18030, sizeof(MyUInt16));
			if (!std::get<0>(Result2))
			{
				file_utf8 << "" << std::endl;
			}
			else
			{
				std::string strHexString = CStringUtils::BytesToHex(&std::get<1>(Result2)[0], (MyUInt32)std::get<1>(Result2).size() - 1, true);
				file_utf8 << strHexString << std::endl;
			}

			auto Result3 = charset.UTF8_2_GB18030(&std::get<1>(Result2)[0], (MyUInt32)std::get<1>(Result2).size() - 1);
			if (!std::get<0>(Result3))
			{
				file_gb18030 << "" << std::endl;
			}
			else
			{
				std::string strHexString = CStringUtils::BytesToHex(&std::get<1>(Result3)[0], (MyUInt32)std::get<1>(Result3).size() - 1, true);
				file_gb18030 << strHexString << std::endl;
			}
		}
		else
		{
			MyUInt32 iGB18030 = CStringUtils::HexString2Value<MyUInt32>(strReadLine);

			char GB18030[sizeof(MyUInt32) + 1]{};
			GB18030[0] = (char)(iGB18030 >> 24);
			GB18030[1] = (char)((iGB18030 >> 16) & 0x00FF);
			GB18030[2] = (char)((iGB18030 >> 8) & 0x0000FF);
			GB18030[3] = (char)(iGB18030 & 0x000000FF);

			auto Result1 = charset.GB18030_2_Unicode(GB18030, sizeof(MyUInt32));
			if (!std::get<0>(Result1))
			{
				file_unicode << "" << std::endl;
			}
			else
			{
				std::string strHexString = CStringUtils::BytesToHex(&std::get<1>(Result1)[0], (MyUInt32)std::get<1>(Result1).size() - 1, true);
				file_unicode << strHexString << std::endl;
			}

			auto Result2 = charset.GB18030_2_UTF8(GB18030, sizeof(MyUInt32));
			if (!std::get<0>(Result2))
			{
				file_utf8 << "" << std::endl;
			}
			else
			{
				std::string strHexString = CStringUtils::BytesToHex(&std::get<1>(Result2)[0], (MyUInt32)std::get<1>(Result2).size() - 1, true);
				file_utf8 << strHexString << std::endl;
			}

			auto Result3 = charset.UTF8_2_GB18030(&std::get<1>(Result2)[0], (MyUInt32)std::get<1>(Result2).size() - 1);
			if (!std::get<0>(Result3))
			{
				file_gb18030 << "" << std::endl;
			}
			else
			{
				std::string strHexString = CStringUtils::BytesToHex(&std::get<1>(Result3)[0], (MyUInt32)std::get<1>(Result3).size() - 1, true);
				file_gb18030 << strHexString << std::endl;
			}
		}
	}
}