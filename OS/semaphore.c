/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Sem                                    #################################
 *                                         ##########    ####       ########
 *  Functions definition                   ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  27-08-2017                             ##########    ####  ###  ######## 
 *  17:40:01                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <assert.h>					 /* assert()					  */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "sem.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

enum
{
	SUCCESS,
	FAIL
};

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *__buf;
};

int SemInit(const char *path, int proj_id, int value, int disappear)
{
	int i;
    union semun arg;
    struct semid_ds buf;
    struct sembuf sb;
    int semid;
    
    key = ftok(path, 0); 
	if (-1 == key)
	{
		PRINT_ERROR("ftok error");
		return (-1);
	}

	semid = semget(key, 1, 0666 | IPC_CREAT | IPC_EXCL); 
	if (-1 != semid)
	{
		ithul.
	}
	
	check if eexist...

	if yes return the existible
	
	if not error handling.

}

int SemPost(int sem_id, int add_val, int undo);

int SemWait(int sem_id, int val, int undo);

int SemRemove(int sem_id);
