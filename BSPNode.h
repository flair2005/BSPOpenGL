#ifndef BSPNODE_H
#define BSPNODE_H

#include <list>

#include "Plane.h"
#include "Vector3.h"
#include "Triangle.h"

class BSPNode
{
public:

    static int renderStep;

    Plane *splitPlane = nullptr;

    /**
     * @brief All the triangles that belong to the split plane
     * (normally just one, the initialTriangle)
     */
    std::list <Triangle*> triangles;

    BSPNode *bspChildBehind = nullptr;
    BSPNode *bspChildFront  = nullptr;

    /**
     * @brief Builds a new BSPNode, taking as splitPlane a "prolongation"
     * of the passed initialTriangle (Auto-partition)
     */
    BSPNode(Triangle *initialTriangle);
    virtual ~BSPNode();

    /**
     * @brief Construct a BSPTree from a list of triangles
     */
    static BSPNode *ConstructBSPTree(std::list<Triangle*> &triangles);

    /**
     * @brief 
     * Renders the triangles inside this BSPNode.
     * 
     */
    void Render(const Vector3 &viewPoint,
                ShaderProgram *program) const;
};

#endif // BSPNODE_H
