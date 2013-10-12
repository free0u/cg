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


//      in_build = false;
//      contour_2 cont;
//      cont.add_point(point_2(0, 0));
//      cont.add_point(point_2(0, 100));
//      cont.add_point(point_2(100, 100));
//      cont.add_point(point_2(100, 0));
//      contours.push_back(cont);

//      ab.push_back(point_2(-50, 50));
//      ab.push_back(point_2(150, 50));

//      build_graph();
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
//      if (in_building_)
//      {
//         drawer.set_color(Qt::white);

//         for (size_t i = 1; i < points_.size(); ++i)
//         {
//            drawer.draw_line(points_[i - 1], points_[i]);
//         }

//         return;
//      }


//      cg::contour_2 cont(points_);

//      if (cg::counterclockwise(cont))
//      {
//         drawer.set_color(cg::convex(cont) ? Qt::green : Qt::red);
//      } else
//      {
//         drawer.set_color(Qt::yellow);
//      }

//      for (size_t i = 1; i < points_.size(); ++i)
//      {
//         drawer.draw_line(points_[i - 1], points_[i]);
//      }
//      drawer.draw_line(points_.front(), points_.back());

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
//      p.corner_stream() << "double-click to clear." << cg::visualization::endl
//                        << "press mouse rbutton for add vertex (click to first point to complete contour)" << cg::visualization::endl
//                        << "move vertex with rbutton" << cg::visualization::endl
//                        << "yellow contour -- not ccw" << cg::visualization::endl
//                        << "green contour -- convex" << cg::visualization::endl
//                        << "red contour -- not convex" << cg::visualization::endl;

//      for (size_t i = 0; i < points_.size(); ++i)
//      {
//         p.global_stream((point_2f)points_[i] + vector_2f(5, 0)) << i;
//      }
   }

   bool on_double_click(const point_2f & p)
   {
//      points_.clear();
//      in_building_ = true;
//      current_vertex_.reset();
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

//      if (in_building_)
//      {
//         if (points_.size() > 1)
//         {
//            if (fabs(points_[0].x - p.x) < 15 && fabs(points_[0].y - p.y) < 15)
//            {
//               in_building_ = false;
//               return true;
//            }
//         }

//         points_.push_back(p);
//         return true;
//      }

//      for (size_t i = 0; i < points_.size(); ++i)
//      {
//         if (fabs(points_[i].x - p.x) < 15 && fabs(points_[i].y - p.y) < 15)
//         {
//            current_vertex_ = i;
//            return true;
//         }
//      }

      return true;
   }

   bool on_release(const point_2f & p)
   {
//      if (in_building_)
//      {
//         return true;
//      }

//      current_vertex_.reset();

      return true;
   }

   bool on_move(const point_2f & p)
   {
//      if (in_building_)
//      {
//         return true;
//      }

//      if (current_vertex_)
//      {
//         points_[*current_vertex_] = p;
//      }

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

   bool is_visible(point_2 const& a, point_2 const& b) {
      segment_2 s0(a, b);
      bool test1 = true;
      for (size_t i = 0; i < contours.size(); ++i) {
         size_t sz = contours[i].size();
         for (size_t l = 0, lp = sz - 1; l != sz; lp = l++) {
            // lp -> l
            segment_2 s1(contours[i][l], contours[i][lp]);
            if (s0[0] == s1[0] ||
                s0[0] == s1[1] ||
                s0[1] == s1[0] ||
                s0[1] == s1[1]) continue;
            if (cg::has_intersection(s0, s1))
               test1 = false;
         }
      }

      // check for point in one contour
      size_t ind1, ind2;
      for (size_t i = 0; i < contours.size(); ++i) {
         ind1 = -1; ind2 = -1;
         for (size_t j = 0; j < contours[i].size(); ++j) {
            if (contours[i][j] == a) ind1 = j;
            if (contours[i][j] == b) ind2 = j;
         }
         if (ind1 != -1 && ind2 != -1) {
            size_t p = (ind2 == 0 ? contours[i].size() - 1 : ind2 - 1);
            size_t n = (ind2 == contours[i].size() - 1 ? 0 : ind2 + 1);
            cg::orientation_t o1 = cg::orientation(a, b, contours[i][n]);
            cg::orientation_t o2 = cg::orientation(a, b, contours[i][p]);
            if (o1 == cg::CG_LEFT && o2 == cg::CG_RIGHT) {
               test1 = false;
            }
            if (o2 == cg::CG_LEFT && o1 == cg::CG_RIGHT) {
               test1 = false;
            }
         }
      }
      return test1;
   }

   vector<point_2> get_visible_points(point_2 const& p) {
      vector<point_2> result;
      for (size_t i = 0; i < contours.size(); ++i) {
         for (size_t j = 0; j < contours[i].size(); ++j) {
            if (p == contours[i][j]) continue;

            if (is_visible(p, contours[i][j])) {
               result.push_back(contours[i][j]);
            }
         }
      }
      return result;
   }

   void build_graph() {
      gr.clear();
      gr_v.clear();

      vector<point_2> t = get_visible_points(ab[0]);
      gr.push_back(t);
      gr_v.push_back(ab[0]);
      for (size_t i = 0; i < contours.size(); ++i) {
         for (size_t j = 0; j < contours[i].size(); ++j) {
            gr.push_back(get_visible_points(contours[i][j]));
            gr_v.push_back(contours[i][j]);
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
//      : eps(0)
//   {}

//   void draw(cg::visualization::drawer_type & drawer) const
//   {
//      drawer.set_color(Qt::green);
//      for (point_2 const & p : points) {
//         drawer.draw_point(p, 3);
//      }

//      for (size_t i = 1; i < simple_points.size(); ++i)
//      {
//       drawer.draw_line(simple_points[i], simple_points[i - 1]);
//      }
//   }

//   void print(cg::visualization::printer_type & p) const
//   {
//      p.corner_stream() << "press mouse rbutton to add point" << cg::visualization::endl
//                        << "points: " << points.size() << cg::visualization::endl
//                        << "simple_points: " << simple_points.size() << cg::visualization::endl
//                        << "eps (j/k for change): " << eps << cg::visualization::endl;
//   }

//   bool on_release(const point_2f & p)
//   {
//      points.push_back(p);
//      return true;
//   }

//   bool on_key(int key)
//   {
//      switch (key)
//      {
//         case Qt::Key_J : eps = eps + 10.0; break;
//         case Qt::Key_K : eps = eps > 10 ? eps - 10 : 0; break;
//         default : return false;
//      }
//      return true;
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
