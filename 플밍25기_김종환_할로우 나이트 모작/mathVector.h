#pragma once
#include <cmath>
using namespace std;

#define EPSILON 0.000001

struct MATHVECTOR
{
    double x, y;
    // ������
    MATHVECTOR(double _x, double _y)
    {
        x = _x, y = _y;
    }
    // ����
    double cross(const MATHVECTOR& _MV) const{
        return x * _MV.y - y * _MV.x;
    }

    MATHVECTOR operator * (double REALNUM) const {
        return MATHVECTOR(x * REALNUM, y * REALNUM);
    }

    MATHVECTOR operator + (MATHVECTOR _MV) const {
        return MATHVECTOR(x + _MV.x, y + _MV.y);
    }

    MATHVECTOR operator - (MATHVECTOR _MV) const {
        return MATHVECTOR(x - _MV.x, y - _MV.y);
    }

    BOOL operator == (MATHVECTOR _MV) const
    {
        return x == _MV.x && y == _MV.y;
    }

    BOOL operator < (MATHVECTOR _MV) const
    {
        return x < _MV.x && y < _MV.y;
    }
};

inline BOOL LineIntersect(MATHVECTOR aV_Start, MATHVECTOR aV_End, MATHVECTOR bV_Start, MATHVECTOR bV_End, MATHVECTOR& IntersectionPoint)
{
    double det = (aV_End - aV_Start).cross(bV_End - bV_Start);
    if (fabs(det) < EPSILON) return false;
    IntersectionPoint = aV_Start + (aV_End - aV_Start) * ((bV_Start - aV_Start).cross(bV_End - bV_Start) / det);
    return true;
}

//�������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
inline double ccw(MATHVECTOR aV, MATHVECTOR bV)
{
    return aV.cross(bV);
}

//�� p�� �������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
inline double ccw(MATHVECTOR pV, MATHVECTOR aV, MATHVECTOR bV)
{
    return ccw(aV - pV, bV - pV);
}

inline BOOL SegmentIntersect(MATHVECTOR aV_Start, MATHVECTOR aV_End, MATHVECTOR bV_Start, MATHVECTOR bV_End)
{
    double ab = ccw(aV_Start, aV_End, bV_Start) * ccw(aV_Start, aV_End, bV_End);
    double cd = ccw(bV_Start, bV_End, aV_Start) * ccw(bV_Start, bV_End, aV_End);

    if (ab == 0 && cd == 0)
    {
        if (aV_End < aV_Start) swap(aV_Start, aV_End);
        if (bV_End < bV_Start) swap(bV_Start, bV_End);
        return !(aV_End < bV_Start || bV_End < aV_Start);
    }
    return ab <= 0 && cd <= 0;
}