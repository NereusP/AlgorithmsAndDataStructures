//Test program under windows system

#include<stdio.h>
#include<process.h>
#include"circularqueue.hpp"

HANDLE hExitedEvent[2];
typedef unsigned char ElementType;

void __stdcall PushThreadFunc(void *param);
void __stdcall PopThreadFunc(void *param);

int main(void)
{
	CircularQueue<ElementType> m_cirqueue(sizeof(ElementType), 10);
	hExitedEvent[0] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
	hExitedEvent[1] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
	(void *)&m_cirqueue;
	_beginthreadex(nullptr, 0, (unsigned int(__stdcall *)(void *))&PushThreadFunc, (void *)&m_cirqueue, 0, nullptr);
	WaitForSingleObject(hExitedEvent[0], INFINITE);
	_beginthreadex(nullptr, 0, (unsigned int(__stdcall *)(void *))&PopThreadFunc, (void *)&m_cirqueue, 0, nullptr);
	WaitForSingleObject(hExitedEvent[1], INFINITE);
	return 0;
}

void __stdcall PushThreadFunc(void * param)
{
	printf("PushThread has started...\n");
	CircularQueue<ElementType> *pCirQueue = (CircularQueue<ElementType> *)param;
	ElementType node = 0;
	for (int i = 0; i < 20; i++)
	{
		node = i;
		pCirQueue->push(&node);
		if (pCirQueue->GetHeadNode(&node))
		{
			printf("HeadNode=%d ", node);
		}
		if (pCirQueue->GetTailNode(&node))
		{
			printf("TailNode=%d\n", node);
		}
	}
	SetEvent(hExitedEvent[0]);
	printf("PushThread has exited...\n\n");
}

void __stdcall PopThreadFunc(void * param)
{
	printf("PopThread has started...\n");
	CircularQueue<ElementType> *pCirQueue = (CircularQueue<ElementType> *)param;
	ElementType node = 0;
	for (int i = 0; i < 20; i++)
	{
		if (pCirQueue->GetHeadNode(&node))
		{
			printf("HeadNode=%d ", node);
		}
		if (pCirQueue->GetTailNode(&node))
		{
			printf("TailNode=%d\n", node);
		}
		pCirQueue->pop();
	}
	SetEvent(hExitedEvent[1]);
	printf("PopThread has exited...\n");
}
