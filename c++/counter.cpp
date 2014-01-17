#include <iostream>
#include <pthread.h>

using namespace std;

class Lock {

public:

    virtual void lock(void) = 0 ;

    virtual void unlock(void) = 0 ;

    virtual ~Lock(void) {};
};

class LockWithMutex : public Lock {

public:

    LockWithMutex(void)  { pthread_mutex_init(&mutex, NULL); }

    virtual void lock(void)  { pthread_mutex_lock(&mutex); }

    virtual void unlock(void)  { pthread_mutex_unlock(&mutex); }

    virtual ~LockWithMutex(void) { pthread_mutex_destroy(&mutex); }

private:    

    pthread_mutex_t mutex;

};

class Thread 
{

public:

    Thread(void) { };
    void Start(void) { };
    virtual void execute(void) {pthread_create(m_thread, NULL,  };

private:

    pthread_t *m_thread;
    
};

class Counter 
{
public:

    Counter(int c)
    {
        m_value = c;
    };

    int getAndIncrement() 
    {
       
        int temp = m_value;
        m_value = temp + 1;
        return temp;
    };

private:

    LockWithMutex m_lock;
    int  m_value;

};



int main()
{
    Counter myCounter(0);
    cout << "Value:" << myCounter.getAndIncrement() << "\n";
    return 0;
}
