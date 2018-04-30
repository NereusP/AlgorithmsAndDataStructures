/*
Description:Singly linked list
*/

#ifndef _SLIST_HPP_
#define _SLIST_HPP_

#include <iostream>

#define INVALID_VALUE -1

struct node
{
	int data;
	node* next;
};

//Single link-list with head node
template<class ElementType>
class slist
{
public:
	slist();//Constructor
	unsigned int get_length();//Get the length of the linked list
	/*
	Starting from beginning, find the position where "value" first appears
	If there is no "value", return -1
	else return the pos(count from 0)
	*/
	int search(ElementType value);
	/*
	Starting from start_pos, find the position where "value" first appears
	If there is no "value", return -1
	else return the pos(count from 0)
	*/
	int search(int start_pos, ElementType value);
	bool front_insert(ElementType value);//Insert at the beginning
	bool back_insert(ElementType value);//Insert at the end
	bool erase(int pos);//erase the pos-th node
	void traverse(ElementType* pBuffer);//Traverse the entire linked list
	void invert();//Invert list
	~slist();//Destructor
protected:
	node* head;
};

template<class ElementType> inline slist<ElementType>::slist()
{
	head = new node;
	head->next = nullptr;
	head->data = INVALID_VALUE;
}

template<class ElementType> unsigned int inline slist<ElementType>::get_length()
{
	node* p = head->next;
	int n = 0;
	//If p's next node is null, then p is the last node
	while (p != nullptr)
	{
		p = p->next;
		n++;
	}
	return n;//Return the total number of nodes(Does not include head node)
}

template<class ElementType> int inline slist<ElementType>::search(ElementType value)
{
	int pos = 0;
	node* p = head->next;
	if (p == nullptr)
	{
		std::cout << "search failed:list is empty!" << std::endl;
		return -1;
	}
	else
	{
		while (p != nullptr)
		{
			if (p->data == value)
			{
				return pos;
			}
			else
			{
				p = p->next;
				++pos;
			}
		}
		std::cout << "no such element!" << std::endl;
		return -1;
	}
}

template<class ElementType>
inline int slist<ElementType>::search(int start_pos, ElementType value)
{
	int pos = 0;
	node* p = head->next;
	if (p == nullptr)
	{
		std::cout << "search failed:list is empty!" << std::endl;
		return -1;
	}
	else
	{
		while (p != nullptr)
		{
			if ((p->data == value) && (pos > start_pos))
			{
				return pos;
			}
			else
			{
				p = p->next;
				++pos;
			}
		}
		std::cout << "no such element!" << std::endl;
		return -1;
	}
}

template<class ElementType> bool inline slist<ElementType>::front_insert(ElementType value)
{
	node* p = new node;
	p->data = value;
	p->next = head->next;
	head->next = p;
	return 0;
}

template<class ElementType> bool inline slist<ElementType>::back_insert(ElementType value)
{
	node* p = head;
	while (p->next != nullptr)
	{
		p = p->next;
	}
	node* q = new node;
	q->data = value;
	q->next = nullptr;
	p->next = q;
	return 0;
}

template<class ElementType> bool inline slist<ElementType>::erase(int pos)
{
	node* p = head->next;
	int i = 0;
	if (p == nullptr)
	{
		std::cout << "delete failed:list is empty!" << std::endl;
		return false;
	}
	else
	{
		while (i < (pos - 1) && p != nullptr)
		{
			p = p->next;
			i++;
		}
		node* q = p->next;
		p->next = q->next;
		delete q;
		return true;
	}
}

template<class ElementType> void inline slist<ElementType>::traverse(ElementType* pBuffer)
{
	node* p = head->next;
	int i = 0;
	if (p == nullptr)
	{
		std::cout << "list is empty!" << std::endl;
	}
	else
	{
		//Do not show the first node,the first node is invalid
		while (p != nullptr)
		{
			std::cout << "node[" << i << "]:" << p->data << std::endl;
			*(pBuffer + i) = p->data;
			p = p->next;
			++i;
		}
	}
}

template<class ElementType> void inline slist<ElementType>::invert()
{
	if (head->next != nullptr)
	{
		node *p, *q, *r;
		p = head->next;
		q = p->next;
		p->next = nullptr;
		while (q != nullptr)
		{
			r = q->next;
			q->next = p;
			p = q;
			q = r;
		}
		head->next = p;
	}
}

template<class ElementType> inline slist<ElementType>::~slist()
{
	while (head->next != nullptr)
	{
		node* p = head->next;
		delete head;
		head = p;
	}
}

#endif
