#ifndef BSPNODE_H
#define BSPNODE_H

#include <list>

#include "Plane.h"
#include "Vector3.h"
#include "Triangle.h"

class BSPNode
{
public:

    Plane *splitPlane = nullptr;

    /**
     * @brief All the triangles that belong to the split plane
     * (normally just one, the initialTriangle)
     */
    std::list <Triangle*> triangles;

    BSPNode *bspFront  = nullptr;
    BSPNode *bspBehind = nullptr;

    /**
     * @brief Builds a new BSPNode, taking as splitPlane a "prolongation"
     * of the passed initialTriangle (Auto-partition)
     */
    BSPNode(Triangle *initialTriangle);
    virtual ~BSPNode();

    /**
     * @brief Inserts a triangle into the BSPNode.
     *  - If the triangle is wholly in front  of splitPlane, then it goes to bspFront.
     *  - If the triangle is wholly in behind of splitPlane, then it goes to bspBehind.
     *  - If the triangle is intersected by the splitPlane, then we split it into 2 triangles,
     *    and each split triangle goes one to front and one to behind
     *  - If the triangle belongs to the splitPlane, then its added to the triangles list.
     */
    void InsertTriangle(Triangle *tri);

    /**
     * @brief 
     * Renders the triangles inside this BSPNode.
     * 
     */
    void Render(const Vector3 &viewPoint,
                ShaderProgram *program) const;
};

#endif // BSPNODE_H
