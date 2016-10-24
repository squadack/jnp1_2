#include <iostream>
#include "strdequeconst.h"

#ifdef NDEBUG
	const bool debug = false;
#else
	const bool debug = true;
#endif

unsigned long emptystrdeque()
{
	if (debug)
		std::cerr << "emptystrdeque()" << std::endl;
	return CONST_DEQUE;
}

