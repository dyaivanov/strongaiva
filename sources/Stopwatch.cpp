// Stopwatch.cpp: implementation of the CStopwatch class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "Stopwatch.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStopwatch::CStopwatch()
{
#ifdef _WIN32
	QueryPerformanceFrequency(&m_liPerfFreq);
#endif // _WIN32
	Start();
}

CStopwatch::~CStopwatch()
{

}

void CStopwatch::Start()
{
#ifdef _WIN32
        QueryPerformanceCounter(&m_liPerfStart);
#else
        timeval tv;
        //void *ptr; //04.05.2022 //05.10.2022
        timezone *ptr; //05.10.2022
            gettimeofday(&tv, ptr);
        m_liPerfStart = (long long)(((long long)tv.tv_sec * (long long)1000) + (long long)tv.tv_usec/(long long)1000);

//            timespec ts;
//            //CLOCK_REALTIME
//            //THREAD_CPUTIME_ID
//            clock_gettime(CLOCK_REALTIME, &ts);
//            m_liPerfStart = (long long)(((long long)ts.tv_sec * (long long)1000) + (long long)ts.tv_nsec/(long long)1000000);
#endif // _WIN32
}


#ifdef _WIN32
        __int64 CStopwatch::Now() const {
        LARGE_INTEGER liPerfNow;
    QueryPerformanceCounter(&liPerfNow);
    return(((liPerfNow.QuadPart - m_liPerfStart.QuadPart)*1000)/m_liPerfFreq.QuadPart);
#else
        long long CStopwatch::Now() const {
            timeval tv;
            //void *ptr; //04.05.2022 //05.10.2022
            timezone *ptr; //05.10.2022
            gettimeofday(&tv, ptr);
            return (long long)(((long long)tv.tv_sec * (long long)1000) + (long long)tv.tv_usec/(long long)1000) - m_liPerfStart;
#endif // _WIN32
}
