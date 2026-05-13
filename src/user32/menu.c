#include <windows.h>
#include "menu.h"
#include "user32.h"

const char EMULJETINA_SIGNATURE[] = "Patched by Emuljetina";

const ResolutionOption NEW_RESOLUTIONS[COUNT_NUM_RESOLUTIONS] = {
    {"1280x720", MENU_ITEM_ID_1280x720},
    {"1280x800", MENU_ITEM_ID_1280x800},
    {"1600x900", MENU_ITEM_ID_1600x900},
    {"1920x1080", MENU_ITEM_ID_1920x1080},
    {"2560x1440", MENU_ITEM_ID_2560x1440},
    {"3840x2160", MENU_ITEM_ID_3840x2160}};

int patchMyMenu(HMENU menu)
{
    traverseAndLogMenu(menu, 0);
    ASSERT(patchFileMenuWithSignature(menu), "Failed to patch File menu with signature");
    ASSERT(patchResolutionsMenu(menu), "Failed to patch Resolutions menu");

    return 1;
}

int patchResolutionsMenu(HMENU menu)
{

    writeLog("Patching Resolutions menu...\n");
    HMENU optionsMenu = GetSubMenu(menu, LAUNCHER_MENU_BAR_CATEGORY_OPTIONS);
    ASSERT(optionsMenu, "Failed to get Options menu");

    for (int i = 0; i < COUNT_NUM_RESOLUTIONS; i++)
    {

        const ResolutionOption *option = &NEW_RESOLUTIONS[i];
        const char *menuItemString = option->resolutionString;
        const int insertPosition = OPTIONS_MENU_POSITION_TO_INSERT_NEW_RESOLUTIONS + i;
        UINT menuItemId = option->menuItemId;

        writeLog("Inserting new resolution menu item: %s with ID: 0x%X\n", menuItemString, menuItemId);
        InsertMenuA(optionsMenu, insertPosition, MF_BYPOSITION, menuItemId, menuItemString);
    }

    return 1;
}

int patchFileMenuWithSignature(HMENU menu)
{
    writeLog("Patching File menu with signature...\n");
    HMENU fileMenu = GetSubMenu(menu, LAUNCHER_MENU_BAR_CATEGORY_FILE);
    ASSERT(fileMenu, "Failed to get File menu");

    ASSERT(!fileMenuHasBeenPatchedWithSignature(fileMenu), "File menu has already been patched with signature");

    int itemCount = GetMenuItemCount(fileMenu);
    int appendResult = AppendMenuA(fileMenu, MF_STRING, 0xB16B00B5, EMULJETINA_SIGNATURE);
    ASSERT(appendResult, "Failed to append signature menu item to File menu");

    return 1;
}

int fileMenuHasBeenPatchedWithSignature(HMENU fileMenu)
{
    int itemCount = GetMenuItemCount(fileMenu);

    char buffer[256];
    GetMenuStringA(fileMenu, itemCount - 1, buffer, sizeof(buffer), MF_BYPOSITION);

    return strcmp(buffer, EMULJETINA_SIGNATURE) == 0;
}

void traverseAndLogMenu(HMENU menu, int depth)
{
    int itemCount = GetMenuItemCount(menu);
    for (int i = 0; i < itemCount; i++)
    {
        UINT menuItemId = GetMenuItemID(menu, i);
        char buffer[256];
        GetMenuStringA(menu, i, buffer, sizeof(buffer), MF_BYPOSITION);
        writeLog("%*sMenu Item %d: %s; ID: 0x%X\n", depth * 2, "", i, buffer, menuItemId);

        HMENU subMenu = GetSubMenu(menu, i);
        if (subMenu)
        {
            traverseAndLogMenu(subMenu, depth + 1);
        }
    }
}
