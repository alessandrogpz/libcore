#include <stdio.h>
#include <string.h> // For standard memchr
#include <stdlib.h> // For NULL, EXIT_SUCCESS
#include "libcore.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
void run_memchr_test(const char *test_name, const void *s, int c, size_t n)
{
    // The standard memchr must be used with the same arguments
    char *core_ptr = core_memchr(s, c, n);
    char *std_ptr = memchr(s, c, n);

    printf("--- Test: %s (N=%zu) ---\n", test_name, n);
    printf("  Search for char '%c' (ASCII %d) in memory block\n", (char)c, c);
    printf("  core_ptr: %p\n", (void *)core_ptr);
    printf("  std_ptr: %p\n", (void *)std_ptr);

    // --- 1. Check Pointer Equality (NULL or Address) ---
    // If both return the same address (or both return NULL/0), they match.
    if (core_ptr == std_ptr)
    {
        printf("  -> \033[32mPASS\033[0m: Pointers Match.\n");

        // Extra check: If found, verify the content at that pointer is correct
        if (core_ptr != NULL)
            printf("  -> Found Value: '%c'\n\n", *core_ptr);
        else
            printf("  -> Result: NOT FOUND (NULL)\n\n");
    }
    else
    {
        printf("  -> \033[31mFAIL (Mismatch)\033[0m: Pointers Differ.\n");
        printf("  -> Expected location: %p, Your location: %p\n\n", (void *)std_ptr, (void *)core_ptr);
    }
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_memchr vs memchr Comparison Tests ---\n\n");

    // Test data block containing a null byte
    const unsigned char data[] = {'H', 'e', '\0', 'l', 'l', 'o', '!'}; // Length 7

    // 1. Basic Search: Found before N runs out
    run_memchr_test("1. Basic Found ('e')", data, 'e', 7);

    // 2. Search Stops at N: Target is beyond N limit (N=3)
    // Should stop after '\0', fail to find 'l'.
    run_memchr_test("2. Stop at N, Not Found ('l')", data, 'l', 3);

    // 3. Null Byte Search: Search for the null byte itself
    run_memchr_test("3. Search for Null ('\\0')", data, '\0', 7);

    // 4. Critical Case: Search MUST continue past '\0'
    // Target is 'l' at index 3. Search N=5.
    // If the function stops at the null byte (index 2), it fails.
    run_memchr_test("4. Found PAST Null Byte ('l')", data, 'l', 5);

    // 5. Found at Final Byte (N=7)
    run_memchr_test("5. Found at Final Byte ('!')", data, '!', 7);

    // 6. Character Not Found
    run_memchr_test("6. Not Found ('z')", data, 'z', 7);

    // 7. N=0 Check
    run_memchr_test("7. Zero N (N=0)", data, 'H', 0);

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}