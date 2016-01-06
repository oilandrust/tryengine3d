#ifndef __GEOMETRY_NEIGHBOURS_H
#define __GEOMETRY_NEIGHBOURS_H

#include "CGLA/Vec3i.h"
#include "CGLA/Vec3f.h"
#include "CGLA/Vec3d.h"

namespace Geometry
{
	extern const CGLA::Vec3f N6f[6];
	extern const CGLA::Vec3i N6i[6];
	extern const CGLA::Vec3d N6d[6];
	
	extern const CGLA::Vec3f N26f[26];
	extern const CGLA::Vec3i N26i[26];
	extern const CGLA::Vec3d N26d[26];

	extern const CGLA::Vec3i CubeCorners8i[8];
	extern const CGLA::Vec3f CubeCorners8f[8];
}


#endif