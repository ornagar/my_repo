#include <stdio.h>

#ifdef _DEBUG
#define DBG(x) x
#else 
#define DBG(x)
#endif

#define MAX(a, b) ((a>b) ? (a) : (b))
