
#ifndef __NICKTHREAD__
#define __NICKTHREAD__

#include "Counter.hh"

class NickThread 
{

public:

    NickThread(void) { };

    void SetCounter(Counter *myCounter) 
    { 
        m_Counter = myCounter; 
    }

    void Start(int thread_number) 
    {
        m_thread_number = thread_number; 
        pthread_create(&m_thread, NULL,(void * (*) (void*))( &NickThread::execute), this); 
    };

    pthread_t GetID(void) { return m_thread; }
    static void *execute(void *);
    
private:
    
    Counter     *m_Counter;
    pthread_t    m_thread;
    unsigned int m_thread_number;

};

void *NickThread::execute(void *myInput) 
{ 
    NickThread *mythis = (NickThread*)myInput;   
    mythis->m_Counter->getAndIncrement();
    pthread_exit(&(mythis->m_thread_number));
};

#endif
