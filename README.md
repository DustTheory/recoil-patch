# Recoil-patch
## The ultimate patch for the 1999 PC video game "Recoil"

<img width="671" height="547" alt="image" src="https://github.com/user-attachments/assets/e2f1ae7e-93e6-4ebd-aa05-2967983bc0f9" />

Currently covers:
* Widescreen patch with the following resolution options added in launcher:
  * 1280x720
  * 1280x800
  * 1600x900
  * 1920x1080
  * 2560x1440
  * 3840x2160
* HUD background patch on non-standard resolutions - first of it's kind for recoil afaik
* no-CD patch
 
Left to do:
* Noclip cheat

## Build instructions:

**Linux only.** The build scripts are Linux-specific and will not work on other platforms.

**Prerequisites:** `i686-w64-mingw32-gcc`, `wine`, Python 3.10+, `uv`

1. Copy `.env.example` to `.env` and set `WINEPREFIX` to the Wine prefix where Recoil is installed (e.g. `~/.wine` or `~/.PlayOnLinux/wineprefix/recoil`). Recoil must be installed at `C:\Games\Zipper\RECOIL` — if it isn't, also update `RECOIL_DIR` in `.env` accordingly.
2. Run `cd scripts && ./build_and_apply.sh`
3. Launch the game with `./run.sh` (or `./run_debugger.sh` for a Wine debugger session) — running the game directly via Wine won't work as the scripts set the required `WINEDLLOVERRIDES`

## Notes
Not tested on an actual windows installation yet - works well under wine on linux

If the game HUD does not show any digits, you are probably missing the symbol.ttf font (common in wine).
Wine actually has it's own font that emulates the original windows symbol.ttf font, and you can get it [here](https://github.com/wine-mirror/wine/blob/master/fonts/symbol.ttf) and drop into your C:\Windows\Fonts folder
