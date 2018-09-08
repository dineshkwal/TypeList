#pragma once

#include "type_list.hpp"
#include "helper_traits.hpp"

#include <type_traits>

namespace strike
{
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
	using largest_type_t = typename largest_type<List>::type;
	
	template<typename List>
	struct largest_type<List, false>
	{
	private:
		using first = front_t<List>;
		using tail_largest = largest_type_t<pop_front_t<List>>;

	public:
		using type = std::conditional_t<sizeof(first) >= sizeof(tail_largest), first, tail_largest>;
	};

	template<typename List>
	struct largest_type<List, true>
	{
		using type = char;
	};


	/**
	* given 2 typelists, check if they are equal
	*/
	template<typename List1, typename List2>
	struct is_equal : value_is<false>
	{
	};

	template<typename List1, typename List2>
	constexpr auto is_equal_v = is_equal<List1, List2>::value;

	template<>
	struct is_equal<empty_list, empty_list> : value_is<true>
	{
	};

	template<typename Head1, typename... Tail1, typename Head2, typename... Tail2>
	struct is_equal<type_list<Head1, Tail1...>, type_list<Head2, Tail2...>> :
		value_is<std::is_same_v<Head1, Head2> && is_equal_v<type_list<Tail1...>, type_list<Tail2...>>>
	{
	};


	/**
	* reverse a typelist
	*/
	template<typename List, bool Empty = is_empty_v<List>>
	struct reverse;

	template<typename List>
	using reverse_t = typename reverse<List>::type;

	template<typename List>
	struct reverse<List, true> : type_is<List>
	{
	};

	template<typename List>
	struct reverse<List, false> : push_back<reverse_t<pop_front_t<List>>, front_t<List>>
	{
	};

	/**
	* remove the last element from a typelist
	*/
	template<typename List>
	struct pop_back : type_is<reverse_t<pop_front_t<reverse_t<List>>>>
	{
	};

	template<typename List>
	using pop_back_t = typename pop_back<List>::type;

	/**
	* transform the typelist by applying given unary metafunction to each type
	*/
	template<typename List, template<typename> class F,
			bool Empty = is_empty_v<List>>
	struct transform;

	template<typename List, template<typename> class F>
	using transform_t = typename transform<List, F>::type;

	template<typename List, template<typename> class F>
	struct transform<List, F, true> : type_is<List>
	{
	};

	template<typename List, template<typename> class F>
	struct transform<List, F, false> : push_front<
		transform_t<pop_front_t<List>, F>,
		typename F<front_t<List>>::type>
	{
	};

	/**
	* accumulate the result type by applying given binary metafunction and initial type I
	*/
	template<typename List, 
			template<typename, typename> class F,
			typename I,
			bool Empty = is_empty_v<List>>
	struct accumulate;

	template<typename List,
			template<typename, typename> class F,
			typename I>
	using accumulate_t = typename accumulate<List, F, I>::type;

	template<typename List,
			template<typename, typename> class F,
			typename I>
	struct accumulate<List, F, I, true> : type_is<I>
	{
	};

	template<typename List,
			template<typename, typename> class F,
			typename I>
	struct accumulate<List, F, I, false> : accumulate<pop_front_t<List>, F, typename F<I, front_t<List>>::type>
	{
	};

} // namespace strike