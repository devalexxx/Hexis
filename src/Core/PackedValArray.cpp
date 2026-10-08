// Copyright (c) 2025 devalexxx
// Distributed under the MIT License.
// https://opensource.org/licenses/MIT

#include "Hexis/Core/PackedValArray.h"

#include <algorithm>

namespace Hx
{

    PackedValArray::PackedValArray(const size_t size, const UInt8 valueSize) :
    mValueSize(valueSize),
    mSpare(0),
    mOverflow(0)
    {
        (void)mSpare;

        constexpr size_t dataSize = sizeof(decltype(mData)::value_type) * 8;
        mValuesPer64 = dataSize / mValueSize;

        const size_t vecSize = std::max(1UL, size / mValuesPer64);
        mData.resize(vecSize);

        mOverflow = vecSize * dataSize - size * valueSize;
    }

    size_t PackedValArray::GetSize() const
    {
        constexpr size_t dataSize = sizeof(decltype(mData)::value_type) * 8;
        return (mData.size() * dataSize - mOverflow) / mValueSize;
    }

    size_t PackedValArray::GetContainerSize() const
    {
        return mData.size();
    }

    UInt8 PackedValArray::GetValueSize() const
    {
        return mValueSize;
    }

    UInt32 PackedValArray::GetOverflow() const
    {
        return mOverflow;
    }

    void PackedValArray::SetValueSize(const UInt8 valueSize)
    {
        if (valueSize == mValueSize)
            return;

        const size_t size = GetSize();
        PackedValArray newArray(size, valueSize);
        for (size_t i = 0; i < size; ++i) { newArray.Set(i, Get(i)); }

        *this = std::move(newArray);
    }

    size_t PackedValArray::Get(const size_t index) const
    {
        constexpr size_t dataSize  = sizeof(decltype(mData)::value_type) * 8;
        const     size_t bitIndex  = index * mValueSize;
        const     size_t dataIndex = bitIndex / dataSize;
        const     size_t offset    = bitIndex % dataSize;
        const     size_t mask      = (1ULL << mValueSize) - 1;

        size_t value = mData[dataIndex] >> offset;
        if (offset + mValueSize > dataSize)
            value |= mData[dataIndex + 1] << (dataSize - offset);

        return value & mask;
    }

    void PackedValArray::Set(const size_t index, const size_t value)
    {
        constexpr size_t dataSize  = sizeof(decltype(mData)::value_type) * 8;
        const     size_t bitIndex  = index * mValueSize;
        const     size_t dataIndex = bitIndex / dataSize;
        const     size_t offset    = bitIndex % dataSize;
        const     size_t mask      = (1ULL << mValueSize) - 1;

        mData[dataIndex] &= ~(mask << offset);
        mData[dataIndex] |= (value & mask) << offset;

        if (offset + mValueSize > dataSize)
        {
            const size_t bitsInNext = (offset + mValueSize) - dataSize;
            mData[dataIndex + 1] &= ~(mask >> (mValueSize - bitsInNext));
            mData[dataIndex + 1] |= (value & mask) >> (mValueSize - bitsInNext);
        }
    }

}