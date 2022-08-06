#ifndef LOG_H
#define LOG_H

#include <stdlib.h>
#include <stdio.h>

#define ANSI_RED   "\x1B[31m"
#define ANSI_CLEAR "\x1B[0m"

#define FATAL(fmt, ...) do {                       \
    PRINT_COLOR(ANSI_RED, fmt, ##__VA_ARGS__);     \
    exit(EXIT_FAILURE);                            \
} while (0)

#define FATAL_ON(cond, fmt, ...) do {              \
    if (cond) {                                    \
        PRINT_COLOR(ANSI_RED, fmt, ##__VA_ARGS__); \
        exit(EXIT_FAILURE);                        \
    }                                              \
} while (0)

#define PRINT_COLOR(color, fmt, ...) \
    printf(ANSI_RED fmt ANSI_CLEAR "\n", ##__VA_ARGS__)

#endif // LOG_H
