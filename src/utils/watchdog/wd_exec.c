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

#include "wd.h"					 	/* all functions declerations	  	*/
#include "scheduler.h"				/* SchedCreate()					*/
#include "uid.h"					/* UidIsBadUid()					*/
#include "utils.h"					/* Or's functions                	*/

/*
 * Holds the data needed for IPC with the calling app
 */
typedef struct
{
	char **argv;		
	pid_t pid;
	sched_t *sched;
	int interval;
	int retries;
}app_t;


/************************HANDLER VARIABLES INITIALIZATION**********************/
int wd_is_alive = 0;		/* Changed by HandleSigusr1 */
int wd_let_me_die = 0;		/* Changed by HandleSigusr2 */
/******************************************************************************/

/*************************STATIC FUNCIONS**************************************/

/* Initialize signal handlers and scheduler tasks*/
static app_t *Init(int argc, char *argv[]);
static void HandleSigusr1(int signal_num); /* Handler for SIGUSR1			  */
static void HandleSigusr2(int signal_num); /* Handler for SIGUSR2			  */
static int SchedSignal(void *param);	   /* Act func for scheduler		  */
static int WakeUpApp(app_t *app);		   /* If app is not signaling		  */
static int SuicideDog(app_t *app);	   	   /* If got SIGUSR2 and ready to die */
/******************************************************************************/
int main(int argc, char *argv[])
{
	app_t *app = NULL;
	
LOG_FLOW("in watchdog");

	/* Initialize app_t scheduler and signal handlers						*/
	app = Init(argc, argv);
	if (NULL == app)
	{
		PRINT_ERROR("scheduler error");
		return (1);
	}
	
	/* Run scheduler until SIGUSR2											*/
	SchedRun(app->sched);
	
	SuicideDog(app);
	
	return (0);
}

static app_t *Init(int argc, char *argv[])
{
	struct 	sigaction act_usr1 = {{0}};	/*handler for SIGUSR1 				*/
	struct 	sigaction act_usr2 = {{0}};	/*handler for SIGUSR2 				*/
	app_t 	*app = NULL;
	int 	i = 0;
	
	/* Allocate app					*/
	if (NULL == (app = calloc(1, sizeof(app_t))))
	{
		PRINT_ERROR("malloc error");
		return (NULL);
	}
	
	/* Allocate space for app->argv */
	if (NULL == (app->argv = malloc(sizeof(char *) * argc)))
	{
		PRINT_ERROR("malloc error");
		free(app);
		return (NULL);
	}
	
	for (i = 0; i < argc - 2; ++i)
	{
		app->argv[i] = argv[3 + i];
	}

	/* Extract interval and retries from argv and restore it to app's argv	  */
	if (3 <= argc)
	{
		app->interval = atoi(argv[1]);
		app->retries = atoi(argv[2]);	
	}

	app->pid = getppid(); 

	/* Initialize handlers			*/
	act_usr1.sa_handler = HandleSigusr1;
	if (-1 == sigaction(SIGUSR1, &act_usr1, NULL))
	{
		PRINT_ERROR("sigaction failure");
		return (NULL);
	}
	
	act_usr2.sa_handler = HandleSigusr2;
	if (-1 == sigaction(SIGUSR2, &act_usr2, NULL))
	{
		PRINT_ERROR("sigaction failure");
		return (NULL);
	}
	
	/* Create scheduler and add task */
	app->sched = SchedCreate();
	if (NULL == app->sched)
	{
		PRINT_ERROR("SchedCreate error");
		return (NULL);
	}
	
	if (UidIsBadId(SchedAdd(app->sched, SchedSignal, app, app->interval)))
	{
		PRINT_ERROR("SchedAdd error");
		SchedDestroy(app->sched);
		return (NULL);
	}

	/* Signal app that watch dog is ready for IPC	*/
	kill(app->pid, SIGALRM);
	
	return (app);
}

static int SuicideDog(app_t *app)
{
	/* Send acknowledge that got SIGUSR2, stop scheduler and free resources */
	kill(app->pid, SIGUSR2);
	
	SchedDestroy(app->sched);
	free(app->argv);
	free(app);
	
	return (0);
}

void HandleSigusr1(int signal_num)
{
	wd_is_alive = 0;
	return;
}

void HandleSigusr2(int signal_num)
{
	wd_let_me_die = 1;
	return;
}

static int SchedSignal(void *param)
{
	app_t *app = param;

LOG_FLOW("in wd SchedSignal");
	
	if (!wd_let_me_die)						/* If app still wants to live 	*/
	{
		++wd_is_alive;
		if (app->retries > wd_is_alive)		/* If app sent signal in 		*/
		{									/* the "retries" time			*/
			kill(app->pid, SIGUSR1);
		}
		else 
		{
			wd_is_alive = 0;
			WakeUpApp(app);
		}
	}
	else
	{
		SchedStop(app->sched);
	}
	
	return (0);
}

static int WakeUpApp(app_t *app)
{
	kill(app->pid, SIGTERM);
fprintf(stderr, "%s\n", app->argv[0]);	
	if (-1 == execvp(app->argv[0], app->argv))
	{
		PRINT_ERROR("CreateApp fatal error");
	}

	return (1);
}
