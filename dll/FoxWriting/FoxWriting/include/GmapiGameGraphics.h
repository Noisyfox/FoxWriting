/************************************************************************/
/* LICENSE:                                                             */
/*                                                                      */
/*  GMAPI is free software; you can redistribute it and/or              */
/*  modify it under the terms of the GNU Lesser General Public          */
/*  License as published by the Free Software Foundation; either        */
/*  version 2.1 of the License, or (at your option) any later version.  */
/*                                                                      */
/*  GMAPI is distributed in the hope that it will be useful,            */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of      */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   */
/*  Lesser General Public License for more details.                     */
/*                                                                      */
/*  You should have received a copy of the GNU Lesser General Public    */
/*  License along with GMAPI; if not, write to the Free Software        */
/*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA       */
/*  02110-1301 USA                                                      */
/************************************************************************/

/************************************************************************/
/*  GmapiGameGraphics.h                                                 */
/*   - Wrapped GM functions; Parser-generated code                      */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once
#include "GmapiInternal.h"

namespace gm {

  void draw_sprite( int sprite, int subimg, double x, double y );
  void draw_sprite_stretched( int sprite, int subimg, double x,
                              double y, double w, double h );
  void draw_sprite_tiled( int sprite, int subimg, double x, double y );
  void draw_sprite_part( int sprite, int subimg, int left, int top,
                         int width, int height, double x, double y );
  void draw_background( int back, double x, double y );
  void draw_background_stretched( int back, double x, double y,
                                  double w, double h );
  void draw_background_tiled( int back, double x, double y );
  void draw_background_part( int back, int left, int top, int width,
                             int height, double x, double y );
  void draw_sprite_ext( int sprite, int subimg, double x, double y,
                        double xscale, double yscale, double rot,
                        int color, double alpha );
  void draw_sprite_stretched_ext( int sprite, int subimg, double x,
                                  double y, double w, double h,
                                  int color, double alpha );
  void draw_sprite_tiled_ext( int sprite, int subimg, double x,
                              double y, double xscale, double yscale,
                              int color, double alpha );
  void draw_sprite_part_ext( int sprite, int subimg, int left, int top,
                             int width, int height, double x, double y,
                             double xscale, double yscale, int color,
                             double alpha );
  void draw_sprite_general( int sprite, int subimg, int left, int top,
                            int width, int height, double x, double y,
                            double xscale, double yscale, double rot,
                            int c1, int c2, int c3, int c4,
                            double alpha );

  void draw_background_ext( int back, double x, double y, double xscale,
                            double yscale, double rot, int color,
                            double alpha );
  void draw_background_stretched_ext( int back, double x, double y,
                                      double w, double h, int color,
                                      double alpha );
  void draw_background_tiled_ext( int back, double x, double y,
                                  double xscale, double yscale, int color,
                                  double alpha );
  void draw_background_part_ext( int back, int left, int top, int width,
                                 int height, double x, double y,
                                 double xscale, double yscale, int color,
                                 double alpha );
  void draw_background_general( int back, int left, int top, int width,
                                int height, double x, double y,
                                double xscale, double yscale, double rot,
                                int c1, int c2, int c3, int c4,
                                double alpha );
  void draw_clear( int col );
  void draw_clear_alpha( int col, double alpha );

  void draw_point( double x, double y );
  void draw_line( double x1, double y1, double x2, double y2 );
  void draw_line_width( double x1, double y1, double x2, double y2,
                        double w );
  void draw_rectangle( double x1, double y1, double x2, double y2,
                       bool outline );
  void draw_roundrect( double x1, double y1, double x2, double y2,
                       bool outline );
  void draw_triangle( double x1, double y1, double x2, double y2,
                      double x3, double y3, bool outline );
  void draw_circle( double x, double y, double r, bool outline );
  void draw_ellipse( double x1, double y1, double x2, double y2,
                     bool outline );
  void draw_set_circle_precision( int precision );
  void draw_arrow( double x1, double y1, double x2, double y2,
                   int size );

  void draw_button( double x1, double y1, double x2, double y2,
                    bool up );
  void draw_path( int path, double x, double y, bool absolute );
  void draw_healthbar( double x1, double y1, double x2, double y2,
                       double amount, int backcol, int mincol,
                       int maxcol, double direction, bool showback,
                       bool showborder );

  void draw_set_color( int col );
  void draw_set_alpha( double alpha );
  int draw_get_color();
  double draw_get_alpha();

  int make_color_rgb( int red, int green, int blue );
  int make_color_hsv( int hue, int saturation, int value );
  int color_get_red( int col );
  int color_get_green( int col );
  int color_get_blue( int col );
  int color_get_hue( int col );
  int color_get_saturation( int col );
  int color_get_value( int col );
  int merge_color( int col1, int col2, double amount );

  int draw_getpixel( double x, double y );

  void screen_save( const CGMVariable& fname );
  void screen_save_part( const CGMVariable& fname, int x, int y,
                         int w, int h );

  void draw_set_font( int font );
  void draw_set_halign( int halign );
  void draw_set_valign( int valign );

  void draw_text( double x, double y, const CGMVariable& string );
  void draw_text_ext( double x, double y, const CGMVariable& string,
                      double sep, int w );

  double string_width( const CGMVariable& string );
  double string_height( const CGMVariable& string );
  double string_width_ext( const CGMVariable& string, double sep, double w );
  double string_height_ext( const CGMVariable& string, double sep, double w );

  void draw_text_transformed( double x, double y, const CGMVariable& string,
                              double xscale, double yscale, double angle );
  void draw_text_ext_transformed( double x, double y, const CGMVariable& string,
                                  double sep, double w, double xscale,
                                  double yscale, double angle );
  void draw_text_color( double x, double y, const CGMVariable& string,
                        int c1, int c2, int c3, int c4,
                        double alpha );
  void draw_text_ext_color( double x, double y, const CGMVariable& string,
                            double sep, double w, int c1, int c2,
                            int c3, int c4, double alpha );
  void draw_text_transformed_color( double x, double y, const CGMVariable& string,
                                    double xscale, double yscale, double angle,
                                    int c1, int c2, int c3, int c4,
                                    double alpha );
  void draw_text_ext_transformed_color( double x, double y,
                                        const CGMVariable& string, double sep,
                                        double w, double xscale,
                                        double yscale, double angle, int c1,
                                        int c2, int c3, int c4,
                                        double alpha );

  void draw_point_color( double x, double y, int col1 );
  void draw_line_color( double x1, double y1, double x2, double y2,
                        int col1, int col2 );
  void draw_line_width_color( double x1, double y1, double x2,
                              double y2, double w, int col1, int col2 );
  void draw_rectangle_color( double x1, double y1, double x2, double y2,
                             int col1, int col2, int col3, int col4,
                             bool outline );
  void draw_roundrect_color( double x1, double y1, double x2, double y2,
                             int col1, int col2, bool outline );
  void draw_triangle_color( double x1, double y1, double x2, double y2,
                            double x3, double y3, int col1, int col2,
                            int col3, bool outline );
  void draw_circle_color( double x, double y, double r, int col1,
                          int col2, bool outline );
  void draw_ellipse_color( double x1, double y1, double x2, double y2,
                           int col1, int col2, bool outline );

  void draw_primitive_begin( int kind );
  void draw_vertex( double x, double y );
  void draw_vertex_color( double x, double y, int col, double alpha );
  void draw_primitive_end();

  int sprite_get_texture( int spr, int subimg );
  int background_get_texture( int back );

  void texture_preload( int texid );
  void texture_set_priority( int texid, int prio );
  int texture_get_width( int texid );
  double texture_get_height( int texid );
  void draw_primitive_begin_texture( int kind, int texid );
  void draw_vertex_texture( double x, double y, double xtex,
                            double ytex );
  void draw_vertex_texture_color( double x, double y, double xtex,
                                  double ytex, int col, double alpha );
  void draw_primitive_end();
  void texture_set_interpolation( bool linear );
  void texture_set_blending( bool blend );
  void texture_set_repeat( double repeat );
  void draw_set_blend_mode( int mode );
  void draw_set_blend_mode_ext( int src, int dest );

  int surface_create( int w, int h );
  void surface_free( int id );
  bool surface_exists( int id );
  int surface_get_width( int id );
  int surface_get_height( int id );
  int surface_get_texture( int id );
  void surface_set_target( int id );
  void surface_reset_target();
  int surface_getpixel( int id, int x, int y );
  void surface_save( int id, const CGMVariable& fname );
  void surface_save_part( int id, const CGMVariable& fname, int x, int y,
                          int w, int h );

  void draw_surface( int id, double x, double y );
  void draw_surface_stretched( int id, double x, double y, double w,
                               double h );
  void draw_surface_tiled( int id, double x, double y );
  void draw_surface_part( int id, int left, int top, int width,
                          int height, double x, double y );
  void draw_surface_ext( int id, double x, double y, double xscale,
                         double yscale, double rot, int color,
                         double alpha );
  void draw_surface_stretched_ext( int id, double x, double y, double w,
                                   double h, int color, double alpha );
  void draw_surface_tiled_ext( int id, double x, double y, double xscale,
                               double yscale, int color, double alpha );
  void draw_surface_part_ext( int id, int left, int top, int width,
                              int height, double x, double y,
                              double xscale, double yscale, int color,
                              double alpha );
  void draw_surface_general( int id, int left, int top, int width,
                             int height, double x, double y,
                             double xscale, double yscale, double rot,
                             int c1, int c2, int c3, int c4,
                             double alpha );

  void surface_copy( int destination, double x, double y, int source );
  void surface_copy_part( int destination, double x, double y,
                          int source, double xs, double ys, double ws,
                          double hs );

  int tile_add( int background, int left, int top, int width,
                int height, double x, double y, int depth );
  void tile_delete( int id );
  bool tile_exists( int id );
  double tile_get_x( int id );
  double tile_get_y( int id );
  int tile_get_left( int id );
  int tile_get_top( int id );
  int tile_get_width( int id );
  int tile_get_height( int id );
  int tile_get_depth( int id );
  bool tile_get_visible( int id );
  double tile_get_xscale( int id );
  double tile_get_yscale( int id );
  int tile_get_background( int id );
  int tile_get_blend( int id );
  double tile_get_alpha( int id );
  void tile_set_position( int id, double x, double y );
  void tile_set_region( int id, double left, double top, double width,
                        double height );
  void tile_set_background( int id, int background );
  void tile_set_visible( int id, bool visible );
  void tile_set_depth( int id, int depth );
  void tile_set_scale( int id, double xscale, double yscale );
  void tile_set_blend( int id, int color );
  void tile_set_alpha( int id, double alpha );

  void tile_layer_hide( int depth );
  void tile_layer_show( int depth );
  void tile_layer_delete( int depth );
  void tile_layer_shift( int depth, double x, double y );
  int tile_layer_find( int depth, double x, double y );
  void tile_layer_delete_at( int depth, double x, double y );
  void tile_layer_depth( int depth, int newdepth );

  int display_get_width();
  int display_get_height();
  int display_get_colordepth();
  int display_get_frequency();
  void display_set_size( int w, int h );
  void display_set_colordepth( int coldepth );
  void display_set_frequency( int frequency );
  void display_set_all( int w, int h, int frequency, int coldepth );
  bool display_test_all( int w, int h, int frequency, int coldepth );
  void display_reset();

  int display_mouse_get_x();
  int display_mouse_get_y();
  void display_mouse_set( int x, int y );

  void window_set_visible( bool visible );
  bool window_get_visible();
  void window_set_fullscreen( bool full );
  bool window_get_fullscreen();
  void window_set_showborder( bool show );
  bool window_get_showborder();
  void window_set_showicons( bool show );
  bool window_get_showicons();
  void window_set_stayontop( bool stay );
  bool window_get_stayontop();
  void window_set_sizeable( bool sizeable );
  bool window_get_sizeable();
  void window_set_caption( const CGMVariable& caption );
  CGMVariable window_get_caption();
  void window_set_cursor( int curs );
  int window_get_cursor();
  void window_set_color( int color );
  int window_get_color();
  void window_set_region_scale( double scale, bool adaptwindow );
  double window_get_region_scale();
  void window_set_position( int x, int y );
  void window_set_size( int w, int h );
  void window_set_rectangle( int x, int y, int w, int h );
  void window_center();
  void window_default();
  int window_get_x();
  int window_get_y();
  int window_get_width();
  int window_get_height();
  int window_mouse_get_x();
  int window_mouse_get_y();
  void window_mouse_set( int x, int y );
  void window_set_region_size( int w, int h, bool adaptwindow );
  int window_get_region_width();
  int window_get_region_height();
  int window_view_mouse_get_x( int id );
  int window_view_mouse_get_y( int id );
  void window_view_mouse_set( int id, int x, int y );
  int window_views_mouse_get_x();
  int window_views_mouse_get_y();
  void window_views_mouse_set( int x, int y );

  void screen_redraw();
  void screen_refresh();

  void set_automatic_draw( bool value );
  void set_synchronization( bool value );
  void screen_wait_vsync();

  HWND window_handle();
}
