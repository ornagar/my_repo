/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Calc                                   #################################
 *                                         ##########    ####       ########
 *  Functions decleration                  ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  20-07-2017                             ##########    ####  ###  ######## 
 *  13:21:22                               #################################
 * 
 * The calculator takes care of multiple operation in one line (string)
 * it follows Mathematical rules and calculates the next operations:
 * adition, substraction, multiplication, divition and power.
 * The use of pharenthesis is allowed and works fine.
 * 
 * Before using the calculate function initialize it with CalcInit
 * max length refers to the string length.
 * After the calculator is not needed any more, 
 * free all its resources with CalcDestroy.
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifndef __CALC_H__
#define __CALC_H__

typedef struct calculator calc_t;

typedef enum 
{
	SUCCESS,
	MATH_ERROR,
	SYNTAX_ERROR
} status_t;

/*
 * Initializes the calculator for usage
 */
calc_t *CalcInit(size_t max_length);

/*
 * Frees all resources after calculator usage
 */
void CalcDestroy(calc_t *calc);

/*
 * Function CalcCalculate takes string str and calculates it taking 
 * care of all math rules using the next operators '/' '*' '-' '+' '^' "()".
 * The function Returns a double result.
 * Return status should be checked with "status variable".
 * Return statuses: SUCCESS, MATH_ERROR & SYNTAX_ERROR.
 */
double CalcCalculate(const char *str, status_t *status, calc_t *calc);

#endif /* __CALC_H__ */
