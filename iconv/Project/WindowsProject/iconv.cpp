// iconv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdint>
#include "iconv.h"

#ifdef _DEBUG
    #pragma comment(lib, "libiconv64D.lib")
#else
    #pragma comment(lib, "libiconv64.lib")
#endif

template <typename T>
static T HexString2Value(const std::string& astrValue)
{
	T value{};
	std::istringstream is(astrValue);
	is >> std::hex >> value;
	return value;
}

template <typename T>
static std::string BytesToHex(const T* apData, uint32_t aiDataLen, bool abUpcase)
{
	std::string strText;

	constexpr char DigitUpper[] = "0123456789ABCDEF";
	constexpr char DigitLower[] = "0123456789abcdef";
	const char* pDigit = abUpcase ? DigitUpper : DigitLower;

	// 这里没有使用CStringUtils::Value2HexString来处理,是因为发现char32_t在转换时不准确
	if (sizeof(T) == 1)
	{
		for (uint32_t i = 0; i < aiDataLen; ++i)
		{
			uint8_t iTemp = (uint8_t)apData[i];
			strText += pDigit[(iTemp & 0xF0) >> 4];
			strText += pDigit[iTemp & 0x0F];
		}
	}
	else if (sizeof(T) == 2)
	{
		for (uint32_t i = 0; i < aiDataLen; ++i)
		{
			uint16_t iValue = (uint16_t)apData[i];
			uint8_t iTemp = (uint8_t)(iValue >> 8);
			strText += pDigit[(iTemp & 0xF0) >> 4];
			strText += pDigit[iTemp & 0x0F];

			iTemp = (uint8_t)(iValue & 0x00FF);
			strText += pDigit[(iTemp & 0xF0) >> 4];
			strText += pDigit[iTemp & 0x0F];
		}
	}
	else if (sizeof(T) == 4)
	{
		for (uint32_t i = 0; i < aiDataLen; ++i)
		{
			uint32_t iValue = (uint32_t)apData[i];
			uint8_t iTemp1 = (uint8_t)(iValue >> 24);
			strText += pDigit[(iTemp1 & 0xF0) >> 4];
			strText += pDigit[iTemp1 & 0x0F];

			uint32_t iTemp2 = (iValue >> 16);
			iTemp1 = (uint8_t)(iTemp2 & 0x0000FFFF);
			strText += pDigit[(iTemp1 & 0xF0) >> 4];
			strText += pDigit[iTemp1 & 0x0F];

			iTemp2 = (iValue >> 8);
			iTemp1 = (uint8_t)(iTemp2 & 0x00FFFFFF);
			strText += pDigit[(iTemp1 & 0xF0) >> 4];
			strText += pDigit[iTemp1 & 0x0F];

			iTemp1 = (uint8_t)(iValue & 0x000000FF);
			strText += pDigit[(iTemp1 & 0xF0) >> 4];
			strText += pDigit[iTemp1 & 0x0F];
		}
	}

	return strText;
}

static void GBK2Other(const std::string& astrFromCode, const std::string& astrToCode, const std::string& astrInputFile, const std::string& astrOutputFile)
{
	iconv_t cd = iconv_open(astrToCode.c_str(), astrFromCode.c_str());
	if (cd == (iconv_t)(-1))
	{
		std::cout << "iconv_open failed. ErrorCode:" << errno << ", FromCode:" << astrFromCode << ", ToCode:" << astrToCode << std::endl;
		return;
	}

	do
	{
		std::ifstream file_input;
		file_input.open(astrInputFile.c_str(), std::ios::in);
		if (!file_input.is_open())
		{
			std::cout << "open input file failed. input file:" << astrInputFile << std::endl;
			break;
		}

		std::ofstream file_output;
		file_output.open(astrOutputFile.c_str(), std::ios::out);
		if (!file_output.is_open())
		{
			std::cout << "open output file failed. output file:" << astrOutputFile << std::endl;
			break;
		}

		std::string strReadLine;
		while (std::getline(file_input, strReadLine))
		{
			uint16_t iGBK = HexString2Value<uint16_t>(strReadLine);

			char GBK[sizeof(uint16_t) + 1]{};
			GBK[0] = (iGBK >> 8);
			GBK[1] = (iGBK & 0x00FF);

			std::size_t iSrcValueSize = sizeof(uint16_t);
			std::size_t iExpectValueSize = iSrcValueSize * MB_LEN_MAX;
			std::size_t iDstValueSize = iExpectValueSize;
			std::shared_ptr<char[]> pValue = std::make_shared<char[]>(iExpectValueSize);
			if (pValue == nullptr)
			{
				std::cout << "alloc failed." << " FromCode:" << astrFromCode << ", ToCode:" << astrToCode << std::endl;
				break;
			}

			char* pSrcValue = const_cast<char*>(GBK);
			char* pDstValue = pValue.get();
			std::string strUTF8;
			std::size_t iSize = iconv(cd, &pSrcValue, &iSrcValueSize, &pDstValue, &iDstValueSize);
			// iconv会移动pDstValue和iDstValueSize的值,iDstValueSize表示最后剩下的字符数
			if (iSize >= 0)
			{
				strUTF8.append(pValue.get(), (iExpectValueSize - iDstValueSize));
			}
			else
			{
				std::cout << "iconv failed. ErrorCode:" << errno << ", FromCode:" << astrFromCode << ", ToCode:" << astrToCode << std::endl;
				break;
			}

			std::string strHexString = BytesToHex(strUTF8.c_str(), (uint32_t)strUTF8.length(), true);
			file_output << strHexString << std::endl;
		}
	} while (false);

	iconv_close(cd);
}

int main()
{
	std::string strGBK = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\gb18030.txt";
	std::string strUnicode = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\unicode.txt";
	std::string strUTF8 = "D:\\Code\\self\\C++\\BaseLibrary\\Test\\iconv\\utf8.txt";

	//std::string strGBK = "D:\\Code\\C++\\BaseLibrary\\Test\\iconv\\gbk.txt";
	//std::string strUnicode = "D:\\Code\\C++\\BaseLibrary\\Test\\iconv\\unicode.txt";
	//std::string strUTF8 = "D:\\Code\\C++\\BaseLibrary\\Test\\iconv\\utf8.txt";

	// windows 11测试结果:Unicode缺少95个汉字,这些汉字都映射到了PUA区(见"gbk.xls"的"映射到PUA的GBK字符"部分)
	GBK2Other("GBK", "UCS-2", strGBK.c_str(), strUnicode.c_str());
	// windows 11测试结果:与上面一样,UTF-8也缺少95个汉字
	GBK2Other("GBK", "UTF-8", strGBK.c_str(), strUTF8.c_str());
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
