// Precomp.h
// Generally used for
// gathering system
// variables and
// precompiler definitions
// applicable to every
// script.

#ifdef _WIN32
    #include <windows.h>
    #include <stdio.h>
    #include <tchar.h>
#elif __unix__
#elif __linux__
    #include <unistd.h>
    #include <stdio.h>
    #include <stdio.h>
    #include <string.h>
#elif __APPLE__
    #include "TargetConditionals.h"
    #ifdef TARGET_IOS_IPHONE
        // iOS
    #elif TARGET_IPHONE_SIMULATOR
        // iOS Simulator
    #elif TARGET_OS_MAC
        // Mac OS
    #endif
#endif
