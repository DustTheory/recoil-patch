#!/usr/bin/env python3
"""Convert a PNG to the raw binary format expected by FUN_0046ef70.

Usage: python image_convert.py input.png output.bin
"""

import struct
import sys
from pathlib import Path


def convert(png_path: Path, bin_path: Path):
    try:
        from PIL import Image
    except ImportError:
        print("Pillow required: pip install Pillow")
        sys.exit(1)

    img = Image.open(png_path).convert("RGBA")
    width, height = img.size
    pixels = list(img.getpixel((x, y)) for y in range(height) for x in range(width))

    has_alpha = any(p[3] < 255 for p in pixels)
    flags = 0x01 | (0x08 if has_alpha else 0x00)  # bit0=16bpp, bit3=alpha plane

    rgb565 = bytearray()
    alpha = bytearray()
    for r, g, b, a in pixels:
        rgb565 += struct.pack("<H", ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3))
        if has_alpha:
            alpha.append(a)

    header = struct.pack("<B3xHHB3xH2x", flags, width, height, 0, 0)

    with open(bin_path, "wb") as f:
        f.write(header)
        f.write(rgb565)
        if has_alpha:
            f.write(alpha)

    print(f"{png_path} -> {bin_path} ({width}x{height}, alpha={has_alpha})")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(__doc__)
        sys.exit(1)
    convert(Path(sys.argv[1]), Path(sys.argv[2]))
