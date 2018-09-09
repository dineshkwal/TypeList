#pragma once

#include "type_list_algo.hpp"

namespace strike
{
	template<typename T, T... Values>
	struct value_list
	{
	};

	template<auto... Values>
	struct generic_value_list
	{
	};

	template<typename List, typename Indices>
	struct select;

	template<typename List, size_t... Indices>
	struct select<List, generic_value_list<Indices...>>
	{
		using type = type_list<nth_element_t<List, Indices>...>;
	}

} // namespace strike