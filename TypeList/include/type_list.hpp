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
	* define en empty typelist
	*/
	using empty_list = type_list<>;

} // namespace strike