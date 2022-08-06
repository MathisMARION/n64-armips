# n64-armips

This project is a wrapper around the [`armips`](https://github.com/Kingcom/armips)
assembler by Kingcom, to make development easier for N64 ROM hacking. I am
using this a cross platform tool to replace the Windows only [Simple ARMIPS
GUI](https://github.com/DavidSM64/SimpleArmipsGui) written by DavidSM64.

Compared to `armips`:
- Automatic recomputing of checksum
- No need to specify `.n64` at the start of assembly files
- No need to specify `.open` and `.close` in the assembly code, the wrapper
  takes care of assembling to the specified ROM

Usage:

    n64-armips patch.asm rom.z64

## Compilation

Initialize the `armips` submodule:

    git submodule update --init

Configure and compile the project:

    cmake .
    make
