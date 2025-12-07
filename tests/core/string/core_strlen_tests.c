#include <stdio.h>
#include <string.h>
#include "libcore.h"

// ====================================================================
//                 TEST EXECUTION FUNCTION
// ===================================================================

// Function to run and display a single test result
void run_strlen_test(char *str)
{
	// The standard strlen returns size_t, which is converted to long for printing
	size_t std_result = strlen(str);

	// Your function returns int
	int core_result = core_strlen(str);

	printf("Testing string: \"%s\"\n", str);
	printf("  core_strlen result: %d\n", core_result);
	printf("  std_strlen result: %zu\n", std_result); // Use %zu for size_t

	if (core_result == (int)std_result)
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
	printf("--- Running core_strlen vs strlen Comparison Tests ---\n\n");

	// 1. Empty String Test (Expected: 0)
	printf("## 1. Empty String Test\n");
	char s1[] = "";
	run_strlen_test(s1);

	// 2. Short String Test (Expected: 5)
	printf("## 2. Short String Test\n");
	char s2[] = "Hello";
	run_strlen_test(s2);

	// 3. String with Spaces (Expected: 8)
	printf("## 3. String with Spaces\n");
	char s3[] = "A B C D E";
	run_strlen_test(s3);

	// 4. String with Control Characters (Expected: 10)
	// Newline and Tab characters must be counted as length 1
	printf("## 4. String with Control Characters\n");
	char s4[] = "Tab\tNewline\n";
	run_strlen_test(s4);

	// 5. Long String Test (Expected: 21)
	printf("## 5. Long String Test\n");
	char s5[] = "This is a long string.";
	run_strlen_test(s5);

	// 6. Null character check within string (The function should stop at the first '\0')
	printf("## 6. Null Character within String\n");
	char s6[] = "Four\0Stop"; // Only "Four" should be counted (Length 4)
	run_strlen_test(s6);

	printf("--- All Tests Complete ---\n");

	return (0);
}