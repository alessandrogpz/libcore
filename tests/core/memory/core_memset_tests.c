#include <stdio.h>
#include <string.h> // For standard memset
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

// Function to check if a memory block contains the expected value
int check_content(unsigned char *ptr, int val, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        // Cast val to unsigned char to match the comparison
        if (ptr[i] != (unsigned char)val)
        {
            return 0; // Failure: Content mismatch
        }
    }
    return 1; // Success
}

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ===================================================================

// Function to run and display a single test result
void run_memset_test(size_t size, int value, size_t len)
{
    // The total size of the buffer, allowing for 5 bytes of safety margin
    size_t total_size = size + 5;

    // Allocate memory and initialize with a known pattern (0xAA)
    unsigned char *core_buf = (unsigned char *)malloc(total_size);
    unsigned char *std_buf = (unsigned char *)malloc(total_size);
    memset(core_buf, 0xAA, total_size);
    memset(std_buf, 0xAA, total_size);

    // Get the initial pointer for return value check
    void *core_start_ptr = core_buf;

    // Run both functions
    void *core_return_ptr = core_memset(core_buf, value, len);

    // FIX: Call standard memset so we can compare
    memset(std_buf, value, len);

    printf("Test: Set %zu bytes to 0x%02X in a %zu-byte block\n", len, (unsigned char)value, size);

    // --- 1. Check Return Value ---
    if (core_return_ptr != core_start_ptr)
    {
        printf("  -> \033[31mFAIL (Return Value)\033[0m: Did not return starting pointer.\n");
    }
    else
    {
        printf("  -> Return Value: \033[32mPASS\033[0m\n");
    }

    // --- 2. Check Content & Integrity (The core test) ---
    // Compare the result of core_memset against the result of std_memset
    if (memcmp(core_buf, std_buf, total_size) == 0)
    {
        printf("  -> Content Check: \033[32mPASS\033[0m\n\n");
    }
    else
    {
        printf("  -> Content Check: \033[31mFAIL (Memory Mismatch)\033[0m\n");
        print_mem("    core_memset result", core_buf, total_size);
        print_mem("    std_memset result", std_buf, total_size);
        printf("\n");
    }

    free(core_buf);
    free(std_buf);
}

// ====================================================================
//                        MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_memset vs memset Comparison Tests ---\n\n");

    // 1. Basic Test: Set 10 bytes to 'A'
    run_memset_test(15, 'A', 10);

    // 2. Boundary Test: Set entire block
    run_memset_test(8, 'Z', 8);

    // 3. Zero (Null) Test: Essential for memory clearing
    run_memset_test(20, 0, 15);

    // 4. Maximum Byte Value Test (0xFF): Should set all bytes to 255
    run_memset_test(10, 0xFF, 5);

    // 5. Zero Length Test: Should change nothing
    run_memset_test(10, 'X', 0);

    // 6. Large Integer Test (Ensures only the lower 8 bits are used)
    // 0x12345678 -> Should set bytes to 0x78
    run_memset_test(10, 0x12345678, 5);

    printf("--- All Tests Complete ---\n");

    return (0);
}