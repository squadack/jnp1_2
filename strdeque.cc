#ifdef NDEBUG
	const bool debug = false;
#else
	const bool debug = true;
#endif

#include <iostream>
#include <map>
#include <deque>
#include <cassert>
#include "strdeque.h"
#include "strdequeconst.h"

#define ID(x) (x == CONST_DEQUE ? "the Empty Deque" : std::to_string(x).c_str())

namespace {

	typedef std::deque<std::string> strdeq;

	//Zastosowanie funkcji jest konieczne aby uniknąć "initialization order fiasco".
	std::map<unsigned long, strdeq>& deque_map()
	{
		static std::map<unsigned long, strdeq> deque_map;
		return deque_map;
	}
}

unsigned long strdeque_new()
{
	static unsigned long counter = 1;
	if (debug)
		std::cerr << "strdeque_new()" << std::endl;
	int res = counter;
	assert(counter != 0);
	strdeq deq;
	deque_map().emplace(counter++, deq);
	if (debug)
		std::cerr << "strdeque_new: deque " << res << " created" << std::endl;
	return res;
}

void strdeque_delete(unsigned long id)
{
	if (debug)
		std::cerr << "strdeque_delete(" << ID(id) << ")" << std::endl;
	if (deque_map().count(id) > 0)
	{
		deque_map().erase(id);
		if (debug)
			std::cerr << "strdeque_delete: deque " << id << " deleted" << std::endl;
	}
	else if (debug)
	{
		if (id == CONST_DEQUE)
		{
			std::cerr << "strdeque_delete: attempt to remove the Empty Deque" << std::endl;
		}
		else
		{
			std::cerr << "strdeque_delete: deque " << id << " not found" << std::endl;
		}
	}
}

size_t strdeque_size(unsigned long id)
{
	if (debug)
		std::cerr << "strdeque_size(" << ID(id) << ")" << std::endl;
	int res = 0;
	if (deque_map().count(id) > 0)
	{	res = deque_map()[id].size();
		if (debug)
			std::cerr << "strdeque_size: deque " << id << " has " << res << " elements" << std::endl;
	}
	else if (debug)
	{
		if (id == CONST_DEQUE)
		{
			std::cerr << "strdeque_size: deque the Empty Deque has 0 elements" << std::endl;
		}
		else
		{
			std::cerr << "strdeque_size: deque " << id << " does not exist" << std::endl;
		}
	}
	return res;
}

void strdeque_insert_at(unsigned long id, size_t pos, const char* value)
{
	if (debug)
	{
		std::cerr << "strdeque_insert_at(" << ID(id) << ", " << pos << ", ";
		if (value == NULL)
			 std::cerr << "NULL";
		else
			std::cerr << "\"" << value << "\"";
		std::cerr << ")" << std::endl;
	}
	
	if (deque_map().count(id) > 0 && value != NULL)
	{
		std::string str(value);
		if (deque_map()[id].size() <= pos)
		{
			pos = deque_map()[id].size();
		}
		deque_map()[id].insert(deque_map()[id].begin() + pos, str);
		
		if (debug)
			std::cerr << "strdeque_insert_at: deque " << id << ", element \"" << str << "\" inserted at " << pos << std::endl;
	}
	else if (debug)
	{
		if (id == CONST_DEQUE)
		{
			std::cerr << "strdeque_insert_at: attempt to insert into the Empty Deque" << std::endl;
		}
		else if (value == NULL)
		{
			std::cerr << "strdeque_insert_at: attempt to insert NULL into a deque" << std::endl;
		}
		else //id nie istnieje
		{
			std::cerr << "strdeque_insert_at: deque: " << id << " does not exist" << std::endl;
		}
	}
}

void strdeque_remove_at(unsigned long id, size_t pos)
{
	if (debug)
		std::cerr << "strdeque_remove_at(" << ID(id) << ", " << pos << ")" << std::endl;
	if (deque_map().count(id) > 0)
	{
		if (deque_map()[id].size() > pos)
		{
			deque_map()[id].erase(deque_map()[id].begin() + pos);
			if (debug)
				std::cerr << "strdeque_remove_at: remove at deque " << id << " element in position " << pos << std::endl;
		}
		else if (debug)
		{
			std::cerr << "strdeque_get_at: deque " << id << " does not contain an element at " << pos << std::endl;
		}
	}
	else if (debug)
	{
		if (id == CONST_DEQUE)
		{
			std::cerr << "strdeque_remove_at: attempt to remove from the Empty Deque" << std::endl;
		}
		else //id nie istnieje
		{
			std::cerr << "strdeque_remove_at: deque: " << id << " does not exist" << std::endl;
		}
	}
}

const char* strdeque_get_at(unsigned long id, size_t pos)
{
	if (debug)
		std::cerr << "strdeque_get_at(" << ID(id) << ", " << pos << ")" << std::endl;
	if (deque_map().count(id) > 0)
	{
		if (deque_map()[id].size() > pos)
		{
			if (debug)
				std::cerr << "strdeque_get_at: return element from deque " << id << " from position " << pos << std::endl;
			return deque_map()[id].at(pos).c_str();
		}
		else if (debug)
		{
			std::cerr << "strdeque_get_at: deque " << id << " does not contain an element at " << pos << std::endl;
		}
	}
	else if (debug)
	{
		if (id == CONST_DEQUE)
		{
			std::cerr << "strdeque_get_at: the Empty Deque does not contain an element at " << pos << std::endl;
		}
		else // id nie istnieje
		{
			std::cerr << "strdeque_get_at: deque: " << id << " does not exist" << std::endl;
		}
	}
	return NULL;
}

void strdeque_clear(unsigned long id)
{
	if (debug)
		std::cerr << "strdeque_clear(" << ID(id) << ")" << std::endl;
	if (deque_map().count(id) > 0)
	{
		deque_map()[id].clear();
		if (debug)
			std::cerr << "strdeque_clear: remove all elements from deque " << id << std::endl;
	}
	else if (debug)
	{
		if (id == CONST_DEQUE)
		{
			std::cerr << "strdeque_clear: attempt to clear the Empty Deque" << std::endl;
		}
		else //id nie istnieje
		{
			std::cerr << "strdeque_clear: deque: " << id << " does not exist" << std::endl;
		}
	}
}

int strdeque_comp(unsigned long id1, unsigned long id2)
{
	if (debug)
		std::cerr << "strdeque_comp(" << ID(id1) << ", " << ID(id2) << ")" << std::endl;
	strdeq tmp1;
	strdeq tmp2;

	if (deque_map().count(id1) > 0) {
		tmp1 = deque_map()[id1];
	}
	if (deque_map().count(id2) > 0) {
		tmp2 = deque_map()[id2];
	}
	if (tmp1 < tmp2)
	{
		if (debug)
			std::cerr << "strdeque_comp: deque: " << ID(id1) << " < deque: " << ID(id2) << std::endl;
		return -1;
	}
	else if (tmp1 == tmp2)
	{
		if (debug)
			std::cerr << "strdeque_comp: deque: " << ID(id1) << " = deque: " << ID(id2) << std::endl;
		return 0;
	}
	else //tmp1 > tmp2
	{
		if (debug)
			std::cerr << "strdeque_comp: deque: " << ID(id1) << " > deque: " << ID(id2) << std::endl;
		return 1;
	}
}
