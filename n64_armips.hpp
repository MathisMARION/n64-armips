#ifndef N64_ARMIPS_HPP
#define N64_ARMIPS_HPP

#include "armips/Util/FileSystem.h"

void n64_armips_assemble(const fs::path &asm_file, const fs::path &rom_path);

#endif // N64_ARMIPS_HPP
