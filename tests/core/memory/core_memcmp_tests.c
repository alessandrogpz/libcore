#include <stdio.h>
#include <string.h> // For standard memcmp
#include <stdlib.h> // For EXIT_SUCCESS
#include "libcore.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Checks if two integers have the same sign (0, positive, or negative)
int check_sign(int core_result, int std_result)
{
    if (core_result == 0 && std_result == 0)
        return 1;
    if (core_result > 0 && std_result > 0)
        return 1;
    if (core_result < 0 && std_result < 0)
        return 1;
    return 0;
}

// Function to run and display a single test result
void run_memcmp_test(const char *test_name, const void *s1, const void *s2, size_t n)
{
    int core_result = core_memcmp(s1, s2, n);
    int std_result = memcmp(s1, s2, n);

    // Check if both results are exactly equal (for n=0 or perfect match) OR have the same sign.
    int exact_match = (core_result == std_result);
    int sign_match = check_sign(core_result, std_result);

    const char *status_color = (exact_match || sign_match) ? "\033[32mPASS\033[0m" : "\033[31mFAIL\033[0m";

    printf("--- Test: %s (N=%zu) ---\n", test_name, n);
    printf("  S1 starts with: %02X %02X %02X...\n", *(unsigned char *)s1, *((unsigned char *)s1 + 1), *((unsigned char *)s1 + 2));
    printf("  S2 starts with: %02X %02X %02X...\n", *(unsigned char *)s2, *((unsigned char *)s2 + 1), *((unsigned char *)s2 + 2));
    printf("  core_memcmp result: %d\n", core_result);
    printf("  std_memcmp result: %d\n", std_result);
    printf("  -> %s\n\n", status_color);
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_memcmp vs memcmp Comparison Tests ---\n\n");

    // DATA SETUP: Blocks containing null bytes ('\0' or 0x00)
    // S1: H, e, l, l, o, \0, W, o, r, l
    unsigned char s1[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x00, 0x57, 0x6F, 0x72, 0x6C};
    // S2: H, e, l, L, o, \0, W, O, r, l
    unsigned char s2[] = {0x48, 0x65, 0x6C, 0x4C, 0x6F, 0x00, 0x57, 0x4F, 0x72, 0x6C};

    // 1. Identity Check (N=3)
    // Compares: H, e, l (Identical) -> Should return 0
    run_memcmp_test("1. Identical (N=3)", s1, s2, 3);

    // 2. Difference Within N (N=4)
    // Compares: H, e, l, l vs H, e, l, L. Difference at 4th byte (0x6C vs 0x4C).
    // Result: Positive (0x6C - 0x4C = 32)
    run_memcmp_test("2. Positive Difference (N=4)", s1, s2, 4);

    // 3. Difference Beyond N (N=4)
    // Compares: H, e, l, l (s1) vs H, e, l, L (s2). Difference at 4th byte.
    // Result: 0, because the comparison stops before the difference in S2 is found (0x6C vs 0x4C)
    run_memcmp_test("3. Difference Beyond N (N=3)", s1, s2, 3);

    // 4. Critical Null Byte Test (N=6)
    // Compares: H, e, l, l, o, \0. Must continue past the 5th byte (0x6F) to include the 0x00 byte.
    // Result: 0
    run_memcmp_test("4. Search Includes Null Byte (N=6)", s1, s2, 6);

    // 5. Comparison Past Null Byte (N=8)
    // Compares: H, e, l, l, o, \0, W, o (s1) vs H, e, l, L, o, \0, W, O (s2)
    // Difference is found at 4th byte (0x6C vs 0x4C).
    run_memcmp_test("5. Difference Before Null (N=8)", s1, s2, 8);

    // 6. Zero N Check
    run_memcmp_test("6. N equals Zero (N=0)", s1, s2, 0);

    // 7. Negative Difference Check (N=8, compare s2 to s1)
    // Compares: H, e, l, L vs H, e, l, l. Difference: 0x4C - 0x6C.
    run_memcmp_test("7. Negative Difference (N=4)", s2, s1, 4);

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}