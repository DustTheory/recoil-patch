#include <windows.h>

// Some Win32 MFC library types
// So far only used in ghidra for easier reversing

#ifndef H_WIN32_TYPES
#define H_WIN32_TYPES

#define CALLBACK __stdcall
typedef LRESULT(CALLBACK *AFX_PMSG)(HWND, UINT, WPARAM, LPARAM);

struct AFX_MSGMAP_ENTRY
{
    UINT nMessage;
    UINT nCode;
    UINT nID;
    UINT nLastID;
    UINT nSig;
    AFX_PMSG pfn;
};

struct AFX_MSGMAP
{
    const AFX_MSGMAP *pBaseMessageMap;
    const AFX_MSGMAP_ENTRY *lpEntries;
};

#endif // H_WIN32_TYPES