
#include <windows.h>
#include <stdio.h>
#include "./kernel32.h"

FILE *logFile;

FARPROC createProcessA_fn;

BOOL WINAPI CreateProcessA(
    LPCSTR lpApplicationName,
    LPSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    WINBOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCSTR lpCurrentDirectory,
    LPSTARTUPINFOA lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation)
{
    if (logFile)
    {
        fprintf(logFile, "CreateProcessA called with:\n");
        fprintf(logFile, "  lpApplicationName: %s\n", lpApplicationName);
        fprintf(logFile, "  lpCommandLine: %s\n", lpCommandLine);
        fprintf(logFile, "  dwCreationFlags: %u\n", dwCreationFlags);
        fprintf(logFile, "  lpCurrentDirectory: %s\n", lpCurrentDirectory);
        fflush(logFile);
    }
    else
    {
        OutputDebugStringA("CreateProcessA called, but log file is not open.\n");
    }
    CreateProcessA_fn real = (CreateProcessA_fn)createProcessA_fn;
    if (!createProcessA_fn)
        return FALSE;
    return real(lpApplicationName, lpCommandLine, lpProcessAttributes,
                lpThreadAttributes, bInheritHandles, dwCreationFlags,
                lpEnvironment, lpCurrentDirectory, lpStartupInfo,
                lpProcessInformation);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        if (!mockLibs())
            return FALSE;
        if ((logFile = fopen("C:\\logs\\kernel32.log", "a")) == NULL)
            return FALSE;
        break;
    case DLL_PROCESS_DETACH:
        if (logFile)
        {
            return fclose(logFile) == 0;
        }
        break;
    }
    return TRUE;
}

BOOL mockLibs()
{
    HMODULE lib = LoadLibraryA("C:\\Windows\\System32\\kernel32.dll");
    if (!lib)
        return FALSE;
    createProcessA_fn = GetProcAddress(lib, "CreateProcessA");
    if (!createProcessA_fn)
        return FALSE;
    return TRUE;
}
