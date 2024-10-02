//
// Created by Alex on 02/10/2024.
//

#ifndef HEXIS_MATH_COMMON_H
#define HEXIS_MATH_COMMON_H

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#	define HEXIS_MATH_IMPORT __declspec(dllimport)
#	define HEXIS_MATH_EXPORT __declspec(dllexport)
#else
#	define HEXIS_MATH_IMPORT __attribute__((visibility("default")))
#	define HEXIS_MATH_EXPORT __attribute__((visibility("default")))
#endif

#ifdef HEXIS_MATH_SHARED
#	ifdef HEXIS_MATH_BUILD
#		define HEXIS_MATH_API HEXIS_MATH_EXPORT
#	else
#		define HEXIS_MATH_API HEXIS_MATH_IMPORT
#	endif
#else
#	define HEXIS_MATH_API
#endif

#endif