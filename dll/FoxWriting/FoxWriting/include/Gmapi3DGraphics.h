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
/*  Gmapi3DGraphics.h                                                   */
/*   - Wrapped GM functions; Parser-generated code                      */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once
#include "GmapiInternal.h"

namespace gm {

  bool d3d_start();
  bool d3d_end();
  void d3d_set_hidden( bool enable );
  void d3d_set_perspective( bool enable );
  void d3d_set_culling( bool enable );
  void d3d_set_depth( int depth );
  void d3d_primitive_begin( int kind );
  void d3d_vertex( double x, double y, double z );
  void d3d_vertex_color( double x, double y, double z, int col, double alpha );
  void d3d_primitive_end();
  void d3d_primitive_begin_texture( int kind, int texid );
  void d3d_vertex_texture( double x, double y, double z, double xtex, double ytex );
  void d3d_vertex_texture_color( double x, double y, double z,  double xtex, double ytex,
                                 int col, double alpha );

  void d3d_draw_block( double x1, double y1, double z1, double x2, double y2, double z2, 
                       int texid, double hrepeat, double vrepeat );
  void d3d_draw_cylinder( double x1, double y1, double z1, double x2, double y2,
                          double z2, int texid, double hrepeat, double vrepeat,
                          bool closed, int steps );
  void d3d_draw_cone( double x1, double y1, double z1, double x2, double y2, double z2,
                      int texid, double hrepeat, double vrepeat, bool closed, int steps );
  void d3d_draw_ellipsoid( double x1, double y1, double z1, double x2, double y2, 
                           double z2, int texid, double hrepeat, double vrepeat,
                           int steps );
  void d3d_draw_wall( double x1, double y1, double z1, double x2, double y2, double z2,
                      int texid, double hrepeat, double vrepeat );
  void d3d_draw_floor( double x1, double y1, double z1, double x2, double y2, double z2,
                       int texid, double hrepeat, double vrepeat );
  void d3d_set_projection( double xfrom, double yfrom, double zfrom, double xto, 
                           double yto, double zto, double xup, double yup, double zup );
  void d3d_set_projection_ext( double xfrom, double yfrom, double zfrom, double xto, 
                               double yto, double zto, double xup, double yup, double zup,
                               double angle, double aspect, double znear, double zfar );
  void d3d_set_projection_ortho( double x, double y, double w, double h, double angle );
  void d3d_set_projection_perspective( double x, double y, double w, double h,
                                       double angle );
  void d3d_transform_set_identity();
  void d3d_transform_set_translation( double xt, double yt, double zt );
  void d3d_transform_set_scaling( double xs, double ys, double zs );
  void d3d_transform_set_rotation_x( double angle );
  void d3d_transform_set_rotation_y( double angle );
  void d3d_transform_set_rotation_z( double angle );
  void d3d_transform_set_rotation_axis( double xa, double ya, double za, double angle );
  void d3d_transform_add_translation( double xt, double yt, double zt );
  void d3d_transform_add_scaling( double xs, double ys, double zs );
  void d3d_transform_add_rotation_x( double angle );
  void d3d_transform_add_rotation_y( double angle );
  void d3d_transform_add_rotation_z( double angle );
  void d3d_transform_add_rotation_axis( double xa, double ya, double za, double angle );
  void d3d_transform_stack_clear();
  bool d3d_transform_stack_empty();
  bool d3d_transform_stack_push();
  bool d3d_transform_stack_pop();
  bool d3d_transform_stack_top();
  bool d3d_transform_stack_discard();
  void d3d_set_fog( bool enable, int color, double start, double end );
  void d3d_set_lighting( bool enable );
  void d3d_set_shading( bool smooth );
  void d3d_light_define_direction( int ind, double dx, double dy,
                                   double dz, int col );
  void d3d_light_define_point( int ind, double x, double y, double z,
                               double range, int col );
  void d3d_light_enable( int ind, bool enable );
  void d3d_vertex_normal( double x, double y, double z, double nx,
                          double ny, double nz );
  void d3d_vertex_normal_color( double x, double y, double z, double nx,
                                double ny, double nz, int col,
                                double alpha );
  void d3d_vertex_normal_texture( double x, double y, double z,
                                  double nx, double ny, double nz,
                                  double xtex, double ytex );
  void d3d_vertex_normal_texture_color( double x, double y, double z,
                                        double nx, double ny, double nz,
                                        double xtex, double ytex, int col,
                                        double alpha );
  int d3d_model_create();
  void d3d_model_destroy( int ind );
  void d3d_model_clear( int ind );
  void d3d_model_save( int ind, const CGMVariable& fname );
  void d3d_model_load( int ind, const CGMVariable& fname );
  void d3d_model_draw( int ind, double x, double y, double z,
                       int texid );
  void d3d_model_primitive_begin( int ind, int kind );
  void d3d_model_vertex( int ind, double x, double y, double z );
  void d3d_model_vertex_color( int ind, double x, double y, double z,
                               int col, double alpha );
  void d3d_model_vertex_texture( int ind, double x, double y, double z,
                                 double xtex, double ytex );
  void d3d_model_vertex_texture_color( int ind, double x, double y,
                                       double z, double xtex, double ytex,
                                       int col, double alpha );
  void d3d_model_vertex_normal( int ind, double x, double y, double z,
                                double nx, double ny, double nz );
  void d3d_model_vertex_normal_color( int ind, double x, double y,
                                      double z, double nx, double ny,
                                      double nz, int col, double alpha );
  void d3d_model_vertex_normal_texture( int ind, double x, double y,
                                        double z, double nx, double ny,
                                        double nz, double xtex, double ytex );
  void d3d_model_vertex_normal_texture_color( int ind, double x, double y,
                                              double z, double nx, double ny,
                                              double nz, double xtex,
                                              double ytex, int col,
                                              double alpha );
  void d3d_model_primitive_end( int ind );
  void d3d_model_block( int ind, double x1, double y1, double z1,
                        double x2, double y2, double z2, double hrepeat,
                        double vrepeat );
  void d3d_model_cylinder( int ind, double x1, double y1, double z1,
                           double x2, double y2, double z2,
                           double hrepeat, double vrepeat, bool closed,
                           int steps );
  void d3d_model_cone( int ind, double x1, double y1, double z1,
                       double x2, double y2, double z2, double hrepeat,
                       double vrepeat, bool closed, int steps );
  void d3d_model_ellipsoid( int ind, double x1, double y1, double z1,
                            double x2, double y2, double z2,
                            double hrepeat, double vrepeat, int steps );
  void d3d_model_wall( int ind, double x1, double y1, double z1,
                       double x2, double y2, double z2, double hrepeat, double vrepeat );
  void d3d_model_floor( int ind, double x1, double y1, double z1,
                        double x2, double y2, double z2, double hrepeat,
                        double vrepeat );

}
