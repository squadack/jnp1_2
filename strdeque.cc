#ifdef NDEBUG
	#define DBG(x)
#else
	#define DBG(x) std::cerr << x << std::endl;
#endif

//przyklad
//DBG("cos")

#include <iostream>
#include <map>
#include <deque>
#include <cassert>
#include "strdeque.h"
#include "strdequeconst.h"

#define ID(x) (x == CONST_DEQUE ? "the Empty Deque" : std::to_string(x).c_str())

namespace {
	typedef std::deque<std::string> strdeq;

	std::map<unsigned long, strdeq>& deque_map()
	{
		static std::map<unsigned long, strdeq> deque_map;
		return deque_map;
	}
}

unsigned long strdeque_new()
{
	static unsigned long counter = 1;
	DBG("strdeque_new");
	int res = counter;
	assert(counter != 0);
	strdeq deq;
	deque_map().emplace(counter++, deq);
	DBG("strdeque_new: deque " << res << " created");
	return res;
}

void strdeque_delete(unsigned long id)
{
	DBG("strdeque_delete(" << ID(id) << ")");
	if (deque_map().count(id) > 0) {
		deque_map().erase(id);
		DBG("strdeque_delete: deque of the key " << id << " deleted");
	} else {
		if (id == CONST_DEQUE)
		{
			DBG("strdeque_delete: attempt to remove the Empty Deque");
		}
		else	
		{
			DBG("strdeque_delete: deque of the key " << id << " not found");
		}
	}
}

size_t strdeque_size(unsigned long id)
{
	DBG("strdeque_size(" << ID(id) << ")");
	int res = 0;
	if (deque_map().count(id) > 0) {
		res = deque_map()[id].size();
		DBG("strdeque_size: deque of the key " << id << "has " << res << " elements");
	} else {
		if (id == CONST_DEQUE)
		{
			DBG("strdeque_size: deque of the key the Empty Deque has 0 elements");
		}
		else
		{
			DBG("strdeque_size: deque of the key " << id << " does not exist");
		}
	}
	return res;
}

void strdeque_insert_at(unsigned long id, size_t pos, const char* value)
{
	DBG("strdeque_insert_at(" << ID(id) << ", " << pos << ", \"" << (value == NULL ? "NULL" : value) << "\")"); //BUG cudzysłow przy NULL
	assert(pos >= 0); //TODO zmienic na ignorowanie
	
	if (deque_map().count(id) > 0 && value != NULL) {
		std::string str(value);
		if (deque_map()[id].size() <= pos) {
			deque_map()[id].push_back(str);

		} else {
			deque_map()[id].insert(deque_map()[id].begin() + pos, str);
		}
		DBG("strdeque_insert_at: element " << str << " inserted");
	} else {
		if (id == CONST_DEQUE)
		{
			DBG("strdeque_insert_at: attempt to insert into the Empty Deque");
		}
		else if (value == NULL)
		{
			DBG("strdeque_insert_at: attempt to insert NULL into a deque");
		}
		else
		{
			DBG("strdeque_insert_at: deque of the key: " << id << " does not exist");
		}
	}
}

void strdeque_remove_at(unsigned long id, size_t pos)
{
	DBG("strdeque_remove_at(" << ID(id) << ", " << pos << ")");
	assert(pos >= 0);//TODO zmienic na ignorowanie
	if (deque_map().count(id) > 0) {
		if (deque_map()[id].size() > pos) {
			deque_map()[id].erase(deque_map()[id].begin() + pos);
			DBG("strdeque_remove_at: remove at deque of the key " << id << " element in position " << pos);
		}
	}
	else 
	{
		if (id == CONST_DEQUE)
		{
			DBG("strdeque_remove_at: attempt to remove from the Empty Deque");
		}
		else //id nie istnieje
		{
			DBG("strdeque_remove_at: deque of the key: " << id << " does not exist");
		}
	}
}

const char* strdeque_get_at(unsigned long id, size_t pos)
{
	DBG("strdeque_get_at(" << ID(id) << ", " << pos << ")");
	assert(pos >= 0);//TODO zmienic na ignorowanie
	if (deque_map().count(id) > 0) {
		if (deque_map()[id].size() > pos) {
			DBG("strdeque_get_at: return element from deque of the key " << id << " from position " << pos);
			return deque_map()[id].at(pos).c_str();
		}
	}
	else
	{
		if (id == CONST_DEQUE)
		{
			DBG("strdeque_get_at: the Empty Deque does not contain an element at " << pos);
		}
		else // id nie istnieje
		{
			DBG("strdeque_get_at: deque of the key: " << id << " does not exist");
		}
	}
	return NULL;
}

void strdeque_clear(unsigned long id)
{
	DBG("strdeque_clear(" << ID(id) << ")");
	if (deque_map().count(id) > 0) {
		deque_map()[id].clear();
		DBG("strdeque_clear: remove all elements from deque of the key " << id);
	}
	else
	{
		if (id == CONST_DEQUE)
		{
			DBG("strdeque_clear: attempt to clear the Empty Deque");
		}
		else
		{
			DBG("strdeque_clear: deque of the key: " << id << " does not exist");
		}
	}
}

int strdeque_comp(unsigned long id1, unsigned long id2)
{
	DBG("strdeque_comp(" << ID(id1) << ", " << ID(id2) << ")");
	strdeq tmp1;
	strdeq tmp2;
	//Jeżeli kolejka dwustronna o którymś z identyfikatorów nie istnieje, to jest
	//traktowana jako leksykograficznie równa liście pustej. - czy wystarczy porownywac
	//do pustej kolejki? Kolejka jest lista :/
	if (deque_map().count(id1) > 0) {
		tmp1 = deque_map()[id1];
	}
	if (deque_map().count(id2) > 0) {
		tmp2 = deque_map()[id2];
	}
	if (tmp1 < tmp2) {
		DBG("strdeque_comp: deque of the key: " << ID(id1) << " < deque of the key: " << ID(id2));
		return -1;
	}
	else if (tmp1 == tmp2) {
		DBG("strdeque_comp: deque of the key: " << ID(id1) << " = deque of the key: " << ID(id2));
		return 0;
	}
	else { //tmp1 > tmp2
		DBG("strdeque_comp: deque of the key: " << ID(id1) << " > deque of the key: " << ID(id2));
		return 1;
	}
}
