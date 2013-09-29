#pragma once
#include <limits>
#include <algorithm>

namespace cg {
namespace algoritms {
   double dist_points(point_2 p, point_2 q) {
      double dx = p.x - q.x;
      double dy = p.y - q.y;
      return sqrt(dx * dx + dy * dy);
   }

   double dist_seg_point(point_2 p, point_2 q, point_2 c) {
      double d = dist_points(p, q);
      double coef = (q - p) * (c - p) / (d * d);

      if (coef >= 0 && coef <= 1) {
         return abs((q - p) ^ (c - p)) / dist_points(p, q);
      } else
      {
         return std::min(dist_points(p, c), dist_points(q, c));
      }

      return 0;
   }

   template<class BidIter, class OutIter>
   OutIter simplify_impl(BidIter p, BidIter q, double eps, OutIter out) {
      if (p == q) return out;

      BidIter index = std::max_element(std::next(p), q, [p, q] (point_2 const& a, point_2 const& b) {
         return dist_seg_point(*p, *q, a) < dist_seg_point(*p, *q, b);
      });
      if (index == q || dist_seg_point(*p, *q, *index) < eps) {
         *out++ = *q;
         return out;
      }

      out = simplify_impl(p, index, eps, out);
      out = simplify_impl(index, q, eps, out);
      return out;
   }

   template<class BidIter, class OutIter>
   OutIter simplify(BidIter p, BidIter q, double eps, OutIter out) {
      if (p == q) return out;
      *out++ = *p;
      --q;
      simplify_impl(p, q, eps, out);
      return out;
   }
}}
