namespace string_to_value
{

template <typename T, typename = void>
struct trans_value
{
	inline void operator() (const std::string& astrValue, T& aValue)
	{
		std::istringstream is(astrValue);
		is >> aValue;
	}
};

template <typename T>
struct trans_value<T, std::enable_if_t<sfinae::is_u8<T>::value>>
{
	inline void operator() (const std::string& astrValue, T& aValue)
	{
		std::istringstream is(astrValue);
		MyUInt32 iTemp = 0;
		is >> iTemp;
		aValue = (MyUInt8)iTemp;
	}
};

template <typename T>
struct trans_value<T, std::enable_if_t<sfinae::is_i8<T>::value>>
{
	inline void operator() (const std::string& astrValue, T& aValue)
	{
		std::istringstream is(astrValue);
		MyInt32 iTemp = 0;
		is >> iTemp;
		aValue = (MyInt8)iTemp;
	}
};

template <typename T>
struct trans_value<T, std::enable_if_t<sfinae::is_string<T>::value>>
{
	inline void operator() (const std::string& astrValue, T& aValue)
	{
		aValue = astrValue;
	}
};

}

// 从string转值
template <typename T>
void CStringUtils::String2Value(const std::string& astrValue, T& aValue)
{
	string_to_value::trans_value<T>()(astrValue, aValue);
}

template <typename T>
void CStringUtils::String2Value(const char* apValue, MyUInt32 aiValueLen, T& aValue, int aBase, std::chars_format aFmt)
{
	CHECK_OBJECT_AND_LEN_NO_RETURN_VALUE(apValue, aiValueLen, UtilsMod_String);
	if constexpr (sfinae::is_float<T>::value || sfinae::is_double<T>::value || std::is_same<T, long double>::value)
	{
		if (auto [p, ec] = std::from_chars(apValue, apValue + aiValueLen, aValue, aFmt); ec != std::errc())
			LogSKV(Error, UtilsMod_String, "CStringUtils::String2Value from_chars Failed", "Value", apValue);
	}
	else
	{
		if (auto [p, ec] = std::from_chars(apValue, apValue + aiValueLen, aValue, aBase); ec != std::errc())
			LogSKV(Error, UtilsMod_String, "CStringUtils::String2Value from_chars Failed", "Value", apValue);
	}
}

// 从值转string
template <typename T>
std::string CStringUtils::Value2String(const T& aValue)
{
	std::ostringstream os;
	if constexpr (sfinae::is_8<T>::value)
	{
		MyInt32 iValue = aValue;
		os << iValue;
	}
	else
	{
		os << aValue;
	}
	return os.str();
}

template <typename T>
void CStringUtils::Value2String(char* apValue, MyUInt32 aiValueLen, const T& aValue, int aBase, std::chars_format aFmt, int aPrecision)
{
	CHECK_OBJECT_AND_LEN_NO_RETURN_VALUE(apValue, aiValueLen, UtilsMod_String);
	if constexpr (sfinae::is_bool<T>::value)
	{
		static_assert(false, "CStringUtils::Value2String type error!");
		return;
	}
	else if constexpr (sfinae::is_float<T>::value || sfinae::is_double<T>::value || std::is_same<T, long double>::value)
	{
		if (auto [p, ec] = std::to_chars(apValue, apValue + aiValueLen, aValue, aFmt, aPrecision); ec != std::errc())
			LogF(Error, UtilsMod_String, "CStringUtils::Value2String to_chars(fmt) Failed!");
	}
	else
	{
		if (auto [p, ec] = std::to_chars(apValue, apValue + aiValueLen, aValue, aBase); ec != std::errc())
			LogF(Error, UtilsMod_String, "CStringUtils::Value2String to_chars(base) Failed!");
	}
}

// 从值转16进制string
template <typename T>
std::string CStringUtils::Value2HexString(const T& aValue, bool abNeedHeader, bool abUpcase)
{
	std::ostringstream os;
	if constexpr (sfinae::is_8<T>::value)
	{
		MyInt16 iValue = aValue;
		if (abNeedHeader)
		{
			if (abUpcase)
				os << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << iValue;
			else
				os << "0x" << std::hex << std::nouppercase << std::setfill('0') << std::setw(2) << iValue;
		}
		else
		{
			if (abUpcase)
				os << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << iValue;
			else
				os << std::hex << std::nouppercase << std::setfill('0') << std::setw(2) << iValue;
		}
	}
	else if constexpr (sfinae::is_16<T>::value)
	{
		if (abNeedHeader)
		{
			if (abUpcase)
				os << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << aValue;
			else
				os << "0x" << std::hex << std::nouppercase << std::setfill('0') << std::setw(4) << aValue;
		}
		else
		{
			if (abUpcase)
				os << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << aValue;
			else
				os << std::hex << std::nouppercase << std::setfill('0') << std::setw(4) << aValue;
		}
	}
	else if constexpr (sfinae::is_32<T>::value)
	{
		if (abNeedHeader)
		{
			if (abUpcase)
				os << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(8) << aValue;
			else
				os << "0x" << std::hex << std::nouppercase << std::setfill('0') << std::setw(8) << aValue;
		}
		else
		{
			if (abUpcase)
				os << std::hex << std::uppercase << std::setfill('0') << std::setw(8) << aValue;
			else
				os << std::hex << std::nouppercase << std::setfill('0') << std::setw(8) << aValue;
		}
	}
	else if constexpr (sfinae::is_64<T>::value)
	{
		if (abNeedHeader)
		{
			if (abUpcase)
				os << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(16) << aValue;
			else
				os << "0x" << std::hex << std::nouppercase << std::setfill('0') << std::setw(16) << aValue;
		}
		else
		{
			if (abUpcase)
				os << std::hex << std::uppercase << std::setfill('0') << std::setw(16) << aValue;
			else
				os << std::hex << std::nouppercase << std::setfill('0') << std::setw(16) << aValue;
		}
	}
	return os.str();
}

// 从16进制string转值
template <typename T>
T CStringUtils::HexString2Value(const std::string& astrValue)
{
	T value{};
	std::istringstream is(astrValue);
	is >> std::hex >> value;
	return value;
}

// 将字节数组转为16进制的文本
template <typename T>
std::string CStringUtils::BytesToHex(const T* apData, MyUInt32 aiDataLen, bool abUpcase)
{
	std::string strText;

	constexpr char DigitUpper[] = "0123456789ABCDEF";
	constexpr char DigitLower[] = "0123456789abcdef";
	const char* pDigit = abUpcase ? DigitUpper : DigitLower;

	// 这里没有使用CStringUtils::Value2HexString来处理,是因为发现char32_t在转换时不准确
	if (sizeof(T) == 1)
	{
		for (MyUInt32 i = 0; i < aiDataLen; ++i)
		{
			MyUInt8 iTemp = (MyUInt8)apData[i];
			strText += pDigit[(iTemp & 0xF0) >> 4];
			strText += pDigit[iTemp & 0x0F];
		}
	}
	else if (sizeof(T) == 2)
	{
		for (MyUInt32 i = 0; i < aiDataLen; ++i)
		{
			MyUInt16 iValue = (MyUInt16)apData[i];
			MyUInt8 iTemp = (MyUInt8)(iValue >> 8);
			strText += pDigit[(iTemp & 0xF0) >> 4];
			strText += pDigit[iTemp & 0x0F];

			iTemp = (MyUInt8)(iValue & 0x00FF);
			strText += pDigit[(iTemp & 0xF0) >> 4];
			strText += pDigit[iTemp & 0x0F];
		}
	}
	else if (sizeof(T) == 4)
	{
		for (MyUInt32 i = 0; i < aiDataLen; ++i)
		{
			MyUInt32 iValue = (MyUInt32)apData[i];
			MyUInt8 iTemp1 = (MyUInt8)(iValue >> 24);
			strText += pDigit[(iTemp1 & 0xF0) >> 4];
			strText += pDigit[iTemp1 & 0x0F];

			MyUInt32 iTemp2 = (iValue >> 16);
			iTemp1 = (MyUInt8)(iTemp2 & 0x0000FFFF);
			strText += pDigit[(iTemp1 & 0xF0) >> 4];
			strText += pDigit[iTemp1 & 0x0F];

			iTemp2 = (iValue >> 8);
			iTemp1 = (MyUInt8)(iTemp2 & 0x00FFFFFF);
			strText += pDigit[(iTemp1 & 0xF0) >> 4];
			strText += pDigit[iTemp1 & 0x0F];

			iTemp1 = (MyUInt8)(iValue & 0x000000FF);
			strText += pDigit[(iTemp1 & 0xF0) >> 4];
			strText += pDigit[iTemp1 & 0x0F];
		}
	}

	return strText;
}