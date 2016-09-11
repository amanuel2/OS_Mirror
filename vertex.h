#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_ 1

#include <stdarg.h>
#include <stdint.h>
#include "stdio.h"
#include "heap.h"

#ifndef NULL
	#define NULL 0
#endif

extern Heap heap;

/*
 * @class LinkedList : IN PROGRESS
 */

template <class T>
struct Node
{
	T info;
	Node *next;
	Node *prev;
};

enum SortingMethod
{
	I_GTL, //Integer Greatest To Least
	I_LTG, //Integer Least to Greatest
	S_GTL, //String Greatest to least
	S_LTG  //String Least to greatest
};

template <typename T>
class Vertex
{
public:
	Vertex();
	~Vertex();
	void insert_begin(T val);
	void insert_end(T val);
	void insert_index(uint32_t index, T val);
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
	uint32_t get_amount();
private:
	uint32_t current_index=0;
	uint32_t num_list=0;
	T contents[];
};

template <typename T>
Vertex<T>::Vertex()
{
}


template <typename T>
Vertex<T>::~Vertex()
{

}

template <class T>
void Vertex<T>::insert_begin(T val)
{
	if(num_list == 0)
	{
		 contents[0] =  val;
		 num_list++;
	}
	else
	{
		T temp;
		temp = contents[0];
		contents[0] = val;
		num_list++;
		for(uint32_t i=1; i<num_list; i++)
		{
			if(i == (num_list-1))
				contents[i] = temp;
			else
			{
				T another_temp;
				another_temp = contents[i];
				contents[i] = temp;
				temp = another_temp;
			}	
		}
		
		current_index++;	
	}
}

template <class T>
void Vertex<T>::insert_end(T val)
{
	contents[++current_index] = val;
	num_list++;
}

template <class T>
void Vertex<T>::insert_index(uint32_t index, T val)
{
	if(index>=num_list)
	{
		contents[++current_index] = val;
		num_list++;
	}
	else
	{
		T temp;
		temp = contents[index];
		contents[index] = val;
		num_list++;
		for(uint32_t i=index+1; i<num_list; i++)
		{
			if(i == (num_list-1))
				contents[i] = temp;
			else
			{
				T another_temp;
				another_temp = contents[i];
				contents[i] = temp;
				temp = another_temp;
			}
		}

	}
}

template <class T>
void Vertex<T>::insert_after_val(T val)
{

}
template <class T>
void Vertex<T>::insert_before_val(T val)
{

}
template <class T>
void Vertex<T>::remove_begin()
{

}
template <class T>
void Vertex<T>::remove_end()
{

}
template <class T>
void Vertex<T>::remove_index(uint32_t index)
{

}
template <class T>
void Vertex<T>::remove_after_val(T val)
{

}
template <class T>
void Vertex<T>::remove_before_val(T val)
{

}

template <class T>
void Vertex<T>::sort(SortingMethod sm)
{

}
template <class T>
void Vertex<T>::reverse()
{

}
template <class T>
uint32_t Vertex<T>::get_index(T val)
{
	return 0;
}
template <class T>
T Vertex<T>::get_val(uint32_t index)
{
	return contents[index];
}

template <class T>
uint32_t Vertex<T>::get_amount()
{
	return this->num_list;
}


#endif
