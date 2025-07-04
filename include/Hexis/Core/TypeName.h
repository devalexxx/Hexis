//
// Created by Alex on 01/10/2024.
//

#ifndef HX_CORE_TYPE_NAME_H
#define HX_CORE_TYPE_NAME_H

#include "Hexis/Core/Common.h"

#include <string>

namespace Hx
{

	template<typename T>
	HX_CORE_API std::string TypeName();

}

#include <Hexis/Core/TypeName.inl>

#endif