#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_ 1

#include <stdarg.h>
#include <stdint.h>

/*
 * @class LinkedList : IN PROGRESS
 */

template <class T>
struct Node
{
	T info;
	Node *next;
};

enum SortingMethod
{
	I_GTL, //Integer Greatest To Least
	I_LTG, //Integer Least to Greatest
	S_GTL, //String Greatest to least
	S_LTG  //String Least to greatest
};

template <class T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	void insert_begin();
	void insert_end();
	void insert_index(uint32_t index);
	void insert_after_val(T val);
	void insert_before_val(T val);
	void remove_begin();
	void remove_end();
	void remove_index(uint32_t index);
	void remove_after_val(T val);
	void remove_before_val(T val);
	void sort(SortingMethod sm);
	void reverse();
	uint32_t get_index(T val);
	T get_val(uint32_t index);
private:
	uint32_t current_index=0;
	Node** nodes;

};

#endif
