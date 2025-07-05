//
// Created by Alex on 30/09/2024.
//

#ifndef HX_CORE_TYPE_LIST_H
#define HX_CORE_TYPE_LIST_H

#include <Hexis/Core/Common.h>
#include <Hexis/Core/Types.h>

namespace Hx
{

	namespace _
	{
		template<u64 N, typename... Ts>
		struct TypeListTypeAt;

		template<u64 N, typename T, typename... Ts>
		struct TypeListIndexOf;

		template<typename C, typename T, typename... Rest>
		static constexpr void TypeListApply(C&& cb);
	}

	template<typename... Ts>
	struct HX_CORE_API TypeList
	{
			template<u64 N>
			using TypeAt = typename _::TypeListTypeAt<N, TypeList<Ts...>>::type;

			static constexpr u64 Count = sizeof...(Ts);

			template<typename T>
			static constexpr u64 IndexOf = _::TypeListIndexOf<0, T, TypeList<Ts...>>::value;

			template<typename C>
			static constexpr auto Apply = _::TypeListApply<C, Ts...>;
	};

}

#include <Hexis/Core/TypeList.inl>

#endif