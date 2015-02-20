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
/*  GmapiFiles.h                                                        */
/*   - Wrapped GM functions; Parser-generated code                      */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once
#include "GmapiInternal.h"

namespace gm {

  int file_text_open_read( const CGMVariable& fname );
  int file_text_open_write( const CGMVariable& fname );
  int file_text_open_append( const CGMVariable& fname );
  void file_text_close( int fileid );
  void file_text_write_string( int fileid, const CGMVariable& str );
  void file_text_write_real( int fileid, double x );
  void file_text_writeln( int fileid );
  CGMVariable file_text_read_string( int fileid );
  double file_text_read_real( int fileid );
  void file_text_readln( int fileid );
  bool file_text_eof( int fileid );
  bool file_text_eoln( int file );
  bool file_exists( const CGMVariable& fname );
  void file_delete( const CGMVariable& fname );
  void file_rename( const CGMVariable& oldname, const CGMVariable& newname );
  void file_copy( const CGMVariable& fname, const CGMVariable& newname );
  bool directory_exists( const CGMVariable& dname );
  void directory_create( const CGMVariable& dname );
  CGMVariable file_find_first( const CGMVariable& mask, int attr );
  CGMVariable file_find_next();
  void file_find_close();
  bool file_attributes( const CGMVariable& fname, int attr );
  CGMVariable filename_name( const CGMVariable& fname );
  CGMVariable filename_path( const CGMVariable& fname );
  CGMVariable filename_dir( const CGMVariable& fname );
  CGMVariable filename_drive( const CGMVariable& fname );
  CGMVariable filename_ext( const CGMVariable& fname );
  CGMVariable filename_change_ext( const CGMVariable& fname, const CGMVariable& newext );
  int file_bin_open( const CGMVariable& fname, int mod );
  void file_bin_rewrite( int fileid );
  void file_bin_close( int fileid );
  int file_bin_size( int fileid );
  int file_bin_position( int fileid );
  void file_bin_seek( int fileid, int pos );
  void file_bin_write_byte( int fileid, int byte );
  int file_bin_read_byte( int fileid );
  void export_include_file( const CGMVariable& fname );
  void export_include_file_location( const CGMVariable& fname, const CGMVariable& location );
  void discard_include_file( const CGMVariable& fname );
  int parameter_count();
  CGMVariable parameter_string( int n );
  CGMVariable environment_get_variable( const CGMVariable& name );

  double disk_size( const CGMVariable& drive );
  double disk_free( const CGMVariable& drive );

  void registry_write_string( const CGMVariable& name, const CGMVariable& str );
  void registry_write_real( const CGMVariable& name, double x );
  CGMVariable registry_read_string( const CGMVariable& name );
  double registry_read_real( const CGMVariable& name );
  bool registry_exists( const CGMVariable& name );
  void registry_write_string_ext( const CGMVariable& key, const CGMVariable& name,
                                  const CGMVariable& str );
  void registry_write_real_ext( const CGMVariable& key, const CGMVariable& name,
                                double x );
  CGMVariable registry_read_string_ext( const CGMVariable& key, const CGMVariable& name );
  double registry_read_real_ext( const CGMVariable& key, const CGMVariable& name );
  bool registry_exists_ext( const CGMVariable& key, const CGMVariable& name );
  void registry_set_root( int root );
  void ini_open( const CGMVariable& name );
  void ini_close();
  CGMVariable ini_read_string( const CGMVariable& section, const CGMVariable& key,
                               const CGMVariable& default_ );
  double ini_read_real( const CGMVariable& section, const CGMVariable& key,
                        double default_ );
  void ini_write_string( const CGMVariable& section, const CGMVariable& key,
                         const CGMVariable& value );
  void ini_write_real( const CGMVariable& section, const CGMVariable& key, double value );
  bool ini_key_exists( const CGMVariable& section, const CGMVariable& key );
  bool ini_section_exists( const CGMVariable& section );
  void ini_key_delete( const CGMVariable& section, const CGMVariable& key );
  void ini_section_delete( const CGMVariable& section );
  void execute_program( const CGMVariable& prog, const CGMVariable& arg, bool wait );
  void execute_shell( const CGMVariable& prog, const CGMVariable& arg );

}
