#include "type_list.hpp"

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

	constexpr auto int_char_list_size = strike::size_v<int_char_list>;
	static_assert(int_char_list_size == 2);

	constexpr auto signed_integral_types_size = strike::size_v<signed_integral_types>;
	static_assert(signed_integral_types_size == 5);
}

void test_front()
{
	using front_type = front_t<int_char_list>;
	static_assert(std::is_same_v<front_type, int>);
}

void test_push_front()
{
	using double_int_char_list = push_front_t<int_char_list, double>;
	static_assert(std::is_same_v<front_t<double_int_char_list>, double>);

	using int_list = push_front_t<type_list<>, int>;
	static_assert(std::is_same_v<front_t<int_list>, int>);
}

int main()
{
	test_size();
	test_front();
	test_push_front();
}