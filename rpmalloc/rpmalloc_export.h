#pragma once

#ifdef RPMALLOC_STATIC_LIB
    #define RPMALLOC_API 
#else
    #ifdef _WIN32
        #ifdef RPMALLOC_EXPORTS_API
            #define RPMALLOC_API __declspec(dllexport)
        #else
            #define RPMALLOC_API __declspec(dllimport)
        #endif
    #else
        #ifdef RPMALLOC_EXPORTS_API
            #define RPMALLOC_API __attribute__ ((visibility ("default")))
        #else
            #define RPMALLOC_API
        #endif
    #endif
#endif
