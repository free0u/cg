#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/triangle.h>
#include <cg/primitives/segment.h>

#include <cg/operations/contains/triangle_point.h>
#include <cg/operations/has_intersection/segment_segment.h>

namespace cg
{
   inline bool has_intersection(triangle_2 const & t, segment_2 const & s);
}
