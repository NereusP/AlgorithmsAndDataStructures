#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include"circularqueue.hpp"

bool ExitFlg = false;
typedef unsigned char ElementType;

int exit_flag=0;
void *PushThreadFunc(void *param);
void *PopThreadFunc(void *param);

int main(void)
{
	CircularQueue<ElementType> m_cirqueue(sizeof(ElementType), 10);
	pthread_t tidp;
	pthread_create(&tidp,NULL,PushThreadFunc,(void*)&m_cirqueue);
	while(exit_flag==0)
	{
		sleep(1);
	}
	pthread_create(&tidp,NULL,PopThreadFunc, (void*)&m_cirqueue);
	while(exit_flag==1)
	{
		sleep(1);
	}
	return 0;
}

void *PushThreadFunc(void * param)
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
	exit_flag=1;
	printf("PushThread has exited...\n\n");
	return nullptr;
}

void *PopThreadFunc(void * param)
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
	exit_flag=2;
	printf("PopThread has exited...\n");
	return nullptr;
}

