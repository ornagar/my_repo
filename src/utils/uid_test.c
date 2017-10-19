/*******************************************************************************
 *  Author: Or Nagar.
 *  Creation date: 25.06.17
 *  Last modified: 25.06.17
 *  Implementation of UID generator.
 *  Functions test file.
 ******************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/

#include "utils.h"
#include "uid.h"

static int Tester(long actual_value, long expected_value, char *str, int line);
static int TestUid(void);		

int main(void)
{
	int err_sum = 0;
	
	err_sum += TestUid();
	
	if (0 == err_sum)
	{
		puts("UID TEST SUCCESS!!");
	}
	else
	{
		printf("found %d bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

/*  1: create test.
 *  2: Is same Id test. 
 *  3: Is bad Id test.
 */
int TestUid(void)		
{
	size_t count_errs = 0;
	
	/*  1: create test 		*/
	rd33_uid_t test  = UidCreate();
	rd33_uid_t test2 = UidCreate();	
	rd33_uid_t test3 = UidCreateBadId();
	rd33_uid_t test4 = test;

	
	/*  2: Is same Id test	*/
	count_errs += Tester(UidIsSameId(test, test4), 1, "IsEmpty: ", __LINE__);
	count_errs += Tester(UidIsSameId(test, test2), 0, "IsEmpty: ", __LINE__);
	
	/*  3: Is bad Id test	*/
	count_errs += Tester(UidIsBadId(test), 0, "IsEmpty: ", __LINE__);
	count_errs += Tester(UidIsBadId(test3), 1, "IsEmpty: ", __LINE__);
	
	return (count_errs);
}

static int Tester(long actual_value, long expected_value, char *str, int line)
{	
	if (actual_value != expected_value)
	{
		printf("function: %s  in line: %d ", str, line);
		printf("- status: fail... expected value was %ld and actual value is %ld\n",
				expected_value, actual_value);
		puts("");
				
		return (1);
	}
	
	return (0);
}
