#include "libcore.h"
#include <stdio.h>
#include <string.h>

// ====================================================================
//                 TEST EXECUTION MACRO
// ====================================================================

// Macro to run and display a single test result for printf
// We use a macro because core_printf handles varargs directly, 
// and we don't have a core_vprintf exposed to wrap easily.
#define RUN_PRINTF_TEST(test_name, format, ...) \
    do { \
        printf("--- Test: %s ---\n", test_name); \
        \
        printf("  [CORE]: "); \
        fflush(stdout); \
        int core_ret = core_printf(format, ##__VA_ARGS__); \
        \
        printf("  [STD] : "); \
        fflush(stdout); \
        int std_ret = printf(format, ##__VA_ARGS__); \
        \
        printf("  core_ret: %d\n", core_ret); \
        printf("  std_ret: %d\n", std_ret); \
        \
        if (core_ret == std_ret) { \
            printf("  -> \033[32mPASS\033[0m: Return values match.\n\n"); \
        } else { \
            printf("  -> \033[31mFAIL (Mismatch)\033[0m: Return values differ (Core: %d, Std: %d)\n\n", core_ret, std_ret); \
        } \
    } while (0)

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_printf vs printf Comparison Tests ---\n\n");

    // 1. Simple String
    RUN_PRINTF_TEST("1. Simple String", "Hello, World!\n");

    // 2. Characters
    RUN_PRINTF_TEST("2. Characters", "Char: %c\n", 'A');

    // 3. Strings
    RUN_PRINTF_TEST("3. Strings", "String: %s\n", "libcore");

    // 4. Integers
    RUN_PRINTF_TEST("4. Integers (d/i)", "Int: %d, %i\n", 42, -42);

    // 5. Unsigned
    RUN_PRINTF_TEST("5. Unsigned", "Unsigned: %u\n", 4294967295U);

    // 6. Hexadecimal
    RUN_PRINTF_TEST("6. Hexadecimal", "Hex: %x, %X\n", 255, 255);

    // 7. Pointer
    int a = 42;
    RUN_PRINTF_TEST("7. Pointer", "Pointer: %p\n", &a);

    // 8. Percent
    RUN_PRINTF_TEST("8. Percent", "Percent: %%\n");

    printf("--- All Tests Complete ---\n");

    return (0);
}
