#include <string.h>
#include <regex>
#include "Utils/StringUtils.h"

// 去除字符串首位的指定字符
void CStringUtils::TrimLeft(std::string& astrValue, const std::string& astrDelimiter)
{
	if (astrValue.empty())
		return;
	astrValue.erase(0, astrValue.find_first_not_of(astrDelimiter));
}

// 去除字符串末位的指定字符
void CStringUtils::TrimRight(std::string& astrValue, const std::string& astrDelimiter)
{
	if (astrValue.empty())
		return;
	astrValue.erase(astrValue.find_last_not_of(astrDelimiter) + 1);
}

// 去除字符串首末位指定字符
void CStringUtils::Trim(std::string& astrValue, const std::string& astrDelimiter)
{
	if (astrValue.empty())
		return;
	TrimLeft(astrValue, astrDelimiter);
	TrimRight(astrValue, astrDelimiter);
}

// 字符串转小写
void CStringUtils::ToLower(std::string& astrValue)
{
	std::transform(astrValue.begin(), astrValue.end(), astrValue.begin(), ::tolower);
}

// 字符串转大写
void CStringUtils::ToUpper(std::string& astrValue)
{
	std::transform(astrValue.begin(), astrValue.end(), astrValue.begin(), ::toupper);
}

// 按拆分字符拆分一个字符串
std::tuple<bool, std::string, std::string> CStringUtils::SplitString(const std::string& astrValue, const std::string& astrSplit)
{
	std::vector<std::string> Result{};
	if (!SplitString(astrValue, astrSplit, Result))
		return std::make_tuple(false, std::string{}, std::string{});
	if (Result.size() != 2)
		return std::make_tuple(false, std::string{}, std::string{});
	return std::make_tuple(true, Result[0], Result[1]);
}

// 按拆分字符拆分一个字符串
bool CStringUtils::SplitString(const std::string& astrValue, const std::string& astrSplit, std::vector<std::string>& aResult)
{
	if (astrValue.empty())
		return false;
	// 对于正则表达式拆分字符不能是".",因为"."在正则表达式中有特殊含义,对于这种情况只能使用原始的字符串拆分
	if (!IsHaveSubString(astrSplit, "."))
	{
		std::regex separator(astrSplit);
		std::sregex_token_iterator it(astrValue.begin(), astrValue.end(), separator, -1);
		std::sregex_token_iterator end;
		while (it != end)
		{
			std::string strValue(*it++);
			Trim(strValue);
			aResult.emplace_back(std::move(strValue));
		}
	}
	else
	{
		std::string::size_type pos1 = 0, pos2 = astrValue.find(astrSplit);
		while (std::string::npos != pos2)
		{
			aResult.emplace_back(astrValue.substr(pos1, pos2 - pos1));
			pos1 = pos2 + astrSplit.size();
			pos2 = astrValue.find(astrSplit, pos1);
		}

		if (pos1 != astrValue.length())
			aResult.emplace_back(astrValue.substr(pos1));
	}
	return (aResult.empty() ? false : true);
}

// 从string转char*
void CStringUtils::String2CharArray(const std::string& astrValue, char* apValue, MyUInt32 aiValueLen)
{
	if (astrValue.empty() || apValue == nullptr || aiValueLen == 0)
		return;
	if (astrValue.length() >= aiValueLen)
		memcpy(apValue, astrValue.c_str(), aiValueLen);
	else
		memcpy(apValue, astrValue.c_str(), astrValue.length());
}

// 从char*转char*
void CStringUtils::CharArray2CharArray(const char* apSrcValue, MyUInt32 aiSrcValueLen, char* apDstValue, MyUInt32 aiDstValueLen)
{
	if (apSrcValue == nullptr || aiSrcValueLen == 0 || apDstValue == nullptr || aiDstValueLen == 0)
		return;
	if (aiSrcValueLen >= aiDstValueLen)
		memcpy(apDstValue, apSrcValue, aiDstValueLen);
	else
		memcpy(apDstValue, apSrcValue, aiSrcValueLen);
}

// 替换字符串
std::string CStringUtils::Replace(const std::string& astrValue, const std::string& astrBefore, const std::string& astrAfter)
{
	std::string strReturn = astrValue;
	std::size_t pos = 0;
	do
	{
		pos = strReturn.find(astrBefore, pos);
		if (pos == std::string::npos)
			break;
		strReturn.replace(pos, astrBefore.length(), astrAfter);
	} while (true);
	return strReturn;
}

// 是否为数字
bool CStringUtils::IsNumber(const std::string& astrValue)
{
	for (auto c : astrValue)
	{
		if (!isdigit(c))
			return false;
	}
	return true;
}

// 是否存在子值
bool CStringUtils::IsHaveSubString(const std::string& astrValue, const std::string& astrSubValue)
{
	auto pos = astrValue.find(astrSubValue);
	return (pos == std::string::npos) ? false : true;
}