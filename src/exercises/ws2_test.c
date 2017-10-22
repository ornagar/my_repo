#include <stdio.h> 		 /*printf()*/
#include <stdlib.h>		 /*Exit_success*/
#include <assert.h>		 /*assert()*/
#include <string.h>
#include "ws2_string.h"

void Tester(double return_value, double wanted_value);

int main(void)
{
	/* testing variables for ws2_string.h*/
	char *name1 = "Or Nagar";
	char *name2 = "OrNagar";
	char *name3 = "Or";
	char *name4 = "Or ";
	char *name5 = "";
	char *name6 = " ";	
	char *name7 = "Or Nagar";
	char *source = "copy me";
	char destination[8];
	char source1[8] = "copy me";
	char destination1[18] = {'\0'};
	char *name10 = "Or Nagar";
	char *name20 = "Or NAgar";
	char *name40 = "or Nagar";
	char *name70 = "Or Nagar";
	char *name101 = "gil1_gil2_gil3_gil4";
	char *dup = NULL;
	char cat_me[20] = "Or";
	char add_me[] = " Nagar";
	char *sub = "gil2";
	int x = 0;
	
	char or[40] = "hi";
	char *c = ",. ";
	char *tok = NULL;
	
	
	/*Strlen test*/
	Tester((double)Strlen(name1), (double)(8));
	Tester((double)Strlen(name2), (double)(7));
	Tester((double)Strlen(name3), (double)(2));
	Tester((double)Strlen(name4), (double)(3));
	Tester((double)Strlen(name5), (double)(0));
	Tester((double)Strlen(name6), (double)(1));
	
	/*Strcmp test*/
	Tester((double)Strcmp(name1, name2), (double)(-46));
	Tester((double)Strcmp(name1, name7), (double)(0));
	Tester((double)Strcmp(name1, name4), (double)(78));
	
	/*Strcpy test*/
	Strcpy(destination, source);
	Tester((double)Strcmp(destination, source), (double)(0));
	
	/*Strncpy test*/
	Strncpy(destination1, source1, 6);
	destination1[7] = '\0';
	x = Strcmp(destination1, "copy m");
	Tester((double)x, (double)(0));
	
	Strncpy(destination1, source1, 15);
	Tester((double)Strcmp(destination1, "copy me"), (double)(0));
	
	/*Strcasecmp test*/
	Tester((double)Strcmp(name10, name20), (double)(32));
	Tester((double)Strcmp(name10, name70), (double)(0));
	Tester((double)Strcmp(name10, name40), (double)(-32));
	
	
	/*Strchr test*/
	Tester((double)*(Strchr(name10, 'a')), (double)('a'));
	
	/*Strdup test*/
	dup = Strdup(source);
	printf("%s\n", dup);
	/*Tester((double)Strcmp(dup, source), (double)(0));*/
	free(dup);
	
	/*Strcat test*/
	Strcat(cat_me, add_me);
	Tester((double)Strcmp(cat_me, "Or Nagar"), (double)(0));
	
	/*Strncat test*/
	Strncat(cat_me, add_me, 3);
	Tester((double)Strcmp(cat_me, "Or Nagar Na"), (double)(0));
	Strncat(cat_me, add_me, 15);
	Tester((double)Strcmp(cat_me, "Or Nagar Na Nagar"), (double)(0));
	
	/*Strstr test*/
	dup = Strstr(name101, sub);
	Tester((double)(*dup), (double)('g'));
	puts(dup);
		
	/*Strtok test*/
	printf("%s\n", or);
	tok = Strtok(or, c);
	printf("%s\n", tok);
	tok = Strtok(NULL, c);
	printf("%s\n", tok);
	tok = Strtok(NULL, c);
	printf("%s\n", tok);
	tok = Strtok(NULL, c);
	printf("%p\n", tok);
	tok = Strtok(NULL, c);
	printf("%p\n", tok);
	return (EXIT_SUCCESS); 
}

/*
 *the tester checks if the functions return value is
 *equal to the expectation.
 */
void Tester(double return_value, double wanted_value)
{
	float epsilon = 0.0000001;
	static int counter = 0;
	if (abs(return_value - wanted_value) < epsilon)
	{
		printf("%d: ", counter);
		puts("Success!!");
		++counter;
	}
	else
	{
		printf("%d: ", counter);
		printf("fail... wanted value was %f and return value is %f\n",
											wanted_value, return_value);
		++counter;
	}
}

