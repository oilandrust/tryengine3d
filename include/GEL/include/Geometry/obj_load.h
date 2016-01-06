#ifndef __GEOMETRY_TRIMESH_FUNCTIONS_H__
#define __GEOMETRY_TRIMESH_FUNCTIONS_H__

#include "TriMesh.h"

namespace Geometry
{
	/// Load a TriMesh from an OBJ file
	void obj_load(const std::string &filename, TriMesh &mesh);
}

#endif
