#pragma once

#include <vector>
#include <stack>

#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include <cg/operations/orientation.h>
#include <cg/operations/convex.h>
#include <cg/operations/has_intersection/segment_segment.h>

#include <cg/primitives/contour.h>

#include "cg/io/point.h"

using cg::point_2;
using cg::point_2f;
using cg::vector_2f;
using cg::contour_2;
using cg::segment_2;
using std::vector;


namespace cg
{
   bool is_extra_edge(vector<contour_2> const& contours, point_2 const& a, point_2 const& b, point_2 const& s_point, point_2 const& f_point) {
      if (a == s_point ||
          b == s_point ||
          a == f_point ||
          b == f_point) return false;

      for (contour_2 const& contour : contours) {
         contour_2::const_iterator it_a = find(contour.begin(), contour.end(), a);
         if (it_a == contour.end()) continue;

         contour_2::circulator_t it_prev = --contour.circulator(it_a);
         contour_2::circulator_t it_next = ++contour.circulator(it_a);

         if (cg::orientation(*it_prev, *it_a, *it_next) == cg::CG_LEFT) {
            if (cg::orientation(*it_next, *it_a, b) != cg::CG_RIGHT &&
                   cg::orientation(*it_prev, *it_a, b) != cg::CG_LEFT) {
               return true;
            } else
            {
               return false;
            }
         } else
         {
            return true;
         }
      }

      return false;
   }

   bool is_visible(vector<contour_2> const& contours, point_2 const& a, point_2 const& b, point_2 const& s_point, point_2 const& f_point) {
      if (a == b) return false;

      segment_2 s0(a, b);
      for (contour_2 const& contour : contours) {
         size_t sz = contour.size();
         for (size_t l = 0, lp = sz - 1; l != sz; lp = l++) {
            // lp -> l
            segment_2 s1(contour[l], contour[lp]);
            if (s0[0] == s1[0] ||
                s0[0] == s1[1] ||
                s0[1] == s1[0] ||
                s0[1] == s1[1]) continue;
            if (cg::has_intersection(s0, s1))
               return false;
         }
      }

      // check if points in same contour
      bool v = true;
      for (contour_2 const& contour : contours) {
         contour_2::const_iterator it_a = find(contour.begin(), contour.end(), a);
         contour_2::const_iterator it_b = find(contour.begin(), contour.end(), b);

         if (it_a == contour.end() || it_b == contour.end()) continue;

         contour_2::circulator_t it_prev = --contour.circulator(it_a);
         contour_2::circulator_t it_next = ++contour.circulator(it_a);

         if (*it_b == *it_prev || *it_b == *it_next) continue;

         if (cg::orientation(*it_prev, *it_a, *it_next) == cg::CG_LEFT) {
            if (cg::orientation(*it_a, *it_prev, *it_b) == cg::CG_LEFT ||
                cg::orientation(*it_next, *it_a, *it_b) == cg::CG_LEFT) {
               continue;
            } else
            {
               v = false;
               break;
            }
         } else
         {
            if (cg::orientation(*it_a, *it_prev, *it_b) == cg::CG_LEFT &&
                cg::orientation(*it_next, *it_a, *it_b) == cg::CG_LEFT) {
               continue;
            } else
            {
               v = false;
               break;
            }
         }
      }

      if (!v) return false;

      if (is_extra_edge(contours, a, b, s_point, f_point) || is_extra_edge(contours, b, a, s_point, f_point)) return false;

      return true;
   }

   vector<point_2> get_visible_points(vector<contour_2> const& contours, point_2 const& p, point_2 const& s_point, point_2 const& f_point) {
      vector<point_2> result;

      for (contour_2 const& contour : contours) {
         for (point_2 const& point : contour) {
            if (is_visible(contours, p, point, s_point, f_point)) {
               result.push_back(point);
            }
         }
      }
      if (is_visible(contours, p, s_point, s_point, f_point)) result.push_back(s_point);
      if (is_visible(contours, p, f_point, s_point, f_point)) result.push_back(f_point);

      return result;
   }

   vector<vector<point_2> > build_graph(vector<contour_2> const& contours, point_2 const& s_point, point_2 const& f_point) {
      vector<vector<point_2> > result;

      result.push_back(get_visible_points(contours, s_point, s_point, f_point));

      for (contour_2 const& contour : contours) {
         for (point_2 const& point : contour) {
            result.push_back(get_visible_points(contours, point, s_point, f_point));
         }
      }

      result.push_back(get_visible_points(contours, f_point, s_point, f_point));

      return result;
   }
}
