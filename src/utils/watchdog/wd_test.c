/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Wd                                     #################################
 *                                         ##########    ####       ########
 *  Tester                                 ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  03-09-2017                             ##########    ####  ###  ######## 
 *  07:59:24                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                  /* printf()                      */
#include <stdlib.h>					/* system(), EXIT_SUCCESS		 */
#include <unistd.h>					/* sleep()						 */

#include "wd.h"						/* all functions declerations	 */
#include "utils.h"					/* Or's functions                */

enum
{
	SUCCESS,
	FAILURE
};


int main(int argc, char **argv)
{	
	wd_t *wdog = NULL;
	int sleep_time = 4;
	
LOG_FLOW("app wake up");
	
	wdog = KeepMeAlive(argc, argv, 1, 10);
	if (NULL == wdog)
	{
		PRINT_ERROR("KeepMeAlive error");
		return (1);
	}

	do
	{
		sleep_time = sleep(sleep_time);
	}
	while (sleep_time);

	LetMeDie(wdog);
	
	return(EXIT_SUCCESS);
}
