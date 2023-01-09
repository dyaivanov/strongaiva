#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
#else

#include <pthread.h>
#include <unistd.h>

typedef pthread_mutex_t CRITICAL_SECTION;

extern void InitializeCriticalSection(pthread_mutex_t* mtx);
extern void EnterCriticalSection(pthread_mutex_t* mtx);
extern void LeaveCriticalSection(pthread_mutex_t* mtx);
extern void DeleteCriticalSection(pthread_mutex_t* mtx);
extern void Sleep(int msec);

typedef int SOCKET;
#define closesocket(a) close(a)
#define SOCKADDR sockaddr
#define SOCKADDR_IN sockaddr_in
#define SOCKET_ERROR (-1)
#define INVALID_SOCKET (-1)

#endif // _WIN32

//#define IMMITATOR_FZI //13.11.2016

#endif // PLATFORM_H

