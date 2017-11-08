/*****************************************************************************
 *  Or Nagar.
 *  Queue library.
 *  Test file.
 *  18/06/17
 ****************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/

#include "queue.h"

int Tester(long actual_value, long expected_value, char *str, int line);
int TestQueue(void);		

int main(void)
{
	int err_sum = 0;
	
	err_sum += TestQueue();
	
	if (0 == err_sum)
	{
		puts("QUEUE TEST SUCCESS!!");
	}
	else
	{
		printf("found %d bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

/* 1: create test				
 * 2: enqueue test				
 * 3: enqueue test				
 * 4: enqueue test							 
 * 5: enqueue test				
 * 6: Peek test				
 * 7: create queue2 test				
 * 8: enqueue test			
 * 9: enqueue test					
 * 10: enqueue test				
 * 11: count test				
 * 12: count test				
 * 13: Append test				
 * 14: Peek test				
 * 15: Peek test				
 * 16: Dequeue test				
 * 17: Dequeue test				
 * 18: Dequeue test				
 * 19: Dequeue test				
 * 20: Dequeue test				
 * 21: Dequeue test				
 * 22: Dequeue test				
 * 23: Dequeue test				
 * 24: enqueue test	
 * 25: destroy test				
 */
int TestQueue(void)		
{
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13, 14, 15, 16, 17}; 
	int *temp_data = NULL;
	int count_errs = 0;
	queue_t *queue = NULL;
	queue_t *queue2 = NULL;
	
	
	/* 1: create test				*/
	queue = QueueCreate();
	if (NULL == queue)
	{
		printf("function: QueueCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}

	/* 2: enqueue test				*/
	count_errs += Tester((long)QueueEnqueue(queue, (void *)&data[0]),
						 0, "Enqueue: ", __LINE__);
	
	/* 3: enqueue test				*/
	count_errs += Tester((long)QueueEnqueue(queue, (void *)&data[1]),
						 0, "Enqueue: ", __LINE__);
						 
	/* 4: enqueue test				*/
	count_errs += Tester((long)QueueEnqueue(queue, (void *)&data[2]),
						 0, "Enqueue: ", __LINE__);
						 
	/* 5: enqueue test				*/
	count_errs += Tester((long)QueueEnqueue(queue, (void *)&data[3]),
						 0, "Enqueue: ", __LINE__);
	
	
	/* 6: Peek test					*/
	temp_data = QueuePeek(queue);
	count_errs += Tester(*temp_data, 1, "peek: ", __LINE__);
	
	
	
	/* 7: create queue2 test		*/
	queue2 = QueueCreate();
	if (NULL == queue)
	{
		printf("function: QueueCreate\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted creation returned NULL\n");
		++count_errs;
	}
	
	/* 8: enqueue test				*/
	count_errs += Tester((long)QueueEnqueue(queue2, (void *)&data[4]),
						 0, "Enqueue: ", __LINE__);
	
	/* 9: enqueue test				*/
	count_errs += Tester((long)QueueEnqueue(queue2, (void *)&data[5]),
						 0, "Enqueue: ", __LINE__);
						 
	/* 10: enqueue test				*/
	count_errs += Tester((long)QueueEnqueue(queue2, (void *)&data[6]),
						 0, "Enqueue: ", __LINE__);
	
	
	/* 11: count test				*/
	count_errs += Tester((long)QueueSize(queue), 4, "Count: ", __LINE__);
	
	/* 12: count test				*/
	count_errs += Tester((long)QueueSize(queue2), 3, "Count: ", __LINE__);
	
	/* 13: Append test				*/
	QueueAppend(queue, queue2);
	count_errs += Tester((long)QueueSize(queue2), 0, "Count: ", __LINE__);
	count_errs += Tester((long)QueueIsEmpty(queue2), 1, "Count: ", __LINE__);
	count_errs += Tester((long)QueueSize(queue), 7, "Count: ", __LINE__);
	count_errs += Tester((long)QueueIsEmpty(queue), 0, "Count: ", __LINE__);
	/********************************/
	
	/* 14: Peek test				*/
	temp_data = QueuePeek(queue);
	count_errs += Tester(*temp_data, 1, "peek: ", __LINE__);
	
	/* 15: Peek test				*/
	temp_data = QueuePeek(queue2);
	if (NULL != temp_data)
	{
		printf("function: QueuePeek\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted NULL returned something else\n");
		++count_errs;
	}
	
	/* 16: Dequeue test				*/
	temp_data = QueueDequeue(queue);
	if (NULL == temp_data)
	{
		printf("function: QueueDequeue\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted NULL returned something else\n");
		++count_errs;
	}
	
	/* 17: Dequeue test				*/
	temp_data = QueueDequeue(queue);
	if (NULL == temp_data)
	{
		printf("function: QueueDequeue\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted NULL returned something else\n");
		++count_errs;
	}
	
	/* 18: Dequeue test				*/
	temp_data = QueueDequeue(queue);
	if (NULL == temp_data)
	{
		printf("function: QueueDequeue\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted NULL returned something else\n");
		++count_errs;
	}
	
	/* 19: Dequeue test				*/
	temp_data = QueueDequeue(queue);
	if (NULL == temp_data)
	{
		printf("function: QueueDequeue\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted NULL returned something else\n");
		++count_errs;
	}
	
	/* 20: Dequeue test				*/
	temp_data = QueueDequeue(queue);
	if (NULL == temp_data)
	{
		printf("function: QueueDequeue\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted NULL returned something else\n");
		++count_errs;
	}
	
	/* 21: Dequeue test				*/
	temp_data = QueueDequeue(queue);
	if (NULL == temp_data)
	{
		printf("function: QueueDequeue\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted NULL returned something else\n");
		++count_errs;
	}
	
	/* 22: Dequeue test				*/
	temp_data = QueueDequeue(queue);
	if (NULL == temp_data)
	{
		printf("function: QueueDequeue\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted NULL returned something else\n");
		++count_errs;
	}
	
	/* 23: Dequeue test				*/
	temp_data = QueueDequeue(queue);
	if (NULL != temp_data)
	{
		printf("function: QueueDequeue\t in line: %d\t", __LINE__);
		puts("- status: fail... wanted NULL returned something else\n");
		++count_errs;
	}
	
	/* 24: enqueue test				*/
	count_errs += Tester((long)QueueEnqueue(queue, (void *)&data[0]),
						 0, "Enqueue: ", __LINE__);
	
	/* 25: destroy test				*/
	QueueDestroy(queue);
	QueueDestroy(queue2);
	
	
	return (count_errs);

}


int Tester(long actual_value, long expected_value, char *str, int line)
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

