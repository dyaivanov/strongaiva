// Stopwatch.h: interface for the CStopwatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STOPWATCH_H__0D25F408_C6A3_40CF_AF51_DD5D7F51483B__INCLUDED_)
#define AFX_STOPWATCH_H__0D25F408_C6A3_40CF_AF51_DD5D7F51483B__INCLUDED_

#ifdef _WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>


#ifndef LARGE_INTEGER
#include <winnt.h>
#endif
#else
#include <sys/time.h>
#endif // _WIN32


//15.02.2017
//СЃС‚СЂСѓРєС‚СѓСЂР° timespec
struct mytimespec
{
    int tv_sec;
    int tv_nsec;

    mytimespec()
    {
        tv_sec = 0;
        tv_nsec = 0;
    }

    void init_null()
    {
        tv_sec = 0;
        tv_nsec = 0;
    }

    friend bool operator < (const mytimespec &tt1, const mytimespec &tt2)
    {
        if (tt1.tv_sec < tt2.tv_sec)
            return true;

        if (tt1.tv_sec == tt2.tv_sec && tt1.tv_nsec < tt2.tv_nsec)
            return true;

        return false;
    }

    friend bool operator == (const mytimespec &tt1, const mytimespec &tt2)
    {
        if (tt1.tv_sec == tt2.tv_sec && tt1.tv_nsec == tt2.tv_nsec)
            return true;

        return false;
    }

    int delay_ms(const mytimespec &t_prev)
    {
        int t_razn_ms = 0;
        if (t_prev.tv_sec == tv_sec)
        {
            t_razn_ms = (tv_nsec - t_prev.tv_nsec) / 1000000;
        }
        else
        {
            t_razn_ms = (tv_nsec + ((int)1000000000 - t_prev.tv_nsec)) / 1000000;
        }

        return t_razn_ms;
    }

};

class CStopwatch
{
public:
	void Start();
	CStopwatch();
	virtual ~CStopwatch();
#ifdef _WIN32
        __int64 Now() const;
#else
        long long Now() const;
#endif // _WIN32     

private:
#ifdef _WIN32
    	LARGE_INTEGER m_liPerfFreq;
	LARGE_INTEGER m_liPerfStart;
#else
	long long m_liPerfStart;
#endif // _WIN32
};

#endif // !defined(AFX_STOPWATCH_H__0D25F408_C6A3_40CF_AF51_DD5D7F51483B__INCLUDED_)

