/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Sem                                    #################################
 *                                         ##########    ####       ########
 *  Functions decleration                  ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  27-08-2017                             ##########    ####  ###  ######## 
 *  17:40:01                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifndef __SEMAPHORE_H_
#define __SEMAPHORE_H_

/* Initializes a semaphore, and returns sem_id.
 * on failure, returns -1.
 * Creates a semaphore in shared memory identifiable by 
 * the int returned if the shared memory does not exist, otherwise simply
 * uses the existing semaphore.
 *  proj_id:
 *      the unique project id used. 
 *      Chars values are used for cross-platform compatibility
 *  value:
 *      Initial value of the semaphore if created, otherwise does nothing.
 *  disappear:
 *      If set to 1, upon exit from the program
 *      cleans up the shared memory from the system.
 *
 * Adds the current process to a group specified by sem_id
 */
int SemInit(const char *path, int proj_id, int value, int disappear);

/*
 * Add a specified value to the semaphore. 
 *  undo: 
 *      If set to 1, undos the operation after the process exits.
 * Upon post, the current process signals all of the other processes
 *  attached to the current semaphore.
 */
int SemPost(int sem_id, int add_val, int undo);

/*
 * Waits until the semaphore has a large enough value to be decremented by val
 *  undo:
 *      If set to 1, undos the decrement of the current action.
 */
int SemWait(int sem_id, int val, int undo);

/*
 * Removes the semaphore's link to the current process.
 */
int SemRemove(int sem_id);

#endif /* __SEMAPHORE_H_ */
