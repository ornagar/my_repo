/*****************************************************************************
 * Or Nagar.
 * Scheduler's Task library.
 * Functions declaration.
 * 26/06/17
 ****************************************************************************/
#ifndef __SCHEDULER_TASK_H__
#define __SCHEDULER_TASK_H__

#include <sys/types.h>

#include "uid.h"

typedef struct sctask sctask_t;

/*
 * Creates a task.
 * Receives a pointer to a function and its param and scheduling cycle time.
 * Return: a pointer to the task on success, NULL on failure.
 */
sctask_t *SCTaskCreate(int (*task_func)(void *param), void *param, 
					time_t cycle_time);

/*
 * Destroys the task.
 */
void SCTaskDestroy(sctask_t *task);

/*
 * Activates the function in the task.
 *
 * Returns the function's return status, as specified on scheduler.h:
 * * 0: Completed OK, Re-schedule
 * * 1: Completed OK, no re-run
 * * 2: Error, no re-run
 */
int SCTaskRun(sctask_t *task);

/*
 * Gets a task and schedules the next running time
 * returns a pointer to the task.
 */
void SCTaskUpdateNextCall(sctask_t *task, time_t run_time);

/*
 * Return the next_time (in seconds) the task should be run.
 */
time_t SCTaskGetNextCall(const sctask_t *task);

/*
 * Returns task's uid.
 */
rd33_uid_t SCTaskGetUid(const sctask_t *task);

/*
 * Checks if task1 runs before task2.
 */
int SCTaskIsBefore(const void *task1, const void *task2, void *param);

/*
 * Compares a given UID to a specific task.
 * Returns 1 if match.
 * Returns 0 if no_match. 
 */
int SCTaskIsMatch(const void *task, const void *uid);

#endif /*____SCHEDULER_TASK_H__*/
