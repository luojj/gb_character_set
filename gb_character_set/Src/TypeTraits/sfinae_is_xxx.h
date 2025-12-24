// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：sfinae_is_xxx.h
// 创建日期：2023-05-05
// 创建人：罗俊杰
// 文件说明：SFINAE即匹配失败不是错误,这里判断是否为某个数据类型
// $_FILEHEADER_END ***********************************************************

#ifndef SFINAE_IS_XXX_H
#define SFINAE_IS_XXX_H

#include <cstdint>
#include <type_traits>
#include <string>
#include <vector>
#include <forward_list>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>

namespace sfinae
{

////////////////////////////////////////////////////////////////////////////////////////////////////
// 基础类型
template <typename Type, std::size_t Size, typename Decayed = typename std::decay_t<Type>>
struct is_unsigned_integral
{
	static constexpr bool value = std::is_integral_v<Decayed> && std::is_unsigned_v<Decayed> && sizeof(Decayed) == Size;
};

template <typename Type, std::size_t Size, typename Decayed = typename std::decay_t<Type>>
struct is_signed_integral
{
	static constexpr bool value = std::is_integral_v<Decayed> && std::is_signed_v<Decayed> && sizeof(Decayed) == Size;
};

template <typename Type, typename Decayed = typename std::decay_t<Type>>
struct is_bool
{
	static constexpr bool value = std::is_same_v<bool, Decayed>;
};

template <typename Type>
struct is_u8
{
	static constexpr bool value = is_unsigned_integral<Type, 1>::value && !is_bool<Type>::value;
};

template <typename Type>
struct is_i8
{
	static constexpr bool value = is_signed_integral<Type, 1>::value && !is_bool<Type>::value;
};

template <typename Type>
struct is_8
{
	static constexpr bool value = (is_u8<Type>::value || is_i8<Type>::value);
};

template <typename Type>
struct is_u16
{
	static constexpr bool value = is_unsigned_integral<Type, 2>::value;
};

template <typename Type>
struct is_i16
{
	static constexpr bool value = is_signed_integral<Type, 2>::value;
};

template <typename Type>
struct is_16
{
	static constexpr bool value = (is_u16<Type>::value || is_i16<Type>::value);
};

template <typename Type>
struct is_u32
{
	static constexpr bool value = is_unsigned_integral<Type, 4>::value;
};

template <typename Type>
struct is_i32
{
	static constexpr bool value = is_signed_integral<Type, 4>::value;
};

template <typename Type>
struct is_32
{
	static constexpr bool value = (is_u32<Type>::value || is_i32<Type>::value);
};

template <typename Type>
struct is_u64
{
	static constexpr bool value = is_unsigned_integral<Type, 8>::value;
};

template <typename Type>
struct is_i64
{
	static constexpr bool value = is_signed_integral<Type, 8>::value;
};

template <typename Type>
struct is_64
{
	static constexpr bool value = (is_u64<Type>::value || is_i64<Type>::value);
};

template <typename Type, typename Decayed = typename std::decay_t<Type>>
struct is_float
{
	static constexpr bool value = std::is_same_v<float, Decayed>;
};

template <typename Type, typename Decayed = typename std::decay_t<Type>>
struct is_double
{
	static constexpr bool value = std::is_same_v<double, Decayed>;
};

template <typename Type>
struct is_base_number
{
	static constexpr bool value = (is_bool<Type>::value || is_8<Type>::value || is_16<Type>::value || is_32<Type>::value || is_64<Type>::value || is_float<Type>::value || is_double<Type>::value);
};

template <typename Type, typename Decayed = typename std::decay_t<Type>>
struct is_string
{
	static constexpr bool value = std::is_same_v<std::string, Decayed>;
};

template <typename Type, typename Decayed = typename std::decay_t<Type>>
struct is_nullptr
{
	static constexpr bool value = std::is_same_v<std::nullptr_t, Decayed>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 具体数组
template <typename SrcType, typename DstType, typename Decayed = typename std::decay_t<SrcType>, typename Decayed_Point = typename std::remove_pointer_t<Decayed>>
struct is_unconst_array
{
	static constexpr bool value = std::is_array_v<SrcType> && std::is_same_v<DstType, Decayed_Point> && !std::is_const_v<Decayed_Point>;
};

template <typename SrcType, typename DstType, typename Decayed = typename std::decay_t<SrcType>, typename Decayed_Point = typename std::remove_pointer_t<Decayed>>
struct is_const_array
{
	static constexpr bool value = std::is_array_v<SrcType> && std::is_same_v<std::add_const_t<DstType>, Decayed_Point> && std::is_const_v<Decayed_Point>;
};

// bool
template <typename Type>
struct is_unconst_bool_array
{
	static constexpr bool value = is_unconst_array<Type, bool>::value;
};

template <typename Type>
struct is_const_bool_array
{
	static constexpr bool value = is_const_array<Type, bool>::value;
};

template <typename Type>
struct is_combination_bool_array
{
	static constexpr bool value = (is_unconst_bool_array<Type>::value || is_const_bool_array<Type>::value);
};

// unsigned char/char
template <typename Type>
struct is_unconst_unsigned_char_array
{
	static constexpr bool value = is_unconst_array<Type, unsigned char>::value;
};

template <typename Type>
struct is_const_unsigned_char_array
{
	static constexpr bool value = is_const_array<Type, unsigned char>::value;
};

template <typename Type>
struct is_unsigned_char_array
{
	static constexpr bool value = (is_unconst_unsigned_char_array<Type>::value || is_const_unsigned_char_array<Type>::value);
};

template <typename Type>
struct is_unconst_signed_char_array
{
	static constexpr bool value = is_unconst_array<Type, char>::value;
};

template <typename Type>
struct is_const_signed_char_array
{
	static constexpr bool value = is_const_array<Type, char>::value;
};

template <typename Type>
struct is_signed_char_array
{
	static constexpr bool value = (is_unconst_signed_char_array<Type>::value || is_const_signed_char_array<Type>::value);
};

template <typename Type>
struct is_combination_char_array
{
	static constexpr bool value = (is_unsigned_char_array<Type>::value || is_signed_char_array<Type>::value);
};

// uint8_t/int8_t
template <typename Type>
struct is_unconst_uint8_array
{
	static constexpr bool value = is_unconst_array<Type, uint8_t>::value;
};

template <typename Type>
struct is_const_uint8_array
{
	static constexpr bool value = is_const_array<Type, uint8_t>::value;
};

template <typename Type>
struct is_uint8_array
{
	static constexpr bool value = (is_unconst_uint8_array<Type>::value || is_const_uint8_array<Type>::value);
};

template <typename Type>
struct is_unconst_int8_array
{
	static constexpr bool value = is_unconst_array<Type, int8_t>::value;
};

template <typename Type>
struct is_const_int8_array
{
	static constexpr bool value = is_const_array<Type, int8_t>::value;
};

template <typename Type>
struct is_int8_array
{
	static constexpr bool value = (is_unconst_int8_array<Type>::value || is_const_int8_array<Type>::value);
};

template <typename Type>
struct is_combination_8_array
{
	static constexpr bool value = (is_uint8_array<Type>::value || is_int8_array<Type>::value);
};

// unsigned short/short
template <typename Type>
struct is_unconst_unsigned_short_array
{
	static constexpr bool value = is_unconst_array<Type, unsigned short>::value;
};

template <typename Type>
struct is_const_unsigned_short_array
{
	static constexpr bool value = is_const_array<Type, unsigned short>::value;
};

template <typename Type>
struct is_unsigned_short_array
{
	static constexpr bool value = (is_unconst_unsigned_short_array<Type>::value || is_const_unsigned_short_array<Type>::value);
};

template <typename Type>
struct is_unconst_signed_short_array
{
	static constexpr bool value = is_unconst_array<Type, short>::value;
};

template <typename Type>
struct is_const_signed_short_array
{
	static constexpr bool value = is_const_array<Type, short>::value;
};

template <typename Type>
struct is_signed_short_array
{
	static constexpr bool value = (is_unconst_signed_short_array<Type>::value || is_const_signed_short_array<Type>::value);
};

template <typename Type>
struct is_combination_short_array
{
	static constexpr bool value = (is_unsigned_short_array<Type>::value || is_signed_short_array<Type>::value);
};

// uint16_t/int16_t
template <typename Type>
struct is_unconst_uint16_array
{
	static constexpr bool value = is_unconst_array<Type, uint16_t>::value;
};

template <typename Type>
struct is_const_uint16_array
{
	static constexpr bool value = is_const_array<Type, uint16_t>::value;
};

template <typename Type>
struct is_uint16_array
{
	static constexpr bool value = (is_unconst_uint16_array<Type>::value || is_const_uint16_array<Type>::value);
};

template <typename Type>
struct is_unconst_int16_array
{
	static constexpr bool value = is_unconst_array<Type, int16_t>::value;
};

template <typename Type>
struct is_const_int16_array
{
	static constexpr bool value = is_const_array<Type, int16_t>::value;
};

template <typename Type>
struct is_int16_array
{
	static constexpr bool value = (is_unconst_int16_array<Type>::value || is_const_int16_array<Type>::value);
};

template <typename Type>
struct is_combination_16_array
{
	static constexpr bool value = (is_uint16_array<Type>::value || is_int16_array<Type>::value);
};

// unsigned int/int
template <typename Type>
struct is_unconst_unsigned_int_array
{
	static constexpr bool value = is_unconst_array<Type, unsigned int>::value;
};

template <typename Type>
struct is_const_unsigned_int_array
{
	static constexpr bool value = is_const_array<Type, unsigned int>::value;
};

template <typename Type>
struct is_unsigned_int_array
{
	static constexpr bool value = (is_unconst_unsigned_int_array<Type>::value || is_const_unsigned_int_array<Type>::value);
};

template <typename Type>
struct is_unconst_signed_int_array
{
	static constexpr bool value = is_unconst_array<Type, int>::value;
};

template <typename Type>
struct is_const_signed_int_array
{
	static constexpr bool value = is_const_array<Type, int>::value;
};

template <typename Type>
struct is_signed_int_array
{
	static constexpr bool value = (is_unconst_signed_int_array<Type>::value || is_const_signed_int_array<Type>::value);
};

template <typename Type>
struct is_combination_int_array
{
	static constexpr bool value = (is_unsigned_int_array<Type>::value || is_signed_int_array<Type>::value);
};

// unsigned long/long
template <typename Type>
struct is_unconst_unsigned_long_array
{
	static constexpr bool value = is_unconst_array<Type, unsigned long>::value;
};

template <typename Type>
struct is_const_unsigned_long_array
{
	static constexpr bool value = is_const_array<Type, unsigned long>::value;
};

template <typename Type>
struct is_unsigned_long_array
{
	static constexpr bool value = (is_unconst_unsigned_long_array<Type>::value || is_const_unsigned_long_array<Type>::value);
};

template <typename Type>
struct is_unconst_signed_long_array
{
	static constexpr bool value = is_unconst_array<Type, long>::value;
};

template <typename Type>
struct is_const_signed_long_array
{
	static constexpr bool value = is_const_array<Type, long>::value;
};

template <typename Type>
struct is_signed_long_array
{
	static constexpr bool value = (is_unconst_signed_long_array<Type>::value || is_const_signed_long_array<Type>::value);
};

template <typename Type>
struct is_combination_long_array
{
	static constexpr bool value = (is_unsigned_long_array<Type>::value || is_signed_long_array<Type>::value);
};

// uint32_t/int32_t
template <typename Type>
struct is_unconst_uint32_array
{
	static constexpr bool value = is_unconst_array<Type, uint32_t>::value;
};

template <typename Type>
struct is_const_uint32_array
{
	static constexpr bool value = is_const_array<Type, uint32_t>::value;
};

template <typename Type>
struct is_uint32_array
{
	static constexpr bool value = (is_unconst_uint32_array<Type>::value || is_const_uint32_array<Type>::value);
};

template <typename Type>
struct is_unconst_int32_array
{
	static constexpr bool value = is_unconst_array<Type, int32_t>::value;
};

template <typename Type>
struct is_const_int32_array
{
	static constexpr bool value = is_const_array<Type, int32_t>::value;
};

template <typename Type>
struct is_int32_array
{
	static constexpr bool value = (is_unconst_int32_array<Type>::value || is_const_int32_array<Type>::value);
};

template <typename Type>
struct is_combination_32_array
{
	static constexpr bool value = (is_uint32_array<Type>::value || is_int32_array<Type>::value);
};

// unsigned long long/long long
template <typename Type>
struct is_unconst_unsigned_long_long_array
{
	static constexpr bool value = is_unconst_array<Type, unsigned long long>::value;
};

template <typename Type>
struct is_const_unsigned_long_long_array
{
	static constexpr bool value = is_const_array<Type, unsigned long long>::value;
};

template <typename Type>
struct is_unsigned_long_long_array
{
	static constexpr bool value = (is_unconst_unsigned_long_long_array<Type>::value || is_const_unsigned_long_long_array<Type>::value);
};

template <typename Type>
struct is_unconst_signed_long_long_array
{
	static constexpr bool value = is_unconst_array<Type, long long>::value;
};

template <typename Type>
struct is_const_signed_long_long_array
{
	static constexpr bool value = is_const_array<Type, long long>::value;
};

template <typename Type>
struct is_signed_long_long_array
{
	static constexpr bool value = (is_unconst_signed_long_long_array<Type>::value || is_const_signed_long_long_array<Type>::value);
};

template <typename Type>
struct is_combination_long_long_array
{
	static constexpr bool value = (is_unsigned_long_long_array<Type>::value || is_signed_long_long_array<Type>::value);
};

// uint64_t/int64_t
template <typename Type>
struct is_unconst_uint64_array
{
	static constexpr bool value = is_unconst_array<Type, uint64_t>::value;
};

template <typename Type>
struct is_const_uint64_array
{
	static constexpr bool value = is_const_array<Type, uint64_t>::value;
};

template <typename Type>
struct is_uint64_array
{
	static constexpr bool value = (is_unconst_uint64_array<Type>::value || is_const_uint64_array<Type>::value);
};

template <typename Type>
struct is_unconst_int64_array
{
	static constexpr bool value = is_unconst_array<Type, int64_t>::value;
};

template <typename Type>
struct is_const_int64_array
{
	static constexpr bool value = is_const_array<Type, int64_t>::value;
};

template <typename Type>
struct is_int64_array
{
	static constexpr bool value = (is_unconst_int64_array<Type>::value || is_const_int64_array<Type>::value);
};

template <typename Type>
struct is_combination_64_array
{
	static constexpr bool value = (is_uint64_array<Type>::value || is_int64_array<Type>::value);
};

// float
template <typename Type>
struct is_unconst_float_array
{
	static constexpr bool value = is_unconst_array<Type, float>::value;
};

template <typename Type>
struct is_const_float_array
{
	static constexpr bool value = is_const_array<Type, float>::value;
};

template <typename Type>
struct is_combination_float_array
{
	static constexpr bool value = (is_unconst_float_array<Type>::value || is_const_float_array<Type>::value);
};

// double
template <typename Type>
struct is_unconst_double_array
{
	static constexpr bool value = is_unconst_array<Type, double>::value;
};

template <typename Type>
struct is_const_double_array
{
	static constexpr bool value = is_const_array<Type, double>::value;
};

template <typename Type>
struct is_combination_double_array
{
	static constexpr bool value = (is_unconst_double_array<Type>::value || is_const_double_array<Type>::value);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 广义数组
template <typename Type, std::size_t Size, typename Decayed = typename std::decay_t<Type>, typename Decayed_Point = typename std::remove_pointer_t<Decayed>>
struct is_unconst_unsigned_array
{
	static constexpr bool value = std::is_array_v<Type> && std::is_unsigned_v<Decayed_Point> && sizeof(Decayed_Point) == Size && !std::is_const_v<Decayed_Point>;
};

template <typename Type, std::size_t Size, typename Decayed = typename std::decay_t<Type>, typename Decayed_Point = typename std::remove_pointer_t<Decayed>>
struct is_const_unsigned_array
{
	static constexpr bool value = std::is_array_v<Type> && std::is_unsigned_v<Decayed_Point> && sizeof(Decayed_Point) == Size && std::is_const_v<Decayed_Point>;
};

template <typename Type, std::size_t Size, typename Decayed = typename std::decay_t<Type>, typename Decayed_Point = typename std::remove_pointer_t<Decayed>>
struct is_unconst_signed_array
{
	static constexpr bool value = std::is_array_v<Type> && std::is_signed_v<Decayed_Point> && sizeof(Decayed_Point) == Size && !std::is_const_v<Decayed_Point>;
};

template <typename Type, std::size_t Size, typename Decayed = typename std::decay_t<Type>, typename Decayed_Point = typename std::remove_pointer_t<Decayed>>
struct is_const_signed_array
{
	static constexpr bool value = std::is_array_v<Type> && std::is_signed_v<Decayed_Point> && sizeof(Decayed_Point) == Size && std::is_const_v<Decayed_Point>;
};

template <typename Type>
struct is_unconst_u8_array
{
	static constexpr bool value = is_unconst_unsigned_array<Type, 1>::value;
};

template <typename Type>
struct is_const_u8_array
{
	static constexpr bool value = is_const_unsigned_array<Type, 1>::value;
};

template <typename Type>
struct is_unconst_i8_array
{
	static constexpr bool value = is_unconst_signed_array<Type, 1>::value;
};

template <typename Type>
struct is_const_i8_array
{
	static constexpr bool value = is_const_signed_array<Type, 1>::value;
};

template <typename Type>
struct is_unconst_u16_array
{
	static constexpr bool value = is_unconst_unsigned_array<Type, 2>::value;
};

template <typename Type>
struct is_const_u16_array
{
	static constexpr bool value = is_const_unsigned_array<Type, 2>::value;
};

template <typename Type>
struct is_unconst_i16_array
{
	static constexpr bool value = is_unconst_signed_array<Type, 2>::value;
};

template <typename Type>
struct is_const_i16_array
{
	static constexpr bool value = is_const_signed_array<Type, 2>::value;
};

template <typename Type>
struct is_unconst_u32_array
{
	static constexpr bool value = is_unconst_unsigned_array<Type, 4>::value;
};

template <typename Type>
struct is_const_u32_array
{
	static constexpr bool value = is_const_unsigned_array<Type, 4>::value;
};

template <typename Type>
struct is_unconst_i32_array
{
	static constexpr bool value = is_unconst_signed_array<Type, 4>::value;
};

template <typename Type>
struct is_const_i32_array
{
	static constexpr bool value = is_const_signed_array<Type, 4>::value;
};

template <typename Type>
struct is_unconst_u64_array
{
	static constexpr bool value = is_unconst_unsigned_array<Type, 8>::value;
};

template <typename Type>
struct is_const_u64_array
{
	static constexpr bool value = is_const_unsigned_array<Type, 8>::value;
};

template <typename Type>
struct is_unconst_i64_array
{
	static constexpr bool value = is_unconst_signed_array<Type, 8>::value;
};

template <typename Type>
struct is_const_i64_array
{
	static constexpr bool value = is_const_signed_array<Type, 8>::value;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 指针
template <typename SrcType, typename DstType, typename Decayed = typename std::decay_t<SrcType>, typename Decayed_Point = typename std::remove_pointer_t<Decayed>>
struct is_unconst_pointer
{
	static constexpr bool value = std::is_pointer_v<SrcType> && std::is_same_v<DstType, Decayed_Point> && !std::is_const_v<Decayed_Point>;
};

template <typename SrcType, typename DstType, typename Decayed = typename std::decay_t<SrcType>, typename Decayed_Point = typename std::remove_pointer_t<Decayed>>
struct is_const_pointer
{
	static constexpr bool value = std::is_pointer_v<SrcType> && std::is_same_v<DstType, std::remove_const_t<Decayed_Point>> && std::is_const_v<Decayed_Point>;
};

// unsigned char*/char*
template <typename Type>
struct is_unconst_unsigned_char_pointer
{
	static constexpr bool value = is_unconst_pointer<Type, unsigned char>::value;
};

template <typename Type>
struct is_const_unsigned_char_pointer
{
	static constexpr bool value = is_const_pointer<Type, unsigned char>::value;
};

template <typename Type>
struct is_combination_unsigned_char_pointer
{
	static constexpr bool value = (is_unconst_unsigned_char_pointer<Type>::value || is_const_unsigned_char_pointer<Type>::value);
};

template <typename Type>
struct is_unconst_signed_char_pointer
{
	static constexpr bool value = is_unconst_pointer<Type, char>::value;
};

template <typename Type>
struct is_const_signed_char_pointer
{
	static constexpr bool value = is_const_pointer<Type, char>::value;
};

template <typename Type>
struct is_combination_signed_char_pointer
{
	static constexpr bool value = (is_unconst_signed_char_pointer<Type>::value || is_const_signed_char_pointer<Type>::value);
};

template <typename Type>
struct is_combination_char_pointer
{
	static constexpr bool value = (is_combination_unsigned_char_pointer<Type>::value || is_combination_signed_char_pointer<Type>::value);
};

// 函数指针
template <typename func>
struct is_func_pointer
{
	static constexpr bool value = (std::is_function_v<func> || std::is_member_function_pointer_v<func>);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 类
template <typename Base, typename Derive, typename BaseDecayed = typename std::decay_t<Base>, typename DeriveDecayed = typename std::decay_t<Derive>>
struct is_derive
{
	static constexpr bool value = (!std::is_void_v<DeriveDecayed> && !std::is_same_v<BaseDecayed, DeriveDecayed> && std::is_base_of_v<BaseDecayed, DeriveDecayed>);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 多个类型检测
template <typename T1, typename... Ts>
struct is_homogeneous
{
	static constexpr bool value = (std::is_same<T1, Ts>::value && ...);
};

template <typename T1, typename... Ts>
constexpr bool IsHomogeneous(T1, Ts...)
{
	return (std::is_same<T1, Ts>::value && ...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 容器检测
template <typename T, typename... Types>
struct is_container_type
{
	static constexpr bool value = false;
};

template <typename T, typename... Types>
struct is_container_type<std::vector<T, Types...>>
{
	static constexpr bool value = true;
};

template <typename T, typename... Types>
struct is_container_type<std::forward_list<T, Types...>>
{
	static constexpr bool value = true;
};

template <typename T, typename... Types>
struct is_container_type<std::list<T, Types...>>
{
	static constexpr bool value = true;
};

template <typename T, typename... Types>
struct is_container_type<std::deque<T, Types...>>
{
	static constexpr bool value = true;
};

template <typename T, typename... Types>
struct is_container_type<std::set<T, Types...>>
{
	static constexpr bool value = true;
};

template <typename T, typename... Types>
struct is_container_type<std::unordered_set<T, Types...>>
{
	static constexpr bool value = true;
};

template <typename T, typename... Types>
struct is_container_type<std::multiset<T, Types...>>
{
	static constexpr bool value = true;
};

template <typename T, typename... Types>
struct is_container_type<std::unordered_multiset<T, Types...>>
{
	static constexpr bool value = true;
};

template <typename K, typename V, typename... Types>
struct is_container_type<std::map<K, V, Types...>>
{
	static constexpr bool value = true;
};

template<typename K, typename V, typename... Types>
struct is_container_type<std::unordered_map<K, V, Types...>>
{
	static constexpr bool value = true;
};

template <typename K, typename V, typename... Types>
struct is_container_type<std::multimap<K, V, Types...>>
{
	static constexpr bool value = true;
};

template<typename K, typename V, typename... Types>
struct is_container_type<std::unordered_multimap<K, V, Types...>>
{
	static constexpr bool value = true;
};

template <typename T, typename... Types>
struct is_container_type<std::stack<T, Types...>>
{
	static constexpr bool value = true;
};

template <typename T, typename... Types>
struct is_container
{
	static constexpr bool value = is_container_type<T, Types...>::value;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为vector
template <typename T, typename... Types>
struct is_vector
{
	static constexpr bool value = false;
};

template <typename T, typename... Types>
struct is_vector<std::vector<T, Types...>>
{
	static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为forward_list
template <typename T, typename... Types>
struct is_forward_list
{
	static constexpr bool value = false;
};

template <typename T, typename... Types>
struct is_forward_list<std::forward_list<T, Types...>>
{
	static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为list
template <typename T, typename... Types>
struct is_list
{
	static constexpr bool value = false;
};

template <typename T, typename... Types>
struct is_list<std::list<T, Types...>>
{
	static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为deque
template <typename T, typename... Types>
struct is_deque
{
	static constexpr bool value = false;
};

template <typename T, typename... Types>
struct is_deque<std::deque<T, Types...>>
{
	static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为set
template <typename T, typename... Types>
struct is_set
{
	static constexpr bool value = false;
};

template <typename T, typename... Types>
struct is_set<std::set<T, Types...>>
{
	static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为unordered_set
template <typename T, typename... Types>
struct is_unordered_set
{
	static constexpr bool value = false;
};

template <typename T, typename... Types>
struct is_unordered_set<std::unordered_set<T, Types...>>
{
	static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为multiset
template <typename T, typename... Types>
struct is_multiset
{
	static constexpr bool value = false;
};

template <typename T, typename... Types>
struct is_multiset<std::multiset<T, Types...>>
{
	static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为unordered_multiset
template <typename T, typename... Types>
struct is_unordered_multiset
{
	static constexpr bool value = false;
};

template <typename T, typename... Types>
struct is_unordered_multiset<std::unordered_multiset<T, Types...>>
{
	static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为map
template <typename T, typename... Types>
struct is_map
{
	static constexpr bool value = false;
};

template <typename K, typename V, typename... Types>
struct is_map<std::map<K, V, Types...>>
{
	static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为unordered_map
template <typename T, typename... Types>
struct is_unordered_map
{
	static constexpr bool value = false;
};

template <typename K, typename V, typename... Types>
struct is_unordered_map<std::unordered_map<K, V, Types...>>
{
	static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为multimap
template <typename T, typename... Types>
struct is_multimap
{
	static constexpr bool value = false;
};

template <typename K, typename V, typename... Types>
struct is_multimap<std::multimap<K, V, Types...>>
{
	static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为unordered_multimap
template <typename T, typename... Types>
struct is_unordered_multimap
{
	static constexpr bool value = false;
};

template <typename K, typename V, typename... Types>
struct is_unordered_multimap<std::unordered_multimap<K, V, Types...>>
{
	static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 是否为stack
template <typename T, typename... Types>
struct is_stack
{
	static constexpr bool value = false;
};

template <typename T, typename... Types>
struct is_stack<std::stack<T, Types...>>
{
	static constexpr bool value = true;
};

}

#endif