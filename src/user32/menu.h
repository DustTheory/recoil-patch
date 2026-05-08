#ifndef MENU_H
#define MENU_H

#include <windows.h>

int patchMyMenu(HMENU menu);
int patchResolutionsMenu(HMENU menu);
int patchFileMenuWithSignature(HMENU menu);
int fileMenuHasBeenPatchedWithSignature(HMENU fileMenu);

void traverseAndLogMenu(HMENU menu, int depth);

extern const char EMULJETINA_SIGNATURE[];

enum LauncherMenuBarDropdownIndex
{
    LAUNCHER_MENU_BAR_CATEGORY_FILE = 0,
    LAUNCHER_MENU_BAR_CATEGORY_OPTIONS = 2,
    LAUNCHER_MENU_BAR_CATEGORY_HELP = 3
};

enum ResolutionOptionsMenuItemId
{
    MENU_ITEM_ID_320x200 = 0x206,
    MENU_ITEM_ID_320x240 = 0x207,
    MENU_ITEM_ID_640x400 = 0x208,
    MENU_ITEM_ID_640x480 = 0x209,
    MENU_ITEM_ID_800x600 = 0x9C71,
    MENU_ITEM_ID_1024x768 = 0x210,
    MENU_ITEM_ID_1280x720 = 0x211,
    MENU_ITEM_ID_1280x800 = 0x212,
    MENU_ITEM_ID_1600x900 = 0x213,
    MENU_ITEM_ID_1920x1080 = 0x214,
    MENU_ITEM_ID_2560x1440 = 0x215,
    MENU_ITEM_ID_3840x2160 = 0x216
};

typedef struct
{
    const char *resolutionString;
    unsigned int menuItemId;
} ResolutionOption;

#define COUNT_NUM_RESOLUTIONS 6
#define OPTIONS_MENU_POSITION_TO_INSERT_NEW_RESOLUTIONS 11
extern const ResolutionOption NEW_RESOLUTIONS[COUNT_NUM_RESOLUTIONS];

#endif