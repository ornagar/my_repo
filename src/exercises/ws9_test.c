/******************************************************************************
 * 29.05.17
 * Work Sheet 9 main function.
 * Or Nagar.
 *****************************************************************************/
#include <stdio.h>			/* printf()		*/
#include <stdlib.h>			/* EXIT_SUCCESS	*/
#include <string.h>			/* strcpy()		*/

#include "ws9.h"

int main(void)
{
	
	char *dest = NULL;
	char car[] = "1010";
	int d = 0;
	char str[] = "hfjdkemeldojfmdldockfmfreldlcivfmdldli";
	char source[] = "take me home and be my friend";

	puts(str);
	MemCpy(str, source, 15);
	puts(str);
	
	dest = Itoa(-1450);
	puts(dest);
	free(dest);
	d = Atoi("-452");
	printf("%d\n", d);
	
	d = AtoAny(car, 2);
	printf("%d\n", d);

	return (EXIT_SUCCESS);
}
