#include <windows.h>
#include <stdio.h>

#include "user32.h"
#include "menu.h"

struct RealUser32
{
    FILE *logFile;
    LoadMenuA_fn LoadMenuA;
} REAL_USER32;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        HMODULE hUser32 = LoadLibraryA("real_user32.dll");
        if (!hUser32)
            return FALSE;

        REAL_USER32.logFile = fopen("C:\\logs\\user32.log", "a");
        if (!REAL_USER32.logFile)
            return FALSE;

        REAL_USER32.LoadMenuA = (LoadMenuA_fn)GetProcAddress(hUser32, "LoadMenuA");
        if (!REAL_USER32.LoadMenuA)
            return FALSE;
    }
    break;
    case DLL_PROCESS_DETACH:
        fclose(REAL_USER32.logFile);
        break;
    }
    return TRUE;
}

HMENU WINAPI LoadMenuA(HINSTANCE hInstance, LPCSTR lpMenuName)
{
    writeLog("LoadMenuA called with hInstance: %p, lpMenuName: %s\n", hInstance, lpMenuName);
    HMENU menu = REAL_USER32.LoadMenuA(hInstance, lpMenuName);
    if (menu)
    {
        patchMyMenu(menu);
    }
    return menu;
}

void writeLog(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(REAL_USER32.logFile, format, args);
    va_end(args);
    fflush(REAL_USER32.logFile);
}