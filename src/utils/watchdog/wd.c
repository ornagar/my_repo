/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Wd                                     #################################
 *                                         ##########    ####       ########
 *  Functions definition                   ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  03-09-2017                             ##########    ####  ###  ######## 
 *  07:59:24                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                  /* printf()                      	*/
#include <stdlib.h>					/* system(), EXIT_SUCCESS		  	*/
#include <assert.h>					/* assert()					  		*/
#include <pthread.h>				/* pthread_create()					*/
#include <string.h>					/* strlen()							*/
#include <signal.h>					/* sigaction()						*/
#include <unistd.h>					/* pause()							*/
#include <sys/types.h>				/* waitpid()						*/
#include <sys/wait.h>				/* waitpid()						*/
#include <semaphore.h>				/* sempost()						*/

#include "wd.h"					 	/* all functions declerations	  	*/
#include "scheduler.h"				/* SchedCreate()					*/
#include "uid.h"					/* UidIsBadUid()					*/
#include "utils.h"					/* Or's functions                	*/

struct wd
{
	char wd_name[10];
	int argc;
	char **argv;
	int interval;
	int retries;
	char intrvl_str[10];
	char retries_str[10];
	pid_t pid;
	sched_t *sched;
	pthread_t thread_id;
};

/***************************STATIC VARIABLES INITIALIZATION********************/
static sig_atomic_t is_alive = 0;
static sig_atomic_t let_me_die = 0;
static sig_atomic_t destroy = 0;
sem_t sem;
/******************************************************************************/
/*************************STATIC FUNCIONS**************************************/
static void *ThreadFunc(void *arg); /* The Main func for the new thread		*/
static int Init(wd_t *wdog);		/* Initializes the handlers for thread	*/
static void HandleSigusr1(int signal_num); /* Handles SIGUSR1				*/
static void HandleSigusr2(int signal_num); /* Handles SIGUSR2				*/
static void HandleAlrm(int signal_num);		   /* Handles SIGALRM				*/
static int CreateWd(wd_t *wdog);		   /* Creates the wd exec			*/
static int SchedSignal(void *param);	   /* Act func for scheduler		*/
static int WakeUpWd(wd_t *wdog);		   /* If wd is not signaling		*/
/******************************************************************************/
/*****************************API FUNCS****************************************/
wd_t *KeepMeAlive(int argc, char **argv, int interval, int retries)
{
	wd_t *wdog = NULL;
	int i = 0;
	char name[10] = "wd_exec";
	
LOG_FLOW("inside KeepMeAlive");	

	/* Initialize semaphore								*/
	if (0 != sem_init(&sem, 0, 0))
	{
		PRINT_ERROR("sem_intit error");
		return (NULL);
	}
	
	/* Allocate wdog									*/
	if (NULL == (wdog = calloc(1, sizeof(*wdog))))
	{
		PRINT_ERROR("wdog malloc error");
		return (NULL);
	}
	
	/* Update wdog values								*/
	wdog->interval = interval;
	wdog->retries = retries;
	wdog->argc = argc + 2;
	
	/* Add wd_name, interval and retries as arguments to wd->argv
	 * so they can be sent to wd_exec
	 */
	if (NULL == (wdog->argv = malloc(sizeof(char *) * (wdog->argc + 2))))
	{
		PRINT_ERROR("wdog.argv malloc error");
		free(wdog);
		return (NULL);
	}

	memcpy(wdog->wd_name, name, strlen(name) + 1);
	sprintf(wdog->retries_str, "%d", retries);
	sprintf(wdog->intrvl_str, "%d", interval);
	
	wdog->argv[0] = wdog->wd_name;
	wdog->argv[1] = wdog->intrvl_str;
	wdog->argv[2] = wdog->retries_str;
	
	for (i = 0; i < argc; ++i)
	{
		wdog->argv[3 + i] = argv[i];
	}
	wdog->argv[3 + i] = NULL;
	
	/* Create scheduler and add task					*/
	wdog->sched = SchedCreate();
	if (NULL == wdog->sched)
	{
		PRINT_ERROR("SchedCreate error");
		for (i = wdog->argc - 2; i < wdog->argc; ++i)
		{
			free(wdog->argv[i]);
		}
		free(wdog->argv);
		free(wdog);
		
		return (NULL);
	}
	
	if (UidIsBadId(SchedAdd(wdog->sched, SchedSignal, wdog, wdog->interval)))
	{
		PRINT_ERROR("SchedAdd error");
		SchedDestroy(wdog->sched);
		for (i = wdog->argc - 2; i < wdog->argc; ++i)
		{
			free(wdog->argv[i]);
		}
		free(wdog->argv);
		free(wdog);
		
		return (NULL);
	}
	
	/* Initialize signal handlers 						*/
	if (-1 == Init(wdog))
	{
		PRINT_ERROR("critical error aborting...");
		SchedDestroy(wdog->sched);
		for (i = wdog->argc - 2; i < wdog->argc; ++i)
		{
			free(wdog->argv[i]);
		}
		free(wdog->argv);
		free(wdog);
		return (NULL);
	}
	
	/* Create the new thread and return to main thread	*/
	pthread_create(&wdog->thread_id, NULL, ThreadFunc, wdog);
	
	return(wdog);
}

int LetMeDie(wd_t *wdog)
{
	int dog_status = 0;
	
LOG_FLOW("inside LetMeDie");	
	
	destroy = 1; /* Indicate SchedSignal task to start termination process	*/
	
	/* Wait for thread to finish											*/
	if (0 != pthread_join(wdog->thread_id, NULL))
	{
		PRINT_ERROR("pthread_join error");
	}	
	
	/* Wait for wd_exec to exit and check return status						*/
	waitpid(wdog->pid, &dog_status, 1);
	if (-1 == dog_status)
	{
		PRINT_ERROR("dog_status error");
		fprintf(stderr, "%d\n", dog_status);
	}
	
	/* Free resources														*/
	SchedDestroy(wdog->sched);

	free(wdog->argv);
	free(wdog);
	
	return (0);
}

/******************************STATIC FUNCS************************************/

static void *ThreadFunc(void *arg)
{
	wd_t *wdog = (wd_t *)arg;
	int i = 0;
LOG_FLOW("inside ThreadFunc");	

	if (-1 == CreateWd(wdog))		/* Create wd_exec						*/
	{
		PRINT_ERROR("critical error aborting...");
		SchedDestroy(wdog->sched);
		for (i = 0; i < wdog->argc; ++i)
		{
			free(wdog->argv[i]);
		}
		free(wdog->argv);
		free(wdog);
		exit(1);
	}
	
LOG_FLOW("before sched run");	

	SchedRun(wdog->sched);			/* Run IPC scheduler					*/

	return (NULL); 
}

static int Init(wd_t *wdog)
{
	struct sigaction act_usr1 = {{0}};
	struct sigaction act_usr2 = {{0}};
	struct sigaction act_alrm = {{0}};
LOG_FLOW("inside Init");	

	act_usr1.sa_handler = HandleSigusr1;
	if (-1 == sigaction(SIGUSR1, &act_usr1, NULL))
	{
		PRINT_ERROR("sigaction failure");
		return (-1);
	}
	
	act_usr2.sa_handler = HandleSigusr2;
	if (-1 == sigaction(SIGUSR2, &act_usr2, NULL))
	{
		PRINT_ERROR("sigaction failure");
		return (-1);
	}
	
	act_alrm.sa_handler = HandleAlrm;
	if (-1 == sigaction(SIGALRM, &act_alrm, NULL))
	{
		PRINT_ERROR("sigaction failure");
		return (-1);
	}
	
	return (0);
}

static void HandleSigusr1(int signal_num)
{
	is_alive = 0;
	return;
}

static void HandleSigusr2(int signal_num)
{
	let_me_die = 1;
	return;
}

static void HandleAlrm(int signal_num)
{
	sem_post(&sem);				/* Watch dog is ready for IPC			*/
	return;
}

static int CreateWd(wd_t *wdog)
{
LOG_FLOW("inside CreateWd");	
	
	wdog->pid = fork();
	if (-1 == wdog->pid)
	{
		PRINT_ERROR("fork error");
		return (-1);
	}

	if (0 == wdog->pid)
	{
		if (-1 == execvp(wdog->argv[0], wdog->argv))
		{
			PRINT_ERROR("execvp error");
			return (-1);
		}        
	}
	
	sem_wait(&sem);				/* Wait for wd_exec to be ready for IPC	*/
	
	return (0);
}

static int SchedSignal(void *param)
{
	wd_t *wdog = param;

LOG_FLOW("in app SchedSignal");

	if (!let_me_die)					/* If app still wants to live 	*/
	{
		++is_alive;
		if (wdog->retries > is_alive)	/* If app sent signal in 		*/
		{								/* the "retries" time			*/
			kill(wdog->pid, SIGUSR1);
		}
		else
		{
			is_alive = 0;
			WakeUpWd(wdog);
		}
	}
	else
	{
		SchedStop(wdog->sched);
	}
	
	if (destroy)
	{
		kill(wdog->pid, SIGUSR2);
		++destroy;
		if (4 >= destroy)
		{
			kill(wdog->pid, SIGALRM);
			++let_me_die;
			destroy = 0;
		}
	}

	return (0);
}

static int WakeUpWd(wd_t *wdog)
{
	kill(wdog->pid, SIGKILL);

	if (-1 == CreateWd(wdog))
	{
		PRINT_ERROR("CreateWd fatal error");
		exit (1);
	}

	return (0);
}
