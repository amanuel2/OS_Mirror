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
	S_LTG,  //String Least to greatest
	REVERSE
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
	void insert_after_val(T val_after, T val);
	void insert_before_val(T val_before, T val);
	void remove_begin();
	void remove_end();
	void remove_index(uint32_t index);
	void remove_after_val(T after_val);
	void remove_before_val(T before_val);
	void sort(SortingMethod sm);
	uint32_t get_index(T val);
	T get_val(uint32_t index);
	uint32_t get_amount();
private:
	uint32_t current_index=0;
	uint32_t num_list=0;
	T contents[];
	void reverse();
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
void Vertex<T>::insert_after_val(T val_after, T val)
{
	this->insert_index(this->get_index(val_after)+1,val);
}
template <class T>
void Vertex<T>::insert_before_val(T val_before, T val)
{
  if((this->get_index(val_before)-1)>0)	
 	this->insert_index(this->get_index(val_before),val);
  else
  {
  	printf("insert_before_val() less than 0");			
	while(true);
  }
}
template <class T>
void Vertex<T>::remove_begin()
{
	for(uint32_t i=1; i<num_list; i++)
		contents[i-1] = contents[i];

	contents[num_list-1]=0;
	num_list--;
	current_index--;
}
template <class T>
void Vertex<T>::remove_end()
{
	contents[num_list-1]=0;
	num_list--;
	current_index--;
}
template <class T>
void Vertex<T>::remove_index(uint32_t index)
{
	for(uint32_t i=(index+1); i<num_list; i++)
		contents[i-1] = contents[i];
	
	contents[num_list-1]=0;
	num_list--;
	current_index--;
}
template <class T>
void Vertex<T>::remove_after_val(T after_val)
{
	uint32_t counter=0;
	for(uint32_t i=get_index(after_val)+1; i<num_list ; i++)
	{
		contents[i]=0;
		counter++;
	}
	num_list-=counter;
	current_index-=counter;
}
/*Annoying Function in Progress*/
template <class T>
void Vertex<T>::remove_before_val(T before_val)
{
	uint32_t counter=0;
	for(uint32_t i=0; i<=2 ; i++)
	{
		contents[i]=contents[2+i+1];
		counter++;
	}
	 //num_list-=counter;
	 //current_index-=counter;
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
	for(uint32_t i=0; i<num_list; i++)
		if(contents[i] == val)
			return i;
	printf("getIndex() Not Found");			
	while(true);
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
