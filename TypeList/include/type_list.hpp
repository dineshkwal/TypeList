#pragma once

#include "helper_traits.hpp"

#include <type_traits>

namespace strike
{
	/**
	* type_list is a compile time list of types. for example:
	*
	* using int_char_list = type_list<int, char>;
	*/
	template<typename... Types>
	class type_list	
	{
	};

	/**
	* empty typelist
	*/
	using empty_list = type_list<>;

	/**
	* check if typelist is empty
	*/
	template<typename List>
	struct is_empty : value_is<false>
	{
	};

	template<>
	struct is_empty<empty_list> : value_is<true>
	{
	};

	template<typename List>
	constexpr auto is_empty_v = is_empty<List>::value;
	
	/**
	* size of a typelist
	*/
	template<typename List>
	struct size;

	template <>
	struct size<empty_list> : value_is<0>
	{
	};

	template<typename Head, typename... Tail>
	struct size<type_list<Head, Tail...>> : value_is<1 + size<type_list<Tail...>>::value>
	{
	};

	template<typename List>
	constexpr auto size_v = size<List>::value;

	/**
	* front of a typelist
	*/
	template<typename List>
	struct front;

	template<typename Head, typename... Tail>
	struct front<type_list<Head, Tail...>> : type_is<Head>
	{
	};

	template<typename List>
	using front_t = typename front<List>::type;

	/**
	* pop the front element of a typelist
	*/
	template<typename List>
	struct pop_front;

	template<typename Head, typename... Tail>
	struct pop_front<type_list<Head, Tail...>> : type_is<type_list<Tail...>>
	{
	};

	template<typename List>
	using pop_front_t = typename pop_front<List>::type;

	/**
	* push a new element at the front of a typelist
	*/
	template<typename List, typename Element>
	struct push_front;

	template<typename... Types, typename Element>
	struct push_front<type_list<Types...>, Element> : type_is<type_list<Element, Types...>>
	{
	};

	template<typename List, typename Element>
	using push_front_t = typename push_front<List, Element>::type;

	/**
	* push a new element at the end of a typelist
	*/

	//  Here push_back is implemented in terms of primitive operations 
	// front, push_front, pop_front, and is_empty
	template<typename List, typename Element, bool Empty = is_empty_v<List>>
	struct push_back;

	template<typename List, typename Element>
	struct push_back<List, Element, false>
	{
	private:
		using first = front_t<List>;
		using rest = pop_front_t<List>;
		using push_back_rest = typename push_back<rest, Element>::type;
	public:
		using type = push_front_t<push_back_rest, first>;
	};

	template<typename List, typename Element>
	struct push_back<List, Element, true> : type_is<push_front_t<List, Element>>
	{
	};

	template<typename List, typename Element>
	using push_back_t = typename push_back<List, Element>::type;

} // namespace strike