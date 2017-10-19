/*****************************************************************************
 * Or Nagar.
 * Scheduler library.
 * Test file.
 * 27/06/17
 ****************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

#include "scheduler.h"

int TestFlow(void);

static int Tester(long actual_value, long expected_value, char *str, int line);
int test1(void *param);
int test2(void *param);
int test3(void *param);
int test4(void *param);
int test5(void *param);

int main(void)
{
	size_t err_sum = 0;

	err_sum = TestFlow();

	if (0 == err_sum)
	{
		puts("\nScheduler TEST SUCCESS!!\n");
	}
	else
	{
		printf("\nfound %lu bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

/* Test Flow:
 *				*
 * 1: Create test 
 * 2: Size & isEmpty test
 * 3: Add test 		
 * 4: Size & isEmpty test
 * 5: 5: Add + stop + add while running test
 * 6: Size test 	
 * 7: Run Time test		
 * 8: Run test
 * 9: Run Time test	
 * 10: Remove test		
 * 11: Run test	
 * 13: Size & isEmpty test
 * 14: Run test
 * 15: Destroy test 		
 */
int TestFlow(void)
{
	size_t count_errs = 0;
	time_t running_time = time(NULL);

	/* 1: Create test 							  */
	sched_t *sched  = SchedCreate();
	rd33_uid_t id;

	/* 2: Size & isEmpty test	  				  */
	count_errs += Tester((long)SchedIsEmpty(sched), 1, "IsEmpty: ", __LINE__);
	count_errs += Tester((long)SchedSize(sched), 0, "Count: ", __LINE__);

	/* 3: Add test 								  */
	SchedAdd(sched, test1, NULL, 1);
	
	/* 4: Size & isEmpty test					  */
	count_errs += Tester((long)SchedIsEmpty(sched), 0, "IsEmpty: ", __LINE__);
	count_errs += Tester((long)SchedSize(sched), 1, "Count: ", __LINE__);
	
	/* 5: Add + stop + add while running test	  */
	id = SchedAdd(sched, test2, NULL, 1);
	SchedAdd(sched, test3, sched, 3);
	SchedAdd(sched, test4, sched, 3);

	/* 6: Size test								  */
	count_errs += Tester((long)SchedSize(sched), 4, "Count: ", __LINE__);
	
	/* 7: Run Time test 						  */
	count_errs += Tester(time(NULL), running_time, "run_time: ", __LINE__);

	/* 8: Run test								  */
	SchedRun(sched);

	/* 9: Run Time test							  */
	count_errs += Tester(time(NULL), running_time + 3, "run_time: ", __LINE__);

	/* 10: Remove test							  */
	count_errs += Tester((long)SchedRemove(sched, id), 0, "Remove: ", __LINE__);
	count_errs += Tester((long)SchedRemove(sched, id), 1, "Remove: ", __LINE__);
	
	/* 11: Run test							      */
	SchedRun(sched);
	
	/* 12: Run Time test						  */
	count_errs += Tester(time(NULL), running_time + 23, "run_time: ", __LINE__);

	/* 13: Size & isEmpty test					   */
	count_errs += Tester((long)SchedSize(sched), 0, "Count: ", __LINE__);
	count_errs += Tester((long)SchedIsEmpty(sched), 1, "IsEmpty: ", __LINE__);
	
	/* 14: Run test 							   */
	SchedRun(sched);

	/* 15: Destroy test 		 				   */
	SchedDestroy(sched);

	return(count_errs);
}


int test1(void *param)
{
	static int count = 23;

	--count;
	/*printf("func1 count: %d, real time: %lu\n", count, time(NULL));
*/
	return(0 >= count);
}

int test2(void *param)
{
	static int count = 10;

	--count;
/*	printf("func2 count: %d, real time: %lu\n", count, time(NULL));
*/
	return(0 >= count);
}

int test3(void *param)
{
/*	printf("func3 count: stop run, real time: %lu\n", time(NULL));
*/

	SchedStop((sched_t *) param);

	return(1);
}

int test4(void *param)
{
	static int count = 1;
	SchedAdd((sched_t *) param, test5, NULL, 3);
/*	printf("func4 count: %d real time: %lu\n", count, time(NULL));
*/
	--count;

	return(0 >= count);
}

int test5(void *param)
{
	static int count = 2;
	char* arg_list[] = 
	{
		"cowsay",
		"gilutils are the best utils in rd33",
		NULL      
	};

	pid_t child_pid = fork ();
	
	if (0 == child_pid)
	{
		execvp (arg_list[0], arg_list);
	}
	
	--count;
/*	printf("i am new here\nfunc5 count: %d real time: %lu\n", count, time(NULL));
*/
	return(0 >= count);
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
