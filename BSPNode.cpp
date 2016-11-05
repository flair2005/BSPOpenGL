#include "BSPNode.h"

#include "GLWidget.h"

int BSPNode::renderStep = 0;

BSPNode::BSPNode(Triangle *initialTriangle)
{
    splitPlane = Plane::FromTriangle(*initialTriangle);
    splitPlane->RefreshData();

    triangles.push_back(initialTriangle);
}

BSPNode::~BSPNode()
{
    delete splitPlane;
    for (Triangle *tri : triangles)
    {
        delete tri;
    }
    if (bspChildFront)  delete bspChildFront;
    if (bspChildBehind) delete bspChildBehind;
}

BSPNode *BSPNode::ConstructBSPTree(std::list<Triangle *> &trianglesPool)
{
    if (trianglesPool.size() == 0) { return nullptr; }

    BSPNode *root = new BSPNode(trianglesPool.front()); trianglesPool.pop_front();
    std::list<Triangle*> trianglesWhollyInFront, trianglesWhollyBehind;
    for (Triangle *tri : trianglesPool)
    {
        if (tri->IsPartOfPlane(root->splitPlane)) // Add it to the list of triangles of the node
        {
            root->triangles.push_back(tri);
        }
        else // It must be wholly in front, wholly behind, or intersecting
        {
            if (tri->IsWhollyInFrontOfPlane(root->splitPlane))     { trianglesWhollyInFront.push_back(tri); } // Wholly in front
            else if (tri->IsWhollyBehindOfPlane(root->splitPlane)) {  trianglesWhollyBehind.push_back(tri); } // Wholly behind
            else                                             // Intersecting (Split and classify)
            {
                // Triangle is intersecting !!!
                Vector3 int1, int2;
                if ( tri->GetIntersectionWithPlane(*root->splitPlane, &int1, &int2) > 0 ) // This should always throw > 0
                {
                    // Split the triangle into 2 parts (3 triangles (one of the parts is a quad, must be triangulated) )
                    Triangle *splitTri1, *splitTri2, *splitTri3;
                    tri->SplitWithPlane(root->splitPlane, &splitTri1, &splitTri2, &splitTri3);

                    // Classify the split triangles either in wholly front or wholly behind
                    if (splitTri1->IsWhollyInFrontOfPlane(root->splitPlane)) { trianglesWhollyInFront.push_back(splitTri1); }
                    else                                                     {  trianglesWhollyBehind.push_back(splitTri1); }
                    if (splitTri2->IsWhollyInFrontOfPlane(root->splitPlane)) { trianglesWhollyInFront.push_back(splitTri2); }
                    else                                                     {  trianglesWhollyBehind.push_back(splitTri2); }
                    if (splitTri3->IsWhollyInFrontOfPlane(root->splitPlane)) { trianglesWhollyInFront.push_back(splitTri3); }
                    else                                                     {  trianglesWhollyBehind.push_back(splitTri3); }
                }
                else
                {
                    std::cerr << "This should never happen dafuq..." << std::endl;
                }
            }
        }
    }

    // Now apply recursively the algorithm
    root->bspChildFront  = BSPNode::ConstructBSPTree(trianglesWhollyInFront);
    root->bspChildBehind = BSPNode::ConstructBSPTree(trianglesWhollyBehind);
    return root;
}

void BSPNode::Render(const Vector3 &viewPoint,
                     ShaderProgram *program) const
{
    BSPNode *firstToRender  = nullptr;
    BSPNode *secondToRender = nullptr;

    if (splitPlane->IsBehind(viewPoint))
    {
        firstToRender = bspChildFront;
        secondToRender = bspChildBehind;
    }
    else
    {
        firstToRender = bspChildBehind;
        secondToRender = bspChildFront;
    }

    if (firstToRender)
    {
        firstToRender->Render(viewPoint, program);
    }

    for (Triangle *tri : triangles)
    {
        ++renderStep;
        tri->Render(program);
        if (renderStep >= GLWidget::GetInstance()->bspRenderSteps) return;
    }

    if (secondToRender)
    {
        secondToRender->Render(viewPoint, program);
    }

    if (GLWidget::GetInstance()->seePlanes)
    {
        splitPlane->Render(program);
    }
}
