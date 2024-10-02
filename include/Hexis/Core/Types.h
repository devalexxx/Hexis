//
// Created by Alex on 30/09/2024.
//

#ifndef HX_CORE_TYPES_H
#define HX_CORE_TYPES_H

#include <cstdint>
#include <type_traits>

namespace Hx
{

	using u8  = std::uint8_t;
	using u16 = std::uint16_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;

	using i8  = std::int8_t;
	using i16 = std::int16_t;
	using i32 = std::int32_t;
	using i64 = std::int64_t;

	using f32 = float;
	using f64 = double;

	template<typename A, typename B>
	concept SameAs = std::is_same_v<A, B>;

	template<typename A, typename B>
	concept NotSameAs = !std::is_same_v<A, B>;

	template<typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

}

#endif