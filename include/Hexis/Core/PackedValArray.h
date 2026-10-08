// Copyright (c) 2025 devalexxx
// Distributed under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HEXIS_CORE_PACKED_VAL_ARRAY_H
#define HEXIS_CORE_PACKED_VAL_ARRAY_H

#include "Hexis/Core/Common.h"
#include "Hexis/Core/Types.h"
#include <vector>

namespace Hx
{

    class HX_CORE_API PackedValArray
    {
      public:
        PackedValArray(size_t size, UInt8 valueSize);

        size_t GetSize() const;
        size_t GetContainerSize() const;
        UInt8  GetValueSize() const;
        UInt32 GetOverflow() const;

        void SetValueSize(UInt8 valueSize);

        size_t Get(size_t index) const;
        void   Set(size_t index, size_t value);

      private:
        std::vector<size_t> mData;

        UInt8  mValueSize;
        UInt8  mValuesPer64;
        UInt16 mSpare;
        UInt32 mOverflow;
    };

}

#endif
