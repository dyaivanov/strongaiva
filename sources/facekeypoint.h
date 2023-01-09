#ifndef CFACEKEYPOINT_H
#define CFACEKEYPOINT_H

#include <vector>
using namespace std;

struct cPointFace
{
    long mx, my, mprec;

    cPointFace()
    {
        mx = 0;
        my = 0;
        mprec = 0;
    }

    cPointFace(long _x, long _y, long _prec)
    {
        mx = _x;
        my = _y;
        mprec = _prec;
    }

    long x()
    {
        return mx;
    }

    long y()
    {
        return my;
    }

    long prec()
    {
        return mprec;
    }
};

#define SZ_KEYPOINTS_FACE 70

class cFaceKeyPoint
{
private:
    cPointFace m_points[SZ_KEYPOINTS_FACE];

public:
    cFaceKeyPoint()
    {
        for(int i = 0; i < SZ_KEYPOINTS_FACE; i++)
        {
            m_points[i].mx = 0;
            m_points[i].my = 0;
            m_points[i].mprec = 0;
        }
    }

    cFaceKeyPoint(vector<cPointFace> &_v)
    {
        for(int i = 0; i < _v.size(); i++)
        {
            if(i < SZ_KEYPOINTS_FACE)
                m_points[i] = _v[i];
        }
    }

    cPointFace part(int pos)
    {
        if(pos >=0 && pos < SZ_KEYPOINTS_FACE)
            return m_points[pos];
    }
};

#endif // CFACEKEYPOINT_H
