#include <stdio.h>
#include <ctype.h>
#include "libcore.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ===================================================================

// Function to run and display a single test result
void run_alnum_test(int c)
{
	int core_result = core_isalnum(c);
	int std_result = isalnum(c);

	// Normalize standard library result (non-zero to 1) for clean comparison
	int std_is_alnum = (std_result != 0) ? 1 : 0;
	int core_is_alnum = (core_result != 0) ? 1 : 0;

	printf("Testing character: '%c' (ASCII %d)\n", (char)c, c);
	printf("  core_isalnum result: %d\n", core_is_alnum);
	printf("  std_isalnum result: %d\n", std_is_alnum);

	if (core_is_alnum == std_is_alnum)
	{
		printf("  -> \033[32mPASS\033[0m\n\n");
	}
	else
	{
		printf("  -> \033[31mFAIL\033[0m - Mismatch!\n\n");
	}
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
	printf("--- Running core_isalnum vs isalnum Comparison Tests ---\n\n");

	// 1. Alphabetic Tests (Expected: TRUE)
	printf("## 1. Alphabetic Tests\n");
	run_alnum_test('a');
	run_alnum_test('M');

	// 2. Digit Tests (Expected: TRUE)
	printf("## 2. Digit Tests\n");
	run_alnum_test('0');
	run_alnum_test('5');

	// 3. Non-Alphanumeric Tests (Expected: FALSE)
	printf("## 3. Non-Alphanumeric Tests\n");
	run_alnum_test('!');
	run_alnum_test(' ');  // Space
	run_alnum_test('\n'); // Newline
	run_alnum_test('@');
	run_alnum_test('[');
	run_alnum_test(1000); // Arbitrary out-of-range integer

	// 4. Boundary Tests
	printf("## 4. Boundary Tests\n");
	run_alnum_test('9' + 1); // :
	run_alnum_test('A' - 1); // @

	printf("--- All Tests Complete ---\n");

	return (0);
}