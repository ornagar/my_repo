/*****************************************************************************
 * Or Nagar.
 * Scheduler project.
 * Functions declaration.
 * 26/06/17
 ****************************************************************************/
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <sys/types.h>

#include "uid.h"

typedef struct sched sched_t;

/*
 * Creates a scheduler.
 * Return:
 * - On success: a pointer to the Scheduler.
 * - On failure: NULL.
 */
sched_t *SchedCreate(void);

/*
 * Destroys the scheduler and frees all resourcess.
 */
void SchedDestroy(sched_t *sched);

/*
 * Receives a function pointer for scheduling.
 * Param is optional, Cycle time in seconds for scheduler scheduling.
 * Returns an UID for the scheduled function.
 * If Add fails returns a Bad UID.
 *
 * task_func return codes:
 * * 0: Completed OK, Re-schedule
 * * 1: Completed OK, no re-run
 * * 2: Error, no re-run
 *
 */
rd33_uid_t SchedAdd(sched_t *sched, int (*task_func)(void *param), void *param,
					time_t cycle_time);

/*
 * Receives an UID  and removes its scheduled function.
 * Returns 0 for success and 1 for failure (when not found).
 */
int SchedRemove(sched_t *sched, rd33_uid_t task_id);

/*
 * Returns number of scheduled tasks (functions).
 * Complexity: O(n)
 */
size_t SchedSize(const sched_t *sched);

/*
 * Returns 1 if scheduler is empty.
 * 0 if not empty.
 * Complexity: O(1)
 */
int SchedIsEmpty(const sched_t *sched);

/*
 * Runs the scheduler until all functions finish
 * their job, or until Scheduler is stopped via Stop function.
 * Returns 0 if finished all tasks, 1 if it gets stopped by Stop function,
 * 2 for error running the Scheduler.
 */
int SchedRun(sched_t *sched);

/*
 * The user should call this function with
 * add function to decide when the schudeler should stop.
 *
 * One of the pre-added tasks (functions) may call the SchedStop() function,
 * to stop running the Scheduler.
 * Note: the Scheduler is stopped, but not destroyed.
 */
int SchedStop(sched_t *sched);

#endif /*__SCHEDULER_H__*/
