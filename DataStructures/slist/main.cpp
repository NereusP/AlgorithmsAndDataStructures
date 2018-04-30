#include "slist.hpp"
#include <iostream>

int main()
{
	slist<int> list0,list1;

	int* pBuffer = new int[100];

	//Insert from the tail
	for (int i = 1; i < 8; i++)
	{
		list0.back_insert(i);
	}
	//Insert from the head
	for (int i = 8; i > 0; i--)
	{
		list1.front_insert(i);
	}
	std::cout << "The length of list0:" << list0.get_length() << std::endl;
	memset(pBuffer, 0, 100 * sizeof(int));
	list0.traverse(pBuffer);
	std::cout << "The length of list1:" << list1.get_length() << std::endl;
	memset(pBuffer, 0, 100 * sizeof(int));
	list1.traverse(pBuffer);

	//Search
	unsigned int pos = list0.search(3);
	std::cout << "Node 3's position in the linked list0:" << pos << std::endl;
	//Delete node
	list0.erase(pos);
	std::cout << "After delete \"3\" from list0:\n";
	memset(pBuffer, 0, 100 * sizeof(int));
	list0.traverse(pBuffer);

	//Search
	pos = list1.search(7);
	std::cout << "Node 7's position in the linked list1:" << pos << std::endl;
	//Delete node
	list1.erase(pos);
	std::cout << "After delete \"7\" from list1:\n";
	memset(pBuffer, 0, 100 * sizeof(int));
	list1.traverse(pBuffer);

	//Reverse the entire list
	list0.invert();
	list1.invert();
	//After invert
	std::cout << "After invert list0:\n";
	memset(pBuffer, 0, 100 * sizeof(int));
	list0.traverse(pBuffer);
	std::cout << "After invert list1:\n";
	memset(pBuffer, 0, 100 * sizeof(int));
	list1.traverse(pBuffer);

	slist<int> list3;
	list3.back_insert(5);
	list3.back_insert(6);
	list3.back_insert(5);
	int pos0 = list3.search(5);
	pos0 = list3.search(pos0, 5);

	delete[] pBuffer;
	return 0;
}
