#include <stdio.h>
#include <string.h> // For standard memmove and memcmp
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
void run_memmove_test(const char *test_name, unsigned char *buffer, size_t src_offset, size_t dest_offset, size_t len, size_t total_size)
{
    // Define the pointers based on offsets
    unsigned char *core_dest = buffer + dest_offset;
    const unsigned char *core_src = buffer + src_offset;

    // Create a control buffer for standard memmove comparison
    unsigned char *std_buffer = (unsigned char *)malloc(total_size);
    memcpy(std_buffer, buffer, total_size);

    // Save starting pointers for return value check
    void *core_start_ptr = core_dest;

    // Run both functions
    void *core_return_ptr = core_memmove(core_dest, core_src, len);

    // FIX: Call standard memmove on the comparison buffer
    memmove(std_buffer + dest_offset, std_buffer + src_offset, len);

    printf("--- Test: %s ---\n", test_name);
    printf("  Copy %zu bytes from index %zu to index %zu\n", len, src_offset, dest_offset);
    printf("  Pointers: dest=%p, src=%p\n", (void *)core_dest, (const void *)core_src);

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
    // Compare the entire buffer to check for overall correctness
    if (memcmp(buffer, std_buffer, total_size) == 0)
    {
        printf("  -> Content Check: \033[32mPASS\033[0m\n\n");
    }
    else
    {
        printf("  -> Content Check: \033[31mFAIL (Memory Mismatch)\033[0m\n");
        print_mem("    core_memmove result", buffer, total_size);
        print_mem("    std_memmove result", std_buffer, total_size);
        printf("\n");
    }

    free(std_buffer);
}

// ====================================================================
//                        MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_memmove vs memmove Comparison Tests ---\n\n");

    // Initialize a single large buffer with known data (0-9, A-F)
    unsigned char buffer[16];
    for (int i = 0; i < 16; i++)
        buffer[i] = '0' + i; // Data: 0123456789:;<=>?

    // 1. Non-Overlapping Test (Copy 5 bytes from index 0 to 10)
    run_memmove_test("1. Non-Overlapping", buffer, 0, 10, 5, 16);

    // 2. Safe Overlap (dest <= src): Forward Copy
    // Copy 5 bytes from index 5 to index 2 (5,6,7,8,9 -> dest[2], dest[3]... dest[6])
    // The source (5,6,7,8,9) is preserved as copy proceeds.
    run_memmove_test("2. Safe Overlap (dest < src)", buffer, 5, 2, 5, 16);

    // 3. Problematic Overlap (dest > src): Backward Copy
    // Copy 5 bytes from index 2 to index 4 (2,3,4,5,6 -> dest[4], dest[5]... dest[8])
    // If copied forward, the '4', '5', and '6' source bytes would be overwritten.
    run_memmove_test("3. Problematic Overlap (dest > src)", buffer, 2, 4, 5, 16);

    // 4. Copy to Self (src == dest): Should be no change
    run_memmove_test("4. Copy to Self (src == dest)", buffer, 5, 5, 5, 16);

    // 5. Zero Length Test
    run_memmove_test("5. Zero Length", buffer, 0, 5, 0, 16);

    printf("--- All Tests Complete ---\n");

    return (0);
}