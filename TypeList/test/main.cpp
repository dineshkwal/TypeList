#include "type_list.hpp"
#include "type_list_algo.hpp"

#include <iostream>
#include <cassert>
#include <type_traits>

using namespace strike;

using int_char_list = type_list<int, char>;
using signed_integral_types = type_list<signed char, short, int, long, long long>;

void test_size()
{
	constexpr auto empty_list_size = size_v<empty_list>;
	static_assert(empty_list_size == 0);

	constexpr auto int_char_list_size = size_v<int_char_list>;
	static_assert(int_char_list_size == 2);

	constexpr auto signed_integral_types_size = size_v<signed_integral_types>;
	static_assert(signed_integral_types_size == 5);
}

void test_front()
{
	using result_type = front_t<int_char_list>;
	static_assert(std::is_same_v<result_type, int>);
}

void test_push_front()
{
	using double_int_char_list = push_front_t<int_char_list, double>;
	static_assert(std::is_same_v<front_t<double_int_char_list>, double>);

	using int_list = push_front_t<empty_list, int>;
	static_assert(std::is_same_v<front_t<int_list>, int>);
}

void test_pop_front()
{
	using result_list = pop_front_t<int_char_list>;
	static_assert(is_equal_v<result_list, type_list<char>>);
}

void test_push_back()
{
	using result_list_1 = push_back_t<int_char_list, double>;
	static_assert(std::is_same_v<nth_element_t<result_list_1, 2>, double>);

	using result_list_2 = push_back_t<empty_list, int>;
	static_assert(std::is_same_v<front_t<result_list_2>, int>);
}

void test_pop_back()
{
	using result_list = pop_back_t<int_char_list>;
	static_assert(is_equal_v<result_list, type_list<int>>);
}

void test_is_empty()
{
	constexpr auto is_empty_1 = is_empty_v<empty_list>;
	static_assert(is_empty_1 == true);

	constexpr auto is_empty_2 = is_empty_v<int_char_list>;
	static_assert(is_empty_2 == false);
}

void test_nth_element()
{
	using result_type = nth_element_t<signed_integral_types, 3>;
	static_assert(std::is_same_v<result_type, long>);
}

void test_largest_type()
{
	using result_type_1 = largest_type_t<empty_list>;
	static_assert(std::is_same_v<result_type_1, char>);

	using result_type_2 = largest_type_t<signed_integral_types>;
	static_assert(std::is_same_v<result_type_2, long long>);
}

void test_is_equal()
{
	static_assert(is_equal_v<empty_list, empty_list>);
	static_assert(!is_equal_v<empty_list, int_char_list>);
	static_assert(is_equal_v<int_char_list, int_char_list>);
	static_assert(!is_equal_v<int_char_list, signed_integral_types>);
}

void test_reverse()
{
	using result_type_1 = reverse_t<int_char_list>;
	static_assert(is_equal_v<result_type_1, type_list<char, int>>);

	using result_type_2 = reverse_t<empty_list>;
	static_assert(is_equal_v<result_type_2, empty_list>);
}

int main()
{
	test_is_empty();
	test_size();
	test_front();
	test_push_front();
	test_pop_front();
	test_push_back();
	test_pop_back();
	test_nth_element();
	test_is_equal();
	test_largest_type();
	test_reverse();
}