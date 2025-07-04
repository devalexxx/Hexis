//
// Created by Alex on 30/09/2024.
//

#include <tuple>

namespace Hx::Priv
{

	template<u64 N, typename T, SameAs<T> C>
	struct TypeListIndexOf<N, T, TypeList<C>>
	{
			static constexpr u64 value = N;
	};

	template<u64 N, typename T, NotSameAs<T> C>
	struct TypeListIndexOf<N, T, TypeList<C>>
	{};

	template<u64 N, typename T, SameAs<T> C, typename... Ts>
	struct TypeListIndexOf<N, T, TypeList<C, Ts...>>
	{
			static constexpr u64 value = N;
	};

	template<u64 N, typename T, NotSameAs<T> C, typename... Ts>
	struct TypeListIndexOf<N, T, TypeList<C, Ts...>>
	{
			static constexpr u64 value = TypeListIndexOf<N + 1, T, TypeList<Ts...>>::value;
	};

	template<u64 N, typename... Ts>
	struct TypeListTypeAt<N, TypeList<Ts...>>
	{
			using type = std::tuple_element_t<N, std::tuple<Ts...>>;
	};

}