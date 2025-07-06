//
// Created by Alex Clorennec on 05/07/2025.
//

#ifndef HX_CORE_ENUM_ARRAY_H
#define HX_CORE_ENUM_ARRAY_H

#include "Hexis/Core/Types.h"
#include "Hexis/Core/Common.h"

#include <utility>
#include <array>

namespace Hx
{

	template<Enum E, typename T>
	class EnumArrayIterator;

	template<Enum E, typename T>
	class HX_CORE_API EnumArray
	{
		public:
			EnumArray(std::initializer_list<std::pair<E, T>> lst);

			T& 		 operator[](E value);
			const T& operator[](E value) const;

			EnumArrayIterator<E, T> begin();
			EnumArrayIterator<E, T> end();

		private:
			std::array<T, std::to_underlying(E::Count)> mData;
	};

	template<Enum E, typename T>
	class HX_CORE_API EnumArrayIterator
	{
		public:
			using iterator_category = std::forward_iterator_tag;
			using difference_type   = typename std::array<T, std::to_underlying(E::Count)>::difference_type;
			using value_type	    = std::pair<E, T&>;

			EnumArrayIterator(EnumArray<E, T>& array, difference_type index);

			value_type operator*() const;

			EnumArrayIterator& operator++();
			EnumArrayIterator  operator++(int);

			template<Enum EE, typename TT>
			friend bool operator==(const EnumArrayIterator<EE, TT>& lhs, const EnumArrayIterator<EE, TT>& rhs);
			template<Enum EE, typename TT>
			friend bool operator!=(const EnumArrayIterator<EE, TT>& lhs, const EnumArrayIterator<EE, TT>& rhs);

		private:
			EnumArray<E, T>& mArray;
			difference_type  mIndex;

	};

}

#include "Hexis/Core/EnumArray.inl"

#endif