#ifndef __GEOMETRY_VERIFICATION_H
#define __GEOMETRY_VERIFICATION_H

#include "Triangle.h"

namespace Geometry
{
  float SqrDistance (const CGLA::Vec3f& rkPoint,const Triangle& rkTri);
}
#endif
