/**
 * @file
 *
 * @author CCHyper
 * @author OmniBlade
 *
 * @brief Basic header files and defines that are always needed.
 *
 * @copyright Baseconfig is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#ifndef BASE_ALWAYS_H
#define BASE_ALWAYS_H

#include "config.h"

#include "bittype.h"
#include "compiler.h"
#include "intrinsics.h"
#include "macros.h"
#include "platform.h"
#include "stringex.h"
#include "targetver.h"
#include <sys/stat.h>
#include <sys/types.h>

#ifdef PLATFORM_WINDOWS
#define NOMINMAX 1
#include <windows.h>
// Include after windows.h
#include "utf.h"
#define NAME_MAX FILENAME_MAX

#ifndef PATH_MAX
#define PATH_MAX MAX_PATH
#endif
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#define O_TEXT 0
#define O_BINARY 0
#else
#include <io.h>
#endif

#ifdef HAVE_LIBGEN_H
#include <libgen.h>
#endif

#ifdef HAVE_DIRENT_H
#include <dirent.h>
#endif

// Enable inline recursion for MSVC
#ifdef COMPILER_MSVC
#pragma inline_recursion(on)
#endif

// Alias the ICU unicode functions when not building against it.
#if !defined BUILD_WITH_ICU && defined PLATFORM_WINDOWS
#define u_strlen wcslen
#define u_strcpy wcscpy
#define u_strcat wcscat
#define u_vsnprintf_u vswprintf
#define u_strcmp wcscmp
#define u_strcasecmp(x, y, z) _wcsicmp(x, y)
#define u_isspace iswspace
#define u_tolower towlower
#define U_COMPARE_CODE_POINT_ORDER 0x8000
#endif

// Based on the build system generated config.h information we define some stuff here
// for cross platform consistency.
#if defined HAVE__STRICMP && !defined HAVE_STRCASECMP
#define strcasecmp _stricmp
#endif

#if defined HAVE__STRNICMP && !defined HAVE_STRNCASECMP
#define strncasecmp _strnicmp
#endif

#ifndef HAVE_STRLWR
#define strlwr ex_strlwr
#endif

#ifndef HAVE_STRUPR
#define strupr ex_strupr
#endif

#ifndef HAVE_STRLCAT
#define strlcat ex_strlcat
#endif

#ifndef HAVE_STRLCPY
#define strlcpy ex_strlcpy
#endif

#ifndef HAVE_STRTRIM
#define strtrim ex_strtrim
#endif

#if !defined HAVE_STD_CLAMP && defined __cplusplus
#include <functional>

namespace std
{
    template<class T, class Compare>
    constexpr const T &clamp(const T &v, const T &lo, const T &hi, Compare comp)
    {
        return comp(v, lo) ? lo : comp(hi, v) ? hi : v;
    }

    template<class T>
    constexpr const T &clamp(const T &v, const T &lo, const T &hi)
    {
        return clamp(v, lo, hi, std::less<T>());
    }
}
#endif

typedef struct stat stat_t;

#endif // BASE_ALWAYS_H
