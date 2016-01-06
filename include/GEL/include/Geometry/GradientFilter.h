#ifndef __GEOMETRY_VOXELGRID_GRADIENTFILTER_H
#define __GEOMETRY_VOXELGRID_GRADIENTFILTER_H
// Author: J. Andreas B�rentzen,
// Created: Wed Feb 13 11:00:1

#include "CGLA/Vec3i.h"
#include "CGLA/Vec3f.h"


namespace Geometry
{
		///	This class is a filter that computes gradients from a grid.
		template<class GridT>
  class GradientFilter
  {
		const GridT* const grid;
  public:
		typedef CGLA::Vec3f DataType;

    GradientFilter(const GridT* const _grid): grid(_grid) {}

		bool map(const CGLA::Vec3i&, CGLA::Vec3f&) const;

		bool in_domain(const CGLA::Vec3i& p) const;

		const CGLA::Vec3f operator[](const CGLA::Vec3i& pi) const
		{
			CGLA::Vec3f g(0);
			map(pi,g);
			return g;
		}
  };

}
#endif
