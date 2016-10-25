#ifndef __STRDEQUECONST_H__
#define __STRDEQUECONST_H__

#ifdef __cplusplus
extern "C" {
#endif

const unsigned long CONST_DEQUE = 0;


// Zwraca identyfikator pustej kolejki dwustronnej, do której nic nie można
// wstawiać i z której nic nie można usuwać.
unsigned long emptystrdeque();

#ifdef __cplusplus
}
#endif

#endif