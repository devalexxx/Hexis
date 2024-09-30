//
// Created by Alex on 30/09/2024.
//

#ifndef HEXIS_CORE_COMMON_H
#define HEXIS_CORE_COMMON_H

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#	define HEXIS_CORE_IMPORT __declspec(dllimport)
#	define HEXIS_CORE_EXPORT __declspec(dllexport)
#else
#	define HEXIS_CORE_IMPORT __attribute__((visibility("default")))
#	define HEXIS_CORE_EXPORT __attribute__((visibility("default")))
#endif

#ifdef HEXIS_CORE_SHARED
#	ifdef HEXIS_CORE_BUILD
#		define HEXIS_CORE_API HEXIS_CORE_EXPORT
#	else
#		define HEXIS_CORE_API HEXIS_CORE_IMPORT
#	endif
#else
#	define HEXIS_CORE_API
#endif

#endif