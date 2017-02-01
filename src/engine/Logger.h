//
//  Author: Shervin Aflatooni
//

#pragma once

#ifdef ANDROID
  #include <android/log.h>
#else
  #include <stdio.h>
#endif

#include <errno.h>
#include <string.h>

#ifndef DEBUG
  #define debug(M, ...)
#else
  #ifdef ANDROID
    #define debug(M, ...) __android_log_print(ANDROID_LOG_DEBUG, "EngineLogger", "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
  #else
    #define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
  #endif
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#ifdef ANDROID
  #define log_err(M, ...) __android_log_print(ANDROID_LOG_ERROR, "EngineLogger", "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#else
  #define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#endif

#ifdef ANDROID
  #define log_warn(M, ...) __android_log_print(ANDROID_LOG_WARN, "EngineLogger", "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#else
  #define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#endif

#ifdef ANDROID
  #define log_info(M, ...) __android_log_print(ANDROID_LOG_VERBOSE, "EngineLogger", "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
  #define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }
