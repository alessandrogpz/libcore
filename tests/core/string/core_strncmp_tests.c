#include <stdio.h>
#include <string.h> // For standard strncmp
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
void run_strncmp_test(const char *test_name, const char *s1, const char *s2, size_t n)
{
    int core_result = core_strncmp(s1, s2, n);
    int std_result = strncmp(s1, s2, n);

    // Check if both results are exactly equal (for n=0 or perfect match) OR have the same sign.
    int exact_match = (core_result == std_result);
    int sign_match = check_sign(core_result, std_result);

    const char *status_color = (exact_match || sign_match) ? "\033[32mPASS\033[0m" : "\033[31mFAIL\033[0m";

    printf("--- Test: %s (N=%zu) ---\n", test_name, n);
    printf("  S1: \"%s\"\n", s1);
    printf("  S2: \"%s\"\n", s2);
    printf("  core_strncmp result: %d\n", core_result);
    printf("  std_strncmp result: %d\n", std_result);
    printf("  -> %s\n\n", status_color);

    if (!(exact_match || sign_match))
    {
        printf("\033[31m  CRITICAL FAILURE: Sign or Exact Value Mismatch\033[0m\n\n");
    }
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_strncmp vs strncmp Comparison Tests ---\n\n");

    // 1. Identity Check (Should return 0)
    run_strncmp_test("1. Identical Strings", "Hello World", "Hello World", 12);

    // 2. N=0 Check (Should return 0)
    run_strncmp_test("2. N equals Zero", "Hello World", "Hello World", 0);

    // 3. Difference Within N (ft > std, Positive Return)
    run_strncmp_test("3. Positive Difference (Within N)", "Aello", "Bello", 5);

    // 4. Difference Within N (ft < std, Negative Return)
    run_strncmp_test("4. Negative Difference (Within N)", "Hello", "Hemma", 5);

    // 5. Difference Beyond N (Should return 0)
    run_strncmp_test("5. Difference Beyond N", "Hello World", "Hello World!", 11);

    // 6. Null-Terminator Stop (S1 is Shorter)
    // Compares 'A\0' vs 'AB', for N=3. Stops at '\0'.
    run_strncmp_test("6. S1 Short (Null Stop)", "A", "AB", 3);

    // 7. Null-Terminator Stop (S2 is Shorter)
    // Compares 'AB' vs 'A\0', for N=3. Stops at '\0'.
    run_strncmp_test("7. S2 Short (Null Stop)", "AB", "A", 3);

    // 8. Null-Terminator Stop (Both Shorter than N)
    run_strncmp_test("8. Both Shorter than N", "Cat", "Cat!", 5);

    // 9. Edge Case: Different Case
    run_strncmp_test("9. Case Difference", "apple", "Apple", 5);

    // 10. Empty Strings
    run_strncmp_test("10. Empty Strings", "", "", 5);

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}