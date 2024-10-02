//
// Created by Alex on 01/10/2024.
//

#ifndef HEXIS_MATH_VEC_H
#define HEXIS_MATH_VEC_H

#include <Hexis/Core/Types.h>

namespace Hx
{

	struct DefaultVecTag
	{};

	template<u64 S, Arithmetic T, typename Tag>
	struct Vec
	{};

	template<u64 S, Arithmetic T, typename LTag, typename RTag>
	struct VecAdapter
	{
			using Cast = std::false_type;
			using SAdd = std::false_type;
			using SSub = std::false_type;
			using SMul = std::false_type;
			using SDiv = std::false_type;
			using Add  = std::false_type;
			using Sub  = std::false_type;
			using Mul  = std::false_type;
			using Div  = std::false_type;
	};

	template<u64 S, Arithmetic T, typename Tag>
	struct VecAdapter<S, T, Tag, Tag>
	{
			using Cast = std::true_type;
			using SAdd = std::true_type;
			using SSub = std::true_type;
			using SMul = std::true_type;
			using SDiv = std::true_type;

			struct Add : std::true_type
			{
					using OTag = Tag;
			};
			struct Sub : std::true_type
			{
					using OTag = Tag;
			};
			struct Mul : std::true_type
			{
					using OTag = Tag;
			};
			struct Div : std::true_type
			{
					using OTag = Tag;
			};
	};

	template<u64 S, Arithmetic T, typename LTag, typename RTag = LTag>
	using AddVecRType = Vec<S, T, typename VecAdapter<S, T, LTag, RTag>::Add::OTag>;

	template<u64 S, Arithmetic T, typename LTag, typename RTag = LTag>
	using SubVecRType = Vec<S, T, typename VecAdapter<S, T, LTag, RTag>::Sub::OTag>;

	template<u64 S, Arithmetic T, typename LTag, typename RTag = LTag>
	using MulVecRType = Vec<S, T, typename VecAdapter<S, T, LTag, RTag>::Mul::OTag>;

	template<u64 S, Arithmetic T, typename LTag, typename RTag = LTag>
	using DivVecRType = Vec<S, T, typename VecAdapter<S, T, LTag, RTag>::Div::OTag>;

}

#endif