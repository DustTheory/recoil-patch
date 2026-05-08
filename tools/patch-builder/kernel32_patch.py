# Patches in a custom dll in place of kernel32.dll
# Not utilized for now but may come in handy

def patchKernel32(binary):
    for entry in binary.imports:
        if entry.name.lower() == "kernel32.dll":
            entry.name = "patchk32.dll"
