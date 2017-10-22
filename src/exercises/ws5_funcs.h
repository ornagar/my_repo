/******************************************************************************
 ws5_funcs.h includes Handle input to files funcions.
 
 22.05.17
 
 Or Nagar.
*******************************************************************************/
#ifndef __WS5_FUNCS_H__
#define __WS2_FUNCS_H__

#include <stdio.h>

/*
 * Takes an input from the user and appends it
 * to the logger file.
 * Return Values:
 * 0 - for successfull return.
 * 1 - if file couldn't be opened.
 *
 * EXTRA SPACES BETWEEN WORDS WILL BE IGNORED.
 */
int HandleAppend(char *input, char *name);

/*
 * Exits the program safely.
 * Return Values:
 * 1 - to exit program.
 */
int HandleExit(char *input, char *name);

/*
 * Removes the file created by the program's run.
 * Return Values:
 * 0 - for successfull return.
 * 1 - if file couldn't be removed.
 */
int HandleRemove(char *input, char *name);

/*
 * Counts the number of lines in the file.
 * Return Values:
 * 0 - for successfull return.
 * 1 - if file couldn't be opened.
 */
int HandleCount(char *input, char *name);

/*
 * Adds the user's input to the begining of the file.
 * Return Values:
 * 0 - for successfull return.
 * 1 - if file couldn't be opened.
 */
int HandlePreppend(char *input, char *name);


#endif /*  __WS5_FUNCS_H__  */
