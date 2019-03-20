include(CheckCXXSourceCompiles)
include(CheckSymbolExists)
include(CheckIncludeFile)

check_include_file(strings.h HAVE_STRINGS_H)
check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(libgen.h HAVE_LIBGEN_H)
check_include_file(dirent.h HAVE_DIRENT_H)
check_include_file(sched.h HAVE_SCHED_H)

if(HAVE_STRINGS_H)
check_symbol_exists(strcasecmp "strings.h" HAVE_STRCASECMP)
check_symbol_exists(strncasecmp "strings.h" HAVE_STRNCASECMP)
endif()

# Check for the existence of some functions we need or their equivalents.
if(NOT HAVE_STRCASECMP)
    check_symbol_exists(_stricmp "string.h" HAVE__STRICMP)
    if(NOT HAVE__STRICMP)
        message(FATAL_ERROR "No case-insensitive compare function found, please report!")
    endif()
endif()

if(NOT HAVE_STRNCASECMP)
    check_symbol_exists(_strnicmp "string.h" HAVE__STRNICMP)
    if(NOT HAVE__STRNICMP)
        message(FATAL_ERROR "No case-insensitive size-limited compare function found, please report!")
    endif()
endif()

check_symbol_exists(strlwr "string.h" HAVE_STRLWR)
check_symbol_exists(strupr "string.h" HAVE_STRUPR)
check_symbol_exists(strlcat "string.h" HAVE_STRLCAT)
check_symbol_exists(strlcpy "string.h" HAVE_STRLCPY)

check_cxx_source_compiles("
    #include <algorithm>
    int main(int argc, char **argv) {
        return std::clamp(argc, 0, 50);
    }" HAVE_STD_CLAMP)

if(NOT HAVE_STD_CLAMP)
message("std::clamp not found, standard lower than C++17? Will provide implementation, though this is technically undefined behavior.")
endif()
