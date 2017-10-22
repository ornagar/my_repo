/*****************************************************************************
 * Or Nagar.
 * My utils.
 * Utils: DBG(), MAX(), MIN(), PRINT_ERROR, MALLOC_ERROR, FILE_OPEN_ERROR.
 * 26/06/17
 ****************************************************************************/

#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>

#ifdef _DEBUG
#define DBG(x) x
#else 
#define DBG(x)
#endif

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/* Prints an error message when error occours */
#ifdef _DEBUG
#define PRINT_ERROR(st) fprintf(stderr,st\
				",%s in file %s%s %sin line %s%d%s\n",\
						KCYN, KRED,__FILE__, KCYN, KRED, __LINE__, KWHT)
#else
#define PRINT_ERROR(st) 
#endif

/* Prints a log message showing process flow */
#ifdef _DLOG_FLOW
#define LOG_FLOW(st) fprintf(stderr,"%s"st\
				":%s in file %s%s %sin line %s%d%s\n",\
						KYEL, KCYN, KGRN,__FILE__, KCYN, KGRN, __LINE__, KWHT)
#else
#define LOG_FLOW(st) 
#endif

#define FUNC_TEST(success) \
			(success ? 1: (printf("***%s: Failure***\n\n", __func__)))

#define TEST(res,str, errs)  \
		  (res) ?   printf(" \b") :\
		   printf("%s %s %s %s\"%s\" line:%d error number: %d\n", \
		  	KRED "FAILED:" KWHT,KWHT,__FUNCTION__,KWHT , str, __LINE__, ++errs)\
		  			

#define DEADBEEF ((void *) 0xDEADBEEFDEADBEEF)

/*******************************************************************************
 * 
 *				 NOT IN USE, KEPT FOR PREVIOUS VERSIONS
 * 
 ******************************************************************************/

/* Prints an error message when malloc fails */
#ifdef _DEBUG
#define MALLOC_ERROR fprintf\
		(stderr,"error allocating memory in function %sin file %s in line %d\n",\
						__func__, __FILE__, __LINE__)
#else
#define MALLOC_ERROR 
#endif

/* Prints an error message when fopen fails */
#ifdef _DEBUG
#define FILE_OPEN_ERROR fprintf\
			(stderr,"error opening file in function %s in file %s in line %d\n",\
						 __func__, __FILE__, __LINE__)						 
#else
#define FILE_OPEN_ERROR 
#endif

#endif		/*__UTILS_H__*/
