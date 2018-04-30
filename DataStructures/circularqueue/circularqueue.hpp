//Circular List Queue

#ifndef _CIRCULAR_LQUEUE_H
#define _CIRCULAR_LQUEUE_H

#include <string.h>
#include "atomiclock.hpp"

template <class T>
class CircularQueue
{
public:
	CircularQueue(unsigned int nodesize,unsigned int numMaxNode);
	~CircularQueue();
	bool push(T* nodedata);
	bool pop(void);
	bool GetHeadNode(T* pNode);
	bool GetTailNode(T* pNode);
	bool isEmpty(void);
	unsigned int GetSize(void);
	bool GetNode(T* pNode,unsigned int npos);

private:
	unsigned int MaxNodeCnt;
	unsigned int CurNodeCnt;//1--MaxNodeCnt
	T *mem_head;//head addr of memory
	int nCurHeadPos;//0--(MaxNodeCnt-1)
	int nCurTailPos;//0--(MaxNodeCnt-1)
	unsigned int MaxNodeSize;//node size in byte
	AtomicLock m_lock;
};

template<class T>
inline CircularQueue<T>::CircularQueue(unsigned int nodesize, unsigned int numMaxNode)
{
	MaxNodeCnt = numMaxNode;
	MaxNodeSize = nodesize;
	mem_head = new T[MaxNodeCnt];
	memset(mem_head, 0, MaxNodeCnt*MaxNodeSize);
	CurNodeCnt = 0;
	nCurHeadPos = 0;
	nCurTailPos = -1;
}

template<class T>
inline CircularQueue<T>::~CircularQueue()
{
	if (mem_head != nullptr)
	{
		delete[] mem_head;
	}
	mem_head = NULL;
}

template<class T>
inline bool CircularQueue<T>::push(T* nodedata)
{
	m_lock.lock();
	nCurTailPos = (nCurTailPos + 1) % MaxNodeCnt;
	*(mem_head + nCurTailPos)=*nodedata;
	if (CurNodeCnt >= MaxNodeCnt)
	{
		nCurHeadPos = (nCurHeadPos + 1) % MaxNodeCnt;
	}
	else
	{
		CurNodeCnt++;
	}
	m_lock.unlock();
	return true;
}

template<class T>
inline bool CircularQueue<T>::pop(void)
{
	m_lock.lock();
	if (CurNodeCnt == 0)
	{
		m_lock.unlock();
		return false;
	}
	else
	{
		nCurHeadPos = (nCurHeadPos + 1) % MaxNodeCnt;
		CurNodeCnt--;
		m_lock.unlock();
		return true;
	}
}

template<class T>
inline bool CircularQueue<T>::GetHeadNode(T* pNode)
{
	m_lock.lock();
	if (pNode != NULL&&CurNodeCnt>0)
	{
		*pNode=*(mem_head + nCurHeadPos);
		m_lock.unlock();
		return true;
	}
	else
	{
		m_lock.unlock();
		return false;
	}
}

template<class T>
inline bool CircularQueue<T>::GetTailNode(T* pNode)
{
	m_lock.lock();
	if (pNode != NULL&&CurNodeCnt>0)
	{
		*pNode = *(mem_head + nCurTailPos);
		m_lock.unlock();
		return true;
	}
	else
	{
		m_lock.unlock();
		return false;
	}
}

template<class T>
inline bool CircularQueue<T>::isEmpty(void)
{
	if (GetSize() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
inline unsigned int CircularQueue<T>::GetSize(void)
{
	unsigned int t_size=0;
	m_lock.lock();
	t_size=CurNodeCnt;
	m_lock.unlock();
	return t_size;
}

template<class T>
inline bool CircularQueue<T>::GetNode(T* pNode,unsigned int npos)
{
	m_lock.lock();
	if (pNode != NULL)
	{
		*pNode=*(mem_head + npos);
		m_lock.unlock();
		return true;
	}
	else
	{
		m_lock.unlock();
		return false;
	}
}

#endif
