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

## How to run

**Only the DirectX renderer is supported** — the 3dfx/Glide version is not patched yet.

### Linux (Wine)

1. Copy the built files from `build/` into your Recoil game directory.
2. Launch via `scripts/run.sh`

If the game HUD does not show any digits, you are probably missing the symbol.ttf font. Wine has its own version you can get [here](https://github.com/wine-mirror/wine/blob/master/fonts/symbol.ttf) — drop it into `C:\Windows\Fonts`.

### Windows 10

1. Copy the built files from `build/` into your Recoil game directory.
2. **Compatibility mode:** Right-click the game executable → Properties → Compatibility, and set it to Windows 98/95, XP, or 7.
3. **DirectPlay:** Enable it via Control Panel → Programs → Turn Windows features on or off → Legacy Components → DirectPlay.
4. **dgVoodoo2:** Download from [dgVoodoo2's github](https://github.com/dege-diosg/dgVoodoo2) and copy `D3D8.dll`, `D3D9.dll`, `D3DImm.dll`, and `DDraw.dll` from the `MS/x86` folder into the game directory.
5. **msvcp50.dll:** Required legacy MSVC runtime. Extract from a Windows installation or find it online (and catch a virus). Place it in the game directory.

## Build instructions

**Linux only.** The build scripts are Linux-specific and will not work on other platforms.

**Prerequisites:** `i686-w64-mingw32-gcc`, `wine`, Python 3.10+, `uv`

1. Copy `.env.example` to `.env` and set `WINEPREFIX` to the Wine prefix where Recoil is installed (e.g. `~/.wine` or `~/.PlayOnLinux/wineprefix/recoil`). Recoil must be installed at `C:\Games\Zipper\RECOIL` — if it isn't, also update `RECOIL_DIR` in `.env` accordingly.
2. Run `scripts/build.sh <path_to_original_RECOIL.dat>`
