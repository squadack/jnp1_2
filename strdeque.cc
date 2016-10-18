#ifdef NDEBUG
	#define DBG(x)
#else
	#define DBG(x) std::cerr << x << std::endl;
#endif

//przyklad
//DBG("cos")

#include <iostream>
#include <deque>
#include <cassert>

typedef std::deque<std::string>> strdeq;


static std::map<unsigned long, strdeq> deque_map;
static unsigned long counter = 0;


unsigned long strdeque_new()
{
	DBG("strdeque_new");
	int res = counter;
	strdeq deq;
	deque_map.insert(make_pair(counter++, deq));
	DBG("strdeque_new: deque " << res << " created");
	return res;
}

void strdeque_delete(unsigned long id)
{
	DBG("strdeque_delete");
	if(deque_map.count(id) > 0){
	  deque_map.erase(id);
	  DBG("strdeque_delete: deque of the key " << id << "deleted");
	} else {
	DBG("strdeque_delete: deque of the key " << id << "not found");
	}
}

size_t strdeque_size(unsigned long id)
{
	DBG("strdeque_size");
	int res = deque_map.count(id);
	if(res > 0){
	  DBG("strdeque_size: deque of the key " << id << "have " << res << "elements");
	  return res;
	} else {
	  DBG("strdeque_size: deque of the key " << id << "have no elements");
	}
}

void strdeque_insert_at(unsigned long id, size_t pos, const char* value)
{
	
	DBG("strdeque_insert_at");
	if(deque_map.count(id) > 0 && value != NULL){
	    std::string str(value);
	    
	}
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
