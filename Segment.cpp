#include "Segment.h"

#include "Plane.h"

Segment::Segment()
{
}

Segment::Segment(const Vector3 &p1, const Vector3 &p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

bool Segment::IsPointInLeft(const Vector3 &p)
{
    return GetOrientation(p) > 0;
}

int Segment::GetOrientation(const Vector3 &p)
{
    float crossProduct = ((p2.x - p1.x) * (p.y - p1.y) - (p2.y - p1.y) * (p.x - p1.x));
    return crossProduct == 0 ? 0 : ( crossProduct > 0 ? 1 : -1 ) ;
}

bool Segment::IsPointOver(const Vector3 &p)
{
    return GetOrientation(p) == 0 && InsideBoundingRect(p);
}

bool Segment::IsPointInRight(const Vector3 &p)
{
    return GetOrientation(p) < 0;
}

// Given (p,q,r) colinear points => returns if r is between(p,q).
inline bool Segment::InsideBoundingRect(const Vector3 &p)
{
    return p.x >= std::min(p1.x, p2.x) && p.x <= std::max(p1.x, p2.x) &&
            p.y >= std::min(p1.y, p2.y) && p.y <= std::max(p1.y, p2.y);
}

bool Segment::GetIntersection(const Plane &plane,
                              Vector3 *intersectionPoint) const
{
    float distp1 = Vector3::Dot(plane.normal, (p1-plane.point));
    float distp2 = Vector3::Dot(plane.normal, (p2-plane.point));
    if (distp1 * distp2 > 0) return false; // There is no intersection

    Vector3 x = (p2-p1).Normalized();
    float dot = Vector3::Dot(plane.normal, x);
    if (dot == 0) return false; // Segment parallel to plane

    *intersectionPoint = p2 - x * (distp2 / dot);
    return true;
}
