//
// Created by Alex Clorennec on 06/07/2025.
//

#ifndef HX_CORE_LAMBDA_AS_FUNC_PTR_H
#define HX_CORE_LAMBDA_AS_FUNC_PTR_H

#include "Hexis/Core/Common.h"

#include <utility>

namespace Hx
{

	template<typename F, int I, typename L, typename R, typename... A>
	HX_CORE_API F LambdaAsFuncPtr(L&& l, R (*)(A...) noexcept(noexcept(std::declval<F>()(std::declval<A>()...))))
	{
		thread_local std::decay_t<L> l_(std::forward<L>(l));

		struct S
		{
			static R f(A... args) noexcept(noexcept(std::declval<F>()(std::declval<A>()...)))
			{
				return l_(std::forward<A>(args)...);
			}
		};

		return &S::f;
	}

	template<typename F, int I = 0, typename L>
	HX_CORE_API F LambdaAsFuncPtr(L&& l)
	{
		return LambdaAsFuncPtr<F, I>(std::forward<L>(l), F());
	}

}

#endif