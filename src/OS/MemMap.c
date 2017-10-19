#include <stdio.h>
#include <dlfcn.h>
#include "a.h"
#include "a1.h"
#include "a2.h"
#include "so1.h"
#include "so2.h"

void MyFunc(void);

int main(void)
{
	void (*fptr)(void) = NULL;
	void *handle = NULL;
	MyFunc();
	Foo();
	Bar1();
	
	handle = dlopen ("libso2.so", RTLD_LAZY);
	fptr = dlsym(handle, "Bar2");
	if (fptr) fptr();
	dlclose(handle);

	return(0);
}

void MyFunc(void)
{
	printf("Enter MyFunc\n");

	return;
}