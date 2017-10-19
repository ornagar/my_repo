/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Heapify                                #################################
 *                                         ##########    ####       ########
 *  Tester                                 ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  02-08-2017                             ##########    ####  ###  ######## 
 *  14:32:23                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */

#include "heapify.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

static int IsBef(const void *data1, const void *data2, void *param);

int main(void)
{
	int arr[] = {0, 1 ,2 ,3, 4, 5, 6 ,7, 8};
	
	/*HeapifyUp(&arr, 9, sizeof(int), 8, IsBef, NULL);
	*/
	printf("%d\n", arr[3]);
	
	
	HeapifyDown(&arr, 9, sizeof(int), 1, IsBef, NULL);
	
	printf("%d\n", arr[4]);
	
	return(EXIT_SUCCESS);
}

static int IsBef(const void *data1, const void *data2, void *param)
{
	return (*(int *)data1 > *(int *)data2);
}


