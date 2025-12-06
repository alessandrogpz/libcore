#include <stdio.h>
#include <ctype.h>  // For standard toupper
#include <stdlib.h> // For EXIT_SUCCESS/FAILURE
#include "includes.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
void run_toupper_test(int c)
{
    int core_result = core_toupper(c);
    int std_result = toupper(c);

    printf("--- Test: Character '%c' (ASCII %d) ---\n", (char)c, c);
    printf("  Expected: '%c' (ASCII %d)\n", (char)std_result, std_result);
    printf("  core_toupper result: '%c' (ASCII %d)\n", (char)core_result, core_result);

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
    printf("--- Running core_toupper vs toupper Comparison Tests ---\n\n");

    // 1. Lowercase Tests (Expected: Conversion)
    run_toupper_test('a');
    run_toupper_test('m');
    run_toupper_test('z');

    // 2. Uppercase Tests (Expected: No Change)
    run_toupper_test('A');
    run_toupper_test('M');
    run_toupper_test('Z');

    // 3. Digit Tests (Expected: No Change)
    run_toupper_test('0');
    run_toupper_test('9');

    // 4. Symbol/Control Tests (Expected: No Change)
    run_toupper_test('@'); // Before 'A'
    run_toupper_test('['); // After 'Z'
    run_toupper_test('`'); // Before 'a'
    run_toupper_test(0);   // NULL character

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}