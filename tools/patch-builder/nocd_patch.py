def applyNoCdPatch(binary):
    # JNZ at 0x0042e75a skips the CD dialog when drive search returns non-NULL.
    binary.patch_address(0x0042e75a, [0xEB])
    print(f"  no-CD patch: JNZ -> JMP at 0x0042e75a")
