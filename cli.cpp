#include "n64_armips.hpp"
#include "log.h"

int main(int argc, char *argv[])
{
    FATAL_ON(argc != 3, "Usage: %s asm-file rom-file", argv[0]);

    fs::path asm_file = fs::absolute(argv[1]);
    fs::path rom_file = fs::absolute(argv[2]);

    n64_armips_assemble(asm_file, rom_file);

    return EXIT_SUCCESS;
}
