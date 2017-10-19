/*****************************************************************************
 * Or Nagar.
 * Scheduler project.
 * Functions definition.
 * The scheduler is based on a priority queue, based on a sorted
 * doubly linked list.
 * 26/06/17
 ****************************************************************************/
#include <stdlib.h> 				/* malloc() 		*/
#include <assert.h>					/* assert() 		*/
#include <unistd.h>					/* sleep() 			*/
#include <time.h>					/* time()	 		*/

#include "utils.h"					/* MALLOC_ERROR 	*/
#include "scheduler_task.h"			/* SCTaskRun() 		*/
#include "pqueue.h"					/* PqueueEnqueue()	*/
#include "scheduler.h"				

enum {SUCCESS, FAIL};
enum {EXIT_FLAG_OFF, EXIT_FLAG_ON};
enum {SCHEDULER_FINISHED, SCHEDULER_STOPPED, SCHEDULER_FAIL};
enum {TASK_CONTINUE, TASK_END, TASK_ERROR};

struct sched
{
	pqueue_t *pq;
	int exit_flag;
};

sched_t *SchedCreate(void)
{
	sched_t *sched = malloc(sizeof(sched_t));
	if (NULL == sched)
	{
		MALLOC_ERROR;

		return(NULL);
	}

	sched->pq = PqueueCreate(SCTaskIsBefore, NULL);
	if (NULL == sched)
	{
		MALLOC_ERROR;

		free(sched);

		return(NULL);
	}

	sched->exit_flag = EXIT_FLAG_OFF;

	return(sched);
}

void SchedDestroy(sched_t *sched)
{
	sctask_t *current_task = NULL;

	assert(sched);

	while (!PqueueIsEmpty(sched->pq))
	{
		current_task = PqueuePeek(sched->pq);
		PqueueDequeue(sched->pq);
		SCTaskDestroy(current_task);
	}

	PqueueDestroy(sched->pq);
	sched->pq = NULL;

	free(sched);

	return;
}

rd33_uid_t SchedAdd(sched_t *sched, int (*task_func)(void *param), void *param,
					time_t cycle_time)
{
	sctask_t *task = NULL;

	assert(sched && task_func);

	task = SCTaskCreate(task_func, param, cycle_time);
	if (NULL == task)
	{
		MALLOC_ERROR;

		return(UidCreateBadId());
	}

	if (FAIL == PqueueEnqueue(sched->pq, task))
	{
		MALLOC_ERROR;
		SCTaskDestroy(task);

		return(UidCreateBadId());
	}

	return(SCTaskGetUid(task));
}

int SchedRemove(sched_t *sched, rd33_uid_t task_id)
{
	sctask_t *task = NULL;

	assert(sched);
	
	if (UidIsBadId(task_id))
	{
		return (FAIL);
	}
	
	task = PqueueRemove(sched->pq, SCTaskIsMatch, &task_id);
	if (NULL == task)
	{
		return(FAIL);
	}
	
	
	SCTaskDestroy(task);

	return(SUCCESS);
}

size_t SchedSize(const sched_t *sched)
{
	assert(sched);

	return(PqueueSize(sched->pq));
}

int SchedIsEmpty(const sched_t *sched)
{
	assert(sched);

	return(PqueueIsEmpty(sched->pq));
}

int SchedRun(sched_t *sched)
{
	time_t offset = 0;
	time_t run_time = 0;
	int run_check = 0;
	time_t sleep_time = 0;
	sctask_t *current_task = NULL;

	assert(sched);

	sched->exit_flag = EXIT_FLAG_OFF;
	offset = time(NULL) - 1;
	run_time = time(NULL) - offset;

	while (!sched->exit_flag && !SchedIsEmpty(sched))
	{
		current_task = PqueuePeek(sched->pq);
		PqueueDequeue(sched->pq);

		if (SCTaskGetNextCall(current_task) >= run_time)
		{
			
			sleep_time = SCTaskGetNextCall(current_task) - run_time;
			do
			{
				sleep_time = sleep(sleep_time);
			}
			while(sleep_time);
			
			run_time = time(NULL) - offset;
			run_check = SCTaskRun(current_task);
		}

		SCTaskUpdateNextCall(current_task, run_time);

		switch (run_check)
		{
			case TASK_CONTINUE:
			  if (FAIL == PqueueEnqueue(sched->pq, current_task))
				{
					MALLOC_ERROR;
					SCTaskDestroy(current_task);

					return(SCHEDULER_FAIL);
				}
			  break;
			case TASK_END:
			  SCTaskDestroy(current_task);
			  run_check = TASK_CONTINUE;
			  break;
			case TASK_ERROR:
			  PRINT_ERROR("SCHED ERROR");
			  SCTaskDestroy(current_task);
			  run_check = TASK_CONTINUE;
			  break;
		}
	}

	return((EXIT_FLAG_ON == sched->exit_flag) ? (SCHEDULER_STOPPED) :
											    (SCHEDULER_FINISHED));
}

int SchedStop(sched_t *sched)
{
	pqueue_t *temp_queue = NULL;
	sctask_t *data = NULL;
	assert(sched);

	sched->exit_flag = EXIT_FLAG_ON;

	temp_queue = PqueueCreate(SCTaskIsBefore, NULL);
	if (NULL == temp_queue)
	{
		MALLOC_ERROR;
		return(FAIL);
	}

	while (!SchedIsEmpty(sched))
	{
		data = PqueuePeek(sched->pq);
		PqueueDequeue(sched->pq);
		SCTaskUpdateNextCall(data, 1);
		PqueueEnqueue(temp_queue, data);
	}

	PqueueDestroy(sched->pq);
	sched->pq = temp_queue;

	return(SUCCESS);
}
