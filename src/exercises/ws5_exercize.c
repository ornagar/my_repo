/******************************************************************************
 * 21.05.17
 * Work Sheet 5.
 * Or Nagar.
 * One Sorvivor game simulation.
 *****************************************************************************/
#include <stdio.h> 		 /* printf()     */
#include <stdlib.h>		 /* Exit_success */
#include <string.h>	
	 
#include "utils.h"		 /* DBG          */

int main(int argc, char **argv)
{
	FILE *fptr = NULL;
	
	fprintf(stdout, "char - %lu\n", sizeof(char));
	fprintf(stdout, "int - %lu\n", sizeof(int));
	fprintf(stdout, "short int - %lu\n", sizeof(short int));
	fprintf(stdout, "long int - %lu\n", sizeof(long int));
	fprintf(stdout, "float - %lu\n", sizeof(float));
	fprintf(stdout, "double - %lu\n", sizeof(double));
	fprintf(stdout, "any pointer - %lu\n", sizeof(int *));
	fprintf(stdout, "FILE - %lu\n", sizeof(FILE));

	fptr = fopen("/home/xyz/test11","a");
	if (NULL == fptr)
	{
		DBG(fprintf(stderr, "error while allocating data: aborting...\n");)
		return (1);
	}
		
	fprintf(fptr,"added in 21.05.17\n");
	
	fclose(fptr);
	
	return (0);
}



