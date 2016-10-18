#ifdef NDEBUG
	#define DBG(x)
#else
	#define DBG(x) x
#endif

#include <iostream>
#include <deque>
#include <cassert>

typedef std::deque<std::string>> strdeq;

static std::map<unsigned long, strdeq> deque_map;
static unsigned long counter = 0;

//DBG(std::cerr << "cos" << std::endl;)

unsigned long strdeque_new()
{
	int res = counter;
	strdeq deq;
	deque_map.insert(make_pair(counter++, deq));
	return res;
}

void strdeque_delete(unsigned long id)
{
	
}

size_t strdeque_size(unsigned long id)
{
	
}

void strdeque_insert_at(unsigned long id, size_t pos, const char* value)
{
	
}

void strdeque_remove_at(unsigned long id, size_t pos)
{
	
}

const char* strdeque_get_at(unsigned long id, size_t pos)
{
	
}

void strdeque_clear(unsigned long id)
{
	
}

int strdeque_comp(unsigned long id1, unsigned long id2)
{
	
}
