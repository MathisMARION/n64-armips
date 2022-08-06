#include <system_error>
#include <cstdio>

#include "armips/Core/Assembler.h"
#include "n64crc/n64crc.h"
#include "n64_armips.hpp"
#include "log.h"

/*
 * Creates a wrapper file to write to the ROM file:
 *
 * .n64
 * .open "rom_file", 0x00000000
 * .include "asm_file"
 * .close
 */
static fs::path create_asm_wrapper_file(const fs::path &asm_file, const fs::path &rom_file)
{
    std::error_code err;
    int ret;

    fs::path tmp_file = fs::temp_directory_path(err) / "n64-armips-tmp.asm";
    FATAL_ON(err, "error finding temporary directory: %s", err.message().c_str());

    std::FILE *fp = std::fopen(tmp_file.c_str(), "wt");
    FATAL_ON(!fp, "error opening '%s'", tmp_file.c_str());
    std::fprintf(fp, ".n64\n");
    std::fprintf(fp, ".open \"%s\", 0x00000000\n", rom_file.c_str());
    std::fprintf(fp, ".include \"%s\"\n", asm_file.c_str());
    std::fprintf(fp, ".close\n");
    ret = fclose(fp);
    FATAL_ON(ret, "error closing '%s'", tmp_file.c_str());

    return tmp_file;
}

void n64_armips_assemble(const fs::path &asm_file, const fs::path &rom_file)
{
    ArmipsArguments armips_args;
    std::error_code err;
    int ret;

    fs::path tmp_file = create_asm_wrapper_file(asm_file, rom_file);

    if (asm_file.has_parent_path()) {
        fs::current_path(asm_file.parent_path(), err);
        FATAL_ON(err, "error setting current directory to '%s': %s",
            asm_file.parent_path().c_str(), err.message().c_str());
    }

    armips_args.inputFileName = tmp_file;

    if (!runArmips(armips_args))
        FATAL("armips failure");

    ret = std::remove(tmp_file.c_str());
    FATAL_ON(ret, "error deleting '%s'", tmp_file.c_str());

    if (n64crc_recompute(rom_file.c_str()))
        FATAL("n64crc failure");
}
