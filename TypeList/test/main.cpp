#include "type_list.hpp"

#include <iostream>
#include <cassert>

using namespace strike;

void test_size()
{
	using empty_list = type_list<>;
	constexpr auto empty_list_size = size_v<empty_list>;
	assert(empty_list_size == 0);

	using int_char_list = strike::type_list<int, char>;
	constexpr auto int_char_list_size = strike::size_v<int_char_list>;
	assert(int_char_list_size == 2);

	using signed_integral_types = type_list<signed char, short, int, long, long long>;
	constexpr auto signed_integral_types_size = strike::size_v<signed_integral_types>;
	assert(signed_integral_types_size == 5);
}

int main()
{
	test_size();
}