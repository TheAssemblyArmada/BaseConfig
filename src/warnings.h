/**
 * @file
 *
 * @author CCHyper
 *
 * @brief Header that defines which warnings to ignore or promote.
 *
 * @copyright BaseConfig is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#pragma once

#ifndef BASE_WARNINGS_H
#define BASE_WARNINGS_H

// Define "IGNORE_WARNINGS" in your CMake file to ignore this header.
#ifndef IGNORE_WARNINGS

// Clang
#if defined(COMPILER_CLANG)
#pragma clang diagnostic ignored "-Wtautological-undefined-compare"
#ifndef NDEBUG
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-private-field"
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wreorder" // "Warn when the compiler reorders code"
//#pragma clang diagnostic ignored "-Woverloaded-virtual" // "Warn about overloaded virtual function names"
#endif // !NDEBUG
#endif // COMPILER_INTEL

// Intel's C++ compiler issues too many warnings in libraries when using warning level 4.
#if defined(__ICL) || defined(__ICC) || defined(__INTEL_COMPILER)
#pragma warning(3)
#pragma warning(disable : 981)	// parameters defined in unspecified order
#pragma warning(disable : 279)	// controlling expressaion is constant
#pragma warning(disable : 271)	// trailing comma is nonstandard
#pragma warning(disable : 171)	// invalid type conversion
#pragma warning(disable : 1)	// last line of file ends without a newline
#endif // COMPILER_INTEL

// Microsoft Visual Studio
// This includes the minimum set of compiler defines and pragmas in order to bring the
// various compilers to a common behavior such that the code will compile without
// error or warning.
#ifdef _MSC_VER

    // Set warning level 4.
    #pragma warning(push, 4)

    // It is safe to ignore the following warning from MSVC 7.1 or higher:
    #if (_MSC_VER >= 1310)
        // warning C: "new behavior: elements of array will be default initialized"
        #pragma warning(disable: 4351)
    #endif // COMPILER_VERSION >= 1310

    // For catching unrefernced local variables, we do not need to worry about this when compiling debug builds.
#ifndef NDEBUG
    #pragma warning(disable : 4189)
    #pragma warning(disable : 4101)
    #pragma warning(disable : 4700) //uninitialized local variable 'x' used
#endif // !NDEBUG

    // warning C4514: "unreferenced inline function has been removed" Yea, so what?
    #pragma warning(disable : 4514)

    // warning C4065: "switch statement contains 'default' but no 'case' labels"
    #pragma warning(disable : 4065)

    // warning C4244: "conversion from 'double' to 'float', possible loss of data" Yea, so what?
    #pragma warning(disable : 4244)

    // warning C4530: Disable warning about exception handling not being enabled.
    // It's used as part of STL - in a part of STL we don't use.
    #pragma warning(disable : 4530)

    // warning C4056: "overflow in floating-point constant arithmetic" This warning occurs even if the
    // loss of precision is insignificant.
    #pragma warning(disable : 4056)

    // warning C4710: "function not inlined" This warning is typically useless. The inline keyword
    // only serves as a suggestion to the compiler and it may or may not inline a
    // function on a case by case basis. No need to be told of this.
    #pragma warning(disable : 4710)

    // warning C4355: "'this' used in base member initializer list" Using "this" in a base member
    // initializer is valid -- no need for this warning.
    #pragma warning(disable : 4355)

    // warning C4097: "typedef-name used as a synonym for class-name". This is by design and should
    // not be a warning.
    #pragma warning(disable : 4097)

    // warning C4091: 'typedef ': ignored on left of '' when no variable is declared
    #pragma warning(disable : 4091)

    // warning C4505: Unreferenced local function removed.
    #pragma warning(disable : 4505)

    // warning C4711: 'function selected for automatic inlining'
    #pragma warning(disable : 4711)

    // warning C4511: 'copy constructor could not be generated'
    #pragma warning(disable : 4511)

    // warning C4512: 'assignment operator could not be generated' 
    #pragma warning(disable : 4512)

    // warning C4100: 'unreferenced formal parameter'
    #pragma warning(disable : 4100)

    // warning C4786: "identifier was truncated to '255' characters in the browser information"
    // Tempates create long identifiers...
    #pragma warning(disable : 4786)

    // warning C4711: 'function selected for automatic inline expansion'.
    // Cool, but since we're treating warnings as errors, don't warn us about this!
    #pragma warning(disable : 4711)

    // warning C4800: 'BOOL' : forcing value to bool 'true' or 'false' (performance warning)
    #pragma warning(disable : 4800)
    
    // warning C4996: 'This function or variable may be unsafe. Consider using fopen_s instead.
    // To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.'
    #pragma warning(disable : 4996)
    
    // To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
    #define _CRT_SECURE_NO_WARNINGS

#endif // _MSC_VER

#endif // BASE_WARNINGS_H

#endif // IGNORE_WARNINGS
