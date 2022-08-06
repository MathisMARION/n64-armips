cmake_minimum_required(VERSION 3.16)
project(n64-armips)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW) # option() does not overwrite
set(ARMIPS_USE_STD_FILESYSTEM ON)
set(ARMIPS_LIBRARY_ONLY ON)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/armips)

add_executable(n64-armips
    main.cpp
    n64crc/n64crc.c
)
add_dependencies(n64-armips armips)
target_link_libraries(n64-armips armips)
