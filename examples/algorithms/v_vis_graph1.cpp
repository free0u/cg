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
#include <cg/visibility/visibility_slow.h>

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
      in_build = true;

//      in_build = false;
//      contour_2 cont;
//      cont.add_point(point_2(0, 0));
//      cont.add_point(point_2(100, 0));
//      cont.add_point(point_2(100, 100));
//      cont.add_point(point_2(0, 100));
//      contours.push_back(cont);

//      ab.push_back(point_2(-50, 50));
//      ab.push_back(point_2(150, 50));

//      build_graph();
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
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
   }

   bool on_double_click(const point_2f & p)
   {
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

   void build_graph() {
      gr = cg::build_graph(contours, ab[0], ab[1]);

      gr_v.clear();
      gr_v.push_back(ab[0]);
      for (contour_2 const& contour : contours) {
         for (point_2 const& point : contour) {
            gr_v.push_back(point);
         }
      }
      gr_v.push_back(ab[1]);
   }

private:
   vector<contour_2> contours;
   contour_2 current_contour;
   bool in_build;

   vector<point_2> ab;
   vector<vector<point_2> > gr;
   vector<point_2> gr_v;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   vis_graph1_viewer viewer;
   cg::visualization::run_viewer(&viewer, "vis_graph1 viewer");
}


