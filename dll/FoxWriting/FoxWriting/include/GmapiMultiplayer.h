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
/*  GmapiMultiplayer.h                                                  */
/*   - Wrapped GM functions; Parser-generated code                      */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once
#include "GmapiInternal.h"

namespace gm {

  void mplay_init_ipx();
  void mplay_init_tcpip( const CGMVariable& addr );
  void mplay_init_modem( const CGMVariable& initstr, const CGMVariable& phonenr );
  void mplay_init_serial( int portno, double baudrate, double stopbits,
                          int parity, int flow );
  int mplay_connect_status();
  void mplay_end();
  CGMVariable mplay_ipaddress();

  bool mplay_session_create( const CGMVariable& sesname, int playnumb,
                             const CGMVariable& playername );
  int mplay_session_find();
  CGMVariable mplay_session_name( int numb );
  bool mplay_session_join( int numb, const CGMVariable& playername );
  void mplay_session_mode( bool move );
  int mplay_session_status();
  void mplay_session_end();

  int mplay_player_find();
  CGMVariable mplay_player_name( int numb );
  int mplay_player_id( int numb );

  void mplay_data_write( int ind, const CGMVariable& val );
  CGMVariable mplay_data_read( int ind );
  void mplay_data_mode( bool guar );

  void mplay_message_send( const CGMVariable& player, int id, const CGMVariable& val );
  void mplay_message_send_guaranteed( const CGMVariable& player, int id,
                                      const CGMVariable& val );
  bool mplay_message_receive( const CGMVariable& player );
  int mplay_message_id();
  CGMVariable mplay_message_value();
  CGMVariable mplay_message_player();
  CGMVariable mplay_message_name();
  int mplay_message_count( const CGMVariable& player );
  void mplay_message_clear( const CGMVariable& player );

}
