#include <iostream>
#include "strdequeconst.h"

#ifdef NDEBUG
	#define DBG(x)
#else
	#define DBG(x) std::cerr << x << std::endl;
#endif


unsigned long emptystrdeque()
{
	DBG("emptystrdeque()");
	return CONST_DEQUE;
}

