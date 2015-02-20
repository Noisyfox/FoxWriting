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
/*  GmapiSounds.h                                                       */
/*   - Wrapped GM functions; Parser-generated code                      */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once
#include "GmapiInternal.h"

namespace gm {

  void sound_play( int index );
  void sound_loop( int index );
  void sound_stop( int index );
  void sound_stop_all();
  bool sound_isplaying( int index );

  void sound_volume( int index, double value );
  void sound_global_volume( double value );
  void sound_fade( int index, double value, int time );
  void sound_pan( int index, double value );
  void sound_background_tempo( double factor );

  void sound_set_search_directory( const CGMVariable& dir );

  void sound_effect_set( int snd, int effect );
  void sound_effect_chorus( int snd, double wetdry, double depth,
                            double feedback, double frequency, int wave,
                            int delay, double phase );
  void sound_effect_echo( int snd, double wetdry, double feedback,
                          int leftdelay, int rightdelay, bool pandelay );
  void sound_effect_flanger( int snd, double wetdry, double depth,
                             double feedback, double frequency, int wave,
                             int delay, double phase );
  void sound_effect_gargle( int snd, double rate, int wave );
  void sound_effect_reverb( int snd, double gain, double mix,
                            double time, double ratio );
  void sound_effect_compressor( int snd, double gain, double attack,
                                double release, double threshold,
                                double ratio, double delay );
  void sound_effect_equalizer( int snd, double center, double bandwidth,
                               double gain );

  void sound_3d_set_sound_position( int snd, double x, double y,
                                    double z );
  void sound_3d_set_sound_velocity( int snd, double x, double y,
                                    double z );
  void sound_3d_set_sound_distance( int snd, double mindist, double maxdist );
  void sound_3d_set_sound_cone( int snd, double x, double y,
                                double z, double anglein, double angleout,
                                double voloutside );

  void cd_init();
  bool cd_present();
  int cd_number();
  bool cd_playing();
  bool cd_paused();
  int cd_track();
  int cd_length();
  int cd_track_length( int n );
  int cd_position();
  int cd_track_position();
  void cd_play( int first, int last );
  void cd_stop();
  void cd_pause();
  void cd_resume();
  void cd_set_position( int pos );
  void cd_set_track_position( int pos );
  void cd_open_door();
  void cd_close_door();

  CGMVariable MCI_command( const CGMVariable& str );

}
