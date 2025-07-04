//
// Created by Alex on 04/10/2024.
//

#ifndef HX_MATH_ADAPTER_H
#define HX_MATH_ADAPTER_H

#include <Hexis/Core/Types.h>

namespace Hx
{

	template<u64 S, Arithmetic T, typename LTag, typename RTag>
	struct VecAdapter
	{};

	template<u64 S, Arithmetic T, typename Tag>
	struct VecAdapter<S, T, Tag, Tag>
	{
			struct Add
			{
					using OTag = Tag;
					struct Scalar
					{
							using OTag = Tag;
					};
			};
			struct Sub
			{
					using OTag = Tag;
					struct Scalar
					{
							using OTag = Tag;
					};
			};
			struct Mul
			{
					using OTag = Tag;
					struct Scalar
					{
							using OTag = Tag;
					};
			};
			struct Div
			{
					using OTag = Tag;
					struct Scalar
					{
							using OTag = Tag;
					};
			};
	};

}

#endif