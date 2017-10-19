/******************************************************************************
 * Or Nagar	                        				                          *
 * 04/06																	  *	
 * Bits array tester.														  *
 ******************************************************************************/
#include <stdio.h>			/* printf()			*/
#include <stdlib.h>			/* EXIT_SUCCESS		*/

#include "utils.h"			/* DBG() 			*/
#include "bits_array.h"		/* BitArrSetOn()	*/

DBG(void BitArrPrint(unsigned long arr);)
static void Tester(unsigned long return_value, unsigned long wanted_value, char *str);
static void TestBitArrSetOn(void);
static void TestBitArrSetOff(void);
static void TestBitArrSet(void);
static void TestBitArrIsOn(void);
static void TestBitArrIsOff(void);
static void TestBitArrFlip(void);
static void TestBitArrRotateRight(void);
static void TestBitArrRotateLeft(void);
static void TestBitArrMirror(void);
static void TestBitArrCountOn(void);
static void TestBitArrCountOff(void);


int main(void)
{
	TestBitArrSetOn();
	
	TestBitArrSetOff();
	
	TestBitArrSet();
	
	TestBitArrIsOn();
	
	TestBitArrIsOff();
	
	TestBitArrFlip();
	
	TestBitArrRotateRight();
	
	TestBitArrRotateLeft();
	
	TestBitArrMirror();
	
	TestBitArrCountOn();
	
	TestBitArrCountOff();

	return (EXIT_SUCCESS);
}

static void TestBitArrSetOn(void)
{
	unsigned long arr = 0x05;
	arr = BitArrSetOn(arr, 0);
	Tester(arr, 0x05, "BitArrSetOn: \t1");
	
	arr = 0x05;
	arr = BitArrSetOn(arr, 63);
	Tester(arr, 0x8000000000000005, "BitArrSetOn: \t2");
	
	arr = 0x05;
	arr = BitArrSetOn(arr, 3);
	Tester(arr, 0x0d, "BitArrSetOn: \t3");
}

static void TestBitArrSetOff(void)
{
	unsigned long arr = 0x05;
	arr = BitArrSetOff(arr, 0);
	Tester(arr, 0x04, "BitArrSetOff: \t1");
	
	arr = 0x05;
	arr = BitArrSetOff(arr, 63);
	Tester(arr, 0x05, "BitArrSetOff: \t2");
	
	arr = 0x05;
	arr = BitArrSetOff(arr, 3);
	Tester(arr, 0x05, "BitArrSetOff: \t3");
}

static void TestBitArrSet(void)
{
	unsigned long arr = 0x01;
	arr = BitArrSet(arr, 63, 1);
	Tester(arr, 0x8000000000000001, "BitArrSet: \t1");
	
	arr = 0x05;
	arr = BitArrSet(arr, 9, 0);
	Tester(arr, 0x05, "BitArrSet: \t2");

	arr = 0x05;
	arr = BitArrSet(arr, 1, 1);
	Tester(arr, 0x07, "BitArrSet: \t3");
}

static void TestBitArrIsOn(void)
{
	Tester(BitArrIsOn(0x05, 2), 1, "BitArrIsOn: \t1");
	
	Tester(BitArrIsOn(0x05, 1), 0, "BitArrIsOn: \t2");

	Tester(BitArrIsOn(0x05, 63), 0, "BitArrIsOn: \t3");
}

static void TestBitArrIsOff(void)
{
	Tester(BitArrIsOff(0x05, 0), 0, "BitArrIsOff: \t1");
	
	Tester(BitArrIsOff(0x05, 1), 1, "BitArrIsOff: \t2");

	Tester(BitArrIsOff(0x05, 63), 1, "BitArrIsOff: \t3");
}

static void TestBitArrFlip(void)
{
	Tester(BitArrFlip(0x05, 0), 0x04, "BitArrFlip: \t1");
	
	Tester(BitArrFlip(0x05, 1), 0x07, "BitArrFlip: \t2");

	Tester(BitArrFlip(0x05, 63), 0x8000000000000005, "BitArrFlip: \t3");
}

static void TestBitArrRotateRight(void)
{
	Tester(BitArrRotateRight(0x05, 1), 0x8000000000000002, "RotateRight: \t1");
	
	Tester(BitArrRotateRight(0x05, 0), 0x05, "RotateRight: \t2");

	Tester(BitArrRotateRight(0x05, 4), 0x5000000000000000, "RotateRight: \t3");
}

static void TestBitArrRotateLeft(void)
{
	Tester(BitArrRotateLeft(0x05, 1), 0x000000000000000a, "BitRotateLeft: \t1");
	
	Tester(BitArrRotateLeft(0x05, 0), 0x05, "BitRotateLeft: \t2");

	Tester(BitArrRotateLeft(0x05, 4), 0x0000000000000050, "BitRotateLeft: \t3");
}

static void TestBitArrMirror(void)
{
	Tester(BitArrMirror(0x05), 0xa000000000000000, "BitArrMirror: \t1");
	
	Tester(BitArrMirror(0xa0a0a0a0a0a0a0a0), 0x0505050505050505, "BitArrMirror: \t2");

	Tester(BitArrMirror(0x01), 0x8000000000000000, "BitArrMirror: \t3");
}

static void TestBitArrCountOn(void)
{
	Tester(BitArrCountOn(0x05), 2, "BitArrCountOn: \t1");
	
	Tester(BitArrCountOn(0xaaaa000000000000), 8, "BitArrCountOn: \t2");

	Tester(BitArrCountOn(0x00), 0, "BitArrCountOn: \t3");
}

static void TestBitArrCountOff(void)
{
	Tester(BitArrCountOff(0x05), 62, "BitCountOff: \t1");
	
	Tester(BitArrCountOff(0xaaaa000000000000), 56, "BitCountOff: \t2");

	Tester(BitArrCountOff(0x00), 64, "BitCountOff: \t3");
}

static void Tester(unsigned long return_value, unsigned long wanted_value, char *str)
{	
	if (return_value == wanted_value)
	{
		printf("%s: ", str);
		puts("Success!!");
	}
	else
	{
		printf("%s: ", str);
		printf("fail... wanted value was 0x%lx and return value is 0x%lx\n",
				wanted_value, return_value);
	}
}

