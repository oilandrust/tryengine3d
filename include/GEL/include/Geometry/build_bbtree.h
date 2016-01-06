#ifndef __GEOMETRY_BUILD_BBTREE_H
#define __GEOMETRY_BUILD_BBTREE_H

#include "BoundingTree.h"
#include "HMesh/Manifold.h"

namespace Geometry
{
typedef BoundingTree<OBox> OBBTree;
typedef BoundingTree<AABox> AABBTree;

void build_OBBTree(HMesh::Manifold& m, OBBTree& tree);
void build_AABBTree(HMesh::Manifold& m, AABBTree& tree);

}
#endif
