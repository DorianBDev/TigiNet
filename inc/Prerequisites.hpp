/**
*
*   TIGINET
*   Copyright (C) 2018  BACHELOT Dorian
*
*   For contact see CONTACT.md file.
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
*	See LICENSE file for more.
*
*/

#ifndef TN_PREREQUISITES_HPP
#define TN_PREREQUISITES_HPP

/* Specify if use c++14 */
#define TN_CPP14 0

/* Are assert enabled */
#define TN_ENABLE_ASSERT 1

/* Are warning enabled */
#define TN_ENABLE_WARNING 1

/* Are abort enabled */
#define TN_ENABLE_ABORT 1

/* Is debugging enable */
#define TN_DEBUG 1

/* Use a thread safe approach */
#define TN_THREAD_SAFE 1

/* TN_DEPRECATED Definition */
#if defined(__GNUC__) || defined(__MINGW32__) || defined(__clang__)
	#define TN_DEPRECATED(inf) __attribute__((__deprecated__("[TIGINET] This function is deprecated : " # inf)))
#elif defined(_MSC_VER)
	#define TN_DEPRECATED(inf) __declspec(deprecated("[TIGINET] This function is deprecated : " # inf))
#else
	#pragma message("[WARNING] : You need to implement DEPRECATED for this compiler")
	#define TN_DEPRECATED(inf) 
#endif


/* TN_EXPORT and TN_IMPORT Definition */
#if defined(_WIN32)
	#define TN_EXPORT __declspec(dllexport)
	#define TN_IMPORT __declspec(dllimport)
#elif defined(__linux__) || defined(__unix__)
	#define TN_EXPORT __attribute__((visibility ("default")))
	#define TN_IMPORT __attribute__((visibility ("default")))
#else
	#define TN_EXPORT 
	#define TN_IMPORT 
#endif

/* Store the function name (C++11) */
#define TN_FUNCTION_NAME __func__

/* Store the actual file path */
#define TN_FILE_PATH __FILE__

/* Store the actual line number */
#define TN_LINE_NUMBER __LINE__


/* Stringify */
#define TN_STRINGIFY(s) #s

/* Create a script (not raw string, use R"delimiter()delimiter" for that) */
#define TN_SCRIPT(s) TN_STRINGIFY(s)


/* Types tests */	

#include <climits>
#include <cstdint>
#include <stddef.h> // For NULL definition

static_assert(CHAR_BIT == 8, "CHAR_BIT is expected to be 8");

static_assert(sizeof(int8_t)   == 1, "[ERROR] : int8_t is not of the correct size");
static_assert(sizeof(int16_t)  == 2, "[ERROR] : int16_t is not of the correct size");
static_assert(sizeof(int32_t)  == 4, "[ERROR] : int32_t is not of the correct size");
static_assert(sizeof(int64_t)  == 8, "[ERROR] : int64_t is not of the correct size");

static_assert(sizeof(uint8_t)  == 1, "[ERROR] : uint8_t is not of the correct size");
static_assert(sizeof(uint16_t) == 2, "[ERROR] : uint16_t is not of the correct size");
static_assert(sizeof(uint32_t) == 4, "[ERROR] : uint32_t is not of the correct size");
static_assert(sizeof(uint64_t) == 8, "[ERROR] : uint64_t is not of the correct size");


/* Base types definition */

/**
* @namespace TN
* @brief Project namespace.
*
* The project namespace to avoid conflict.
*
*/
namespace TN
{
	/** 8 bits signed integer */
	using int_8 = int8_t;

	/** 8 bits unsigned integer */
	using uint_8 = uint8_t;


	/** 16 bits signed integer */
	using int_16 = int16_t;

	/** 16 bits unsigned integer */
	using uint_16 = uint16_t;


	/** 32 bits signed integer */
	using int_32 = int32_t;

	/** 32 bits unsigned integer */
	using uint_32 = uint32_t;


	/** 64 bits signed integer */
	using int_64 = int64_t;

	/** 64 bits unsigned integer */
	using uint_64 = uint64_t;

}


/* Other base types definition */

//typedef TN::uint_64 size_t;

#endif