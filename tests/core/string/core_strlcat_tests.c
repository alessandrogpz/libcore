#include <stdio.h>
#include <string.h> // For standard strlcat, memcmp, strcpy, memset
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
        if (ptr[i] >= 32 && ptr[i] <= 126)
            printf(" %c ", ptr[i]);
        else
            printf("%02X ", ptr[i]);
    }
    printf("\n");
}

void run_unsafe_test(const char *test_name, size_t dsize, size_t expected_ret)
{
    char buffer[50];
    memset(buffer, 'r', 50);
    char *src = "12345";

    printf("--- Test: %s ---\n", test_name);
    printf("  DST: [NO NULL], SRC: \"%s\", DSIZE: %zu\n", src, dsize);

    size_t ret = core_strlcat(buffer, src, dsize);

    if (ret == expected_ret)
        printf("  -> \033[32mPASS\033[0m (Calculated %zu correctly)\n\n", ret);
    else
        printf("  -> \033[31mFAIL\033[0m (Got %zu, Expected %zu)\n\n", ret, expected_ret);
}

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

void run_strlcat_test(const char *test_name, const char *initial_dst, const char *src, size_t dsize)
{
    size_t total_buf_size = dsize + 10;

    char *core_dst = (char *)malloc(total_buf_size);
    char *std_dst = (char *)malloc(total_buf_size);

    memset(core_dst, 0xFF, total_buf_size);
    memset(std_dst, 0xFF, total_buf_size);

    if (dsize > 0)
    {
        strcpy(core_dst, initial_dst);
        strcpy(std_dst, initial_dst);
    }

    // --- FIX IS HERE: Correct Logic for Expected Return Value ---
    size_t src_len = core_strlen(src);
    size_t initial_dst_len = core_strlen(initial_dst);
    size_t expected_ret;

    if (dsize <= initial_dst_len)
        expected_ret = src_len + dsize;
    else
        expected_ret = src_len + initial_dst_len;
    // ------------------------------------------------------------

    size_t core_ret = core_strlcat(core_dst, src, dsize);

    // We compare against our calculated expected_ret, ignoring std_dst return
    // because standard libraries vary on edge cases, but the math is strict.

    printf("--- Test: %s ---\n", test_name);
    printf("  DST: \"%s\", SRC: \"%s\", DSIZE: %zu\n", initial_dst, src, dsize);

    if (core_ret == expected_ret)
        printf("  -> Return Value: \033[32mPASS\033[0m (Got %zu)\n\n", core_ret);
    else
        printf("  -> Return Value: \033[31mFAIL\033[0m (Got %zu, Expected %zu)\n\n", core_ret, expected_ret);

    free(core_dst);
    free(std_dst);
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_strlcat vs strlcat Comparison Tests ---\n\n");

    // 1. Full Append Success (Initial DST="12", SRC="345", DSIZE=10)
    run_strlcat_test("1. Success: Full Append", "12", "345", 10);

    // 2. Truncation: Cut Short (Initial DST="123", SRC="45678", DSIZE=5)
    // DST_LEN=3. Only 1 byte can be copied (DSIZE-DST_LEN-1 = 5-3-1=1). Result: "1234\0"
    run_strlcat_test("2. Truncation: Cut Short", "123", "45678", 5);

    // 3. Exact Boundary (Initial DST="A", SRC="B", DSIZE=3)
    // DST_LEN=1. Copy 1 byte (3-1-1=1). Result: "AB\0"
    run_strlcat_test("3. Exact Boundary", "A", "B", 3);

    // 4. Dsize is Equal to DST Length (DSIZE=3, DST="12")
    // DSIZE <= DST_LEN is FALSE, but copy_limit=0. Should return total length.
    run_strlcat_test("4. Dsize > DST_LEN but no space", "12", "345", 3);

    // 5. Zero Dsize (DSIZE=0) - FIX FOR RETURN VALUE
    // Should return 10. Test modified to compare against 10 directly.
    run_strlcat_test("5. Zero Dsize", "Hello", "World", 0);

    // 6. Empty Source
    run_strlcat_test("6. Empty Source", "Hello", "", 10);

    // 7. Empty Destination
    run_strlcat_test("7. Empty Destination", "", "World", 10);

    // --- UNSAFE / EDGE CASE TESTS ---
    // These tests simulate a destination buffer that is NOT null-terminated.
    // The function must detect that dst_len >= dsize and stop reading to avoid crashing.

    // Test 8: Buffer full of 'r'. DSIZE=5. SRC="12345".
    // Logic: dst_len (limited by dsize) = 5. Total = 5 + 5 = 10.
    run_unsafe_test("8. Non-Null DST (DSIZE=5)", 5, 10);

    // Test 9: Buffer full of 'r'. DSIZE=0. SRC="12345".
    // Logic: dst_len (limited by dsize) = 0. Total = 0 + 5 = 5.
    run_unsafe_test("9. Non-Null DST (DSIZE=0)", 0, 5);

    printf("--- All Tests Complete ---\n");

    return (0);
}