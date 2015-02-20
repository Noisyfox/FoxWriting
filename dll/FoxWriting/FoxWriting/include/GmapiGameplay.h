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
/*  GmapiGameplay.h                                                     */
/*   - Wrapped GM functions; Parser-generated code                      */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once
#include "GmapiInternal.h"

namespace gm {

  bool place_free( double x, double y );
  bool place_empty( double x, double y );
  bool place_meeting( double x, double y, int obj );
  bool place_snapped( double hsnap, double vsnap );

  void move_random( double hsnap, double vsnap );
  void move_snap( double hsnap, double vsnap );
  void move_wrap( double hor, double vert, double margin );
  void move_towards_point( double x, double y, double sp );
  void move_bounce_solid( bool adv );
  void move_bounce_all( bool adv );
  void move_contact_solid( double dir, double maxdist );
  void move_contact_all( double dir, double maxdist );
  void move_outside_solid( double dir, double maxdist );
  void move_outside_all( double dir, double maxdist );

  void distance_to_point( double x, double y );
  void distance_to_object( int obj );

  bool position_empty( double x, double y );
  bool position_meeting( double x, double y, int obj );

  void path_start( int path, double speed, int endaction,
                   bool absolute );
  void path_end();

  bool mp_linear_step( double x, double y, double stepsize,
                       bool checkall );
  bool mp_linear_step_object( double x, double y, double stepsize,
                              int obj );
  bool mp_potential_step( double x, double y, double stepsize,
                          bool checkall );
  bool mp_potential_step_object( double x, double y, double stepsize,
                                 int obj );
  void mp_potential_settings( double maxrot, double rotstep,
                              int ahead, bool onspot );
  bool mp_linear_path( int path, double xg, double yg,
                       double stepsize, bool checkall );
  bool mp_linear_path_object( int path, double xg, double yg,
                              double stepsize, int obj );
  bool mp_potential_path( int path, double xg, double yg,
                          double stepsize, int factor,
                          bool checkall );
  bool mp_potential_path_object( int path, double xg, double yg,
                                 double stepsize, int factor,
                                 int obj );
  int mp_grid_create( double left, double top, int hcells,
                      int vcells, double cellwidth, double cellheight );
  void mp_grid_destroy( int id );
  void mp_grid_clear_all( int id );
  void mp_grid_clear_cell( int id, int h, int v );
  void mp_grid_clear_rectangle( int id, double left, double top,
                                double right, double bottom );
  void mp_grid_add_cell( int id, int h, int v );
  void mp_grid_add_rectangle( int id, double left, double top,
                              double right, double bottom );
  void mp_grid_add_instances( int id, int obj, bool prec );
  bool mp_grid_path( int id, int path, double xstart,
                     double ystart, double xgoal, double ygoal,
                     bool allowdiag );
  void mp_grid_draw( int id );

  bool collision_point( double x, double y, int obj,
                        bool prec, bool notme );
  bool collision_rectangle( double x1, double y1, double x2,
                            double y2, int obj,
                            bool prec, bool notme );
  bool collision_circle( double xc, double yc, double radius,
                            bool prec, bool notme );
  bool collision_ellipse( double x1, double y1, double x2,
                          double y2, int obj,
                          bool prec, bool notme );
  bool collision_line( double x1, double y1, double x2,
                       double y2, int obj,
                       bool prec, bool notme );

  int instance_find( int obj, int n );
  bool instance_exists( int obj );
  int instance_number( int obj );
  int instance_position( double x, double y, int obj );
  int instance_nearest( double x, double y, int obj );
  int instance_furthest( double x, double y, int obj );
  int instance_place( double x, double y, int obj );
  int instance_create( double x, double y, int obj );
  int instance_copy( bool performevent );
  void instance_destroy();
  void instance_change( int obj, bool perf );
  void position_destroy( double x, double y );
  void position_change( double x, double y, int obj, bool perf );
  void instance_deactivate_all( bool notme );
  void instance_deactivate_object( int obj );
  void instance_deactivate_region( double left, double top,
                                   double width, double height,
                                   bool inside, bool notme );
  void instance_activate_all();
  void instance_activate_object( int obj );
  void instance_activate_region( double left, double top,
                                 double width, double height,
                                 bool inside );

  void room_goto( int numb );
  void room_goto_previous();
  void room_goto_next();
  void room_restart();
  int room_previous( int numb );
  int room_next( int numb );

  void game_end();
  void game_restart();
  void game_save( const CGMVariable& string );
  void game_load( const CGMVariable& string );

  void transition_define( int kind, const CGMVariable& name );
  bool transition_exists( int kind );

  void event_perform( int type, int numb );
  void event_perform_object( int obj, int type, int numb );
  void event_user( int numb );
  void event_inherited();

  void show_debug_message( const CGMVariable& str );

  bool variable_global_exists( const CGMVariable& name );
  bool variable_local_exists( const CGMVariable& name );
  CGMVariable variable_global_get( const CGMVariable& name );
  CGMVariable variable_global_array_get( const CGMVariable& name, int ind );
  CGMVariable variable_global_array2_get( const CGMVariable& name, int ind1,
                                          int ind2 );
  CGMVariable variable_local_get( const CGMVariable& name );
  CGMVariable variable_local_array_get( const CGMVariable& name, int ind );
  CGMVariable variable_local_array2_get( const CGMVariable& name, int ind1,
                                         int ind2 );
  void variable_global_set( const CGMVariable& name, const CGMVariable& value );
  void variable_global_array_set( const CGMVariable& name, int ind,
                                  const CGMVariable& value );
  void variable_global_array2_set( const CGMVariable& name, int ind1,
                                   int ind2, const CGMVariable& value );
  void variable_local_set( const CGMVariable& name, const CGMVariable& value );
  void variable_local_array_set( const CGMVariable& name, int ind,
                                 const CGMVariable& value );
  void variable_local_array2_set( const CGMVariable& name, int ind1,
                                  int ind2, const CGMVariable& value );

  void set_program_priority( int priority );
  void set_application_title( const CGMVariable& title );

}
