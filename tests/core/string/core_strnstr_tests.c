#include <stdio.h>
#include <string.h> // For standard string functions
#include <stdlib.h> // For NULL
#include "includes.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

// Function to run and display a single test result
// NOTE: Compares core_ptr against the calculated EXPECTED ADDRESS.
void run_strnstr_test(const char *test_name, const char *haystack, const char *needle, size_t len, int expected_index)
{
    // Calculate the expected pointer address based on the index
    char *expected_ptr;
    if (expected_index >= 0)
        expected_ptr = (char *)(haystack + expected_index); // Address is Haystack_Start + Index
    else
        expected_ptr = NULL; // Expected NULL if index is -1

    char *core_ptr = core_strnstr(haystack, needle, len);

    printf("--- Test: %s (LEN=%zu) ---\n", test_name, len);
    printf("  HAYSTACK: \"%s\", NEEDLE: \"%s\"\n", haystack, needle);
    printf("  Expected Index: %d\n", expected_index);
    printf("  core_ptr: %p\n", (void *)core_ptr);

    // --- 1. Check Pointer Equality (core_ptr vs expected_ptr) ---
    if (core_ptr == expected_ptr)
    {
        printf("  -> \033[32mPASS\033[0m: Pointers Match.\n");

        // Extra check: If found, verify the string at that pointer
        if (core_ptr != NULL)
            printf("  -> Found Match: \"%s\"\n\n", core_ptr);
        else
            printf("  -> Result: NOT FOUND (NULL)\n\n");
    }
    else
    {
        printf("  -> \033[31mFAIL (Mismatch)\033[0m\n");
        printf("  -> Expected address: %p, Your address: %p\n\n", (void *)expected_ptr, (void *)core_ptr);
    }
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_strnstr Custom Comparison Tests ---\n\n");

    const char *haystack = "lorem ipsum dolor sit amet";

    // 1. Needle is Empty (Expected: Haystack pointer, Index 0)
    run_strnstr_test("1. Empty Needle", haystack, "", 10, 0);

    // 2. Basic Found (Index 6)
    // "ipsum" starts at index 6.
    run_strnstr_test("2. Basic Found ('ipsum')", haystack, "ipsum", 20, 6);

    // 3. Substring Exists, but Search Stops Before Match (CRITICAL LIMIT TEST)
    // The word 'dolor' starts at index 12. Limit search to 10.
    run_strnstr_test("3. Search Stops Before Match", haystack, "dolor", 10, -1);

    // 4. Match Found, Ends Exactly at Limit (Index 6)
    // Search for "ipsum d" (7 chars). Start is index 6. 6 + 7 = 13.
    run_strnstr_test("4. Match Found, Ends Exactly at Limit", haystack, "ipsum d", 13, 6);

    // 5. Match Starts Within Limit, but Continues Beyond (Truncated Match)
    // Match starts at index 12. Needle is 'dolor sit amet'. Limit is 15.
    // Index 12 + 4 chars = 16. Stop before 16. Match fails.
    run_strnstr_test("5. Truncation Stops Match", haystack, "dolor sit amet", 15, -1);

    // 6. Needle Longer than Haystack (Expected: NULL)
    run_strnstr_test("6. Needle Longer Than Haystack", "abc", "abcd", 10, -1);

    // 7. Haystack is Empty (Expected: NULL)
    run_strnstr_test("7. Empty Haystack", "", "a", 5, -1);

    // 8. Zero Len (N=0)
    run_strnstr_test("8. Zero Len (N=0, Needle present)", haystack, "lorem", 0, -1);

    // 9. Simple Not Found
    // Search for "xyz" in "abc". Should return NULL (-1).
    run_strnstr_test("9. Simple Not Found", "lorem ipsum", "xyz", 20, -1);

    printf("--- All Tests Complete ---\n");

    return (EXIT_SUCCESS);
}