// 字节序转换
template <typename T>
T CByteOrderUtils::ByteOrderTrans(T aValue)
{
	// 只支持16位整数,32位整数,64位整数的转换
	static_assert(!(!sfinae::is_16<T>::value && !sfinae::is_32<T>::value && !sfinae::is_64<T>::value), "CByteOrderUtils::ByteOrderTrans Not Support!");

	constexpr int iSize = sizeof(T);
	char szBuffBefore[iSize]{};
	char szBuffAfter[iSize]{};
	memcpy(szBuffBefore, &aValue, iSize);
	for (int i = 0; i < iSize; ++i)
		szBuffAfter[iSize - 1 - i] = szBuffBefore[i];

	T Result{};
	memcpy(&Result, szBuffAfter, iSize);
	return Result;
}

// 获取8位数值中的数据
template <typename Src, typename Dst>
Dst CByteOrderUtils::GetValue(Src aSrcValue, Dst aDstValue, const std::bitset<8>& aMask, ENUM_SHIFT_TYPE aType, MyUInt16 aiShiftCount)
{
	// 只支持8位整数
	static_assert(sfinae::is_8<Src>::value, "CByteOrderUtils::GetValue Not Support!");

	Src mask = (Src)aMask.to_ulong();
	Dst Result{};
	if (aType == ENUM_SHIFT_TYPE::Default)
		Result = (Dst)(aSrcValue & mask);
	else if (aType == ENUM_SHIFT_TYPE::Left)
		Result = (Dst)((aSrcValue & mask) << aiShiftCount);
	else if (aType == ENUM_SHIFT_TYPE::Right)
		Result = (Dst)((aSrcValue & mask) >> aiShiftCount);
	return Result;
}

// 获取16位数值中的数据
template <typename T>
T CByteOrderUtils::GetValue(T aValue, const std::bitset<16>& aMask, ENUM_SHIFT_TYPE aType, MyUInt16 aiShiftCount)
{
	// 只支持16位整数
	static_assert(sfinae::is_16<T>::value, "CByteOrderUtils::GetValue Not Support!");

	T mask = (T)aMask.to_ulong();
	T Result{};
	if (aType == ENUM_SHIFT_TYPE::Default)
		Result = (T)(aValue & mask);
	else if (aType == ENUM_SHIFT_TYPE::Left)
		Result = (T)((aValue & mask) << aiShiftCount);
	else if (aType == ENUM_SHIFT_TYPE::Right)
		Result = (T)((aValue & mask) >> aiShiftCount);
	return Result;
}