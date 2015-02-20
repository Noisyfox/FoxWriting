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
/*  GmapiDataStructures.h                                               */
/*   - Wrapped GM functions; Parser-generated code                      */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once
#include "GmapiInternal.h"

namespace gm {

  void ds_set_precision( double prec );

  int ds_list_create();
  void ds_list_destroy( int id );

  void ds_list_clear( int id );
  void ds_list_copy( int id, int source );
  int ds_list_size( int id );
  bool ds_list_empty( int id );

  void ds_list_add( int id, const CGMVariable& val );
  void ds_list_insert( int id, int pos, const CGMVariable& val );
  void ds_list_replace( int id, int pos, const CGMVariable& val );
  void ds_list_delete( int id, int pos );

  int ds_list_find_index( int id, const CGMVariable& val );
  CGMVariable ds_list_find_value( int id, int pos );

  void ds_list_sort( int id, int ascend );
  void ds_list_shuffle( int id );

  CGMVariable ds_list_write( int id );
  void ds_list_read( int id, const CGMVariable& str );

  int ds_stack_create();
  void ds_stack_destroy( int id );
  void ds_stack_clear( int id );
  void ds_stack_copy( int id, int source );
  int ds_stack_size( int id );
  bool ds_stack_empty( int id );
  void ds_stack_push( int id, const CGMVariable& val );
  CGMVariable ds_stack_pop( int id );
  CGMVariable ds_stack_top( int id );
  CGMVariable ds_stack_write( int id );
  void ds_stack_read( int id, const CGMVariable& str );

  int ds_queue_create();
  void ds_queue_destroy( int id );
  void ds_queue_clear( int id );
  void ds_queue_copy( int id, int source );
  int ds_queue_size( int id );
  bool ds_queue_empty( int id );
  void ds_queue_enqueue( int id, const CGMVariable& val );
  CGMVariable ds_queue_dequeue( int id );
  CGMVariable ds_queue_head( int id );
  CGMVariable ds_queue_tail( int id );
  CGMVariable ds_queue_write( int id );
  void ds_queue_read( int id, const CGMVariable& str );

  int ds_map_create();
  void ds_map_destroy( int id );
  void ds_map_clear( int id );
  void ds_map_copy( int id, int source );
  int ds_map_size( int id );
  bool ds_map_empty( int id );
  void ds_map_add( int id, const CGMVariable& key, const CGMVariable& val );
  void ds_map_replace( int id, const CGMVariable& key, const CGMVariable& val );
  void ds_map_delete( int id, const CGMVariable& key );
  bool ds_map_exists( int id, const CGMVariable& key );
  CGMVariable ds_map_find_value( int id, const CGMVariable& key );
  CGMVariable ds_map_find_previous( int id, const CGMVariable& key );
  CGMVariable ds_map_find_next( int id, const CGMVariable& key );
  CGMVariable ds_map_find_first( int id );
  CGMVariable ds_map_find_last( int id );
  CGMVariable ds_map_write( int id );
  void ds_map_read( int id, const CGMVariable& str );

  int ds_priority_create();
  void ds_priority_destroy( int id );
  void ds_priority_clear( int id );
  void ds_priority_copy( int id, int source );
  int ds_priority_size( int id );
  bool ds_priority_empty( int id );
  void ds_priority_add( int id, const CGMVariable& val, int prio );
  void ds_priority_change_priority( int id, const CGMVariable& val,
                                    int prio );
  int ds_priority_find_priority( int id, const CGMVariable& val );
  void ds_priority_delete_value( int id, const CGMVariable& val );
  CGMVariable ds_priority_delete_min( int id );
  CGMVariable ds_priority_find_min( int id );
  CGMVariable ds_priority_delete_max( int id );
  CGMVariable ds_priority_find_max( int id );
  CGMVariable ds_priority_write( int id );
  void ds_priority_read( int id, const CGMVariable& str );

  int ds_grid_create( int w, int h );
  void ds_grid_destroy( int id );
  void ds_grid_delete( int id );
  void ds_grid_copy( int id, int source );
  void ds_grid_resize( int id, int w, int h );
  int ds_grid_width( int id );
  int ds_grid_height( int id );
  void ds_grid_clear( int id, const CGMVariable& val );
  void ds_grid_set( int id, int x, int y, const CGMVariable& val );
  void ds_grid_add( int id, int x, int y, const CGMVariable& val );
  void ds_grid_multiply( int id, int x, int y, const CGMVariable& val );
  void ds_grid_set_region( int id, int x1, int y1, int x2,
                           int y2, const CGMVariable& val );
  void ds_grid_add_region( int id, int x1, int y1, int x2,
                           int y2, const CGMVariable& val );
  void ds_grid_multiply_region( int id, int x1, int y1, int x2,
                                int y2, const CGMVariable& val );
  void ds_grid_set_disk( int id, int xm, int ym, int r,
                         const CGMVariable& val );
  void ds_grid_add_disk( int id, int xm, int ym, int r,
                         const CGMVariable& val );
  void ds_grid_multiply_disk( int id, int xm, int ym, int r,
                         const CGMVariable& val );
  void ds_grid_set_grid_region( int id, int source, int x1, int y1,
                                int x2, int y2, int xpos, int ypos );
  void ds_grid_add_grid_region( int id, int source, int x1, int y1,
                                int x2, int y2, int xpos, int ypos );
  void ds_grid_multiply_grid_region( int id, int source, int x1, int y1,
                                     int x2, int y2, int xpos, int ypos );
  CGMVariable ds_grid_get( int id, int x, int y );
  double ds_grid_get_sum( int id, int x1, int y1, int x2,
                          int y2 );
  double ds_grid_get_max( int id, int x1, int y1, int x2,
                          int y2 );
  double ds_grid_get_min( int id, int x1, int y1, int x2,
                          int y2 );
  double ds_grid_get_mean( int id, int x1, int y1, int x2,
                           int y2 );
  double ds_grid_get_disk_sum( int id, int xm, int ym, int r );
  double ds_grid_get_disk_min( int id, int xm, int ym, int r );
  double ds_grid_get_disk_max( int id, int xm, int ym, int r );
  double ds_grid_get_disk_mean( int id, int xm, int ym, int r );
  double ds_grid_get_min( int id, int x1, int y1, int x2,
                          int y2 );
  bool ds_grid_value_exists( int id, int x1, int y1, int x2,
                             int y2, const CGMVariable& val );
  int ds_grid_value_x( int id, int x1, int y1, int x2,
                       int y2, const CGMVariable& val );
  int ds_grid_value_y( int id, int x1, int y1, int x2,
                       int y2, const CGMVariable& val );
  bool ds_grid_value_disk_exists( int id, int xm, int ym, int r,
                                  const CGMVariable& val );
  int ds_grid_value_disk_x( int id, int xm, int ym, int r,
                            const CGMVariable& val );
  int ds_grid_value_disk_y( int id, int xm, int ym, int r,
                            const CGMVariable& val );
  void ds_grid_shuffle( int id );
  CGMVariable ds_grid_write( int id );
  void ds_grid_read( int id, const CGMVariable& str );

}
