#include <stdio.h>
#include <string.h> // For standard strlcpy and memcmp
#include <stdlib.h> // For malloc
#include "libcore.h"

// ====================================================================
//            LOCAL FUNCTION DEFINITIONS (FOR TESTING)
// ====================================================================

// Function to print a memory block (for debugging)
void print_mem(const char *label, unsigned char *ptr, size_t size)
{
    printf("%s: ", label);
    for (size_t i = 0; i < size; i++)
    {
        // Print character if printable, otherwise print hex
        if (ptr[i] >= 32 && ptr[i] <= 126)
            printf(" %c ", ptr[i]);
        else
            printf("%02X ", ptr[i]);
    }
    printf("\n");
}

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ===================================================================

// Function to run and display a single test result
void run_strlcpy_test(const char *test_name, const char *src, size_t dsize)
{
    size_t len_src = strlen(src);
    size_t total_buf_size = dsize + 5; // Extra space for integrity check

    // Allocate buffers and initialize with 0xFF (255) to check for null termination/integrity
    char *core_dst = (char *)malloc(total_buf_size);
    char *std_dst = (char *)malloc(total_buf_size);
    memset(core_dst, 0xFF, total_buf_size);
    memset(std_dst, 0xFF, total_buf_size);

    // Run both functions and capture return values
    size_t core_ret = core_strlcpy(core_dst, src, dsize);
    size_t std_ret = strlcpy(std_dst, src, dsize);

    printf("--- Test: %s (dsize=%zu, src_len=%zu) ---\n", test_name, dsize, len_src);

    // --- 1. Check Return Value ---
    if (core_ret == std_ret)
        printf("  -> Return Value: \033[32mPASS\033[0m (Returned %zu)\n", core_ret);
    else
        printf("  -> Return Value: \033[31mFAIL\033[0m (ft=%zu, std=%zu)\n", core_ret, std_ret);

    // --- 2. Check Content and Integrity ---
    // Compare the entire buffer to ensure correct truncation and no overflow
    if (memcmp(core_dst, std_dst, total_buf_size) == 0)
        printf("  -> Content Check: \033[32mPASS\033[0m\n\n");
    else
    {
        printf("  -> Content Check: \033[31mFAIL (Mismatch)\033[0m\n");
        print_mem("    core_strlcpy result", (unsigned char *)core_dst, total_buf_size);
        print_mem("    std_strlcpy result", (unsigned char *)std_dst, total_buf_size);
        printf("\n");
    }

    free(core_dst);
    free(std_dst);
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_strlcpy vs strlcpy Comparison Tests ---\n\n");

    // 1. Success: Full Copy (Src shorter than Dsize)
    run_strlcpy_test("1. Success: Full Copy", "12345", 10);

    // 2. Truncation: Source longer than Dsize
    run_strlcpy_test("2. Truncation: Cut short", "ABCDEFGHIJKLMNOP", 5);

    // 3. Exact Boundary: Src fits exactly (Src_len = Dsize - 1)
    run_strlcpy_test("3. Exact Boundary", "1234", 5);

    // 4. Zero Destination Size (Dsize = 0): Must return src_len, copy nothing
    run_strlcpy_test("4. Zero Dsize", "Test", 0);

    // 5. Small Dsize (Dsize = 1): Must copy 0 bytes, only null terminator
    run_strlcpy_test("5. Small Dsize (1)", "Test", 1);

    // 6. Dsize = Src_len (Truncation, copies Dsize-1 chars)
    run_strlcpy_test("6. Dsize == Src_len", "ABCDE", 5);

    printf("--- All Tests Complete ---\n");

    return (0);
}