#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include "cg/io/point.h"

#include <cg/primitives/segment.h>
#include <cg/primitives/point.h>
#include <cg/operations/has_intersection/segment_segment.h>

using cg::point_2f;
using cg::point_2;
using cg::segment_2;


struct segment_intersect_segment_viewer : cg::visualization::viewer_adapter
{
   segment_intersect_segment_viewer()
      : s1_(point_2(0, -50), point_2(0, 50)),
        s2_(point_2(-50, 0), point_2(50, 0))
   {
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      if (cg::has_intersection(s1_, s2_))
      {
         drawer.set_color(Qt::red);
      }

      drawer.draw_line(s1_[0], s1_[1]);
      drawer.draw_line(s2_[0], s2_[1]);
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton near segment vertex to move it"
                        << cg::visualization::endl
                        << "if segments is red segments intersect"
                        << cg::visualization::endl;
   }

   bool on_press(const point_2f & p)
   {
      for (size_t i = 0; i != 2; ++i)
      {
         if ((fabs(p.x - s1_[i].x) < 15) && (fabs(p.y -s1_[i].y) < 15))
         {
            id_segmentx_ = &s1_;
            idx_ = i;
            return true;
         }
      }

      for (size_t i = 0; i != 2; ++i)
      {
         if ((fabs(p.x - s2_[i].x) < 15) && (fabs(p.y - s2_[i].y) < 15))
         {
            id_segmentx_ = &s2_;
            idx_ = i;
            return true;
         }
      }

      return false;
   }

   bool on_release(const point_2f & p)
   {
      id_segmentx_.reset();
      return false;
   }

   bool on_move(const point_2f & p)
   {
//      current_point_ = p;

//      if (!idx_)
//         return true;

//      t_[*idx_] = p;

      if (!id_segmentx_)
      {
         return true;
      }

      (**id_segmentx_)[*idx_] = p;
      return true;
   }

private:
   cg::segment_2 s1_, s2_;
   boost::optional<segment_2*> id_segmentx_;
   boost::optional<size_t> idx_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   segment_intersect_segment_viewer viewer;
   cg::visualization::run_viewer(&viewer, "segment intersect segment");
}
