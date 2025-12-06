#include <stdio.h>
#include <ctype.h>
#include "includes.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ===================================================================

// Function to run and display a single test result
void run_digit_test(int c)
{
	int core_result = core_isdigit(c);
	int std_result = isdigit(c);

	// isdigit returns non-zero for true, so we normalize both to 1 or 0 for comparison
	int std_is_digit = (std_result != 0) ? 1 : 0;
	int core_is_digit = (core_result != 0) ? 1 : 0;

	printf("Testing character: '%c' (ASCII %d)\n", (char)c, c);
	printf("  core_isdigit result: %d\n", core_is_digit);
	printf("  std_isdigit result: %d\n", std_is_digit);

	if (core_is_digit == std_is_digit)
	{
		printf("  -> \033[32mPASS\033[0m\n\n"); // Green text for PASS
	}
	else
	{
		printf("  -> \033[31mFAIL\033[0m - Mismatch!\n\n"); // Red text for FAIL
	}
}

// ====================================================================
//                         MAIN FUNCTION
// ====================================================================

int main(void)
{
	printf("--- Running core_isdigit vs isdigit Comparison Tests ---\n\n");

	// 1. Digit Tests (Expected: TRUE)
	printf("## 1. Digit Tests\n");
	run_digit_test('0'); // Boundary start
	run_digit_test('5'); // Mid-range
	run_digit_test('9'); // Boundary end

	// 2. Alphabet Tests (Expected: FALSE)
	printf("## 2. Alphabet Tests\n");
	run_digit_test('a');
	run_digit_test('Z');

	// 3. Characters Immediately Outside the Digit Range (CRITICAL BOUNDARY TESTS)
	printf("## 3. Boundary Tests\n");
	run_digit_test('0' - 1); // Character before '0' (ASCII 47 '/')
	run_digit_test('9' + 1); // Character after '9' (ASCII 58 ':')

	// 4. Symbol/Whitespace Tests (Expected: FALSE)
	printf("## 4. Symbol and Whitespace Tests\n");
	run_digit_test('$');
	run_digit_test(' ');  // Space
	run_digit_test('\n'); // Newline
	run_digit_test('\t'); // Tab

	// 5. Special Value Test (EOF)
	// IMPORTANT: Though core_isdigit shouldn't strictly handle EOF for correctness,
	// it's good practice to ensure it doesn't crash or return garbage.
	printf("## 5. EOF Test\n");
	run_digit_test(-1); // EOF (Expected: FALSE)

	printf("--- All Tests Complete ---\n");

	return (0);
}