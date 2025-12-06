#include <stdio.h>
#include <ctype.h>
#include "includes.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ===================================================================

// Function to run and display a single test result
void run_ascii_test(int c)
{
	int core_result = core_isascii(c);
	int std_result = isascii(c);

	// Normalize standard library result (non-zero to 1) for clean comparison
	int std_is_ascii = (std_result != 0) ? 1 : 0;
	int core_is_ascii = (core_result != 0) ? 1 : 0;

	printf("Testing value: %d ('%c')\n", c, (c >= 0 && c <= 127) ? (char)c : '?');
	printf("  core_isascii result: %d\n", core_is_ascii);
	printf("  std_isascii result: %d\n", std_is_ascii);

	if (core_is_ascii == std_is_ascii)
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
	printf("--- Running core_isascii vs isascii Comparison Tests ---\n\n");

	// 1. Lower Boundary Tests (Expected: TRUE)
	printf("## 1. Lower Boundary Tests\n");
	run_ascii_test(0); // ASCII 0 (Null)
	run_ascii_test(1);
	run_ascii_test(' '); // ASCII 32 (Space)

	// 2. Mid-Range Tests (Expected: TRUE)
	printf("## 2. Mid-Range Tests\n");
	run_ascii_test('A'); // Letter
	run_ascii_test('5'); // Digit
	run_ascii_test('~'); // ASCII 126

	// 3. Upper Boundary Tests (Expected: TRUE)
	printf("## 3. Upper Boundary Tests\n");
	run_ascii_test(127); // ASCII 127 (DEL)

	// 4. Out-of-Range Tests (Expected: FALSE)
	printf("## 4. Out-of-Range Tests\n");
	run_ascii_test(128); // First extended ASCII char
	run_ascii_test(255); // Max char value on some systems
	run_ascii_test(-1);	 // EOF value
	run_ascii_test(500); // Large integer

	printf("--- All Tests Complete ---\n");

	return (0);
}