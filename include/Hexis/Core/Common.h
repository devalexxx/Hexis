//
// Created by Alex on 30/09/2024.
//

#ifndef HX_CORE_COMMON_H
#define HX_CORE_COMMON_H

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#	define HX_CORE_IMPORT __declspec(dllimport)
#	define HX_CORE_EXPORT __declspec(dllexport)
#else
#	define HX_CORE_IMPORT __attribute__((visibility("default")))
#	define HX_CORE_EXPORT __attribute__((visibility("default")))
#endif

#ifdef HX_CORE_SHARED
#	ifdef HX_CORE_BUILD
#		define HX_CORE_API HX_CORE_EXPORT
#	else
#		define HX_CORE_API HX_CORE_IMPORT
#	endif
#else
#	define HX_CORE_API
#endif

#endif