#include <windows.h>

#ifndef USER32_H
#define USER32_H

typedef HMENU(WINAPI *LoadMenuA_fn)(HINSTANCE hInstance, LPCSTR lpMenuName);

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif
HMENU WINAPI LoadMenuA(HINSTANCE hInstance, LPCSTR lpMenuName);
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#define ASSERT(expr, errorMessage)                                                        \
    do                                                                                    \
    {                                                                                     \
        if (!(expr))                                                                      \
        {                                                                                 \
            writeLog("Assertion failed: %s. Error: %lu\n", errorMessage, GetLastError()); \
            return 0;                                                                     \
        }                                                                                 \
    } while (0)

extern struct RealUser32 REAL_USER32;
void writeLog(const char *format, ...);

#endif
