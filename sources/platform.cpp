#include "platform.h"

#ifndef _WIN32

void InitializeCriticalSection(pthread_mutex_t* mtx)
{
    //pthread_mutexattr_t attr;
    //pthread_mutexattr_init(&attr);
    //pthread_mutex_init(mtx, &attr);
    pthread_mutex_init(mtx, NULL);
}

void EnterCriticalSection(pthread_mutex_t* mtx)
{
    pthread_mutex_lock(mtx);
}

void LeaveCriticalSection(pthread_mutex_t* mtx)
{
    pthread_mutex_unlock(mtx);
}

void DeleteCriticalSection(pthread_mutex_t* mtx)
{
    pthread_mutex_destroy(mtx);
}

void Sleep(int msec)
{
    usleep(msec * 1000);
}

#endif // _WIN32

