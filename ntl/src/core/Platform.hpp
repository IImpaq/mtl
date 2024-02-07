/**
* @file Platform.hpp
* @author Marcus Gugacs
* @date 02/07/2024
* @copyright Copyright (c) 2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_PLATFORM_HPP
#define NTL_PLATFORM_HPP

#ifdef _WIN32                                    // Windows 32-Bit/64-Bit
  #ifdef _WIN64                                  // Windows 64-Bit
    #define NTL_PLATFORM_WINDOWS
  #else                                          // Windows 32-Bit
    #error "x86 architecture is not supported!"
  #endif
#elif defined(__APPLE__) || defined(__MACH__)    // Apple platforms
  #include <TargetConditionals.h>

  #define NTL_PLATFORM_APPLE

  #if TARGET_OS_SIMULATOR                        // iOS simulator
    #error "iOS simulator is not supported!"
  #elif TARGET_OS_IOS                            // iOS
    #define NTL_PLATFORM_IOS
    #error "iOS is not supported yet!"
  #elif TARGET_OS_TV                             // tvOS
    #define NTL_PLATFORM_TVOS
    #error "tvOS is not supported yet!"
  #elif TARGET_OS_WATCH                          // watchOS
    #define NTL_PLATFORM_WATCHOS
    #error "watchOS is not supported yet!"
  #elif TARGET_OS_MAC                            // macOS
    #define NTL_PLATFORM_MACOS
  #else                                          // Unknown Apple platform
    #error "Unknown Apple platform!"
  #endif

#elif defined(__ANDROID__)                       // Android
  #define NTL_PLATFORM_ANDROID
    #error "Android is not supported yet!"
  #elif defined(__linux__)                       // Linux
	  #define NTL_PLATFORM_LINUX
  #else                                          // Unknown
	  #error "Unknown platform!"
#endif

#ifdef NDEBUG
  #define NTL_RELEASE
  #define NTL_PROFILE 0
#else
  #define NTL_DEBUG
  #define NTL_PROFILE 1
#endif

#endif //NTL_PLATFORM_HPP
