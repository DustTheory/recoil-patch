// Some DirectDraw library types and definitions
// So far only used in ghidra for easier reversing

typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;
typedef int HRESULT;
typedef void *LPVOID;
typedef const void *LPCVOID;
typedef DWORD *LPDWORD;
typedef void *HWND;
typedef void *HDC;
typedef void *HMODULE;
typedef void *HMENU;
typedef char *LPSTR;
typedef const char *LPCSTR;
typedef void *LPRECT;
typedef void *LPVOID_ANY;

typedef struct _RECT
{
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT;

typedef struct _DDSCAPS
{
    DWORD dwCaps;
} DDSCAPS;

typedef struct _DDCOLORKEY
{
    DWORD dwColorSpaceLowValue;
    DWORD dwColorSpaceHighValue;
} DDCOLORKEY;

typedef struct _DDPIXELFORMAT
{
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwFourCC;
    DWORD dwRGBBitCount;
    DWORD dwRBitMask;
    DWORD dwGBitMask;
    DWORD dwBBitMask;
    DWORD dwRGBAlphaBitMask;
} DDPIXELFORMAT;

typedef struct _DDSURFACEDESC
{
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwHeight;
    DWORD dwWidth;
    LONG lPitch;
    DWORD dwBackBufferCount;
    DWORD dwRefreshRate;
    DWORD dwAlphaBitDepth;
    DWORD dwReserved;
    LPVOID lpSurface;
    DDCOLORKEY ddckCKDestOverlay;
    DDCOLORKEY ddckCKDestBlt;
    DDCOLORKEY ddckCKSrcOverlay;
    DDCOLORKEY ddckCKSrcBlt;
    DDPIXELFORMAT ddpfPixelFormat;
    DDSCAPS ddsCaps;
} DDSURFACEDESC;

typedef DDSURFACEDESC *LPDDSURFACEDESC;
typedef DDSCAPS *LPDDSCAPS;
typedef DDCOLORKEY *LPDDCOLORKEY;

typedef struct _DDBLTFX
{
    DWORD dwSize;
    DWORD dwDDFX;
    DWORD dwROP;
    DWORD dwDDROP;
    DWORD dwRotationAngle;
    DWORD dwZBufferOpCode;
    DWORD dwZBufferLow;
    DWORD dwZBufferHigh;
    DWORD dwZBufferBaseDest;
    DWORD dwZDestConstBitDepth;
    DWORD dwZDestConst;
    LPVOID lpDDSZBufferDest;
    DWORD dwZSrcConstBitDepth;
    DWORD dwZSrcConst;
    LPVOID lpDDSZBufferSrc;
    DWORD dwAlphaEdgeBlendBitDepth;
    DWORD dwAlphaEdgeBlend;
    DWORD dwReserved;
    DWORD dwAlphaDestConstBitDepth;
    DWORD dwAlphaDestConst;
    LPVOID lpDDSAlphaDest;
    DWORD dwAlphaSrcConstBitDepth;
    DWORD dwAlphaSrcConst;
    LPVOID lpDDSAlphaSrc;
    DDCOLORKEY ddckDestColorkey;
    DDCOLORKEY ddckSrcColorkey;
} DDBLTFX;

typedef DDBLTFX *LPDDBLTFX;

typedef struct _DDCAPS
{
    DWORD dwSize;
    BYTE blob[0x180];
} DDCAPS;

typedef DDCAPS *LPDDCAPS;

struct IDirectDraw;
struct IDirectDrawSurface;
struct IDirectDrawPalette;
struct IDirectDrawClipper;

typedef struct IDirectDraw *LPDIRECTDRAW;
typedef struct IDirectDrawSurface *LPDIRECTDRAWSURFACE;
typedef struct IDirectDrawPalette *LPDIRECTDRAWPALETTE;
typedef struct IDirectDrawClipper *LPDIRECTDRAWCLIPPER;

typedef HRESULT (*LPDDENUMMODESCALLBACK)(LPDDSURFACEDESC, LPVOID);
typedef HRESULT (*LPDDENUMSURFACESCALLBACK)(LPDIRECTDRAWSURFACE, LPDDSURFACEDESC, LPVOID);

typedef struct _GUID
{
    DWORD Data1;
    WORD Data2;
    WORD Data3;
    BYTE Data4[8];
} GUID;
typedef GUID IID;
typedef GUID *LPGUID;
typedef GUID *REFIID;

typedef struct IDirectDrawVtbl
{
    HRESULT (*QueryInterface)(LPDIRECTDRAW This, REFIID riid, LPVOID *ppv);
    DWORD (*AddRef)(LPDIRECTDRAW This);
    DWORD (*Release)(LPDIRECTDRAW This);

    HRESULT (*Compact)(LPDIRECTDRAW This);
    HRESULT (*CreateClipper)(LPDIRECTDRAW This, DWORD dwFlags, LPDIRECTDRAWCLIPPER *lplpDDClipper, LPVOID pUnkOuter);
    HRESULT (*CreatePalette)(LPDIRECTDRAW This, DWORD dwFlags, LPVOID lpDDColorArray, LPDIRECTDRAWPALETTE *lplpDDPalette, LPVOID pUnkOuter);
    HRESULT (*CreateSurface)(LPDIRECTDRAW This, LPDDSURFACEDESC lpDDSurfaceDesc, LPDIRECTDRAWSURFACE *lplpDDSurface, LPVOID pUnkOuter);
    HRESULT (*DuplicateSurface)(LPDIRECTDRAW This, LPDIRECTDRAWSURFACE lpDDSurface, LPDIRECTDRAWSURFACE *lplpDupDDSurface);
    HRESULT (*EnumDisplayModes)(LPDIRECTDRAW This, DWORD dwFlags, LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext, LPDDENUMMODESCALLBACK lpEnumModesCallback);
    HRESULT (*EnumSurfaces)(LPDIRECTDRAW This, DWORD dwFlags, LPDDSURFACEDESC lpDDSD, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpEnumCallback);
    HRESULT (*FlipToGDISurface)(LPDIRECTDRAW This);
    HRESULT (*GetCaps)(LPDIRECTDRAW This, LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps);
    HRESULT (*GetDisplayMode)(LPDIRECTDRAW This, LPDDSURFACEDESC lpDDSurfaceDesc);
    HRESULT (*GetFourCCCodes)(LPDIRECTDRAW This, LPDWORD lpNumCodes, LPDWORD lpCodes);
    HRESULT (*GetGDISurface)(LPDIRECTDRAW This, LPDIRECTDRAWSURFACE *lplpGDIDDSSurface);
    HRESULT (*GetMonitorFrequency)(LPDIRECTDRAW This, LPDWORD lpdwFreq);
    HRESULT (*GetScanLine)(LPDIRECTDRAW This, LPDWORD lpdwScanLine);
    HRESULT (*GetVerticalBlankStatus)(LPDIRECTDRAW This, LPDWORD lpbIsInVB);
    HRESULT (*Initialize)(LPDIRECTDRAW This, LPGUID lpGUID);
    HRESULT (*RestoreDisplayMode)(LPDIRECTDRAW This);
    HRESULT (*SetCooperativeLevel)(LPDIRECTDRAW This, HWND hWnd, DWORD dwFlags);
    HRESULT (*SetDisplayMode)(LPDIRECTDRAW This, DWORD dwWidth, DWORD dwHeight, DWORD dwBpp);
    HRESULT (*WaitForVerticalBlank)(LPDIRECTDRAW This, DWORD dwFlags, void *hEvent);
} IDirectDrawVtbl;

typedef struct IDirectDraw
{
    IDirectDrawVtbl *lpVtbl;
} IDirectDraw;

typedef struct IDirectDrawSurfaceVtbl
{
    HRESULT (*QueryInterface)(LPDIRECTDRAWSURFACE This, REFIID riid, LPVOID *ppv);
    DWORD (*AddRef)(LPDIRECTDRAWSURFACE This);
    DWORD (*Release)(LPDIRECTDRAWSURFACE This);

    HRESULT (*AddAttachedSurface)(LPDIRECTDRAWSURFACE This, LPDIRECTDRAWSURFACE lpDDSAttachedSurface);
    HRESULT (*AddOverlayDirtyRect)(LPDIRECTDRAWSURFACE This, LPRECT lpRect);
    HRESULT (*Blt)(LPDIRECTDRAWSURFACE This, LPRECT lpDestRect, LPDIRECTDRAWSURFACE lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx);
    HRESULT (*BltBatch)(LPDIRECTDRAWSURFACE This, LPVOID lpDDBltBatch, DWORD dwCount, DWORD dwFlags);
    HRESULT (*BltFast)(LPDIRECTDRAWSURFACE This, DWORD dwX, DWORD dwY, LPDIRECTDRAWSURFACE lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwTrans);
    HRESULT (*DeleteAttachedSurface)(LPDIRECTDRAWSURFACE This, DWORD dwFlags, LPDIRECTDRAWSURFACE lpDDSAttachedSurface);
    HRESULT (*EnumAttachedSurfaces)(LPDIRECTDRAWSURFACE This, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpEnumSurfacesCallback);
    HRESULT (*EnumOverlayZOrders)(LPDIRECTDRAWSURFACE This, DWORD dwFlags, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpfnCallback);
    HRESULT (*Flip)(LPDIRECTDRAWSURFACE This, LPDIRECTDRAWSURFACE lpDDSurfaceTargetOverride, DWORD dwFlags);
    HRESULT (*GetAttachedSurface)(LPDIRECTDRAWSURFACE This, LPDDSCAPS lpDDSCaps, LPDIRECTDRAWSURFACE *lplpDDAttachedSurface);
    HRESULT (*GetBltStatus)(LPDIRECTDRAWSURFACE This, DWORD dwFlags);
    HRESULT (*GetCaps)(LPDIRECTDRAWSURFACE This, LPDDSCAPS lpDDSCaps);
    HRESULT (*GetClipper)(LPDIRECTDRAWSURFACE This, LPDIRECTDRAWCLIPPER *lplpDDClipper);
    HRESULT (*GetColorKey)(LPDIRECTDRAWSURFACE This, DWORD dwFlags, LPDDCOLORKEY lpDDColorKey);
    HRESULT (*GetDC)(LPDIRECTDRAWSURFACE This, HDC *lphDC);
    HRESULT (*GetFlipStatus)(LPDIRECTDRAWSURFACE This, DWORD dwFlags);
    HRESULT (*GetOverlayPosition)(LPDIRECTDRAWSURFACE This, LONG *lplX, LONG *lplY);
    HRESULT (*GetPalette)(LPDIRECTDRAWSURFACE This, LPDIRECTDRAWPALETTE *lplpDDPalette);
    HRESULT (*GetPixelFormat)(LPDIRECTDRAWSURFACE This, DDPIXELFORMAT *lpDDPixelFormat);
    HRESULT (*GetSurfaceDesc)(LPDIRECTDRAWSURFACE This, LPDDSURFACEDESC lpDDSurfaceDesc);
    HRESULT (*Initialize)(LPDIRECTDRAWSURFACE This, LPDIRECTDRAW lpDD, LPDDSURFACEDESC lpDDSurfaceDesc);
    HRESULT (*IsLost)(LPDIRECTDRAWSURFACE This);
    HRESULT (*Lock)(LPDIRECTDRAWSURFACE This, LPRECT lpDestRect, LPDDSURFACEDESC lpDDSurfaceDesc, DWORD dwFlags, void *hEvent);
    HRESULT (*ReleaseDC)(LPDIRECTDRAWSURFACE This, HDC hDC);
    HRESULT (*Restore)(LPDIRECTDRAWSURFACE This);
    HRESULT (*SetClipper)(LPDIRECTDRAWSURFACE This, LPDIRECTDRAWCLIPPER lpDDClipper);
    HRESULT (*SetColorKey)(LPDIRECTDRAWSURFACE This, DWORD dwFlags, LPDDCOLORKEY lpDDColorKey);
    HRESULT (*SetOverlayPosition)(LPDIRECTDRAWSURFACE This, LONG lX, LONG lY);
    HRESULT (*SetPalette)(LPDIRECTDRAWSURFACE This, LPDIRECTDRAWPALETTE lpDDPalette);
    HRESULT (*Unlock)(LPDIRECTDRAWSURFACE This, LPVOID lpSurfaceData);
    HRESULT (*UpdateOverlay)(LPDIRECTDRAWSURFACE This, LPRECT lpSrcRect, LPDIRECTDRAWSURFACE lpDDDestSurface, LPRECT lpDestRect, DWORD dwFlags, LPDDBLTFX lpDDOverlayFx);
    HRESULT (*UpdateOverlayDisplay)(LPDIRECTDRAWSURFACE This, DWORD dwFlags);
    HRESULT (*UpdateOverlayZOrder)(LPDIRECTDRAWSURFACE This, DWORD dwFlags, LPDIRECTDRAWSURFACE lpDDSReference);
} IDirectDrawSurfaceVtbl;

typedef struct IDirectDrawSurface
{
    IDirectDrawSurfaceVtbl *lpVtbl;
} IDirectDrawSurface;

/* SetCooperativeLevel flags. */
#define DDSCL_FULLSCREEN 0x00000001
#define DDSCL_ALLOWREBOOT 0x00000002
#define DDSCL_NOWINDOWCHANGES 0x00000004
#define DDSCL_NORMAL 0x00000008
#define DDSCL_EXCLUSIVE 0x00000010
#define DDSCL_ALLOWMODEX 0x00000040

/* Blt flags. */
#define DDBLT_WAIT 0x01000000
#define DDBLT_ASYNC 0x00000200
#define DDBLT_COLORFILL 0x00000400

/* DD error codes */
#define DD_OK 0
#define DDERR_GENERIC 0x80004005
#define DDERR_INVALIDPARAMS 0x80070057
#define DDERR_SURFACELOST 0x887601C2
#define DDERR_WASSTILLDRAWING 0x8876021C
