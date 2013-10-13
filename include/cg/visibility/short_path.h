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
#include <map>

using cg::point_2;
using cg::point_2f;
using cg::vector_2f;
using cg::contour_2;
using cg::segment_2;
using std::vector;
using std::map;


namespace cg
{
   double dist(point_2 const& a, point_2 const& b) {
      vector_2 v(a - b);
      return sqrt(v * v);
   }

   vector<point_2> get_shortest_path(vector<vector<point_2> > const& gr, vector<point_2> const& gr_v) {
      map<point_2, int> point_ind;
      for (size_t i = 0; i < gr_v.size(); ++i) {
         point_ind[gr_v[i]] = i;
      }

      int n = gr.size();

      vector<double> d(n, INFINITY);
      vector<int> p(n, -1);
      vector<bool> used(n);
      d[0] = 0;
      for (int i = 0; i < n; ++i) {
         int v = -1;
         for (size_t j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || d[j] < d[v])) {
               v = j;
            }
         }
         if (v != -1 && d[v] < INFINITY) {
            used[v] = true;
            point_2 from = gr_v[v];
            for (size_t j = 0; j < gr[v].size(); ++j) {
               point_2 to = gr[v][j];
               int to_ind = point_ind[to];
               double len = dist(from, to);
               if (d[v] + len < d[to_ind]) {
                  d[to_ind] = d[v] + len;
                  p[to_ind] = v;
               }
            }
         }
      }
      vector<point_2> ans;
      int ind = n - 1;
      while (ind != -1) {
         ans.push_back(gr_v[ind]);
         ind = p[ind];
      }
      std::reverse(ans.begin(), ans.end());
      return ans;
   }
}
