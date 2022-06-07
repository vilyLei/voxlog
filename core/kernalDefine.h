#pragma once
#ifndef VOXL_KERNAL_DEF_H_
#    define VOXL_KERNAL_DEF_H_

#    include <string>
#    define VOXL_VERSION 220214
constexpr unsigned int VOXL_INT_BYTES_SIZE = sizeof(int);

#    if VOXL_INT_BYTES_SIZE == 32
#   define VOXL_SYS_BIT32
#    elif VOXL_INT_BYTES_SIZE == 64
#        define VOXL_SYS_BIT64
#endif

#    if defined(__clang__) && !defined(__ibmxl__)
#        define VOXL_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)
#    else
#        define VOXL_CLANG_VERSION 0
#    endif

#    if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER) && \
        !defined(__NVCOMPILER)
#        define VOXL_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#    else
#        define VOXL_GCC_VERSION 0
#    endif

#    ifndef VOXL_GCC_PRAGMA
// Workaround _Pragma bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=59884.
#        if VOXL_GCC_VERSION >= 504
#            define VOXL_GCC_PRAGMA(arg) _Pragma(arg)
#        else
#            define VOXL_GCC_PRAGMA(arg)
#        endif
#    endif

#    ifdef __ICL
#        define VOXL_ICC_VERSION __ICL
#    elif defined(__INTEL_COMPILER)
#        define VOXL_ICC_VERSION __INTEL_COMPILER
#    else
#        define VOXL_ICC_VERSION 0
#    endif

#    ifdef __NVCC__
#        define VOXL_NVCC __NVCC__
#    else
#        define VOXL_NVCC 0
#    endif

#    ifdef _MSC_VER
#        define VOXL_MSC_VER          _MSC_VER
#        define VOXL_MSC_WARNING(...) __pragma(warning(__VA_ARGS__))
#    else
#        define VOXL_MSC_VER 0
#        define VOXL_MSC_WARNING(...)
#    endif

#    ifndef VOXL_INLINE
#        if VOXL_GCC_VERSION || VOXL_CLANG_VERSION
#            define VOXL_INLINE inline __attribute__((always_inline))
#        else
#            define VOXL_INLINE inline
#        endif
#    endif

#    if (__cplusplus > 201703L) || (_MSVC_LANG > 201703L)
#        define VOXL_CPLUSPLUS_MAJOR_20 2020
#    elif (__cplusplus >= 201103L) || (_MSVC_LANG >= 201103L)
#        define VOXL_CPLUSPLUS_MAJOR_11 2011
#    else
#        define VOXL_CPLUSPLUS_MAJOR_03 2003
#    endif

//major,minor
//VOXL_INLINE std::string getCompilerIdns()
// c++ 20 ago, can not support constexpr
VOXL_INLINE std::string getCompilerIdns()
{
#    if defined(_MSC_VER)
    return "msvc_compiler";
#    elif defined(__clang__)
    return "clang_cmpiler";
#    elif defined(__GNUC_)
    return "gun_cmpiler";
#    else
    return "undefined_cmpiler";
#    endif
}
constexpr int getCplusplusMajorVersion()
{
#    if defined(VOXL_CPLUSPLUS_MAJOR_20)
    return 2020;
#    elif defined(VOXL_CPLUSPLUS_MAJOR_11)
    return 2011;
#    else
    return 2003;
#    endif
}
#endif