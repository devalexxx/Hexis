//
// Created by Alex Clorennec on 12/03/2026.
//

#ifndef HX_CORE_VARIANT_UTILS_H
#define HX_CORE_VARIANT_UTILS_H

namespace Hx
{

    template<class... Ts>
    struct Overloaded : Ts... { using Ts::operator()...; };

    template<class... Ts>
    Overloaded(Ts...) -> Overloaded<Ts...>;

}

#endif
