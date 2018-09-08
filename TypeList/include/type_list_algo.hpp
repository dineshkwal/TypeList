#pragma once

#include "type_list.hpp"

namespace strike
{
	/**
	* Query the nth element in a typelist
	*/
	template<typename List, size_t N>
	struct nth_element;

	template<typename List>
	struct nth_element<List, 0> : front<List>
	{
	};

	template<typename List, size_t N>
	struct nth_element : nth_element<pop_front_t<List>, N - 1>
	{
	};

	template<typename List, size_t N>
	using nth_element_t = typename nth_element<List, N>::type;

} // namespace strike