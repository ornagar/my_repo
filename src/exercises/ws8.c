/******************************************************************************
 * 26.05.17
 * Work Sheet 8.
 * Or Nagar.
 * creating a struct of student info using an input file.
 *****************************************************************************/
#include <stdio.h>			/* printf()		*/
#include <stdlib.h>			/* EXIT_SUCCESS	*/
#include <string.h>			/* strtok()		*/
#include <assert.h>			/* assert()		*/

#include "utils.h"			/*DEBUG()		*/

typedef struct 							/*declaring a struct of type student_t  */
{
	unsigned long    id;
	char first_name[16];
	char  last_name[16];
	char   cell_num[12];
	char         gender;
	
} student_t;

/**********************function's declarations*********************************/
student_t    *CreateStudentArray(void);
void     PrintStudents(student_t *ptr);
void    PrintArrOffset(student_t *ptr);
void PrintStructOffset(student_t *ptr);

int            CountLines(char *name);
/******************************************************************************/

#define STUDENT_NUM	(CountLines("input_file.txt"))	
#define LINE_SIZE		    				   (50)

int main(void)
{
	student_t *student = NULL;
	printf("%d\n", STUDENT_NUM);
	student = CreateStudentArray();
	PrintStudents(student);
	PrintArrOffset(student);
	PrintStructOffset(student);
	
	free(student);
	student = NULL;
	
	return (EXIT_SUCCESS);
}

/*
 * Function takes input lines from a file and assigns each variable
 * of STUDENTS to the right part of the line.
 * the function returns a pointer to the array.
 */
student_t *CreateStudentArray(void)
{
	student_t *students = NULL;
	student_t *students_start = NULL;
	FILE *fptr = NULL;
	char line[LINE_SIZE];
	char delim[] = " .,\t\n\0";
	char *temp;
	int i = 0;
	
	/* allocating memory for number of lines in input * student_t */
	if (NULL == (students = malloc(STUDENT_NUM*sizeof(student_t))))	
	{
		DBG(fprintf(stderr, "error while allocating memory: aborting...\n");)
		return (NULL);
	}
	students_start = students;
	
	/* opens the file in read mode */
	if (NULL == (fptr = fopen("input_file.txt", "r")))	
	{
		DBG(fprintf(stderr, "error while opening file: aborting...\n");)
		return (NULL);
	}
	
	
	/* for each member in the array. */
	for (i = 0; i < STUDENT_NUM; ++i)	
	{
		fgets(line ,LINE_SIZE, fptr);		/* scans each line of the file. */
		
		/* using strtok we take each part of
		 * the line to the coresponding variable. 
		 */

		strcpy(students->first_name, strtok(line, delim));
		strcpy(students->last_name, strtok(NULL, delim));
		students->id = atol(strtok(NULL, delim));
		strcpy(students->cell_num, strtok(NULL, delim));
		temp = strtok(NULL, delim);
		students->gender = temp[0];
		
		++students;
	}

	fclose(fptr);
	return (students_start);
}

/*
 * Function takes a pointer to student_t and prints all of its 
 * variables in a formated way.
 */
void PrintStudents(student_t *ptr)
{
	int i = 0;
	
	assert(ptr);
	
	puts("Students list:");
	
	while (i < STUDENT_NUM)
	{
		printf("student #%d: ", i+1);
		
		printf("%s ", ptr->first_name);
		printf("%s, ", ptr->last_name);
		printf("%s, ", ptr->cell_num);
		printf("%09lu, ", ptr->id);
		printf("%c.\n", ptr->gender);
		
		++i;
		++ptr;
	}
}

/*
 * Function takes a pointer to student_t and prints the
 * offsets of each member in the student_t's array.
 */
void PrintArrOffset(student_t *ptr)
{
	int i = 0;
	
	assert(ptr);
	
	puts("Arr offsets:");
	
	for (i = 0; i <STUDENT_NUM; ++i)
	{
		printf("offset: students[%d] = %ld;\n",
        	i, ((size_t)&ptr[i] - (size_t)&ptr[0]));
	}
	
	return;
}

/*
 * Function takes a pointer to student_t and prints the
 * offsets of each variable in the array's first student_t's member.
 */
void PrintStructOffset(student_t *ptr)
{
	assert(ptr);
	
	puts("Struct offsets:");
	
	printf("offset: students[0].id = %ld;\n",
      	((size_t)&ptr[0].id - (size_t)&ptr[0]));
	printf("offset: students[0].first_name = %ld;\n",
		((size_t)&ptr[0].first_name - (size_t)&ptr[0]));
	printf("offset: students[0].last_name = %ld;\n",
		((size_t)&ptr[0].last_name - (size_t)&ptr[0]));
	printf("offset: students[0].cell_num = %ld;\n",
		((size_t)&ptr[0].cell_num - (size_t)&ptr[0]));
	printf("offset: students[0].gender = %ld;\n",
       	((size_t)&ptr[0].gender - (size_t)&ptr[0]));
       	printf("offset: students[1] - students[0]gender = %ld;\n",
       	((size_t)&ptr[1] - (size_t)&ptr[0].gender));
       	
	return;	
}



int CountLines(char *name)
{
	FILE *fptr = NULL;
	
	char line[LINE_SIZE];
	int count  = 0;
	
	assert(name);
	
	if (NULL == (fptr = fopen(name, "r")))	/*opens the file in read mode	*/
	{
		DBG(fprintf(stderr, "error while opening file: aborting...\n");)
		return (1);
	}
	
	while(NULL != fgets(line ,LINE_SIZE, fptr))		/*counts number of Lines	*/
	{
		++count;
	}
	fclose(fptr);
	
	return (count);
}
