//
// Created by Alex on 30/09/2024.
//

#ifndef HX_CORE_TYPE_LIST_H
#define HX_CORE_TYPE_LIST_H

#include <Hexis/Core/Common.h>
#include <Hexis/Core/Types.h>

namespace Hx
{

	namespace Priv
	{
		template<u64 N, typename T, typename... Ts>
		struct TypeListIndexOf;

		template<u64 N, typename... Ts>
		struct TypeListTypeAt;

	}

	template<typename... Ts>
	struct HX_CORE_API TypeList
	{
			static constexpr u64 Size = sizeof...(Ts);

			template<typename T>
			static constexpr u64 IndexOf = Priv::TypeListIndexOf<0, T, TypeList<Ts...>>::value;

			template<u64 N>
			using TypeAt = typename Priv::TypeListTypeAt<N, TypeList<Ts...>>::type;
	};

}

#include <Hexis/Core/TypeList.inl>

#endif