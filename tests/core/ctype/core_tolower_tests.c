#include <stdio.h>
#include <ctype.h>  // For standard tolower
#include <stdlib.h> // For EXIT_SUCCESS/FAILURE
#include "libcore.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
void run_tolower_test(int c)
{
    int core_result = core_tolower(c);
    int std_result = tolower(c);

    printf("--- Test: Character '%c' (ASCII %d) ---\n", (char)c, c);
    printf("  Expected: '%c' (ASCII %d)\n", (char)std_result, std_result);
    printf("  core_tolower result: '%c' (ASCII %d)\n", (char)core_result, core_result);

    // --- 1. Check Return Value ---
    if (core_result == std_result)
    {
        printf("  -> \033[32mPASS\033[0m\n\n");
    }
    else
    {
        printf("  -> \033[31mFAIL (Mismatch)\033[0m\n\n");
    }
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_tolower vs tolower Comparison Tests ---\n\n");

    // 1. Uppercase Tests (Expected: Conversion)
    run_tolower_test('A');
    run_tolower_test('M');
    run_tolower_test('Z');

    // 2. Lowercase Tests (Expected: No Change)
    run_tolower_test('a');
    run_tolower_test('m');
    run_tolower_test('z');

    // 3. Digit Tests (Expected: No Change)
    run_tolower_test('1');
    run_tolower_test('8');

    // 4. Symbol/Control Tests (Expected: No Change)
    run_tolower_test('@');  // Before 'A'
    run_tolower_test('[');  // After 'Z'
    run_tolower_test('{');  // After 'z'
    run_tolower_test('\n'); // Newline character

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}