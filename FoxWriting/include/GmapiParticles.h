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
/*  GmapiParticles.h                                                    */
/*   - Wrapped GM functions; Parser-generated code                      */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once
#include "GmapiInternal.h"

namespace gm {

  void effect_create_below( int kind, double x, double y, int size,
                            int color );
  void effect_create_above( int kind, double x, double y, int size,
                            int color );
  void effect_clear();
  int part_type_create();
  void part_type_destroy( int ind );
  bool part_type_exists( int ind );
  void part_type_clear( int ind );
  void part_type_shape( int ind, int shape );
  void part_type_sprite( int ind, int sprite, bool animat, bool stretch,
                         bool random );
  void part_type_size( int ind, double size_min, double size_max,
                       double size_incr, double size_wiggle );
  void part_type_scale( int ind, double xscale, double yscale );
  void part_type_orientation( int ind, double ang_min, double ang_max,
                              double ang_incr, double ang_wiggle,
                              bool ang_relative );
  void part_type_color1( int ind, int color1 );
  void part_type_color2( int ind, int color1, int color2 );
  void part_type_color3( int ind, int color1, int color2, int color3 );
  void part_type_color_mix( int ind, int color1, int color2 );
  void part_type_color_rgb( int ind, int rmin, int rmax, int gmin,
                            int gmax, int bmin, int bmax );
  void part_type_color_hsv( int ind, int hmin, int hmax, int smin,
                            int smax, int vmin, int vmax );
  void part_type_alpha1( int ind, double alpha1 );
  void part_type_alpha2( int ind, double alpha1, double alpha2 );
  void part_type_alpha3( int ind, double alpha1, double alpha2,
                         double alpha3 );
  void part_type_blend( int ind, bool additive );
  void part_type_life( int ind, double life_min, double life_max );
  void part_type_step( int ind, int step_number, int step_type );
  void part_type_death( int ind, int death_number, int death_type );
  void part_type_speed( int ind, double speed_min, double speed_max,
                        double speed_incr, double speed_wiggle );
  void part_type_direction( int ind, double dir_min, double dir_max,
                            double dir_incr, double dir_wiggle );
  void part_type_gravity( int ind, double grav_amount, double grav_dir );
  int part_system_create();
  void part_system_destroy( int ind );
  bool part_system_exists( int ind );
  void part_system_clear( int ind );
  void part_system_draw_order( int ind, bool oldtonew );
  void part_system_depth( int ind, int depth );
  void part_system_position( int ind, double x, double y );
  void part_system_automatic_update( int ind, bool automatic );
  void part_system_automatic_draw( int ind, bool automatic );
  void part_system_update( int ind );
  void part_system_drawit( int ind );
  void part_particles_create( int ind, double x, double y, int parttype,
                              int number );
  void part_particles_create_color( int ind, double x, double y,
                                    int parttype, int color, int number );
  void part_particles_clear( int ind );
  int part_particles_count( int ind );
  int part_emitter_create( int ps );
  void part_emitter_destroy( int ps, int ind );
  void part_emitter_destroy_all( int ps );
  bool part_emitter_exists( int ps, int ind );
  void part_emitter_clear( int ps, int ind );
  void part_emitter_region( int ps, int ind, double xmin, double xmax,
                            double ymin, double ymax, int shape,
                            int distribution );
  void part_emitter_burst( int ps, int ind, int parttype, int number );
  void part_emitter_stream( int ps, int ind, int parttype, int number );
  int part_attractor_create( int ps );
  void part_attractor_destroy( int ps, int ind );
  void part_attractor_destroy_all( int ps );
  bool part_attractor_exists( int ps, int ind );
  void part_attractor_clear( int ps, int ind );
  void part_attractor_position( int ps, int ind, double x, double y );
  void part_attractor_force( int ps, int ind, double force, int dist,
                             int kind, bool aditive );
  int part_destroyer_create( int ps );
  void part_destroyer_destroy( int ps, int ind );
  void part_destroyer_destroy_all( int ps );
  bool part_destroyer_exists( int ps, int ind );
  void part_destroyer_clear( int ps, int ind );
  int part_destroyer_region( int ps, int ind, double xmin, double xmax,
                             double ymin, double ymax, int shape );
  int part_attractor_create( int ps );
  void part_deflector_destroy( int ps, int ind );
  void part_deflector_destroy_all( int ps );
  bool part_deflector_exists( int ps, int ind );
  void part_deflector_clear( int ps, int ind );
  void part_deflector_region( int ps, int ind, double xmin, double xmax,
                              double ymin, double ymax );
  void part_deflector_kind( int ps, int ind, int kind );
  void part_deflector_friction( int ps, int ind, double friction );
  int part_changer_create( int ps );
  void part_changer_destroy( int ps, int ind );
  void part_changer_destroy_all( int ps );
  bool part_changer_exists( int ps, int ind );
  void part_changer_clear( int ps, int ind );
  void part_changer_region( int ps, int ind, double xmin, double xmax,
                            double ymin, double ymax, int shape );
  void part_changer_types( int ps, int ind, int parttype1,
                           int parttype2 );
  void part_changer_kind( int ps, int ind, int kind );

}
