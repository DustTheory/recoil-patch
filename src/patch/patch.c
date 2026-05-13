#include <patch.h>

static const ResolutionParams RESOLUTION_PARAMS_MAP[] = {
    {0, 0, 0, 0, 0, 16},             // index 0: invalid
    {0, 0, 0, 0, 0, 16},             // index 1: invalid
    {320, 200, 640, 400, 1, 16},     // RESOLUTION_320x200
    {320, 240, 640, 480, 1, 16},     // RESOLUTION_320x240
    {640, 400, 640, 400, 0, 16},     // RESOLUTION_640x400
    {640, 480, 640, 480, 0, 16},     // RESOLUTION_640x480
    {800, 600, 800, 600, 0, 16},     // RESOLUTION_800x600
    {1024, 768, 1024, 768, 0, 16},   // RESOLUTION_1024x768
    {1280, 720, 1280, 720, 0, 16},   // RESOLUTION_1280x720
    {1280, 800, 1280, 800, 0, 16},   // RESOLUTION_1280x800
    {1600, 900, 1600, 900, 0, 16},   // RESOLUTION_1600x900
    {1920, 1080, 1920, 1080, 0, 16}, // RESOLUTION_1920x1080
    {2560, 1440, 2560, 1440, 0, 16}, // RESOLUTION_2560x1440
    {3840, 2160, 3840, 2160, 0, 16}  // RESOLUTION_3840x2160
};

// Sets renderer globals
void __fastcall setVideoModeParams(int resolutionIdentifier)
{
    if (resolutionIdentifier < 2 || resolutionIdentifier > 13)
        return; // Invalid resolution

    const ResolutionParams *resolutionParams = &RESOLUTION_PARAMS_MAP[resolutionIdentifier];

    DOUBLE_SCAN_GLOBAL = resolutionParams->doubleScan;
    RENDER_WIDTH_GLOBAL = resolutionParams->width;
    RENDER_HEIGHT_GLOBAL = resolutionParams->height;
    DISPLAY_WIDTH_1_GLOBAL = resolutionParams->displayWidth;
    DISPLAY_HEIGHT_1_GLOBAL = resolutionParams->displayHeight;
    DISPLAY_WIDTH_2_GLOBAL = resolutionParams->displayWidth;
    DISPLAY_HEIGHT_2_GLOBAL = resolutionParams->displayHeight;
    BITS_PER_PIXEL_GLOBAL = resolutionParams->bpp;
}

// Set selected resolution on resolution menu item clicked
void __fastcall setResolution(int resolutionIdentifier)
{
    if (resolutionIdentifier < 2 || resolutionIdentifier > 13)
    {
        *RESOLUTION_IDENTIFIER_GLOBAL = 0;
        return; // Invalid resolution
    }

    const ResolutionParams *resolutionParams = &RESOLUTION_PARAMS_MAP[resolutionIdentifier];

    *RESOLUTION_IDENTIFIER_GLOBAL = resolutionIdentifier;
    FUN_00408530(0, 0);
    FUN_00408500(resolutionParams->width, resolutionParams->height);
    FUN_00408700(0, 0);
    FUN_004086e0(resolutionParams->displayWidth, resolutionParams->displayHeight);
    FUN_004085e0(0, 0);
    FUN_00408620(resolutionParams->displayWidth, resolutionParams->displayHeight);
    FUN_00408680(resolutionParams->bpp);
    FUN_00408300(resolutionParams->doubleScan);
}

// Handler for each menu itme clicked individually
void __thiscall handle320x200ResolutionSelected(void *this)
{
    setResolution(RESOLUTION_320x200);
    FUN_004308c0(this);
    return;
}

void __thiscall handle320x240ResolutionSelected(void *this)
{
    setResolution(RESOLUTION_320x240);
    FUN_004308c0(this);
    return;
}

void __thiscall handle640x400ResolutionSelected(void *this)
{
    setResolution(RESOLUTION_640x400);
    FUN_004308c0(this);
    return;
}

void __thiscall handle640x480ResolutionSelected(void *this)
{
    setResolution(RESOLUTION_640x480);
    FUN_004308c0(this);
    return;
}

void __thiscall handle800x600ResolutionSelected(void *this)
{
    setResolution(RESOLUTION_800x600);
    FUN_004308c0(this);
    return;
}

void __thiscall handle1024x768ResolutionSelected(void *this)
{
    setResolution(RESOLUTION_1024x768);
    FUN_004308c0(this);
    return;
}

void __thiscall handle1280x720ResolutionSelected(void *this)
{
    setResolution(RESOLUTION_1280x720);
    FUN_004308c0(this);
    return;
}

void __thiscall handle1280x800ResolutionSelected(void *this)
{
    setResolution(RESOLUTION_1280x800);
    FUN_004308c0(this);
    return;
}

void __thiscall handle1600x900ResolutionSelected(void *this)
{
    setResolution(RESOLUTION_1600x900);
    FUN_004308c0(this);
    return;
}

void __thiscall handle1920x1080ResolutionSelected(void *this)
{
    setResolution(RESOLUTION_1920x1080);
    FUN_004308c0(this);
    return;
}

void __thiscall handle2560x1440ResolutionSelected(void *this)
{
    setResolution(RESOLUTION_2560x1440);
    FUN_004308c0(this);
    return;
}

void __thiscall handle3840x2160ResolutionSelected(void *this)
{
    setResolution(RESOLUTION_3840x2160);
    FUN_004308c0(this);
    return;
}

// Handler for resolution menu item update event
// Sets menu item enabled and if the matching resolution is selected sets the checked property
static void updateResolutionMenuItem(void *pCmdUI, int myResolution)
{
    void **vtable = *(void ***)pCmdUI;
    ((CCmdUI_Enable)vtable[0])(pCmdUI, 1);
    ((CCmdUI_SetCheck)vtable[1])(pCmdUI, *RESOLUTION_IDENTIFIER_GLOBAL == myResolution ? 1 : 0);
}

// Handler for each resolution menu item update individually
void __thiscall handle1280x720ResolutionUpdate(void *this, void *pCmdUI) { updateResolutionMenuItem(pCmdUI, RESOLUTION_1280x720); }
void __thiscall handle1280x800ResolutionUpdate(void *this, void *pCmdUI) { updateResolutionMenuItem(pCmdUI, RESOLUTION_1280x800); }
void __thiscall handle1600x900ResolutionUpdate(void *this, void *pCmdUI) { updateResolutionMenuItem(pCmdUI, RESOLUTION_1600x900); }
void __thiscall handle1920x1080ResolutionUpdate(void *this, void *pCmdUI) { updateResolutionMenuItem(pCmdUI, RESOLUTION_1920x1080); }
void __thiscall handle2560x1440ResolutionUpdate(void *this, void *pCmdUI) { updateResolutionMenuItem(pCmdUI, RESOLUTION_2560x1440); }
void __thiscall handle3840x2160ResolutionUpdate(void *this, void *pCmdUI) { updateResolutionMenuItem(pCmdUI, RESOLUTION_3840x2160); }

// Fixes rendering issues at larger resolutions
// by initializing menu offset values for each sprite to 0 in constructor
void zeroMenuOffsetsAndCallA6840(void)
{
    __asm__ volatile(
        "movl $0, 0xa944(%%ebp)\n"
        "movl $0, 0xa948(%%ebp)\n"
        "jmp %P0\n"
        :
        : "i"(FUN_004a6840));
}

static const ImageOverrideEntry OVERRIDE_TABLE[] = {
    {"topstrip", 1280, "tops1280.bin"},
    {"topstrip", 1600, "tops1600.bin"},
    {"topstrip", 1920, "tops1920.bin"},
    {"topstrip", 2560, "tops2560.bin"},
    {"topstrip", 3840, "tops3840.bin"},
    {"iconback", 1280, "iback1280.bin"},
    {"iconback", 1600, "iback1600.bin"},
    {"iconback", 1920, "iback1920.bin"},
    {"iconback", 2560, "iback2560.bin"},
    {"iconback", 3840, "iback3840.bin"},
};

#define OVERRIDE_TABLE_LEN (sizeof(OVERRIDE_TABLE) / sizeof(OVERRIDE_TABLE[0]))

// Overrides loadImage function from original binary to insert our own patched images
void *__fastcall loadImageOverride(const char *name)
{

    const ImageOverrideEntry *entry = 0;
    for (int i = 0; i < (int)OVERRIDE_TABLE_LEN; i++)
    {
        if (streq(OVERRIDE_TABLE[i].name, name) && OVERRIDE_TABLE[i].width == RENDER_WIDTH_GLOBAL)
        {
            entry = &OVERRIDE_TABLE[i];
            break;
        }
    }
    if (!entry)
    {
        return loadImage(name);
    }

    char path[512];
    char cwd[256];
    recoil_GetCurrentDirectoryA(sizeof(cwd), cwd);
    recoil_sprintf(path, "%s\\patch-assets\\%s", cwd, entry->file);

    void *fp = recoil_fopen(path, "rb");
    if (!fp)
    {
        return loadImage(name);
    }

    void *image = FUN_0046ef70(fp);
    recoil_fclose(fp);

    if (!image)
    {
        return loadImage(name);
    }

    return image;
}

static int streq(const char *a, const char *b)
{
    while (*a && *a == *b)
    {
        a++;
        b++;
    }
    return *a == *b;
}