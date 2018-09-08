#pragma once

namespace strike
{
	template<typename T>
	struct type_is
	{
		using type = T;
	};

	template<auto N>
	struct value_is
	{
		static constexpr auto value = N;
	};

} // namespace strike
