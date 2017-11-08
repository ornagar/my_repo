/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Calc                                   #################################
 *                                         ##########    ####       ########
 *  Functions definition                   ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  20-07-2017                             ##########    ####  ###  ######## 
 *  13:21:22                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <assert.h>					 /* assert()					  */
#include <math.h>					 /* pow()						  */

#include "calc.h"					 /* all functions declerations	  */
#include "stack.h"					 /* stack_t						  */
#include "utils.h"					 /* Or's functions                */

#define ASCII_RANGE (256)
#define STATE_RANGE (3)

/*
 * States for state machine.
 */
typedef enum
{
	WAIT_FOR_NUM,
	WAIT_FOR_OP,
	ERROR
	
} state_t;

/*
 * Enum for operators priority.
 */
typedef enum 
{
	NOTHING = 0,
	OPEN_PAR,
	SUB,
	ADD = SUB,
	MULT,
	DIV = MULT,
	POW,
	CLOSING_PAR
	
}priority_t;

/*
 * State entry for state machine table.
 */
typedef struct 
{
	status_t (*handler)(char **char_ptr, calc_t *calc);
	state_t next_state;
	
}state_entry_t;

/*
 * Priority entry for operators table.
 */
typedef struct
{
	status_t (*calc_func)(double *num1, double num2);
	priority_t priority;
	
} operator_t;

/*
 * Calculator managing struct.
 */
struct calculator
{
	state_entry_t table[STATE_RANGE][ASCII_RANGE];
	operator_t operators[ASCII_RANGE];
	stack_t *num_stack;
	stack_t *op_stack;
};

/***************************STATIC FUNCS***************************************/
static status_t HandleNum(char **char_ptr, calc_t *calc);
static status_t HandleOperator(char **char_ptr, calc_t *calc);
static status_t HandleOpenBrac(char **char_ptr, calc_t *calc);
static status_t HandleCloseBrac(char **char_ptr, calc_t *calc);
static status_t HandleStrEnd(char **char_ptr, calc_t *calc);
static status_t HandleUnary(char **char_ptr, calc_t *calc);
static status_t HandleSpaces(char **char_ptr, calc_t *calc);
static status_t HandleError(char **char_ptr, calc_t *calc);

static status_t Mult(double *num1, double num2);
static status_t Div(double *num1, double num2);
static status_t Sum(double *num1, double num2);
static status_t Sub(double *num1, double num2);
static status_t Dummy(double *num1, double num2);
static status_t Power(double *num1, double num2);
/******************************************************************************/

calc_t *CalcInit(size_t max_length)
{
	calc_t *calc = NULL;
	int i = 0;
	int j = 0;
	char dummy = NOTHING;
	
	assert(2 <= max_length);
	
	if (NULL == (calc = (calc_t *) malloc(sizeof(calc_t))))
	{
		MALLOC_ERROR;
		return (NULL);
	}
	
	/* Initialize num_stack to max_length elements of type double */
	calc->num_stack = StackCreate(max_length, sizeof(double));
	if (NULL == calc->num_stack)
	{
		MALLOC_ERROR;
		free(calc);
		return (NULL);
	}
	
	/* Initialize op_stack to max_length elements of type char */
	calc->op_stack = StackCreate(max_length, sizeof(char));
	if (NULL == calc->op_stack)
	{
		MALLOC_ERROR;
		
		StackDestroy(calc->num_stack);
		free(calc);
		return (NULL);
	}
	/* Dummy is a fake operator for operators handlers */
	StackPush(calc->op_stack, &dummy);
	
	/* For all next_state = ERROR, func will point to HandleError */
	for (i = WAIT_FOR_NUM; i < ERROR; ++i)
	{
		for (j = 0; j < ASCII_RANGE; ++j)
		{
			calc->table[i][j].handler = HandleError;
			calc->table[i][j].next_state = ERROR;
		}
	}
	
	 /* For table[WAIT_FOR_OP]['\0'] state = WAIT_FOR_OP, 
	  * func = HandleStrEnd 
	  */
	calc->table[WAIT_FOR_OP]['\0'].next_state = ERROR;
	calc->table[WAIT_FOR_OP]['\0'].handler = HandleStrEnd;
	 
	/* For table[WAIT_FOR_NUM]['0' - '9'] state = WAIT_FOR_OP,
	 * func = HandleNUM 
	 */
	for (i = '0'; i <= '9'; ++i)
	{
		calc->table[WAIT_FOR_NUM][i].next_state = WAIT_FOR_OP;
		calc->table[WAIT_FOR_NUM][i].handler = HandleNum;
	}
	
	/* Handle unary '+' '-' (ignore them)									  */
	calc->table[WAIT_FOR_NUM]['-'].next_state = WAIT_FOR_OP;
	calc->table[WAIT_FOR_NUM]['-'].handler = HandleUnary;
	calc->table[WAIT_FOR_NUM]['+'].next_state = WAIT_FOR_OP;
	calc->table[WAIT_FOR_NUM]['+'].handler = HandleUnary;
	
	/* For table[WAIT_FOR_OP]['/''*''-''+''^'] state = WAIT_FOR_NUM,
	 * func = HandleOperator 
	 */
	calc->table[WAIT_FOR_OP]['+'].next_state = WAIT_FOR_NUM;
	calc->table[WAIT_FOR_OP]['+'].handler = HandleOperator;
	
	calc->table[WAIT_FOR_OP]['-'].next_state = WAIT_FOR_NUM;
	calc->table[WAIT_FOR_OP]['-'].handler = HandleOperator;
	
	calc->table[WAIT_FOR_OP]['*'].next_state = WAIT_FOR_NUM;
	calc->table[WAIT_FOR_OP]['*'].handler = HandleOperator;
	
	calc->table[WAIT_FOR_OP]['/'].next_state = WAIT_FOR_NUM;
	calc->table[WAIT_FOR_OP]['/'].handler = HandleOperator;
	
	calc->table[WAIT_FOR_OP]['^'].next_state = WAIT_FOR_NUM;
	calc->table[WAIT_FOR_OP]['^'].handler = HandleOperator;

	/*For table[WAIT_FOR_NUM]['('] state = WAIT_FOR_NUM, func = HandleOpenBrac*/
	calc->table[WAIT_FOR_NUM]['('].next_state = WAIT_FOR_NUM;
	calc->table[WAIT_FOR_NUM]['('].handler = HandleOpenBrac;
	
	/* For table[WAIT_FOR_OP][')'] state = WAIT_FOR_OP, func = HandleCloseBrac*/
	calc->table[WAIT_FOR_OP][')'].next_state = WAIT_FOR_OP;
	calc->table[WAIT_FOR_OP][')'].handler = HandleCloseBrac;	 
	
	/* Handle spaces (ignore them)											  */
	calc->table[WAIT_FOR_OP][' '].next_state = WAIT_FOR_OP;
	calc->table[WAIT_FOR_OP][' '].handler = HandleSpaces;
	calc->table[WAIT_FOR_NUM][' '].next_state = WAIT_FOR_NUM;
	calc->table[WAIT_FOR_NUM][' '].handler = HandleSpaces;
	
	/* Initialize  operator_table's vars and funcs	*/
		/* For all priority = NOTHING, func = Dummy */
	for (i = 0; i < ASCII_RANGE; ++i)
	{
		calc->operators[i].priority = NOTHING;
		calc->operators[i].calc_func = Dummy;
	}
		 
	calc->operators['/'].priority = DIV;
	calc->operators['/'].calc_func = Div;
	
	calc->operators['*'].priority = MULT;
	calc->operators['*'].calc_func = Mult;
	
	calc->operators['+'].priority = ADD;
	calc->operators['+'].calc_func = Sum;
	
	calc->operators['-'].priority = SUB;
	calc->operators['-'].calc_func = Sub;
	
	calc->operators['^'].priority = POW;
	calc->operators['^'].calc_func = Power;
	
	return (calc);
}

void CalcDestroy(calc_t *calc)
{
	assert(calc);
	
	StackDestroy(calc->num_stack);
	StackDestroy(calc->op_stack);
	calc->num_stack = calc->op_stack = NULL;
	free(calc);
	
	return;
}

double CalcCalculate(const char *str, status_t *status, calc_t *calc)
{
	status_t handler_status = SUCCESS;
	state_t state = WAIT_FOR_NUM;
	char *runner  = (char *)str;
	double result = 0; 
	
	assert(str && calc && status);
	
	while (ERROR != state && SUCCESS == handler_status) 
	{
		handler_status = (status_t)calc->table[state][(int)*runner].
								handler(&runner, calc);
		state = calc->table[state][(int)*(runner-1)].next_state;
	}
	
	if (SUCCESS == handler_status)
	{
		result  = *(double *)StackPeek(calc->num_stack);
	}
	*status = handler_status;
	 
	while (0 < StackSize(calc->num_stack))
	{
		StackPop(calc->num_stack);
	}
	 
	while (1 < StackSize(calc->op_stack))
	{
		StackPop(calc->op_stack);
	}
	 
	 return(result);
}

/***************************STATIC FUNCS***************************************/
static status_t HandleNum(char **char_ptr, calc_t *calc)
{
	double num = strtod(*char_ptr, char_ptr);
	return (StackPush(calc->num_stack, &num));
}

static status_t HandleOperator(char **char_ptr, calc_t *calc)
{
	double var = 0; 
	status_t status = SUCCESS;
	unsigned char peek_cpy = *(char *)StackPeek(calc->op_stack);
	
	/* while  char_ptr.priority <= peek.priority */
	while (calc->operators[(int)**char_ptr].priority <=
		   calc->operators[peek_cpy].priority)
	{
		var = *(double *)StackPeek(calc->num_stack);
		StackPop(calc->num_stack);
		
		status = calc->operators[peek_cpy].
						   calc_func((double *)StackPeek(calc->num_stack), var);
		
		if (SUCCESS != status)
		{
			return (status);
		}
		
		StackPop(calc->op_stack);
		peek_cpy = *(char *)StackPeek(calc->op_stack);
	}
	
	StackPush(calc->op_stack, *char_ptr);
	
	/* move pointer to next char */
	++(*char_ptr);
	
	return(status);
}

static status_t HandleOpenBrac(char **char_ptr, calc_t *calc)
{
	StackPush(calc->op_stack, *char_ptr);
	
	++(*char_ptr);
		
	return (SUCCESS);
}

static status_t HandleCloseBrac(char **char_ptr, calc_t *calc)
{
	char old = *(char *)StackPeek(calc->op_stack);
	double var = 0; 
	status_t status = SUCCESS;
	
	while (old != '(' && SUCCESS == status)
	{
		var = *(double *)StackPeek(calc->num_stack);
		StackPop(calc->num_stack);
		
		status = calc->operators[(int)*(char *)StackPeek(calc->op_stack)].
						calc_func((double *)StackPeek(calc->num_stack), var);
		if (SUCCESS != status)
		{
			return (status);
		}
		
		StackPop(calc->op_stack);
		old = *(char *)StackPeek(calc->op_stack);
	}
	
	StackPop(calc->op_stack);
	
	/* move pointer to next char */
	++(*char_ptr);
	
	return(status);
}

static status_t HandleStrEnd(char **char_ptr, calc_t *calc)
{
	double var = 0;
	status_t status = SUCCESS;
	/* while  not empty */
	while (1 < StackSize(calc->op_stack))
	{
		var = *(double *)StackPeek(calc->num_stack);
		StackPop(calc->num_stack);
		status = calc->operators[(int)*(char *)StackPeek(calc->op_stack)].
						calc_func((double *)StackPeek(calc->num_stack), var);
		if (SUCCESS != status)
		{
			return (status);
		}			
		StackPop(calc->op_stack);
	}
	
	if (1 != StackSize(calc->op_stack) || 1 != StackSize(calc->num_stack))
	{
		return (SYNTAX_ERROR);
	}
	++(*char_ptr);
	/* calc all */
	return (SUCCESS);
}

static status_t HandleUnary(char **char_ptr, calc_t *calc)
{
	char *prev_ptr = *char_ptr;
	
	double num = strtod(*char_ptr, char_ptr);
	
	if (prev_ptr == *char_ptr)
	{
		return (SYNTAX_ERROR);
	}
	
	return (StackPush(calc->num_stack, &num));
}

static status_t HandleSpaces(char **char_ptr, calc_t *calc)
{
	/* move pointer to next char */
	++(*char_ptr);
	
	return(SUCCESS);
}

static status_t HandleError(char **char_ptr, calc_t *calc)
{
	return (SYNTAX_ERROR);
}

static status_t Mult(double *num1, double num2)
{
	*num1 *= num2;
	return (SUCCESS);
}

static status_t Div(double *num1, double num2)
{
	if (0.0 == num2)
	{
		return (MATH_ERROR);
	}
	*num1 /= num2;
	return (SUCCESS);
}

static status_t Sum(double *num1, double num2)
{
	*num1 += num2;
	return (SUCCESS);
}

static status_t Sub(double *num1, double num2)
{
	*num1 -= num2;
	return (SUCCESS);
}

static status_t Power(double *num1, double num2)
{
	*num1 = pow(*num1, num2);
	return (SUCCESS);
}

static status_t Dummy(double *num1, double num2)
{
	return (SYNTAX_ERROR);
}
