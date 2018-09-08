#pragma once

#include "type_list.hpp"

#include <type_traits>

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

	/**
	* Query the largest type in a typelist
	*/
	template<typename List, bool Empty = is_empty_v<List>>
	struct largest_type;

	template<typename List>
	struct largest_type<List, false>
	{
	private:
		using first = front_t<List>;
		using tail_largest = typename largest_type<pop_front_t<List>>::type;

	public:
		using type = std::conditional_t<sizeof(first) >= sizeof(tail_largest), first, tail_largest>;
	};

	template<typename List>
	struct largest_type<List, true>
	{
		using type = char;
	};

	template<typename List>
	using largest_type_t = typename largest_type<List>::type;

} // namespace strike