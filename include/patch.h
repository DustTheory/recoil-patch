#ifndef RECOIL_PATCH_H
#define RECOIL_PATCH_H

// Binary originally supports 6 resolutions represented by these values
typedef enum
{
    // Previously existing resolutions options
    RESOLUTION_320x200 = 2,
    RESOLUTION_320x240 = 3,
    RESOLUTION_640x400 = 4,
    RESOLUTION_640x480 = 5,
    RESOLUTION_800x600 = 6,
    RESOLUTION_1024x768 = 7,
    // Injected resolution options
    RESOLUTION_1280x720 = 8,
    RESOLUTION_1280x800 = 9,
    RESOLUTION_1600x900 = 10,
    RESOLUTION_1920x1080 = 11,
    RESOLUTION_2560x1440 = 12,
    RESOLUTION_3840x2160 = 13
} ResolutionOptionIdentifier;

// Functions from the original binary referenced in patch
extern void FUN_004a6840(void);
extern void __thiscall FUN_004308c0(void *this);
extern void __fastcall FUN_00408530(int, int) asm("FUN_00408530");
extern void __fastcall FUN_00408500(int width, int height) asm("FUN_00408500");
extern void __fastcall FUN_00408700(int, int) asm("FUN_00408700");
extern void __fastcall FUN_004086e0(int dispW, int dispH) asm("FUN_004086e0");
extern void __fastcall FUN_004085e0(int, int) asm("FUN_004085e0");
extern void __fastcall FUN_00408620(int dispW, int dispH) asm("FUN_00408620");
extern void __fastcall FUN_00408680(int) asm("FUN_00408680");
extern void __fastcall FUN_00408300(int doubleScan) asm("FUN_00408300");

// Image loader functions from the original binary
extern void *__fastcall loadImage(const char *name) asm("FUN_0046dd30");
extern void *__fastcall FUN_0046ef70(void *fp) asm("FUN_0046ef70");

// Globals from the original binary referenced in patch
#define RESOLUTION_IDENTIFIER_GLOBAL DAT_004e5d30
extern ResolutionOptionIdentifier *DAT_004e5d30;
#define DOUBLE_SCAN_GLOBAL DAT_00632128
extern int DAT_00632128;
#define RENDER_WIDTH_GLOBAL DAT_00632200
extern int DAT_00632200;
#define RENDER_HEIGHT_GLOBAL DAT_00632204
extern int DAT_00632204;
#define DISPLAY_WIDTH_1_GLOBAL DAT_00632220
extern int DAT_00632220;
#define DISPLAY_HEIGHT_1_GLOBAL DAT_00632224
extern int DAT_00632224;
#define DISPLAY_WIDTH_2_GLOBAL DAT_00632240
extern int DAT_00632240;
#define DISPLAY_HEIGHT_2_GLOBAL DAT_00632244
extern int DAT_00632244;
#define BITS_PER_PIXEL_GLOBAL DAT_00632150
extern int DAT_00632150;

// Function types from the original binary referenced in patch
typedef void(__thiscall *CCmdUI_Enable)(void *self, int bEnable);  // CCmdUI::Enable
typedef void(__thiscall *CCmdUI_SetCheck)(void *self, int nCheck); // CCmdUI::SetCheck

// patch.c does not have it's own imports so we utilize the already imported DLL functions
#define RECOIL_DLL_CALL(fn_type, va, ...) ((fn_type)(*(void **)(va)))(__VA_ARGS__)
#define recoil_fopen(p, m) RECOIL_DLL_CALL(void *(*)(const char *, const char *), 0x4cc5b8, p, m)
#define recoil_fclose(fp) RECOIL_DLL_CALL(int (*)(void *), 0x4cc5c0, fp)
#define recoil_sprintf(b, f, ...) RECOIL_DLL_CALL(int (*)(char *, const char *, ...), 0x4cc5c4, b, f, __VA_ARGS__)
#define recoil_GetCurrentDirectoryA(n, b) RECOIL_DLL_CALL(int (*)(int, char *), 0x4cc12c, n, b)

// ****************** MY OWN HELPERS ******************

typedef struct
{
    int width, height, displayWidth, displayHeight, doubleScan, bpp;
} ResolutionParams;

typedef struct
{
    const char *name;
    int width;
    const char *file;
} ImageOverrideEntry;

void __fastcall setVideoModeParams(int resolutionIdentifier) asm("setVideoModeParams");

__attribute__((naked)) void zeroMenuOffsetsAndCallA6840(void) asm("zeroMenuOffsetsAndCallA6840");

void *__fastcall loadImageOverride(const char *name) asm("loadImageOverride");

static int streq(const char *a, const char *b);

#endif // RECOIL_PATCH_H
