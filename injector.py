import os
import pymem
import pymem.process

dll_path = os.path.abspath(r"build\src\client\client.dll")

if not os.path.isfile(dll_path):
    print(f"Error: DLL not found at {dll_path}")
    raise SystemExit(1)

try:
    pm = pymem.Pymem("HytaleClient.exe")
except Exception as e:
    print("Error: Could not open process")
    print(e)
    raise SystemExit(1)

try:
    pymem.process.inject_dll_from_path(pm.process_handle, dll_path)
    print("Injected ✔")
except Exception as e:
    print("Injection failed:", e)
