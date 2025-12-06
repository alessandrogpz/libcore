#include <stdio.h>
#include <ctype.h>
#include "includes.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ===================================================================

// Function to run and display a single test result
void run_test(char c)
{
	int core_result = core_isalpha(c);
	int std_result = isalpha(c);

	// isalpha returns non-zero for true, so we simplify both to 1 or 0 for comparison
	int std_is_alpha = (std_result != 0) ? 1 : 0;
	int core_is_alpha = (core_result != 0) ? 1 : 0;

	printf("Testing character: '%c' (ASCII %d)\n", c, c);
	printf("  core_isalpha result: %d\n", core_is_alpha);
	printf("  std_isalpha result: %d\n", std_is_alpha);

	if (core_is_alpha == std_is_alpha)
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
	printf("--- Running core_isalpha vs isalpha Comparison Tests ---\n\n");

	// 1. Lowercase Tests (Expected: TRUE)
	printf("## 1. Lowercase Tests\n");
	run_test('a');
	run_test('m');
	run_test('z');

	// 2. Uppercase Tests (Expected: TRUE)
	printf("## 2. Uppercase Tests\n");
	run_test('A');
	run_test('M');
	run_test('Z');

	// 3. Digit Tests (Expected: FALSE)
	printf("## 3. Digit Tests\n");
	run_test('0');
	run_test('5');
	run_test('9');

	// 4. Symbol/Punctuation Tests (Expected: FALSE)
	printf("## 4. Symbol/Punctuation Tests\n");
	run_test('!');
	run_test('@');
	run_test('#');
	run_test('(');
	run_test('{');

	// 5. Whitespace and Control Characters (Expected: FALSE)
	printf("## 5. Whitespace and Control Characters\n");
	run_test(' ');	// Space
	run_test('\n'); // Newline
	run_test('\t'); // Tab
	run_test(47);	// ASCII '/' (Just before '0')
	run_test(58);	// ASCII ':' (Just after '9')
	run_test(91);	// ASCII '[' (Just after 'Z')
	run_test(96);	// ASCII '`' (Just before 'a')
	run_test(123);	// ASCII '{' (Just after 'z')
	run_test(0);	// Null character

	printf("--- All Tests Complete ---\n");

	return (0);
}