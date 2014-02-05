#include <pthread.h>

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

