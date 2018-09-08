#pragma once

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
	* size of a typelist
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

	/**
	* front of a typelist
	*/
	template<typename List>
	struct front;

	template<typename Head, typename... Tail>
	struct front<type_list<Head, Tail...>>
	{
		using type = Head;
	};

	template<typename List>
	using front_t = typename front<List>::type;

	/**
	* pop the front element of a typelist
	*/
	template<typename List>
	struct pop_front;

	template<typename Head, typename... Tail>
	struct pop_front<type_list<Head, Tail...>>
	{
		using type = type_list<Tail...>;
	};

	template<typename List>
	using pop_front_t = typename pop_front<List>::type;

	/**
	* push a new element in the front of a typelist
	*/
	template<typename List, typename NewType>
	struct push_front;

	template<typename... Types, typename NewType>
	struct push_front<type_list<Types...>, NewType>
	{
		using type = type_list<NewType, Types...>;
	};

	template<typename List, typename NewType>
	using push_front_t = typename push_front<List, NewType>::type;

} // namespace strike