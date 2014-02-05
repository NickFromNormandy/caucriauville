

#ifndef __NICKCOUNTER__
#define __NICKCOUNTER__

#include "Lock.hh"

class Counter 
{

public:

    Counter(int c)
    {
        m_value = c;
    };

    int getAndIncrement() 
    {
        m_lock.lock();
        int temp = m_value;
	//	sleep(0);
        m_value = temp + 1;
        m_lock.unlock();
        return temp;
    };

    void Print(void)
    {
        std::cout << "Counter:" << m_value << "\n";
    }

private:

    LockWithMutex m_lock;
    int  m_value;

};

#endif
