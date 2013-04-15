#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include "cg/io/point.h"

#include <cg/primitives/segment.h>
#include <cg/primitives/point.h>
#include <cg/primitives/triangle.h>
#include <cg/operations/has_intersection/triangle_segment.h>

using cg::point_2f;
using cg::point_2;
using cg::segment_2;


struct segment_intersect_triangle_viewer : cg::visualization::viewer_adapter
{
   segment_intersect_triangle_viewer()
      : s_(point_2(-50, 0), point_2(50, 0)),
        t_(point_2(0, -50), point_2(0, 50), point_2(20, 0))
   {
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      for (size_t l = 0, ln = 2; l != 3; ln = l++)
      {
         drawer.draw_line(t_[l], t_[ln]);
      }

      if (cg::has_intersection(t_, s_))
      {
         drawer.set_color(Qt::red);
      }
      drawer.draw_line(s_[0], s_[1]);
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton near vertex to move it"
                        << cg::visualization::endl
                        << "if segment is red segment intersect triangle"
                        << cg::visualization::endl;
   }

   bool on_press(const point_2f & p)
   {
      for (size_t i = 0; i != 2; ++i)
      {
         if ((fabs(p.x - s_[i].x) < 15) && (fabs(p.y - s_[i].y) < 15))
         {
            id_pointx_ = &s_[i];
            return true;
         }
      }

      for (size_t i = 0; i != 3; ++i)
      {
         if ((fabs(p.x - t_[i].x) < 15) && (fabs(p.y - t_[i].y) < 15))
         {
            id_pointx_ = &t_[i];
            return true;
         }
      }

      return false;
   }

   bool on_release(const point_2f & p)
   {
      id_pointx_.reset();
      return false;
   }

   bool on_move(const point_2f & p)
   {
      if (!id_pointx_)
      {
         return false;
      }
      **id_pointx_ = p;
      return true;
   }

private:
   cg::segment_2 s_;
   cg::triangle_2 t_;
   boost::optional<point_2*> id_pointx_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   segment_intersect_triangle_viewer viewer;
   cg::visualization::run_viewer(&viewer, "segment intersect triangle");
}
