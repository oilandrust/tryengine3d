/*
 *  load.h
 *  GEL
 *
 *  Created by J. Andreas Bærentzen on 08/03/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __GEOMETRY_LOAD_H__
#define __GEOMETRY_LOAD_H__

#include "TriMesh.h"

namespace Geometry
{
	/// Load a TriMesh from a file. Loader chosen based on extension.
	void load(const std::string &filename, TriMesh &mesh);
}



#endif