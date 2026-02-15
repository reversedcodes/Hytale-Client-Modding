# Hytale Client Mod

This repository serves as a practical example for **Hytale Client modding** and **reverse engineering**. It provides a workflow to bypass the challenges of Native AOT compilation and start coding your own modifications.

---

# Reverse Engineering the Hytale Client

The Hytale client is compiled using **Native AOT**.  
Most of the game logic is located inside `HytaleClient.dll`, which was originally written in **C#**.

## The Challenge

The main difficulty is making the loaded DLL’s C# logic visible again.

- IDA Pro currently cannot properly decompile Native AOT binaries (and there is no reliable plugin for this).
- Tools like **dnSpy** also do not work for Native AOT.

## The Solution

A working reconstruction workflow:

- Scylla → dump and rebuild imports
- Ghidra → analyze the dumped binary
- Native AOT Ghidra Plugin → reconstruct managed structures

This does **not** restore everything, but it gives a very strong base for analysis.

---

## 1. Dumping the Client (Scylla)
To analyze the binary, we first need to extract a "clean" version from memory and fix the **Import Address Table (IAT)**.

1. **Launch Hytale**: The process must be running.
2. **Open Scylla**: Run `Scylla_x64.exe` (Download [here](https://github.com/NtQuery/Scylla/releases)).
3. **Attach**: Select the `HytaleClient.exe` process.
4. **Search IAT**: Click **IAT Autosearch** and confirm.
5. **Get Imports**: Click the **Get Imports** button.
6. **Dump**: 
   - Click **Dump** and save it as `HytaleClient_dump.exe`.
   - Click **Fix Dump**, select the `HytaleClient_dump.exe` you just created.
   - This will generate `HytaleClient_dump_SCY.exe`.

---

## 2. Reverse Engineering (Ghidra)
To make the native code readable again, we use Ghidra with a specific Native AOT plugin.

1. **Install Plugin**: Download the [Native AOT Analyzer](https://github.com/Washi1337/ghidra-nativeaot/releases).
2. **Setup Ghidra**: 
   - Open [Ghidra](https://github.com/NationalSecurityAgency/ghidra/releases).
   - Go to `File` -> `Install Extensions`.
   - Select the NativeAOT Zip file and restart Ghidra.
3. **Analysis**:
   - Import `HytaleClient_dump_SCY.exe` into a new project.
   - When prompted for analysis, ensure **Native AOT Analyzer** is selected (this is crucial).
   - Wait for the analysis to complete (this may take several minutes).

---

## 3. Development Setup (CMake)
It is mandatory to build your mod DLL in **Release** mode for it to work correctly.

* **IDE**: Visual Studio Code with the **CMake Extension**.
* **Compiler**: MSVC 2024/2026 x64 (Release).
* **Usage**: Open the project in VS Code. The CMake extension should detect the project automatically. Simply select the `MSVC x64 Release` kit and build.

---

## 4. Injector
The project includes a simple Python-based injector using the `PyMem` library.

**Installation:**
```bash
pip install -r requirements.txt
```

---

## License

This project is licensed under the Apache License 2.0.  
You are free to use, modify, and distribute this software under the terms of the license.