#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include "cg/io/point.h"

#include <cg/primitives/point.h>
#include <cg/visibility/visibility_slow.h>

#include <cg/visibility/short_path.h>

#include <boost/assign/list_of.hpp>
#include <vector>

using cg::point_2f;
using cg::point_2;
using std::vector;

struct contour_contains_point_viewer : cg::visualization::viewer_adapter
{
   contour_contains_point_viewer()
      : current_polygon_(0)
      , modification_mode_(false)
      , s(-120, -120)
      , f(120, 120)
   {}

   void draw(cg::visualization::drawer_type & drawer) const override
   {
      drawer.set_color(Qt::white);
      for(size_t i = 0; i < contours.size(); ++i)
         for(size_t l = 0, lp = contours[i].size() - 1; l != contours[i].size(); lp = l++)
            drawer.draw_line(contours[i][lp], contours[i][l]);

      if(modification_mode_)
      {
         drawer.set_color(Qt::red);
         for(size_t l = 0, lp = contours[current_polygon_].size() - 1; l != contours[current_polygon_].size(); lp = l++)
            drawer.draw_line(contours[current_polygon_][lp], contours[current_polygon_][l]);
      }

      drawer.set_color(Qt::green);

      for (size_t i = 0; i < ans.size(); ++i) {
         for (size_t j = 0; j < ans[i].size(); ++j) {
            drawer.draw_line(gr_v[i], ans[i][j]);
         }
      }

      drawer.set_color(Qt::blue);
      drawer.draw_point(f, 15);
      drawer.draw_point(s, 15);

      drawer.set_color(Qt::blue);
      for(int i = 0; i < (int)path.size() - 1; ++i)
         drawer.draw_line(path[i], path[i + 1]);
   }

   void print(cg::visualization::printer_type & p) const override
   {
      p.corner_stream() << "Double-click to clear"
                        << cg::visualization::endl
                        << "Click in insertion mode to create new polygon"
                        << cg::visualization::endl
                        << "Click in modification mode to add new point to polygon"
                        << cg::visualization::endl
                        << "Current mode: " << (modification_mode_ ? "modification" : "insertion")
                        << cg::visualization::endl
                        << "To switch mode press i"
                        << cg::visualization::endl;
   }

   bool on_double_click(const point_2f & p)
   {
      contours.clear();
      ans.clear();
      path.clear();
      modification_mode_ = false;
      return true;
   }

   bool on_press(const point_2f & p) override
   {
      if(fabs(p.x - s.x) < 4 && fabs(p.y - s.y) < 4)
      {
         idx_ = -1;
         return true;
      }
      if(fabs(p.x - f.x) < 4 && fabs(p.y - f.y) < 4)
      {
         idx_ = -2;
         return true;
      }

      for(size_t i = 0; i < contours.size(); ++i)
      {
         for (size_t l = 0; l != contours[i].size(); ++l)
         {
            if (fabs(p.x - contours[i][l].x) < 6 && fabs(p.y - contours[i][l].y) < 6)
            {
               current_polygon_ = i;
               idx_ = l;
               return true;
            }
         }
      }

      if(modification_mode_)
      {
         contours[current_polygon_].add_point(p);
         gr_v.clear();
         gr_v.push_back(s);
         for (contour_2 const& contour : contours) {
            for (point_2 const& point : contour) {
               gr_v.push_back(point);
            }
         }
         gr_v.push_back(f);
         ans = cg::build_graph(contours, s, f);
         path = cg::get_shortest_path(ans, gr_v);
         return true;
      }
      else
      {
         cg::contour_2 contour;
         contour.add_point(p);
         contours.push_back(contour);
         modification_mode_ = true;
         current_polygon_ = contours.size() - 1;
         gr_v.clear();
         gr_v.push_back(s);
         for (contour_2 const& contour : contours) {
            for (point_2 const& point : contour) {
               gr_v.push_back(point);
            }
         }
         gr_v.push_back(f);
         ans = cg::build_graph(contours, s, f);
         path = cg::get_shortest_path(ans, gr_v);
         return true;
      }

      return false;
   }

   bool on_release(const point_2f & p) override
   {
      idx_.reset();
      return false;
   }

   bool on_move(const point_2f & p) override
   {
      if (!idx_)
         return false;
      if(*idx_ == -1)
         s = p;
      else if(*idx_ == -2)
         f = p;
      else
         contours[current_polygon_][*idx_] = p;
      gr_v.clear();
      gr_v.push_back(s);
      for (contour_2 const& contour : contours) {
         for (point_2 const& point : contour) {
            gr_v.push_back(point);
         }
      }
      gr_v.push_back(f);
      ans = cg::build_graph(contours, s, f);
      path = cg::get_shortest_path(ans, gr_v);
      return true;
   }

   bool on_key(int key)
   {
      switch (key)
      {
      case Qt::Key_I :
         if(!contours.empty())
         {
            modification_mode_ = !modification_mode_;
            current_polygon_ = 0;
         }
         break;
      case Qt::Key_Left :
         if(modification_mode_)
         {
            if(--current_polygon_ == -1)
               current_polygon_ += contours.size();
         }
         break;
      case Qt::Key_Right :
         if(modification_mode_)
         {
            if(++current_polygon_ == contours.size())
               current_polygon_ -= contours.size();
         }
         break;
      default:
         return false;
      }
      return true;
   }

private:
   std::vector< cg::contour_2 > contours;
   vector<point_2> gr_v;
   boost::optional<int> idx_;
   int current_polygon_;
   boost::optional<cg::point_2> current_point_;
   vector<vector<point_2> > ans;
   std::vector< cg::point_2 > path;
   bool modification_mode_;
   cg::point_2 s, f;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   contour_contains_point_viewer viewer;
   cg::visualization::run_viewer(&viewer, "Visibility");
}
