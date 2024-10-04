//
// Created by Alex on 04/10/2024.
//

#ifndef HEXIS_MATH_OPERATOR_H
#define HEXIS_MATH_OPERATOR_H

#include <Hexis/Core/Types.h>

#include <Hexis/Math/Vector/Adapter.h>

namespace Hx
{

	template<u64 S, Arithmetic T, typename Tag>
	struct Vec;

	template<u64 S, Arithmetic T, typename Tag1, typename Tag2>
	struct OperatorRType
	{
			using Adapter = VecAdapter<S, T, Tag1, Tag2>;

			struct Cast
			{
					using Type = Vec<S, T, typename Adapter::Cast::OTag>;
			};

			struct Add
			{
					using Type = Vec<S, T, typename Adapter::Add::OTag>;
					struct Scalar
					{
							using Type = Vec<S, T, typename Adapter::Add::Scalar::OTag>;
					};
			};

			struct Sub
			{
					using Type = Vec<S, T, typename Adapter::Sub::OTag>;
					struct Scalar
					{
							using Type = Vec<S, T, typename Adapter::Sub::Scalar::OTag>;
					};
			};

			struct Mul
			{
					using Type = Vec<S, T, typename Adapter::Mul::OTag>;
					struct Scalar
					{
							using Type = Vec<S, T, typename Adapter::Mul::Scalar::OTag>;
					};
			};

			struct Div
			{
					using Type = Vec<S, T, typename Adapter::Div::OTag>;
					struct Scalar
					{
							using Type = Vec<S, T, typename Adapter::Div::Scalar::OTag>;
					};
			};
	};

}

#endif