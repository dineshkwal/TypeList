#pragma once

namespace strike
{
	/**
	* type_list<> is the empty typelist
	*/

	template<typename... Types>
	class type_list	
	{
	};

	/**
	* Size of a typelist
	*/
	template<typename List>
	struct size;

	template<typename Head, typename... Tail>
	struct size<type_list<Head, Tail...>>
	{
		static constexpr size_t value = 1 + size<type_list<Tail...>>::value;
	};

	template <>
	struct size<type_list<>>
	{
		static constexpr size_t value = 0;
	};

	template<typename List>
	constexpr auto size_v = size<List>::value;

} // namespace strike