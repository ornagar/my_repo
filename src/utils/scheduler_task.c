/*****************************************************************************
 * Or Nagar.
 * Task library.
 * Functions definition.
 * 26/06/17
 ****************************************************************************/
#include <stdlib.h> 					/* malloc() 		*/
#include <assert.h>

#include "utils.h"
#include "scheduler_task.h"

struct sctask
{
	time_t cycle_time;
	time_t next_run;
	rd33_uid_t uid;
	int (*task_func)(void *param);
	void *param;
};

sctask_t *SCTaskCreate(int (*task_func)(void *param), void *param, 
					time_t cycle_time)
{
	sctask_t *task = NULL;

	assert(task_func);

	if (NULL == (task = malloc(sizeof(sctask_t))))
	{
		MALLOC_ERROR;

		return(NULL);
	}

	task->cycle_time = cycle_time;
	task->next_run = 0;
	task->uid = UidCreate();
	task->task_func = task_func;
	task->param = param;

	return(task);
}

void SCTaskDestroy(sctask_t *task)
{
	assert(task);

	task->task_func = NULL;
	task->param = NULL;

	free(task);

	return;
}

int SCTaskRun(sctask_t *task)
{
	assert(task);

	return(task->task_func(task->param));
}

void SCTaskUpdateNextCall(sctask_t *task, time_t run_time)
{
	assert(task);

	task->next_run = run_time + task->cycle_time;

	return;
}

time_t SCTaskGetNextCall(const sctask_t *task)
{
	assert(task);

	return(task->next_run);
}

rd33_uid_t SCTaskGetUid(const sctask_t *task)
{
	assert(task);

	return(task->uid);
}

int SCTaskIsBefore(const void *task1, const void *task2, void *param)
{
	assert(task1 && task2);

	return(((sctask_t *)task1)->next_run < ((sctask_t *)task2)->next_run);
}

int SCTaskIsMatch(const void *task, const void *uid)
{
	assert(task);

	return(UidIsSameId(*((rd33_uid_t *)uid), ((sctask_t *)task)->uid));
}


