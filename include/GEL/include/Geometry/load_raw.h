#ifndef __GEOMETRY_VOXELGRID_LOAD_RAW_H__
#define __GEOMETRY_VOXELGRID_LOAD_RAW_H__

#include <string>
#include "CGLA/Mat4x4f.h"
#include "RGrid.h"

namespace Geometry
{

	template<class T>
		bool load_raw(const std::string& file, RGrid<T>& grid);
	
}

#endif
