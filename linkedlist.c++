#include "linkedlist.h"



template <class T>
LinkedList<T>::LinkedList()
{
	nodes = NULL;
}


template <class T>
LinkedList<T>::~LinkedList()
{

}

template <class T>
void LinkedList<T>::insert_begin(T val)
{
	if(num_list == 0)
	{
		nodes[0]->info = val;
		nodes[0]->next = NULL;
		nodes[0]->prev = NULL;
		current_index++;
		num_list++;
	}
	else
	{
		/*Inserting Beggining With Other Content*/
		 Node<T> *node_tmp;
		 node_tmp->info = val;
		 node_tmp->next = nodes[0];
		 node_tmp->prev = NULL;
		 nodes[0]->prev = node_tmp;
		 current_index++;
		 num_list++;
	}
}
template <class T>
void LinkedList<T>::insert_end(T val)
{
	nodes[current_index]->info = val;
	nodes[current_index]->next = NULL;
	nodes[current_index]->prev = nodes[current_index-1];
	current_index++;
	num_list++;
}
template <class T>
void LinkedList<T>::insert_index(uint32_t index)
{

}
template <class T>
void LinkedList<T>::insert_after_val(T val)
{

}
template <class T>
void LinkedList<T>::insert_before_val(T val)
{

}
template <class T>
void LinkedList<T>::remove_begin()
{

}
template <class T>
void LinkedList<T>::remove_end()
{

}
template <class T>
void LinkedList<T>::remove_index(uint32_t index)
{

}
template <class T>
void LinkedList<T>::remove_after_val(T val)
{

}
template <class T>
void LinkedList<T>::remove_before_val(T val)
{

}

template <class T>
void LinkedList<T>::sort(SortingMethod sm)
{

}
template <class T>
void LinkedList<T>::reverse()
{

}
template <class T>
uint32_t LinkedList<T>::get_index(T val)
{
	return 0;
}
template <class T>
T LinkedList<T>::get_val(uint32_t index)
{
	return 0;
}
