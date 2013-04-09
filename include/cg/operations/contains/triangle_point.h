#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/triangle.h>
#include <cg/primitives/segment.h>

#include <cg/operations/orientation.h>
#include <cg/operations/contains/segment_point.h>
#include <algorithm>

namespace cg
{
   inline bool contains(triangle_2 const & t, point_2 const & q);
}
