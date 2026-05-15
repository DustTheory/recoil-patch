import sys

import lief

from nocd_patch import applyNoCdPatch
from widescreen_patch import applyWidescreenPatch

def main():
    if len(sys.argv) != 3:
        print("Usage: python main.py <path_to_binary> <output_path>")
        return

    binary_path = sys.argv[1]
    binary_output_path = sys.argv[2]

    binary = lief.parse(binary_path)
    if not binary:
        print(f"Failed to parse the binary: {binary_path}")
        return

    print(f"Successfully parsed the binary: {binary_path}")

    applyWidescreenPatch(binary)
    applyNoCdPatch(binary)

    builder_config = lief.PE.Builder.config_t()
    builder_config.imports = True

    binary.write(binary_output_path, builder_config)
    print(f"Modified binary written to: {binary_output_path}")


if __name__ == "__main__":
    main()
