#include <stdio.h>
#include <string.h> // For standard memset/bzero and memcmp
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
        printf("%02X ", ptr[i]);
    }
    printf("\n");
}

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ===================================================================

// Function to run and display a single test result
void run_bzero_test(size_t size, size_t len)
{
    // The total size of the buffer, allowing for 5 bytes of safety margin
    size_t total_size = size + 5;

    // Allocate memory and initialize with a known non-zero pattern (0xFF)
    unsigned char *core_buf = (unsigned char *)malloc(total_size);
    unsigned char *std_buf = (unsigned char *)malloc(total_size);

    // Initialize both buffers to all 0xFF (255) to ensure bzero actually clears them
    memset(core_buf, 0xFF, total_size);
    memset(std_buf, 0xFF, total_size);

    printf("Test: Clear %zu bytes in a %zu-byte block\n", len, size);

    // Run both functions
    core_bzero(core_buf, len);

    // Use standard memset to simulate standard bzero behavior for comparison
    memset(std_buf, 0, len);

    // --- 1. Check Content & Integrity ---
    // Compare the entire memory block written by bzero against the result of memset(0)
    if (memcmp(core_buf, std_buf, total_size) == 0)
    {
        printf("  -> Content Check: \033[32mPASS\033[0m\n\n");
    }
    else
    {
        printf("  -> Content Check: \033[31mFAIL (Memory Mismatch)\033[0m\n");
        print_mem("    core_bzero result", core_buf, total_size);
        print_mem("    std_bzero result", std_buf, total_size);
        printf("\n");
    }

    free(core_buf);
    free(std_buf);
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_bzero vs memset(0) Comparison Tests ---\n\n");

    // 1. Basic Test: Clear 10 bytes
    run_bzero_test(15, 10);

    // 2. Boundary Test: Clear entire block
    run_bzero_test(8, 8);

    // 3. Clear Zero Length Test: Should change nothing
    run_bzero_test(10, 0);

    // 4. Large Block Test
    run_bzero_test(50, 45);

    // 5. Short Clear in Large Block Test (Ensures trailing bytes are untouched)
    run_bzero_test(30, 5);

    printf("--- All Tests Complete ---\n");

    return (0);
}