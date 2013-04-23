#pragma once

#include <cg/primitives/contour.h>
#include <cg/primitives/point.h>
#include <cg/primitives/triangle.h>
#include <cg/operations/orientation.h>
#include <cg/operations/contains/triangle_point.h>
#include <cg/operations/contains/segment_point.h>

#include <iostream>
#include <cg/io/point.h>
using std::cerr;
using std::endl;

namespace cg
{
   // c is convex contour ccw orientation
   inline bool convex_contains(contour_2 const & c, point_2 const & q)
   {
      int cnt_vertices = c.size();

      if (cnt_vertices == 0)
         return false;
      if (cnt_vertices == 1)
         return c[0] == q;
      if (cnt_vertices == 2)
         return cg::contains(cg::segment_2(c[0], c[1]), q);

      if (q == c[0])
         return true;

      contour_2::const_iterator it_begin = c.begin();
      contour_2::const_iterator it_end = c.end();

      contour_2::const_iterator it = std::lower_bound(it_begin + 1, it_end, q,
         [it_begin] (point_2 const& a, point_2 const& b)
         {
            return cg::orientation(*it_begin, a, b) == cg::CG_LEFT;
         }
      );

      if (it == it_end) // out
      {
         return false;
      }

      if (it == it_begin + 1)
      {
         return cg::contains(triangle_2(*it_begin, *(it_begin + 1), *(it_begin + 2)), q);
      }

      return cg::contains(triangle_2(*it_begin, *(it), *(it - 1)), q);
   }

   // c is ordinary contour
   inline bool contains(contour_2 const & c, point_2 const & q);
}
