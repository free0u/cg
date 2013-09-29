#include <QColor>
#include <QApplication>

#include <iterator>
#include <boost/optional.hpp>

#include <cg/visualization/viewer_adapter.h>
#include <cg/visualization/draw_util.h>

#include <cg/io/point.h>

#include <cg/primitives/point.h>
#include <cg/primitives/vector.h>
#include <cg/convex_hull/graham.h>
#include <cg/convex_hull/andrew.h>
#include <cg/convex_hull/quick_hull.h>
#include <cg/convex_hull/jarvis.h>
#include <cg/algorithms/douglas.h>

using cg::point_2f;
using cg::point_2;
using cg::vector_2f;

struct douglas_viewer : cg::visualization::viewer_adapter
{
   douglas_viewer()
      : eps(0)
   {}

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::green);
      for (point_2 const & p : points) {
         drawer.draw_point(p, 3);
      }

      for (size_t i = 1; i < simple_points.size(); ++i)
      {
       drawer.draw_line(simple_points[i], simple_points[i - 1]);
      }
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton to add point" << cg::visualization::endl
                        << "points: " << points.size() << cg::visualization::endl
                        << "simple_points: " << simple_points.size() << cg::visualization::endl
                        << "eps (j/k for change): " << eps << cg::visualization::endl;
   }

   bool on_release(const point_2f & p)
   {
      points.push_back(p);
      update_simple_points();
      return true;
   }

   bool on_key(int key)
   {
      switch (key)
      {
         case Qt::Key_J : eps = eps + 10.0; break;
         case Qt::Key_K : eps = eps > 10 ? eps - 10 : 0; break;
         default : return false;
      }
      update_simple_points();
      return true;
   }

private:
   void update_simple_points() {
      simple_points.clear();
      cg::algoritms::simplify(points.begin(), points.end(), eps, std::back_inserter(simple_points));
   }

   double eps;
   std::vector<point_2> points;
   std::vector<point_2> simple_points;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   douglas_viewer viewer;
   cg::visualization::run_viewer(&viewer, "douglas");
}
