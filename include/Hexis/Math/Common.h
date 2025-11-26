//
// Created by Alex on 02/10/2024.
//

#ifndef HX_MATH_COMMON_H
#define HX_MATH_COMMON_H

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#    define HX_MATH_IMPORT __declspec(dllimport)
#    define HX_MATH_EXPORT __declspec(dllexport)
#else
#    define HX_MATH_IMPORT __attribute__((visibility("default")))
#    define HX_MATH_EXPORT __attribute__((visibility("default")))
#endif

#ifdef HX_MATH_SHARED
#    ifdef HX_MATH_BUILD
#        define HX_MATH_API HX_MATH_EXPORT
#    else
#        define HX_MATH_API HX_MATH_IMPORT
#    endif
#else
#    define HX_MATH_API
#endif

#endif