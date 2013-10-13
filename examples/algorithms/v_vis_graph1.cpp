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


struct vis_graph1_viewer : cg::visualization::viewer_adapter
{
   vis_graph1_viewer()
   {
     in_building_ = true;
     in_build = true;


//     in_build = false;
//     contour_2 cont;
//     cont.add_point(point_2(0, 0));
//     cont.add_point(point_2(100, 0));
//     cont.add_point(point_2(100, 100));
//     cont.add_point(point_2(0, 100));
//     contours.push_back(cont);

//     ab.push_back(point_2(-50, 50));
//     ab.push_back(point_2(150, 50));

//     build_graph();
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
//     if (in_building_)
//     {
//       drawer.set_color(Qt::white);

//       for (size_t i = 1; i < points_.size(); ++i)
//       {
//         drawer.draw_line(points_[i - 1], points_[i]);
//       }

//       return;
//     }


//     cg::contour_2 cont(points_);

//     if (cg::counterclockwise(cont))
//     {
//       drawer.set_color(cg::convex(cont) ? Qt::green : Qt::red);
//     } else
//     {
//       drawer.set_color(Qt::yellow);
//     }

//     for (size_t i = 1; i < points_.size(); ++i)
//     {
//       drawer.draw_line(points_[i - 1], points_[i]);
//     }
//     drawer.draw_line(points_.front(), points_.back());

     drawer.set_color(Qt::green);
     for (size_t j = 0; j < contours.size(); ++j) {
       size_t sz = contours[j].size();
       for (size_t i = 1; i < sz; ++i)
       {
         drawer.draw_line(contours[j][i - 1], contours[j][i]);
       }
       drawer.draw_line(contours[j][0], contours[j][sz - 1]);
     }

     drawer.set_color(Qt::yellow);

     size_t sz = current_contour.size();
     if (sz > 0) {
       for (size_t i = 1; i < sz; ++i)
       {
         drawer.draw_line(current_contour[i - 1], current_contour[i]);
       }
       drawer.draw_line(current_contour[0], current_contour[sz - 1]);
     }

     drawer.set_color(Qt::yellow);
     for (size_t i = 0; i < ab.size(); ++i) {
       drawer.draw_point(ab[i], 5);
     }
     if (ab.size() == 2) {
       // view visibility graph
       drawer.set_color(Qt::red);
       for (size_t i = 0; i < gr.size(); ++i) {
         for (size_t j = 0; j < gr[i].size(); ++j) {
            drawer.draw_line(gr_v[i], gr[i][j]);
         }
       }
     }
   }

   void print(cg::visualization::printer_type & p) const
   {
//     p.corner_stream() << "double-click to clear." << cg::visualization::endl
//                  << "press mouse rbutton for add vertex (click to first point to complete contour)" << cg::visualization::endl
//                  << "move vertex with rbutton" << cg::visualization::endl
//                  << "yellow contour -- not ccw" << cg::visualization::endl
//                  << "green contour -- convex" << cg::visualization::endl
//                  << "red contour -- not convex" << cg::visualization::endl;

//     for (size_t i = 0; i < points_.size(); ++i)
//     {
//       p.global_stream((point_2f)points_[i] + vector_2f(5, 0)) << i;
//     }
   }

   bool on_double_click(const point_2f & p)
   {
//     points_.clear();
//     in_building_ = true;
//     current_vertex_.reset();
     if (in_build) {
       contours.push_back(current_contour);
       current_contour.clear();
       return true;
     }

     return true;
   }

   bool on_press(const point_2f & p)
   {
     if (in_build) {
       current_contour.add_point(p);
       return true;
     }

     if (ab.size() < 2) {
       ab.push_back(p);
     }

     if (ab.size() == 2) {
       build_graph();
     }

//     if (in_building_)
//     {
//       if (points_.size() > 1)
//       {
//         if (fabs(points_[0].x - p.x) < 15 && fabs(points_[0].y - p.y) < 15)
//         {
//            in_building_ = false;
//            return true;
//         }
//       }

//       points_.push_back(p);
//       return true;
//     }

//     for (size_t i = 0; i < points_.size(); ++i)
//     {
//       if (fabs(points_[i].x - p.x) < 15 && fabs(points_[i].y - p.y) < 15)
//       {
//         current_vertex_ = i;
//         return true;
//       }
//     }

     return true;
   }

   bool on_release(const point_2f & p)
   {
//     if (in_building_)
//     {
//       return true;
//     }

//     current_vertex_.reset();

     return true;
   }

   bool on_move(const point_2f & p)
   {
//     if (in_building_)
//     {
//       return true;
//     }

//     if (current_vertex_)
//     {
//       points_[*current_vertex_] = p;
//     }

     return true;
   }

   bool on_key(int key)
   {
     switch (key)
     {
       case Qt::Key_Space : in_build = false; break;
       default : return false;
     }
     return true;
   }

   bool is_extra_edge(point_2 const& a, point_2 const& b) {
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

   bool is_visible(point_2 const& a, point_2 const& b) {
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

      if (is_extra_edge(a, b) || is_extra_edge(b, a)) return false;

      return true;
   }

   vector<point_2> get_visible_points(point_2 const& p) {
      vector<point_2> result;

      for (contour_2 const& contour : contours) {
         for (point_2 const& point : contour) {
            if (is_visible(p, point)) {
               result.push_back(point);
            }
         }
      }

      return result;
   }

   void build_graph() {
      gr.clear();
      gr_v.clear();

      gr.push_back(get_visible_points(ab[0]));
      gr_v.push_back(ab[0]);

      for (contour_2 const& contour : contours) {
         for (point_2 const& point : contour) {
            gr.push_back(get_visible_points(point));
            gr_v.push_back(point);
         }
      }

      gr.push_back(get_visible_points(ab[1]));
      gr_v.push_back(ab[1]);
   }

private:
   vector<contour_2> contours;
   contour_2 current_contour;
   bool in_build;

   vector<point_2> ab;
   vector<vector<point_2> > gr;
   vector<point_2> gr_v;


   bool in_building_;
   std::vector<point_2> points_;
   boost::optional<int> current_vertex_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   vis_graph1_viewer viewer;
   cg::visualization::run_viewer(&viewer, "vis_graph1 viewer");
}



//#include <QColor>
//#include <QApplication>

//#include <iterator>
//#include <boost/optional.hpp>

//#include <cg/visualization/viewer_adapter.h>
//#include <cg/visualization/draw_util.h>

//#include <cg/io/point.h>

//#include <cg/primitives/point.h>
//#include <cg/primitives/vector.h>
//#include <cg/convex_hull/graham.h>
//#include <cg/convex_hull/andrew.h>
//#include <cg/convex_hull/quick_hull.h>
//#include <cg/convex_hull/jarvis.h>
//#include <cg/algorithms/douglas.h>

//using cg::point_2f;
//using cg::point_2;
//using cg::vector_2f;

//struct vis_graph1_viewer : cg::visualization::viewer_adapter
//{
//   vis_graph1_viewer()
//     : eps(0)
//   {}

//   void draw(cg::visualization::drawer_type & drawer) const
//   {
//     drawer.set_color(Qt::green);
//     for (point_2 const & p : points) {
//       drawer.draw_point(p, 3);
//     }

//     for (size_t i = 1; i < simple_points.size(); ++i)
//     {
//      drawer.draw_line(simple_points[i], simple_points[i - 1]);
//     }
//   }

//   void print(cg::visualization::printer_type & p) const
//   {
//     p.corner_stream() << "press mouse rbutton to add point" << cg::visualization::endl
//                  << "points: " << points.size() << cg::visualization::endl
//                  << "simple_points: " << simple_points.size() << cg::visualization::endl
//                  << "eps (j/k for change): " << eps << cg::visualization::endl;
//   }

//   bool on_release(const point_2f & p)
//   {
//     points.push_back(p);
//     return true;
//   }

//   bool on_key(int key)
//   {
//     switch (key)
//     {
//       case Qt::Key_J : eps = eps + 10.0; break;
//       case Qt::Key_K : eps = eps > 10 ? eps - 10 : 0; break;
//       default : return false;
//     }
//     return true;
//   }

//private:

//   double eps;
//   std::vector<point_2> points;
//   std::vector<point_2> simple_points;
//};

//int main(int argc, char ** argv)
//{
//   QApplication app(argc, argv);
//   vis_graph1_viewer viewer;
//   cg::visualization::run_viewer(&viewer, "vis_graph1");
//}
