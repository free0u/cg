#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include "cg/io/point.h"

#include <cg/primitives/triangle.h>
#include <cg/primitives/point.h>
#include <cg/primitives/range.h>

#include <cg/operations/contains/rectangle_point.h>
#include <cg/operations/has_intersection/rectangle_segment.h>

using cg::point_2f;
using cg::point_2;

typedef cg::range_t<double> range_2;

struct segment_intersect_rectangle_viewer : cg::visualization::viewer_adapter
{
   segment_intersect_rectangle_viewer()
      : t_(range_2(0, 50), range_2(0, 100)),
        s_(point_2(-50, 50), point_2(100, 50))
   {}

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      if (cg::has_intersection(t_, s_))
         drawer.set_color(Qt::red);
      drawer.draw_line(s_[0], s_[1]);


      drawer.set_color(Qt::white);

      int ind[4][2] =
      {
         {0, 0},
         {1, 0},
         {1, 1},
         {0, 1}
      };

      for (size_t l = 0, lp = 3; l != 4; lp = l++)
      {
         drawer.draw_line(t_.corner(ind[lp][0], ind[lp][1]), t_.corner(ind[l][0], ind[l][1]));
      }
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton near rectangle vertex to move it"
                        << cg::visualization::endl
                        << "if rectangle is red segment intersect rectangle"
                        << cg::visualization::endl;
   }

   bool on_press(const point_2f & p)
   {
      segment_clicked = false;

      for (size_t i = 0; i != 2; ++i)
      {
         if ((fabs(p.x - s_[i].x) < 15) && (fabs(p.y - s_[i].y) < 15))
         {
            segment_clicked = true;
            id_pointx_ = &s_[i];
            return true;
         }
      }


      for (size_t l = 0; l != 4; ++l)
      {
         if (fabs(p.x - t_[l].x) < 15 && fabs(p.y - t_[l].y) < 15)
         {
            idx_ = l;
            return true;
         }
      }

      return false;
   }

   bool on_release(const point_2f & p)
   {
      id_pointx_.reset();
      idx_.reset();
      return false;
   }

   bool on_move(const point_2f & p)
   {
      current_point_ = p;

      if (segment_clicked && id_pointx_)
      {
         **id_pointx_ = p;
         return true;
      }

      if (!segment_clicked && idx_)
      {
         int ind[4][2] =
         {
            {0, 0},
            {1, 0},
            {1, 1},
            {0, 1}
         };
         point_2 corner_to_change = t_[*idx_];

         boost::optional<double> min_range = 10;
         for (size_t i = 0; i != 4; ++i)
         {
            point_2 current_corner = t_.corner(ind[i][0], ind[i][1]);

            if (current_corner == corner_to_change)
            {
               t_.set_corner(ind[i][0], ind[i][1], p, min_range);
               continue;
            }

            if (current_corner.x == corner_to_change.x)
            {
               t_.set_corner(ind[i][0], ind[i][1], point_2(p.x, current_corner.y), min_range);
               continue;
            }

            if (current_corner.y == corner_to_change.y)
            {
               t_.set_corner(ind[i][0], ind[i][1], point_2(current_corner.x, p.y), min_range);
               continue;
            }
         }
      }

      return true;
   }

private:
   cg::rectangle_2 t_;
   cg::segment_2 s_;
   boost::optional<size_t> idx_;
   boost::optional<point_2*> id_pointx_;
   bool segment_clicked;
   boost::optional<cg::point_2> current_point_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   segment_intersect_rectangle_viewer viewer;
   cg::visualization::run_viewer(&viewer, "segment_intersect_rectangle");
}
