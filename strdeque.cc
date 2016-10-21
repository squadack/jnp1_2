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

typedef std::deque<std::string> strdeq;


static std::map<unsigned long, strdeq> deque_map;
static unsigned long counter = 0;


unsigned long strdeque_new()
{
	DBG("strdeque_new");
	int res = counter;
	strdeq deq;
	deque_map.emplace(counter++, deq);
	DBG("strdeque_new: deque " << res << " created");
	
	return res;
}

void strdeque_delete(unsigned long id)
{
	DBG("strdeque_delete(" << id << ")");
	if (deque_map.count(id) > 0) {
		deque_map.erase(id);
		DBG("strdeque_delete: deque of the key " << id << "deleted");
	} else {
		DBG("strdeque_delete: deque of the key " << id << "not found");
	}
}

size_t strdeque_size(unsigned long id)
{
	DBG("strdeque_size(" << id << ")");
	strdeq tmp;
	int res = 0;
	if (deque_map.count(id) > 0) {
		tmp = deque_map[id];
		res = tmp.size();
		DBG("strdeque_size: deque of the key " << id << "have " << res << "elements");
	} else {
		DBG("strdeque_size: deque of the key " << id << "have no elements");
	}
	return res;
}

void strdeque_insert_at(unsigned long id, size_t pos, const char* value)
{
	DBG("strdeque_insert_at(" << id << ", " << pos << ", \"" << value << "\")");
	assert(pos >= 0);
	
	if (deque_map.count(id) > 0 && value != NULL) {
		std::string str(value);
		strdeq tmp = deque_map[id];
		if (tmp.size() <= pos) {
			tmp.push_back(str);

		} else {
			tmp.insert(tmp.begin()+pos, str);
		}
		deque_map[id] = tmp;
		DBG("strdeque_insert_at: element " << str << "inserted");
	} else {
		DBG("strdeque_insert_at: deque of the key: " << id << "does not exist");
	}
}

void strdeque_remove_at(unsigned long id, size_t pos)
{
	DBG("strdeque_remove_at(" << id << ", " << pos << ")");
	assert(pos >= 0);
	if(deque_map.count(id) > 0) {
		strdeq tmp = deque_map[id];
		if(tmp.size() > pos) {
			tmp.erase(tmp.begin() + pos);
			deque_map[id] = tmp;
			DBG("strdeque_remove_at: remove at deque of the key " << id << "element in position " << pos);
		}
	}
}

const char* strdeque_get_at(unsigned long id, size_t pos)
{
	DBG("strdeque_get_at(" << id << ", " << pos << ")");
	assert(pos >= 0);
	if (deque_map.count(id) > 0) {
		if (deque_map[id].size() > pos) {
			DBG("strdeque_get_at: return element from deque of the key " << id << "from position " << pos);
			//juz zwraca const char * ;)
			return deque_map[id].at(pos).c_str();
		}
	}
	return NULL;
}

void strdeque_clear(unsigned long id)
{
	DBG("strdeque_clear(" << id << ")");
	if (deque_map.count(id) > 0){
		deque_map[id].clear();
		DBG("strdeque_clear: remove all elements from deque of the key " << id);
	}
}

int strdeque_comp(unsigned long id1, unsigned long id2)
{
	DBG("strdeque_comp(" << id1 << ", " << id2 << ")");
	strdeq tmp1;
	strdeq tmp2;
	//Jeżeli kolejka dwustronna o którymś z identyfikatorów nie istnieje, to jest
	//traktowana jako leksykograficznie równa liście pustej. - czy wystarczy porownywac
	//do pustej kolejki? Kolejka jest lista :/
	if (deque_map.count(id1) > 0) {
		tmp1 = deque_map[id1];
	}
	if (deque_map.count(id2) > 0) {
		tmp2 = deque_map[id2];
	}
	if (tmp1 < tmp2) {
		DBG("strdeque_comp: deque of the key: " << id1 << " < deque of the key: " << id2);
		return -1;
	}
	else if (tmp1 == tmp2) {
		DBG("strdeque_comp: deque of the key: " << id1 << " = deque of the key: " << id2);
		return 0;
	}
	else { //tmp1 > tmp2
		DBG("strdeque_comp: deque of the key: " << id1 << " > deque of the key: " << id2);
		return 1;
	}
}
