#include <stdio.h>
#include <stdlib.h> // For standard strdup, malloc, free
#include <string.h> // For standard strlen and memcmp
#include "includes.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
void run_strdup_test(const char *test_name, const char *src)
{
    size_t len = core_strlen(src);

    // --- 1. Run core_strdup ---
    char *core_dup = core_strdup(src);

    printf("--- Test: %s ---\n", test_name);
    printf("  Source String: \"%s\" (Len: %zu)\n", src, len);
    printf("  core_dup Address: %p\n", (void *)core_dup);

    if (core_dup == NULL)
    {
        printf("  -> \033[31mFAIL\033[0m: Allocation failed (returned NULL).\n\n");
        return;
    }

    // --- 2. Check Content (Same characters) ---
    if (strcmp(src, core_dup) == 0)
        printf("  -> Content Check: \033[32mPASS\033[0m (Strings are identical)\n");
    else
        printf("  -> Content Check: \033[31mFAIL\033[0m (Content mismatch)\n");

    // --- 3. Check Independence (Different memory location) ---
    if (core_dup != src)
        printf("  -> Address Check: \033[32mPASS\033[0m (Pointers are different)\n\n");
    else
        printf("  -> Address Check: \033[31mFAIL\033[0m (Pointers are identical—no duplication occurred)\n\n");

    // Clean up allocated memory
    free(core_dup);
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_strdup Comparison Tests ---\n\n");

    // 1. Basic String Test
    run_strdup_test("1. Basic Alpha-Numeric String", "Hello42World");

    // 2. Empty String Test (Critical edge case: allocates 1 byte for '\0')
    run_strdup_test("2. Empty String", "");

    // 3. String with Spaces
    run_strdup_test("3. String with Spaces/Symbols", "1 2 3 ! @ #");

    // 4. Long String Test
    run_strdup_test("4. Long String", "This is a much longer string to ensure proper allocation size.");

    return (EXIT_SUCCESS);
}