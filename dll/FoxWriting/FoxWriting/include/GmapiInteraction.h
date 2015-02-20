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
/*  GmapiInteraction.h                                                  */
/*   - Wrapped GM functions; Parser-generated code                      */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once
#include "GmapiInternal.h"

namespace gm {

  void keyboard_set_map( int key1, int key2 );
  int keyboard_get_map( int key );
  void keyboard_unset_map();
  bool keyboard_check( int key );
  bool keyboard_check_pressed( int key );
  bool keyboard_check_released( int key );
  bool keyboard_check_direct( int key );
  bool keyboard_get_numlock();
  void keyboard_set_numlock( bool on );
  void keyboard_key_press( int key );
  void keyboard_key_release( int key );
  void keyboard_clear( int key );
  void io_clear();
  void keyboard_wait();
  bool mouse_check_button( int numb );
  bool mouse_check_button_pressed( int numb );
  bool mouse_check_button_released( int numb );
  bool mouse_wheel_up();
  bool mouse_wheel_down();
  void mouse_clear( int button );
  void io_clear();
  void io_handle();
  void mouse_wait();
  bool joystick_exists( int id );
  CGMVariable joystick_name( int id );
  int joystick_axes( int id );
  int joystick_buttons( int id );
  bool joystick_has_pov( int id );
  int joystick_direction( int id );
  bool joystick_check_button( int id, int numb );
  int joystick_xpos( int id );
  int joystick_ypos( int id );
  int joystick_zpos( int id );
  int joystick_rpos( int id );
  int joystick_upos( int id );
  int joystick_vpos( int id );
  int joystick_pov( int id );

}
