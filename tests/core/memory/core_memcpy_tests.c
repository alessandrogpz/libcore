#include <stdio.h>
#include <string.h> // For standard memcpy and memcmp
#include <stdlib.h> // For malloc
#include "includes.h"

// ====================================================================
//            LOCAL FUNCTION DEFINITIONS (FOR TESTING)
// ====================================================================

// Function to print a memory block (for debugging)
void print_mem(const char *label, unsigned char *ptr, size_t size)
{
    printf("%s: ", label);
    for (size_t i = 0; i < size; i++)
    {
        printf("%02X ", ptr[i]);
    }
    printf("\n");
}

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ===================================================================

// Function to run and display a single test result
void run_memcpy_test(const char *test_name, const unsigned char *src_data, size_t src_len, size_t copy_len)
{
    // The total size of the destination buffer
    size_t total_size = src_len + 5;

    // Allocate memory for core_memcpy and standard memcpy
    unsigned char *core_dest = (unsigned char *)malloc(total_size);
    unsigned char *std_dest = (unsigned char *)malloc(total_size);

    // Initialize both destination buffers to a known non-source pattern (0xFF)
    memset(core_dest, 0xFF, total_size);
    memset(std_dest, 0xFF, total_size);

    // Create non-const pointers to save the starting address
    void *core_start_ptr = core_dest;

    // Run both functions
    void *core_return_ptr = core_memcpy(core_dest, src_data, copy_len);

    // FIX: Call standard memcpy so we have something to compare against!
    memcpy(std_dest, src_data, copy_len);

    printf("--- Test: %s (Copy %zu bytes) ---\n", test_name, copy_len);

    // --- 1. Check Return Value ---
    if (core_return_ptr != core_start_ptr)
    {
        printf("  -> \033[31mFAIL (Return Value)\033[0m: Did not return starting destination pointer.\n");
    }
    else
    {
        printf("  -> Return Value: \033[32mPASS\033[0m\n");
    }

    // --- 2. Check Content & Integrity ---
    // Compare the entire destination block (including the trailing 0xFF bytes)
    if (memcmp(core_dest, std_dest, total_size) == 0)
    {
        printf("  -> Content Check: \033[32mPASS\033[0m\n\n");
    }
    else
    {
        printf("  -> Content Check: \033[31mFAIL (Memory Mismatch)\033[0m\n");
        print_mem("    core_memcpy result", core_dest, total_size);
        print_mem("    std_memcpy result", std_dest, total_size);
        printf("\n");
    }

    free(core_dest);
    free(std_dest);
}

// ====================================================================
//                        MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_memcpy vs memcpy Comparison Tests ---\n\n");

    // Sample data array containing null bytes (0x00)
    // This is crucial to distinguish memcpy from strcpy
    const unsigned char data1[] = {'H', 'e', 0x00, 'l', 'l', 'o', 0xAA, 0xBB};
    const unsigned char data2[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    // 1. Basic String Copy
    run_memcpy_test("Basic String Copy ('10')", (const unsigned char *)"10 bytes.", 10, 10);

    // 2. Binary Copy (Crucial: copy includes null byte 0x00)
    // Copies 6 bytes: H, e, 0x00, l, l, o
    run_memcpy_test("Binary Copy (6 bytes)", data1, sizeof(data1), 6);

    // 3. Zero Length Copy (Should change nothing)
    run_memcpy_test("Zero Length Copy", data2, sizeof(data2), 0);

    // 4. Partial Copy (Copies 3 bytes)
    // Copies 0x01, 0x02, 0x03
    run_memcpy_test("Partial Copy (3 bytes)", data2, sizeof(data2), 3);

    // 5. Copy full buffer size
    run_memcpy_test("Full Buffer Copy (7 bytes)", data2, sizeof(data2), 7);

    printf("--- All Tests Complete ---\n");

    return (0);
}