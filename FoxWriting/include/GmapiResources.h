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
/*  GmapiResources.h                                                    */
/*   - Wrapped GM functions; Parser-generated code                      */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once
#include "GmapiInternal.h"

namespace gm {
  CGMVariable script_execute( int ind, const CGMVariable* aArguments = NULL,
                              int aArgCount = 0 );
  CGMVariable execute_string( const CGMVariable& str, const CGMVariable* aArguments = NULL,
                              int aArgCount = 0 );
  CGMVariable execute_file( const CGMVariable& fname, const CGMVariable* aArguments = NULL,
                             int aArgCount = 0 );

  int external_define( const CGMVariable& dll, const CGMVariable& name, int calltype,
                       int restype, int argnumb, const int* aArgTypes );
  CGMVariable external_call( int id, const CGMVariable* aArguments, int aArgCount );
  void external_free( const CGMVariable& dll );

  void sprite_set_offset( int ind, int xoff, int yoff );
  void sprite_set_bbox_mode( int ind, int mode );
  void sprite_set_bbox( int ind, int left, int top, int right,
                        int bottom );
  void sprite_set_precise( int ind, bool mode );
  int sprite_duplicate( int ind );
  void sprite_assign( int ind, int spr );
  void sprite_merge( int ind1, int ind2 );

  /// GM6/GM7 version
  int sprite_add( const CGMVariable& fname, int imgnumb, bool precise,
                  bool transparent, bool smooth, bool preload,
                  int xorig, int yorig );

  /// GM8 version
  int sprite_add( const CGMVariable& fname, int imgnumb, bool removeback,
                  bool smooth, int xorig, int yorig );

  int sprite_add_sprite( const CGMVariable& fname );
  int sprite_add_alpha( const CGMVariable& fname, int imgnumb, bool precise,
                        bool preload, int xorig, int yorig );

  /// GM6/GM7 version
  void sprite_replace( int ind, const CGMVariable& fname, int imgnumb,
                       bool precise, bool transparent, bool smooth,
                       bool preload, int xorig, int yorig );

  /// GM8 version
  void sprite_replace( int ind, const CGMVariable& fname, int imgnumb,
                       bool removeback, bool smooth, int xorig,
                       int yorig );

  void sprite_replace_sprite( int ind, const CGMVariable& fname );
  void sprite_replace_alpha( int ind, const CGMVariable& fname, int imgnumb,
                             bool precise, bool preload, int xorig,
                             int yorig );

  /// GM6/GM7 version
  int sprite_create_from_screen( int x, int y, int w, int h,
                                 bool precise, bool transparent,
                                 bool smooth, bool preload, int xorig,
                                 int yorig );

  /// GM8 version
  int sprite_create_from_screen( int x, int y, int w, int h,
                                 bool removeback, bool smooth, int xorig,
                                 int yorig );

  /// GM6/GM7 version
  void sprite_add_from_screen( int ind, int x, int y, int w,
                               int h );

  /// GM8 version
  void sprite_add_from_screen( int ind, int x, int y, int w,
                               int h, bool removeback, bool smooth );

  /// GM6/GM7 version
  int sprite_create_from_surface( int id, int x, int y, int w,
                                  int h, bool precise, bool transparent,
                                  bool smooth, bool preload, int xorig,
                                  int yorig );

  /// GM8 version
  int sprite_create_from_surface( int id, int x, int y, int w,
                                  int h, bool removeback, bool smooth,
                                  int xorig, int yorig );

  /// GM6/GM7 version
  void sprite_add_from_surface( int ind, int id, int x, int y,
                                int w, int h );

  /// GM8 version
  void sprite_add_from_surface( int ind, int id, int x, int y,
                                int w, int h, bool removeback, bool smooth );

  void sprite_delete( int ind );
  void sprite_set_alpha_from_sprite( int ind, int spr );
  void sprite_collision_mask( int ind,  bool sepmasks, int bboxmode,
                              int bbleft, int bbright, int bbtop,
                              int bbbottom, int kind, int tolerance );

  int sound_add( const CGMVariable& fname, int kind, bool preload );
  void sound_replace( int index, const CGMVariable& fname, int kind,
                      bool preload );
  void sound_delete( int index );

  int background_duplicate( int ind );
  void background_assign( int ind, int back );

  /// GM6/GM7 version
  int background_add( const CGMVariable& fname, bool transparent, bool smooth,
                      bool preload );

  /// GM8 version
  int background_add( const CGMVariable& fname, bool removeback, bool smooth );

  int background_add_background( const CGMVariable& fname );
  int background_add_alpha( const CGMVariable& fname, bool preload );

  /// GM6/GM7 version
  void background_replace( int ind, const CGMVariable& fname, bool transparent,
                           bool smooth, bool preload );

  /// GM8 version
  void background_replace( int ind, const CGMVariable& fname, bool removeback,
                           bool smooth );

  void background_replace_background( int ind, const CGMVariable& fname );
  void background_replace_alpha( int ind, const CGMVariable& fname, bool preload );

  /// GM6/GM7 version
  int background_create_color( int w, int h, int col, bool preload );

  /// GM8 version
  int background_create_color( int w, int h, int col );

  /// GM6/GM7 version
  int background_create_gradient( int w, int h, int col1, int col2,
                                  int kind, bool preload );

  /// GM8 version
  int background_create_gradient( int w, int h, int col1, int col2,
                                  int kind );

  /// GM6/GM7 version
  int background_create_from_screen( int x, int y, int w, int h,
                                     bool transparent, bool smooth,
                                     bool preload );
  /// GM8 version
  int background_create_from_screen( int x, int y, int w, int h,
                                     bool removeback, bool smooth );

  /// GM6/GM7 version
  int background_create_from_surface( int id, int x, int y, int w,
                                      int h, bool transparent, bool smooth,
                                      bool preload );

  /// GM8 version
  int background_create_from_surface( int id, int x, int y, int w,
                                      int h, bool removeback, bool smooth );

  void background_delete( int ind );
  void background_set_alpha_from_background( int ind, int back );

  int font_add( const CGMVariable& name, int size, bool bold, bool italic,
                int first, int last );
  int font_add_sprite( int spr, int first, bool prop, int sep );
  void font_replace( int ind, const CGMVariable& name, int size, bool bold,
                     bool italic, int first, int last );
  void font_replace_sprite( int ind, int spr, int first, bool prop,
                            int sep );
  void font_delete( int ind );

  void path_set_kind( int ind, int val );
  void path_set_closed( int ind, bool closed );
  void path_set_precision( int ind, int prec );
  int path_add();
  void path_delete( int ind );
  int path_duplicate( int ind );
  void path_assign( int ind, int path );
  void path_append( int ind, int path );
  void path_add_point( int ind, double x, double y, double speed );
  void path_insert_point( int ind, int n, double x, double y,
                          double speed );
  void path_change_point( int ind, int n, double x, double y,
                          double speed );
  void path_delete_point( int ind, int n );
  void path_clear_points( int ind );
  void path_reverse( int ind );
  void path_mirror( int ind );
  void path_flip( int ind );
  void path_rotate( int ind, double angle );
  void path_scale( int ind, double xscale, double yscale );
  void path_shift( int ind, double xshift, double yshift );

  int timeline_add();
  void timeline_delete( int ind );
  void timeline_moment_add( int ind, int step, const CGMVariable& codestr );
  void timeline_moment_clear( int ind, int step );
  void timeline_clear( int ind );

  void object_set_sprite( int ind, int spr );
  void object_set_solid( int ind, bool solid );
  void object_set_visible( int ind, bool vis );
  void object_set_depth( int ind, int depth );
  void object_set_persistent( int ind, bool pers );
  void object_set_mask( int ind, int spr );
  void object_set_parent( int ind, int obj );
  int object_add();
  void object_delete( int ind );
  void object_event_add( int ind, int evtype, int evnumb,
                         const CGMVariable& codestr );
  void object_event_clear( int ind, int evtype, int evnumb );

  void room_set_width( int ind, int w );
  void room_set_height( int ind, int h );
  void room_set_caption( int ind, const CGMVariable& str );
  void room_set_persistent( int ind, bool val );
  void room_set_code( int ind, const CGMVariable& str );
  void room_set_background_color( int ind, int col, bool show );
  void room_set_background( int ind, int bind, bool vis, bool fore,
                            int back, int x, int y, bool htiled,
                            bool vtiled, double hspeed, double vspeed,
                            double alpha );
  void room_set_view( int ind, int vind, bool vis, int xview,
                      int yview, int wview, int hview, int xport,
                      int yport, int wport, int hport, int hborder,
                      int vborder, double hspeed, double vspeed,
                      int obj );
  void room_set_view_enabled( int ind, int val );
  int room_add();
  void room_duplicate( int ind );
  void room_assign( int ind, int room );
  int room_instance_add( int ind, double x, double y, int obj );
  void room_instance_clear( int ind );
  int room_tile_add( int ind, int back, int left, int top,
                     int width, int height, double x, double y,
                     int depth );
  int room_tile_add_ext( int ind, int back, int left, int top,
                         int width, int height, double x, double y,
                         int depth, double xscale, double yscale,
                         double alpha );
  void room_tile_clear( int ind );

  bool sprite_exists( int ind );
  CGMVariable sprite_get_name( int ind );
  int sprite_get_number( int ind );
  int sprite_get_width( int ind );
  int sprite_get_height( int ind );
  bool sprite_get_transparent( int ind );
  bool sprite_get_smooth( int ind );
  bool sprite_get_preload( int ind );
  int sprite_get_xoffset( int ind );
  int sprite_get_yoffset( int ind );
  int sprite_get_bbox_left( int ind );
  int sprite_get_bbox_right( int ind );
  int sprite_get_bbox_top( int ind );
  int sprite_get_bbox_bottom( int ind );
  int sprite_get_bbox_mode( int ind );
  bool sprite_get_precise( int ind );
  void sprite_save( int ind, int subimg, const CGMVariable& fname );
  void sprite_save_strip( int ind, const CGMVariable& fname );

  bool sound_exists( int ind );
  CGMVariable sound_get_name( int ind );
  int sound_get_kind( int ind );
  bool sound_get_preload( int ind );
  void sound_discard( int index );
  void sound_restore( int index );

  bool background_exists( int ind );
  CGMVariable background_get_name( int ind );
  int background_get_width( int ind );
  int background_get_height( int ind );
  bool background_get_transparent( int ind );
  bool background_get_smooth( int ind );
  bool background_get_preload( int ind );
  void background_save( int ind, const CGMVariable& fname );

  bool font_exists( int ind );
  CGMVariable font_get_name( int ind );
  CGMVariable font_get_fontname( int ind );
  bool font_get_bold( int ind );
  bool font_get_italic( int ind );
  int font_get_first( int ind );
  int font_get_last( int ind );

  bool path_exists( int ind );
  CGMVariable path_get_name( int ind );
  int path_get_length( int ind );
  int path_get_kind( int ind );
  bool path_get_closed( int ind );
  int path_get_precision( int ind );
  int path_get_number( int ind );
  double path_get_point_x( int ind, int n );
  double path_get_point_y( int ind, int n );
  double path_get_point_speed( int ind, int n );
  double path_get_x( int ind, double pos );
  double path_get_y( int ind, double pos );
  double path_get_speed( int ind, double pos );

  bool script_exists( int ind );
  CGMVariable script_get_name( int ind );
  CGMVariable script_get_text( int ind );

  bool timeline_exists( int ind );
  CGMVariable timeline_get_name( int ind );

  bool object_exists( int ind );
  CGMVariable object_get_name( int ind );
  int object_get_sprite( int ind );
  bool object_get_solid( int ind );
  bool object_get_visible( int ind );
  int object_get_depth( int ind );
  bool object_get_persistent( int ind );
  int object_get_mask( int ind );
  int object_get_parent( int ind );
  bool object_is_ancestor( int ind1, int ind2 );

  bool room_exists( int ind );
  CGMVariable room_get_name( int ind );

}
