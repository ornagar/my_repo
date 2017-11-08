/******************************************************************************
 * creator :  Or Nagar		                                                  *
 * 04/06                                                                      *	
 * Bits array library header file.                                            *
 ******************************************************************************/

#ifndef __BITS_ARRAY_H__ /* include guard */
#define __BITS_ARRAY_H__



/****************************************************************************** 
   assumption : index is 0 or more and smaller then 64
   otherwise is unpredictable
 ******************************************************************************/


/* check if all bits are on return 1 for true and 0 for false */
#define	BITS_ARR_IS_ALL_ON(arr)		(~0ul==arr) 

/* check if all bits are off return 1 for true and 0 for false */
#define BITS_ARR_IS_ALL_OFF(arr)	( 0ul==arr)

/* 
 * the function receieves a bit array and an index
 * and returns the array with the index bit set on
 */
unsigned long BitArrSetOn(unsigned long arr, unsigned int index);

/*
 * the function receieves a bit array and an index
 * and returns the array with the index bit set off
 */
 unsigned long BitArrSetOff(unsigned long arr, unsigned int index);

/*
 * the function receieves a bit array an index and a value
 * and returns the array with the index bit set to the value
 */
unsigned long BitArrSet(unsigned long arr, unsigned int index, unsigned int value);

/*
 * the function receieves a bit array and an index
 * and returns the 1 if the index bit is on and 0 else
 */
int BitArrIsOn(unsigned long arr, unsigned int index);

/*
 * the function receieves a bit array and an index
 * and returns the 1 if the index bit is off and 0 else
 */
int BitArrIsOff(unsigned long arr, unsigned int index);

/*
 * the function receieves a bit array and an index
 * and returns the array with the index bit value fliped
 */
unsigned long BitArrFlip(unsigned long arr, unsigned int index);

/*
 * the function receieves a bit array and a number
 * and returns the array rotated n times to the right
 * assumption n is positive or 0 otherwise is unpredictable
 */
unsigned long BitArrRotateRight(unsigned long arr, size_t n);

/*
 * the function receieves a bit array and a number
 * and returns the array rotated n times to the left
 * assumption n is positive or 0 otherwise is unpredictable
 */
unsigned long BitArrRotateLeft(unsigned long arr, size_t n);

/*
 * the function receieves a bit array
 * and returns the array's mirror
 */
unsigned long BitArrMirror(unsigned long arr);

/*
 * the function receieves a bit array
 * and returns the number of the set on bits in the array
 */
int BitArrCountOn(unsigned long arr);

/*
 * the function receieves a bit array
 * and returns the number of the set off bits in the array
 */
int BitArrCountOff(unsigned long arr);

#endif /* __BITS_ARRAY_H__ */
