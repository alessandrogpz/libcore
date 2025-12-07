#include <stdio.h>
#include <stdlib.h> // For free, malloc
#include "libcore.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ====================================================================

void run_calloc_test(size_t nelem, size_t elsize)
{
    printf("--- Test: core_calloc(%zu, %zu) ---\n", nelem, elsize);

    // 1. Run calloc
    int *arr = (int *)core_calloc(nelem, elsize);

    // 2. Check Allocation Failure (simulated or real)
    if (!arr)
    {
        // Check for overflow using (size_t)-1 instead of SIZE_MAX
        // Logic: if elsize > MAX / nelem, then nelem * elsize would overflow.
        size_t max_size = (size_t)-1;

        if (nelem != 0 && elsize > max_size / nelem)
            printf("  -> \033[32mPASS\033[0m (Overflow correctly returned NULL)\n\n");
        else if (nelem == 0 || elsize == 0) // Some mallocs return NULL for size 0
            printf("  -> Result is NULL (Allowed for size 0)\n\n");
        else
            printf("  -> \033[31mFAIL\033[0m (Allocation failed unexpectedly)\n\n");
        return;
    }

    // 3. Check Zero-Initialization
    // We can only check content if allocation succeeded and size > 0
    if (nelem > 0 && elsize > 0)
    {
        size_t total_bytes = nelem * elsize;
        unsigned char *byte_ptr = (unsigned char *)arr;
        int is_zeroed = 1;

        for (size_t i = 0; i < total_bytes; i++)
        {
            if (byte_ptr[i] != 0)
            {
                is_zeroed = 0;
                break;
            }
        }

        if (is_zeroed)
            printf("  -> \033[32mPASS\033[0m (Memory is zeroed)\n");
        else
            printf("  -> \033[31mFAIL\033[0m (Memory contains garbage)\n");
    }
    else
    {
        printf("  -> Result is valid pointer (non-NULL) for size 0\n");
    }

    // Clean up
    free(arr);
    printf("\n");
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
    printf("--- Running core_calloc Tests ---\n\n");

    // 1. Standard Allocation
    run_calloc_test(5, sizeof(int));

    // 2. Zero Elements
    run_calloc_test(0, sizeof(int));

    // 3. Zero Size
    run_calloc_test(5, 0);

    // 4. Large Allocation (Overflow Check)
    // We pass the maximum possible size_t and 2.
    // Their product effectively wraps around, but the check inside calloc
    // should catch it before malloc tries to allocate a huge chunk.
    run_calloc_test((size_t)-1, 2);

    // 5. Another Overflow Check (Half max * 4)
    // ((size_t)-1 / 2) + 100 ensures we are slightly above half, so * 4 will definitely overflow
    run_calloc_test(((size_t)-1 / 2) + 100, 4);

    return (0);
}