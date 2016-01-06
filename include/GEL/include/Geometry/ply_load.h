#ifndef __GEOMETRY_PLYLOAD_H_
#define __GEOMETRY_PLYLOAD_H_


/*
 *  ply_load.h
 *  GEL
 *
 *  Created by J. Andreas Bærentzen on 08/08/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "Geometry/TriMesh.h"

namespace Geometry
{
	/** Load geometry from a ply file into a TriMesh. This is a very crude loader which only extracts the 
		raw geometry. */
	void ply_load(const std::string& fn, Geometry::TriMesh& mesh);
}

#endif