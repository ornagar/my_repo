/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Wd                                     #################################
 *                                         ##########    ####       ########
 *  Functions decleration                  ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  03-09-2017                             ##########    ####  ###  ######## 
 *  07:59:24                               #################################
 * 
 * The Watch Dog program is an application that keeps your 
 * process in the air in case of crash or the process got stuck. 
 * 
 * Warnings: 
 * Finishing a process without calling LetMeDie will cause 
 * the watchdog to restart the process.
 * 
 * retries must be greater then retries or unexpected results might happen.
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifndef __WD_H__
#define __WD_H__

typedef struct wd wd_t;

/* 
 * Start your application with KeepMeAlive func, sending with it
 * the argc, argv from your main, the interval is the timing (in seconds)
 * that the wd will check on your process to see its alive. retries is the 
 * number of intervals to do when the process is not responding before 
 * restarting it.
 * Returns a pointer to a struct wd_t used for LetMeDie function.
 * returns NULL on failure.
 */
wd_t *KeepMeAlive(int argc, char **argv, int interval, int retries);

/*
 * LetMeDie funcion tells the watch dog to finish his job and cleanup resources.
 * Returns 0 for success and 1 for failure.
 */
int LetMeDie(wd_t *wd);


#endif /* __WD_H__ */


