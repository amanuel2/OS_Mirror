#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_ 1

#include <stdarg.h>
#include <stdint.h>

/*
 * @class LinkedList : IN PROGRESS
 */

template <class T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	  T next;
private:
	uint32_t current_index=0;

};

#endif
