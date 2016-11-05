#ifndef SEGMENT_H
#define SEGMENT_H

#include "Vector3.h"

class Plane;
class Segment
{
public:
    Vector3 p1, p2;

    Segment();
    Segment(const Vector3 &p1, const Vector3 &p2);


    bool IsPartOfPlane(Plane *plane) const;

    int GetOrientation(const Vector3 &p);

    bool IsPointInLeft(const Vector3& p);
    bool IsPointOver(const Vector3& p);
    bool IsPointInRight(const Vector3& p);
    bool InsideBoundingRect(const Vector3 &p);

    bool GetIntersection(const Plane &plane,
                         Vector3 *intersectionPoint) const;
};

#endif // SEGMENT_H
