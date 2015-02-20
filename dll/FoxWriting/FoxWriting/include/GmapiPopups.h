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
/*  GmapiPopups.h                                                       */
/*   - Wrapped GM functions; Parser-generated code                      */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once
#include "GmapiInternal.h"

namespace gm {
  void show_message( const CGMVariable& str );
  double show_message_ext( const CGMVariable& str, const CGMVariable& but1,
                           const CGMVariable& but2, const CGMVariable& but3 );
  bool show_question( const CGMVariable& str );

  double get_integer( const CGMVariable& str, double def );
  CGMVariable get_string( const CGMVariable& str, const CGMVariable& def );

  void message_background( int back );
  void message_alpha( double alpha );
  void message_button( int spr );
  void message_text_font( const CGMVariable& name, int size,
                          int color, int style );
  void message_button_font( const CGMVariable& name, int size,
                            int color, int style );

  void message_input_font( const CGMVariable& name, int size,
                           int color, int style );
  void message_input_color( int col );
  void message_mouse_color( int col );
  void message_caption( bool show, const CGMVariable& str );
  void message_position( int x, int y );
  void message_size( int w, int h );

  int show_menu( const CGMVariable& str, int def );
  int show_menu_pos( int x, int y, const CGMVariable& str, int def );

  int get_color( int defcol );
  CGMVariable get_open_filename( const CGMVariable& filter, const CGMVariable& fname );
  CGMVariable get_save_filename( const CGMVariable& filter, const CGMVariable& fname );
  CGMVariable get_directory( const CGMVariable& dname );
  CGMVariable get_directory_alt( const CGMVariable& capt, const CGMVariable& root );

  void splash_show_video( const CGMVariable& fname, bool loop );
  void splash_show_text( const CGMVariable& fname, int delay );
  void splash_show_image( const CGMVariable& fname, int delay );
  void splash_show_web( const CGMVariable& url, int delay );

  void splash_set_main( bool main );
  void splash_set_scale( double scape );
  void splash_set_cursor( bool vis );
  void splash_set_color( int col );
  void splash_set_caption( const CGMVariable& cap );
  void splash_set_fullscreen( bool full );
  void splash_set_border( bool border );
  void splash_set_size( int w, int h );
  void splash_set_adapt( bool adapt );
  void splash_set_top( bool top );
  void splash_set_interrupt( bool interrupt );
  void splash_set_stop_key( bool stop );
  void splash_set_stop_mouse( bool stop );
  void splash_set_position( int x, int y );
  void splash_set_close_button( bool show );

  void show_info();
  void load_info( const CGMVariable& fname );
  void show_error( const CGMVariable& str, bool abort );

  void highscore_show( double numb );
  void highscore_set_background( int back );
  void highscore_set_border( bool show );
  void highscore_set_font( const CGMVariable& name, int size, int style );
  void highscore_set_colors( int back, int new_, int other );
  void highscore_set_strings( const CGMVariable& caption, const CGMVariable& nobody,
                              const CGMVariable& escape );
  void highscore_show_ext( double numb, int back, bool border,
                           int col1, int col2,
                           const CGMVariable& name, int size );
  void highscore_clear();
  void highscore_add( const CGMVariable& str, double numb );
  void highscore_add_current();
  double highscore_value( int place );
  CGMVariable highscore_name( int place );
  void draw_highscore( double x1, double y1,
                       double x2, double y2 );

}
