#include <stdio.h>
#include <ctype.h>
#include "libcore.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ===================================================================

// Function to run and display a single test result
void run_print_test(int c)
{
	int core_result = core_isprint(c);
	int std_result = isprint(c);

	// Normalize standard library result (non-zero to 1) for clean comparison
	int std_is_print = (std_result != 0) ? 1 : 0;
	int core_is_print = (core_result != 0) ? 1 : 0;

	printf("Testing value: %d ('%c' or Control)\n", c, (c >= 32 && c <= 126) ? (char)c : '?');
	printf("  core_isprint result: %d\n", core_is_print);
	printf("  std_isprint result: %d\n", std_is_print);

	if (core_is_print == std_is_print)
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
	printf("--- Running core_isprint vs isprint Comparison Tests ---\n\n");

	// 1. Lower Boundary (Control Characters -> Printable)
	printf("## 1. Lower Boundary Tests (ASCII 31, 32)\n");
	run_print_test(31); // Unit Separator (Control, Expected: FALSE)
	run_print_test(32); // Space ' ' (First Printable, Expected: TRUE)

	// 2. Mid-Range Printable Tests (Expected: TRUE)
	printf("## 2. Mid-Range Printable Tests\n");
	run_print_test('a'); // Lowercase
	run_print_test('Z'); // Uppercase
	run_print_test('9'); // Digit
	run_print_test('#'); // Symbol

	// 3. Upper Boundary (Printable -> Control Character)
	printf("## 3. Upper Boundary Tests (ASCII 126, 127)\n");
	run_print_test(126); // Tilde '~' (Last Printable, Expected: TRUE)
	run_print_test(127); // DEL (Control, Expected: FALSE)

	// 4. Other Non-Printable/Control Characters (Expected: FALSE)
	printf("## 4. Other Control/Out-of-Range Tests\n");
	run_print_test('\n'); // Newline (ASCII 10)
	run_print_test('\t'); // Tab (ASCII 9)
	run_print_test(0);	  // NULL (ASCII 0)
	run_print_test(-1);	  // EOF
	run_print_test(200);  // Extended ASCII range

	printf("--- All Tests Complete ---\n");

	return (0);
}