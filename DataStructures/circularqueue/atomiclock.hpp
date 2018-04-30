//#pragma once

//AtomicLock

#ifndef _ATOMIC_LOCK_H
#define _ATOMIC_LOCK_H

#if defined(_WIN32)
#include <Windows.h>
#elif defined(__GNUC__)
#else
#error Unsupported OS type
#endif

class AtomicLock
{
public:
	AtomicLock(void)
	{
		m_atmlck = 0;
	}

	~AtomicLock(void)
	{
		m_atmlck = 0;
	}

	void lock(void)
	{
#if defined(_WIN32)
#include <Windows.h>
		while (1 == InterlockedCompareExchange(&m_atmlck, 1, 0));
#elif defined(__GNUC__)
		while (1 == __sync_val_compare_and_swap(&m_atmlck, 0, 1));
#else
#error Unsupported OS type
#endif
	}

	void unlock(void)
	{
		m_atmlck = 0;
	}

private:
	long m_atmlck;
};

#endif

