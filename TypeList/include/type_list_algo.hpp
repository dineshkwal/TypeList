#pragma once

#include "type_list.hpp"

namespace strike
{
	/**
	* Query the nth element in a typelist
	*/
	template<typename List, size_t N>
	struct nth_element;

	template<typename Head, typename... Tail>
	struct nth_element<type_list<Head, Tail...>, 0>
	{
		using type = Head;
	};

	template<typename Head, typename... Tail, size_t N>
	struct nth_element<type_list<Head, Tail...>, N>
	{
		using type = typename nth_element<type_list<Tail...>, N - 1>::type;
	};

	template<typename List, size_t N>
	using nth_element_t = typename nth_element<List, N>::type;

} // namespace strike