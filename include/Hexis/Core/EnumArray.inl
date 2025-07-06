//
// Created by Alex Clorennec on 05/07/2025.
//

#include "EnumArray.h"

#include <memory>

namespace Hx
{

	template<Enum E, typename T>
	EnumArray<E, T>::EnumArray(std::initializer_list<std::pair<E, T>> lst) : mData({})
	{
		for (auto [k, v]: lst)
		{
			mData[std::to_underlying(k)] = v;
		}
	}

	template<Enum E, typename T>
	T&  EnumArray<E, T>::operator[](E value)
	{
		return mData[std::to_underlying(value)];
	}

	template<Enum E, typename T>
	const T& EnumArray<E, T>::operator[](E value) const
	{
		return mData[std::to_underlying(value)];
	}

	template<Enum E, typename T>
	EnumArrayIterator<E, T> EnumArray<E, T>::begin()
	{
		return EnumArrayIterator<E, T>(*this, 0);
	}

	template<Enum E, typename T>
	EnumArrayIterator<E, T> EnumArray<E, T>::end()
	{
		return EnumArrayIterator<E, T>(*this, mData.size());
	}

	template<Enum E, typename T>
	EnumArrayIterator<E, T>::EnumArrayIterator(EnumArray<E, T>& array, difference_type index) :
		mArray(array),
		mIndex(index)
	{}

	template<Enum E, typename T>
	typename EnumArrayIterator<E, T>::value_type EnumArrayIterator<E, T>::operator*() const
	{
		auto key = static_cast<E>(mIndex);
		return std::make_pair(key, std::ref(mArray[key]));
	}

	template<Enum E, typename T>
	EnumArrayIterator<E, T>& EnumArrayIterator<E, T>::operator++()
	{
		++mIndex;
		return *this;
	}

	template<Enum E, typename T>
	EnumArrayIterator<E, T> EnumArrayIterator<E, T>::operator++(int)
	{
		EnumArrayIterator tmp = *this;
		++(*this);
		return tmp;
	}

	template<Enum EE, typename TT>
	bool operator==(const EnumArrayIterator<EE, TT>& lhs, const EnumArrayIterator<EE, TT>& rhs)
	{
		return lhs.mIndex == rhs.mIndex;
	}

	template<Enum EE, typename TT>
	bool operator!=(const EnumArrayIterator<EE, TT>& lhs, const EnumArrayIterator<EE, TT>& rhs)
	{
		return !(lhs == rhs);
	}

}