/******************************************************************************
 ws3_string.h includes string manipulation funcions.
 14.05.17
 
 For all functions, pointer arguments are not checked for NULL value.
*******************************************************************************/
#ifndef __WS2_STRING_H__
#define __WS2_STRING_H__

#include <stddef.h>			/*size_t*/

/*
 * Strlen returns char array's length (excluding null terminator).
 * pointer arguments are not checked for NULL value.
 */
size_t Strlen(const char *str);

/* 
 * Strcmp compares each index in two given strings and returns
 * the difference between the first occurrence of inequality.
 * pointer arguments are not checked for NULL value.
 * RETURN VALUE:
 *  0 - strings are equal.
 * >0 - str1 is larger than str2 (comparing single char in ascii values).
 * <0 - str2 is larger than str1 (comparing single char in ascii values).
 */
int Strcmp(const char *str1, const char *str2);

/*
 * Strcpy copies a source array to a given destination array 
 *                  *W A R N I N G*
 * DESTINATION ARRAY MUST BE EQUAL OR LARGER THAN SOURCE!!!
 * RETURN VALUE: a pointer to the destination string dest.
 */
char *Strcpy(char *dest, const char *src);

/*
 * Strcpy copies first n bytes of a source array 
 * to a given destination array. 
 * RETURN VALUE: a pointer to the destination string dest.
 */
char *Strncpy(char *dest, char *src, size_t size);

/*
 * Strcasecmp compares each index in two given strings and returns
 * the difference between the first occurrence of inequality
 * ignoring case difference.
 * RETURN VALUE:
 *  0 - strings are equal.
 * >0 - str1 is larger than str2 (comparing single char in ascii values).
 * <0 - str2 is larger than str1 (comparing single char in ascii values). 
 */
int Strcasecmp(char *str1, char *str2);

/*
 * Strchr returns a pointer to the first occurrence
 * of the character ch in the string str.
 * RETURN VALUE: a pointer to the matched character or NULL if
 * the character is not found.
 */
char *Strchr(const char *str, int ch);

/*
 * Strdup duplicates a given string to a new assigned char pointer.
 * It is the user's responsability to free the allocated memory using free().
 * RETURN VALUE: a pointer to the duplicated  string.
 */
char *Strdup(const char *str);

/*
 * Strcat appends src to the dest string, overwriting the terminating
 * null byte ('\0') at the end of dest, and then adds a terminating null byte.
 * RETURN VALUE: pointer to the resulting string dest.
 */
char *Strcat(char *dest, const char *src);

/*
 * Strncat is like Strcat exept it appends only -n- bytes 
 * from src. 
 * RETURN VALUE: pointer to the resulting string dest.
 */
 char *Strncat(char *dest, const char *src, size_t size);
 
/*
 * Strstr finds the first occurrence of needle in haystack.
 * The terminating null bytes ('\0') are not compared.
 * RETURN VALUE: a pointer to the beginning of the substring, or NULL if the substring
 * is not found.
 */
char *Strstr(const char *haystack, const char *needle);

/*
 * Strtok
 */
char *Strtok(char *str, const char *delim);
 
 /*
 * RmSpaces takes a string and removes spaces from the begining 
 * and the end of the string, and removes spaces in the middle 
 * of the string if there is more than one.
 */
void RmSpaces(char *str);
 
#endif /*  __WS2_STRING_H__  */


