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
/*  GmapiInternal.h                                                     */
/*  - Declarations of GMAPI classes and interfaces                      */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once

#ifdef __GNUC__
  #define sprintf_s snprintf
#endif

#include <windows.h>

#include <string>
#include <iostream>

#include "GmapiCore.h"
#include "GmapiConsts.h"
#include "GmapiDefs.h"

namespace gm {
  /// Used internally
  class CGlobals {
    friend class CGMAPI;

    public:
      static inline bool UseNewStructs() {
        return m_alternativeStructures;
      }

    private:
      static inline PGMVARIABLELIST InstanceVarList( PGMINSTANCE aInstance );
      static inline int InstanceID( PGMINSTANCE aInstance );
      static inline int InstanceObjectID( PGMINSTANCE aInstance );
      static inline bool IsInstanceDeactivated( PGMINSTANCE aInstance );

      static bool m_alternativeStructures;
  };

  /************************************************************************/
  /* CGMVariable                                                          */
  /************************************************************************/

  /// CGMVariable
  /// Class that mimics GM's variable. It is used in GM functions as
  /// string/unspecified (i.e. that ones which can be either "real" or
  /// "string") parameters and return values. The class uses GM runner
  /// to manage strings, as the runner requires to pass Delphi strings
  /// to the functions.
  ///
  class CGMVariable {
    public:
      ~CGMVariable() {
        if ( m_isString && m_stringPtr && m_stringDispose )
          StringDeallocate();
      }

      /// Ctor( int aValue ) [default]
      ///   Initializes the variable to specified int value
      ///   (it will be casted to double) and sets its type
      ///   to "real".
      ///
      /// Parameters:
      ///   aValue: [optional] Initializing value.
      ///
      CGMVariable( int aValue = 0 ): m_isString( false ),
                                     m_stringDispose( true ),
                                     m_stringPtr( NULL ),
                                     m_real( aValue ) {}

      /// Ctor( double aValue )
      ///   Initializes the variable to specified value
      ///   and sets its type to "real".
      ///
      /// Parameters:
      ///   aValue: Initializing value.
      ///
      CGMVariable( double aValue ): m_isString( false ),
                                    m_stringDispose( true ),
                                    m_stringPtr( NULL ),
                                    m_real( aValue ) {}

      /// Ctor( bool aValue )
      ///   Initializes the variable to specified bool value
      ///   (it will be casted to double) and sets its type
      ///   to "real".
      ///
      /// Parameters:
      ///   aValue: Initializing value.
      ///
      CGMVariable( bool aValue ): m_isString( false ),
                                  m_stringDispose( true ),
                                  m_stringPtr( NULL ),
                                  m_real( aValue ) {}

      /// Ctor( const char* aValue )
      ///   Initializes the variable with specified string
      ///   and sets its type to "string".
      ///
      /// Parameters:
      ///   aString: Initializing string.
      ///
      CGMVariable( const char* aString ): m_isString( true ),
                                          m_stringDispose( true ),
                                          m_stringPtr( NULL ),
                                          m_real( 0.0 ) {
        StringSet( aString );
      }

      /// Ctor( const std::string& aValue )
      ///   Initializes the variable with specified string
      ///   and sets its type to "string".
      ///
      /// Parameters:
      ///   aString: Initializing string.
      ///
      CGMVariable( const std::string& aString ): m_isString( true ),
                                                 m_stringDispose( true ),
                                                 m_stringPtr( NULL ),
                                                 m_real( 0.0 ) {
        StringSet( aString.c_str() );
      }

      /// Ctor( const GMVALUE& aValue )
      ///   Initializes the variables using the GMVALUE structure.
      ///
      /// Parameter:
      ///   aValue: GMVALUE structure that will be used to initialize
      ///           the variable.
      ///
      CGMVariable( const GMVALUE& aValue );

      /// Ctor( const CGMVariable& aValue )
      ///   Copy constructor. Initializes the object basing
      ///   on an existing class instance.
      ///
      CGMVariable( const CGMVariable& aValue ): m_isString( false ),
                                                m_stringDispose( true ),
                                                m_stringPtr( NULL ),
                                                m_real( 0.0 ) {
        *this = aValue;
      }

      /// Set( bool aValue )
      ///   Sets the variable to specified value of type "bool", thus,
      ///   changing its type to "real". If the variable was previously
      ///   of a "string" type - the string will be deallocated.
      ///
      /// Parameters:
      ///   aValue: New value
      ///
      void Set( bool aValue ) {
        Set( (double) aValue );
      }

      /// Set( double aValue )
      ///   Sets the variable to specified value of type "double", thus,
      ///   changing its type to "real". If the variable was previously
      ///   of a "string" type - the string will be deallocated.
      ///
      /// Parameters:
      ///   aValue: New value
      ///
      void Set( double aValue ) {
        if ( m_isString ) {
          StringClear();
          m_isString = false;
        }

        m_real = aValue;
      }

      /// Set( const char* aString )
      ///   Sets variable to specified string. Thus, changing its type
      ///   to "string". If previously variable was of "real" type - it'll
      ///   be set to zero.
      ///
      /// Parameters:
      ///   aValue: New value
      ///
      void Set( const char* aString ) {
        if ( !m_isString ) {
          m_real = 0.0;
          m_isString = true;
        }

        if ( aString )
          StringSet( aString );
        else
          StringClear();
      }

      /// Set( const std::string& aValue )
      ///   Sets variable to specified string. Thus, changing its type
      ///   to "string". If previously variable was of "real" type - it'll
      ///   be set to zero.
      ///
      /// Parameters:
      ///   aValue: New value
      ///
      void Set( const std::string& aValue ) {
        Set( aValue.c_str() );
      }

      /// c_str()
      ///   Returns variable as C-style string.
      ///
      /// Returns:
      ///   C-style string if variable's type is string, otherwise NULL.
      ///
      const char* c_str() const {
        if ( m_stringPtr && m_isString )
          if ( *m_stringPtr )
            return *m_stringPtr;
          else
            return "\xFF\xFF\xFF\xFF\x00\x00\x00\x00" + 8;
        else
          return NULL;
      }

      /// real()
      ///   Returns variable as a real value.
      ///
      /// Returns:
      ///   Real value of the variable.
      ///
      double real() const {
        return m_real;
      }

      /// RealToString( double aValue )
      ///   Sets the variable to string by converting specifed
      ///   value to the string.
      ///
      /// Parameters:
      ///    aValue: Floating point value to convert.
      ///
      void RealToString( double aValue ) {
        char buffer[0x80];
        sprintf_s( buffer, 0x80, "%.16g", aValue );

        Set( buffer );
      }

      /// RealToString()
      ///   Converts the variable to a string.
      ///
      /// Returns:
      ///   False if the variable is not of a "real" type. Otherwise true.
      ///
      bool RealToString() {
        if ( m_isString )
          return false;

        char buffer[0x80];
        sprintf_s( buffer, 0x80, "%.16g", m_real );

        Set( buffer );
        return true;
      }

      /// StringToReal( const char* aString )
      ///   Sets the variable to real value by converting specified
      ///   string to floating point value.
      ///
      /// Parameters:
      ///   aString: String to convert.
      ///
      void StringToReal( const char* aString ) {
        Set( atof( aString ) );
      }

      /// StringToReal()
      ///   Converts the variable to real.
      ///
      /// Returns:
      ///   False if the variable is not of a "string" type. Otherwise true.
      ///
      bool StringToReal() {
        if ( !m_isString )
          return false;

        Set( atof( c_str() ) );
        return true;
      }

      /// IsString()
      ///   Checks whether the variable is of string type.
      ///
      /// Returns:
      ///   True if variable's type is string, otherwise returns false.
      ///
      bool IsString() const {
        return m_isString;
      }

      /************************************************************************/
      /* Assignment operator overloading                                      */
      /************************************************************************/

      CGMVariable& operator=( bool aValue ) {
        Set( aValue );
        return *this;
      }

      CGMVariable& operator=( double aValue ) {
        Set( aValue );
        return *this;
      }

      CGMVariable& operator=( const char* aValue ) {
        Set( aValue );
        return *this;
      }

      CGMVariable& operator=( const std::string& aValue ) {
        Set( aValue.c_str() );
        return *this;
      }

      CGMVariable& operator=( const GMVALUE& aValue );
      CGMVariable& operator=( const CGMVariable& aValue ) {
        if ( aValue.m_isString )
          Set( *aValue.m_stringPtr );
        else
          Set( aValue.m_real );

        return *this;
      }

      /************************************************************************/
      /* Type casting                                                         */
      /************************************************************************/

      operator double() {
        if ( !m_isString )
          return m_real;

        return 0.0;
      }

      operator const char*() {
        if ( m_isString )
          return *m_stringPtr;

        return NULL;
      }

      /************************************************************************/
      /* Operator overloads for real-value op.                                */
      /************************************************************************/

      CGMVariable& operator++() {
        if ( !m_isString )
          ++m_real;
        return *this;
      }

      CGMVariable operator++(int) {
        CGMVariable old( *this );

        if ( !m_isString )
          ++(*this);

        return old;
      }

      CGMVariable& operator--() {
        if ( !m_isString )
          --m_real;

        return *this;
      }

      CGMVariable operator--(int) {
        CGMVariable old( *this );

        if ( !m_isString )
          --(*this);

        return old;
      }

      void operator+=( double aValue ) {
        if ( !m_isString )
          m_real += aValue;
      }

      void operator-=( double aValue ) {
        if ( !m_isString )
          m_real -= aValue;
      }

    private:
      void StringSet( const char* aValue );
      void StringClear();
      void StringDeallocate();

      bool m_isString, m_stringDispose;
      const char** m_stringPtr;
      double m_real;
  };

  /************************************************************************/
  /* Operator overloading (other)                                         */
  /************************************************************************/

  std::ostream& operator<<( std::ostream& aStream, const CGMVariable& aValue );
  std::ostream& operator<<( std::ostream& aStream, const GMVALUE& aValue );

  /************************************************************************/
  /* Types                                                                */
  /************************************************************************/

  typedef bool (*INSTANCEENUMPROC)( GMINSTANCE&, void* );
  typedef bool (*PARTICLEENUMPROC)( GMPARTICLE&, void* );
  typedef void (*WITHPROC)( void* );
  typedef void (*GMAPIGMFUNCTION)( PGMINSTANCE, PGMINSTANCE, GMVALUE*, int, int, PGMVALUE );
  typedef void (*GMFUCTION)( PGMVALUE, int, GMVALUE*, int, PGMINSTANCE, PGMINSTANCE );

  //////////////////////////////////////////////////////////////////////////

  struct GMVARIABLESYMBOLID {
    int symbolId;
    __PADDING4 _padding0;
  };

  /// GMVALUE
  ///   Represents internal GM value structure.
  ///
  ///   That structure is used internally to specify
  ///   arguments and return values in GM functions.
  ///
  struct GMVALUE {
    GMVALUE(): type( VT_REAL ),
               real( 0 ),
               string( NULL ) {}
    GMVALUE( const GMVALUE& aValue );

    GMVALUE( double aValue ): type( VT_REAL ),
                              real( aValue ),
                              string( NULL ) {}

    GMVALUE( const char* aValue ): type( VT_REAL ),
                             string( aValue ) {}

    GMVALUE( const CGMVariable& aValue ) {
      *this = aValue;
    }

    GMVALUE& operator=( double aValue );
    GMVALUE& operator=( const char* aValue );
    GMVALUE& operator=( const CGMVariable& aValue );

    operator double() {
      if ( type == VT_REAL )
        return real;

      return 0.0;
    }

    operator const char*() {
      if ( type == VT_STRING )
        return string;

      return NULL;
    }

    /// Set( const char* aString )
    ///   Modifies the string stored in the structure.
    ///   This should be used only if the GM runner has
    ///   initialized the struct.
    ///
    /// Parameters:
    ///   aString: New string.
    ///
    void Set( const char* aString ) {
      type = VT_STRING;
      core::DelphiStringSetFromPChar( aString, &string );
    }

    /// Set( const char* aString )
    ///   Sets the structure to real value.
    ///
    /// Parameters:
    ///   aValue: New value.
    ///
    void Set( double aValue ) {
      type = VT_REAL;
      real = aValue;
    }

    /// Type of the value
    GMValueType type;

    __PADDING4 _padding1;

    /// GM holds real value here if its type is "real".
    double real;

    /// GM holds here pointer to the string if value's type is "string".
    const char* string;

    __PADDING4 _padding2;
  };

  struct GMVARIABLE: public GMVARIABLESYMBOLID, public GMVALUE {
    /// GetFirstDimensionSize()
    ///   If the variable is an array, method will return number
    ///   of elements in the first dimension
    ///
    unsigned long GetFirstDimensionSize() {
      if ( values )
        return (DWORD) values[-1];

      return 0;
    }

    /// GetSecondDimensionSize( unsigned long aFirstIndex )
    ///   If the variable is an array, method will return number
    ///   of elements in the second dimension of specified array's first index
    ///
    /// Parameters:
    ///   aFirstIndex: Index of the first dimension.
    unsigned long GetSecondDimensionSize( unsigned long aFirstIndex ) {
      if ( values )
        if ( values[aFirstIndex] )
          return ((DWORD*) values[aFirstIndex])[-1];

      return 0;
    }

    GMVARIABLE& operator=( double aValue );
    GMVARIABLE& operator=( const char* aValue );
    GMVARIABLE& operator=( const CGMVariable& aValue );

    /// Dereferences "values" component of the structure
    GMVALUE* operator[]( int aIndex ) {
      return values[aIndex];
    };

    /// Pointer to 2D array which contains elements of GM array.
    /// Contains NULL if variable is not an array.
    GMVALUE** values;
    __PADDING4 _padding3;
  };

  /// GMINSTANCE
  ///   Structure that runner uses to hold the data of an instance.
  ///   Most of its members are a properties that can be used to
  ///   set the specified instance variables without having to check the
  ///   version of the GM runner - since the 8th version of Game Maker
  ///   the structure have changed.
  ///
  struct GMINSTANCE {
  #ifdef _MSC_VER
     __declspec( property( get = _Get_id, put = _Set_id ) ) int id;
    int& _Get_id() {
      return ( CGlobals::UseNewStructs() ? structNew.id : structOld.id );
    }

    int& _Set_id( int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.id : structOld.id ) = aValue;
    }

    __declspec( property( get = _Get_sprite_index, put = _Set_sprite_index ) ) int sprite_index;
    int& _Get_sprite_index() {
      return ( CGlobals::UseNewStructs() ? structNew.sprite_index : structOld.sprite_index );
    }

    int& _Set_sprite_index( int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.sprite_index : structOld.sprite_index ) = aValue;
    }

    __declspec( property( get = _Get_image_index, put = _Set_image_index ) ) double image_index;
    double& _Get_image_index() {
      return ( CGlobals::UseNewStructs() ? structNew.image_index : structOld.image_index );
    }

    double& _Set_image_index( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.image_index : structOld.image_index ) = aValue;
    }

    __declspec( property( get = _Get_image_speed, put = _Set_image_speed ) ) double image_speed;
    double& _Get_image_speed() {
      return ( CGlobals::UseNewStructs() ? structNew.image_speed : structOld.image_speed );
    }

    double& _Set_image_speed( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.image_speed : structOld.image_speed ) = aValue;
    }

    __declspec( property( get = _Get_image_xscale, put = _Set_image_xscale ) ) double image_xscale;
    double& _Get_image_xscale() {
      return ( CGlobals::UseNewStructs() ? structNew.image_xscale : structOld.image_xscale );
    }

    double& _Set_image_xscale( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.image_xscale : structOld.image_xscale ) = aValue;
    }

    __declspec( property( get = _Get_image_yscale, put = _Set_image_yscale ) ) double image_yscale;
    double& _Get_image_yscale() {
      return ( CGlobals::UseNewStructs() ? structNew.image_yscale : structOld.image_yscale );
    }

    double& _Set_image_yscale( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.image_yscale : structOld.image_yscale ) = aValue;
    }

    __declspec( property( get = _Get_image_angle, put = _Set_image_angle ) ) double image_angle;
    double& _Get_image_angle() {
      return ( CGlobals::UseNewStructs() ? structNew.image_angle : structOld.image_angle );
    }

    double& _Set_image_angle( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.image_angle : structOld.image_angle ) = aValue;
    }

    __declspec( property( get = _Get_image_alpha, put = _Set_image_alpha ) ) double image_alpha;
    double& _Get_image_alpha() {
      return ( CGlobals::UseNewStructs() ? structNew.image_alpha : structOld.image_alpha );
    }

    double& _Set_image_alpha( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.image_alpha : structOld.image_alpha ) = aValue;
    }

    __declspec( property( get = _Get_image_blend, put = _Set_image_blend ) ) int image_blend;
    int& _Get_image_blend() {
      return ( CGlobals::UseNewStructs() ? structNew.image_blend : structOld.image_blend );
    }

    int& _Set_image_blend( int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.image_blend : structOld.image_blend ) = aValue;
    }

    __declspec( property( get = _Get_mask_index, put = _Set_mask_index ) ) int mask_index;
    int& _Get_mask_index() {
      return ( CGlobals::UseNewStructs() ? structNew.mask_index : structOld.mask_index );
    }

    int& _Set_mask_index( int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.mask_index : structOld.mask_index ) = aValue;
    }

    __declspec( property( get = _Get_depth, put = _Set_depth ) ) double depth;
    double& _Get_depth() {
      return ( CGlobals::UseNewStructs() ? structNew.depth : structOld.depth );
    }

    double& _Set_depth( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.depth : structOld.depth ) = aValue;
    }

    __declspec( property( get = _Get_x, put = _Set_x ) ) double x;
    double& _Get_x() {
      return ( CGlobals::UseNewStructs() ? structNew.x : structOld.x );
    }

    double& _Set_x( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.x : structOld.x ) = aValue;
    }

    __declspec( property( get = _Get_y, put = _Set_y ) ) double y;
    double& _Get_y() {
      return ( CGlobals::UseNewStructs() ? structNew.y : structOld.y );
    }

    double& _Set_y( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.y : structOld.y ) = aValue;
    }

    __declspec( property( get = _Get_xstart, put = _Set_xstart ) ) double xstart;
    double& _Get_xstart() {
      return ( CGlobals::UseNewStructs() ? structNew.xstart : structOld.xstart );
    }

    double& _Set_xstart( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.xstart : structOld.xstart ) = aValue;
    }

    __declspec( property( get = _Get_ystart, put = _Set_ystart ) ) double ystart;
    double& _Get_ystart() {
      return ( CGlobals::UseNewStructs() ? structNew.ystart : structOld.ystart );
    }

    double& _Set_ystart( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.ystart : structOld.ystart ) = aValue;
    }

    __declspec( property( get = _Get_xprevious, put = _Set_xprevious ) ) double xprevious;
    double& _Get_xprevious() {
      return ( CGlobals::UseNewStructs() ? structNew.xprevious : structOld.xprevious );
    }

    double& _Set_xprevious( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.xprevious : structOld.xprevious ) = aValue;
    }

    __declspec( property( get = _Get_yprevious, put = _Set_yprevious ) ) double yprevious;
    double& _Get_yprevious() {
      return ( CGlobals::UseNewStructs() ? structNew.yprevious : structOld.yprevious );
    }

    double& _Set_yprevious( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.yprevious : structOld.yprevious ) = aValue;
    }

    __declspec( property( get = _Get_direction, put = _Set_direction ) ) double direction;
    double& _Get_direction() {
      return ( CGlobals::UseNewStructs() ? structNew.direction : structOld.direction );
    }

    double& _Set_direction( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.direction : structOld.direction ) = aValue;
    }

    __declspec( property( get = _Get_speed, put = _Set_speed ) ) double speed;
    double& _Get_speed() {
      return ( CGlobals::UseNewStructs() ? structNew.speed : structOld.speed );
    }

    double& _Set_speed( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.speed : structOld.speed ) = aValue;
    }

    __declspec( property( get = _Get_friction, put = _Set_friction ) ) double friction;
    double& _Get_friction() {
      return ( CGlobals::UseNewStructs() ? structNew.friction : structOld.friction );
    }

    double& _Set_friction( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.friction : structOld.friction ) = aValue;
    }

    __declspec( property( get = _Get_gravity_direction, put = _Set_gravity_direction ) ) double gravity_direction;
    double& _Get_gravity_direction() {
      return ( CGlobals::UseNewStructs() ? structNew.gravity_direction : structOld.gravity_direction );
    }

    double& _Set_gravity_direction( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.gravity_direction : structOld.gravity_direction ) = aValue;
    }

    __declspec( property( get = _Get_gravity, put = _Set_gravity ) ) double gravity;
    double& _Get_gravity() {
      return ( CGlobals::UseNewStructs() ? structNew.gravity : structOld.gravity );
    }

    double& _Set_gravity( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.gravity : structOld.gravity ) = aValue;
    }

    __declspec( property( get = _Get_hspeed, put = _Set_hspeed ) ) double hspeed;
    double& _Get_hspeed() {
      return ( CGlobals::UseNewStructs() ? structNew.hspeed : structOld.hspeed );
    }

    double& _Set_hspeed( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.hspeed : structOld.hspeed ) = aValue;
    }

    __declspec( property( get = _Get_vspeed, put = _Set_vspeed ) ) double vspeed;
    double& _Get_vspeed() {
      return ( CGlobals::UseNewStructs() ? structNew.vspeed : structOld.vspeed );
    }

    double& _Set_vspeed( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.vspeed : structOld.vspeed ) = aValue;
    }

    __declspec( property( get = _Get_bbox_left, put = _Set_bbox_left ) ) int bbox_left;
    int& _Get_bbox_left() {
      return ( CGlobals::UseNewStructs() ? structNew.bbox_left : structOld.bbox_left );
    }

    int& _Set_bbox_left( int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.bbox_left : structOld.bbox_left ) = aValue;
    }

    __declspec( property( get = _Get_bbox_top, put = _Set_bbox_top ) ) int bbox_top;
    int& _Get_bbox_top() {
      return ( CGlobals::UseNewStructs() ? structNew.bbox_top : structOld.bbox_top );
    }

    int& _Set_bbox_top( int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.bbox_top : structOld.bbox_top ) = aValue;
    }

    __declspec( property( get = _Get_bbox_right, put = _Set_bbox_right ) ) int bbox_right;
    int& _Get_bbox_right() {
      return ( CGlobals::UseNewStructs() ? structNew.bbox_right : structOld.bbox_right );
    }

    int& _Set_bbox_right( int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.bbox_right : structOld.bbox_right ) = aValue;
    }

    __declspec( property( get = _Get_bbox_bottom, put = _Set_bbox_bottom ) ) int bbox_bottom;
    int& _Get_bbox_bottom() {
      return ( CGlobals::UseNewStructs() ? structNew.bbox_bottom : structOld.bbox_bottom );
    }

    int& _Set_bbox_bottom( int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.bbox_bottom : structOld.bbox_bottom ) = aValue;
    }

    __declspec( property( get = _Get_visible, put = _Set_visible ) ) bool visible;
    bool& _Get_visible() {
      return ( CGlobals::UseNewStructs() ? structNew.visible : structOld.visible );
    }

    bool& _Set_visible( bool aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.visible : structOld.visible ) = aValue;
    }

    __declspec( property( get = _Get_solid, put = _Set_solid ) ) bool solid;
    bool& _Get_solid() {
      return ( CGlobals::UseNewStructs() ? structNew.solid : structOld.solid );
    }

    bool& _Set_solid( bool aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.solid : structOld.solid ) = aValue;
    }

    __declspec( property( get = _Get_persistent, put = _Set_persistent ) ) bool persistent;
    bool& _Get_persistent() {
      return ( CGlobals::UseNewStructs() ? structNew.persistent : structOld.persistent );
    }

    bool& _Set_persistent( bool aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.persistent : structOld.persistent ) = aValue;
    }

    __declspec( property( get = _Get_object_index, put = _Set_object_index ) ) int object_index;
    int& _Get_object_index() {
      return ( CGlobals::UseNewStructs() ? structNew.object_index : structOld.object_index );
    }

    int& _Set_object_index( int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.object_index : structOld.object_index ) = aValue;
    }

    __declspec( property( get = _Get_alarm, put = _Set_alarm ) ) int alarm[12];
    int& _Get_alarm( int aIndex ) {
      return ( CGlobals::UseNewStructs() ? structNew.alarm[aIndex] : structOld.alarm[aIndex] );
    }

    int& _Set_alarm( int aIndex, int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.alarm[aIndex] : structOld.alarm[aIndex] ) = aValue;
    }

    __declspec( property( get = _Get_variableListPtr, put = _Set_variableListPtr ) ) PGMVARIABLELIST variableListPtr;
    PGMVARIABLELIST& _Get_variableListPtr() {
      return ( CGlobals::UseNewStructs() ? structNew.variableListPtr : structOld.variableListPtr );
    }

    PGMVARIABLELIST& _Set_variableListPtr( PGMVARIABLELIST aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.variableListPtr : structOld.variableListPtr ) = aValue;
    }

    __declspec( property( get = _Get_deactivated, put = _Set_deactivated ) ) bool deactivated;
    bool& _Get_deactivated() {
      return ( CGlobals::UseNewStructs() ? structNew.deactivated : structOld.deactivated );
    }

    bool& _Set_deactivated( bool aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.deactivated : structOld.deactivated ) = aValue;
    }

    __declspec( property( get = _Get_path_index, put = _Set_path_index ) ) int path_index;
    int& _Get_path_index() {
      return ( CGlobals::UseNewStructs() ? structNew.path_index : structOld.path_index );
    }

    int& _Set_path_index( int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.path_index : structOld.path_index ) = aValue;
    }

    __declspec( property( get = _Get_path_position, put = _Set_path_position ) ) double path_position;
    double& _Get_path_position() {
      return ( CGlobals::UseNewStructs() ? structNew.path_position : structOld.path_position );
    }

    double& _Set_path_position( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.path_position : structOld.path_position ) = aValue;
    }

    __declspec( property( get = _Get_path_positionprevious, put = _Set_path_positionprevious ) ) double path_positionprevious;
    double& _Get_path_positionprevious() {
      return ( CGlobals::UseNewStructs() ? structNew.path_positionprevious : structOld.path_positionprevious );
    }

    double& _Set_path_positionprevious( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.path_positionprevious : structOld.path_positionprevious ) = aValue;
    }

    __declspec( property( get = _Get_path_speed, put = _Set_path_speed ) ) double path_speed;
    double& _Get_path_speed() {
      return ( CGlobals::UseNewStructs() ? structNew.path_speed : structOld.path_speed );
    }

    double& _Set_path_speed( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.path_speed : structOld.path_speed ) = aValue;
    }

    __declspec( property( get = _Get_path_scale, put = _Set_path_scale ) ) double path_scale;
    double& _Get_path_scale() {
      return ( CGlobals::UseNewStructs() ? structNew.path_scale : structOld.path_scale );
    }

    double& _Set_path_scale( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.path_scale : structOld.path_scale ) = aValue;
    }

    __declspec( property( get = _Get_path_orientation, put = _Set_path_orientation ) ) double path_orientation;
    double& _Get_path_orientation() {
      return ( CGlobals::UseNewStructs() ? structNew.path_orientation : structOld.path_orientation );
    }

    double& _Set_path_orientation( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.path_orientation : structOld.path_orientation ) = aValue;
    }

    __declspec( property( get = _Get_path_endaction, put = _Set_path_endaction ) ) int path_endaction;
    int& _Get_path_endaction() {
      return ( CGlobals::UseNewStructs() ? structNew.path_endaction : structOld.path_endaction );
    }

    int& _Set_path_endaction( int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.path_endaction : structOld.path_endaction ) = aValue;
    }

    __declspec( property( get = _Get_timeline_index, put = _Set_timeline_index ) ) int timeline_index;
    int& _Get_timeline_index() {
      return ( CGlobals::UseNewStructs() ? structNew.timeline_index : structOld.timeline_index );
    }

    int& _Set_timeline_index( int aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.timeline_index : structOld.timeline_index ) = aValue;
    }

    __declspec( property( get = _Get_timeline_position, put = _Set_timeline_position ) ) double timeline_position;
    double& _Get_timeline_position() {
      return ( CGlobals::UseNewStructs() ? structNew.timeline_position : structOld.timeline_position );
    }

    double& _Set_timeline_position( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.timeline_position : structOld.timeline_position ) = aValue;
    }

    __declspec( property( get = _Get_timeline_speed, put = _Set_timeline_speed ) ) double timeline_speed;
    double& _Get_timeline_speed() {
      return ( CGlobals::UseNewStructs() ? structNew.timeline_speed : structOld.timeline_speed );
    }

    double& _Set_timeline_speed( double aValue ) {
      return ( CGlobals::UseNewStructs() ? structNew.timeline_speed : structOld.timeline_speed ) = aValue;
    }

    /// Unavailable in GM versions below 8
    __declspec( property( get = _Get_timeline_running, put = _Set_timeline_running ) ) bool timeline_running;
    bool& _Get_timeline_running() {
      return structNew.timeline_running;
    }

    /// Unavailable in GM versions below 8
    bool& _Set_timeline_running( bool aValue ) {
      return structNew.timeline_running = aValue;
    }

    /// Unavailable in GM versions below 8
    __declspec( property( get = _Get_timeline_loop, put = _Set_timeline_loop ) ) bool timeline_loop;
    bool& _Get_timeline_loop() {
      return structNew.timeline_loop;
    }

    /// Unavailable in GM versions below 8
    bool& _Set_timeline_loop( bool aValue ) {
      return structNew.timeline_loop = aValue;
    }
  #endif

    union {
      /// Version of the structure in GM6.1/7
      GMINSTANCE_OLD structOld;

      /// Version of the structure in GM8
      GMINSTANCE_NEW structNew;
    };
  };

   /************************************************************************/
   /* Exceptions                                                           */
   /************************************************************************/

  /// EGMAPIException
  ///   Base class of GMAPI exceptions.
  class EGMAPIException: public std::exception {
    public:
      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const {
        MessageBoxA( 0, STR_EXC_UNKNOWN, 0, MB_SYSTEMMODAL );
      }
  };

  class EGMAPIResourceException: public EGMAPIException {
    public:
      /// GetResourceID()
      ///   Returns ID of the resource that caused exception
      ///
      int GetResourceID() const {
        return m_resourceId;
      }

    protected:
      int m_resourceId;
  };

  class EGMAPISpriteNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPISpriteNotExist( int aSprite ) {
        m_resourceId = aSprite;
      }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;
  };

  class EGMAPIInvalidSubimage: public EGMAPIResourceException {
    public:
      explicit EGMAPIInvalidSubimage( int aSprite, int aSubimage ): m_subimage( aSubimage ) {
        m_resourceId = aSprite;
      }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;

    protected:
      int m_subimage;
  };

  class EGMAPIBackgroundNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPIBackgroundNotExist( int aBackground ) {
        m_resourceId = aBackground;
      }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;
  };

  class EGMAPIScriptNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPIScriptNotExist( int aScript ) {
        m_resourceId = aScript;
      }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;
  };

  class EGMAPISoundNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPISoundNotExist( int aSound ) {
        m_resourceId = aSound;
      }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;
  };

  class EGMAPISurfaceNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPISurfaceNotExist( int aSurface ) {
        m_resourceId = aSurface;
      }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;
  };

  class EGMAPIFontNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPIFontNotExist( int aFont ) {
        m_resourceId = aFont;
      }

    /// ShowError()
    ///   Shows message box with error message
    ///
    virtual void ShowError() const;
  };

  class EGMAPIParticleSystemNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPIParticleSystemNotExist( int aParticleSystem ) {
        m_resourceId = aParticleSystem;
     }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;
  };

  class EGMAPIParticleTypeNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPIParticleTypeNotExist( int aParticleTypeId ) {
        m_resourceId = aParticleTypeId;
     }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;
  };

  class EGMAPIChangerNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPIChangerNotExist( int aChanger ) {
        m_resourceId = aChanger;
     }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;
  };

  class EGMAPIDestroyerNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPIDestroyerNotExist( int aDestroyer ) {
        m_resourceId = aDestroyer;
     }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;
  };
  class EGMAPIDeflectorNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPIDeflectorNotExist( int aDeflector ) {
        m_resourceId = aDeflector;
     }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;
  };

  class EGMAPIAttractorNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPIAttractorNotExist( int aAttractor ) {
        m_resourceId = aAttractor;
     }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;
  };

  class EGMAPIEmitterNotExist: public EGMAPIResourceException {
    public:
      explicit EGMAPIEmitterNotExist( int aEmitter ) {
        m_resourceId = aEmitter;
     }

      /// ShowError()
      ///   Shows message box with error message
      ///
      virtual void ShowError() const;
  };

  /************************************************************************/
  /* GM resources accessors interfaces                                    */
  /************************************************************************/

  /// ISpriteSubimage
  ///   Interface that provides simplier access to the sprite subimage data.
  ///   It should be accessed only from within the ISpriteSubimages interface.
  ///
  class ISpriteSubimage {
    friend class ISpriteSubimages;

    public:
      /// GetBitmap()
      ///   Returns pointer to the sprite's subimage bitmap. The color
      ///   format is 32bit ARGB.
      ///
      /// Returns:
      ///   Pointer to the bitmap.
      ///
      inline unsigned char* GetBitmap();

      /// GetBitmapSize()
      ///   Returns the size of sprite's subimage bitmap in bytes.
      ///
      /// Returns:
      ///  Sprite's subimage bitmap size in bytes.
      ///
      inline unsigned long GetBitmapSize();

      /// GetTextureID()
      ///  Gets a texture ID of the subimage.
      ///
      /// Returns:
      ///   Texture ID of the subimage.
      ///
      inline int GetTextureID();

      /// GetTexture()
      ///  Retrieves a pointer to a Direct3DTexture interface associated
      ///  with the subimage's texture.
      ///
      /// Returns:
      ///   Pointer to IDirect3DTexture8 associated the subimage's texture.
      ///
      inline IDirect3DTexture8* GetTexture();

    private:
      static int m_subimage;
  };

  /// ISpriteSubimages
  ///   Interface that provides simplier access to the sprite subimages.
  ///   It should be accessed only from within the ISprite interface.
  ///
  class ISpriteSubimages {
    friend class ISprite;
    friend class ISprites;

    public:
      /// operator []
      ///   Provides access to specified sprite's subimage. Number specified
      ///   in brackets determines which subimage will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPIInvalidSubimage object in case when specifed number
      ///   of a subimage is not valid.
      ///
      /// Returns:
      ///   Reference to an ISpriteSubimage class instance.
      ///
      inline ISpriteSubimage& operator[]( int aSubimage );

      /// GetCount()
      ///   Returns number of subimages in the sprite.
      ///
      /// Returns:
      ///   Number of subimages.
      ///
      inline int GetCount();

    private:
      ISpriteSubimage m_subimage;
  };

  /// ISprite
  ///   Interface that provides simplier access to sprite data.
  ///   It should be accessed only from within the ISprites interface.
  ///
  class ISprite {
    friend class ISprites;
    friend class ISpriteSubimages;

    public:
      /// Sprite subimages accessor interface class instance
      ISpriteSubimages Subimages;

      /// GetName()
      ///   Gets the name of the sprite.
      ///
      /// Returns
      ///   Pointer to name of the sprite
      ///
      inline const char* GetName();

      /// GetWidth()
      ///   Returns width of the sprite.
      ///
      /// Returns:
      ///   Sprite's width.
      ///
      int GetWidth();

      /// GetHeight()
      ///   Returns height of the sprite.
      ///
      /// Returns:
      ///   Sprite's height.
      ///
      int GetHeight();

      /// GetOffsetX()
      ///   Returns sprite's X origin.
      ///
      /// Returns:
      ///   Sprite's X origin.
      ///
      int GetOffsetX() {
        return ( CGlobals::UseNewStructs() ? m_sprite->structNew.originX : m_sprite->structOld.originX );
      }

      /// GetOffsetY()
      ///   Returns sprite's Y origin.
      ///
      /// Returns:
      ///   Sprite's Y origin.
      ///
      int GetOffsetY() {
        return ( CGlobals::UseNewStructs() ? m_sprite->structNew.originY : m_sprite->structOld.originY );
      }

      /// SetOffset( int aOffsetX, int aOffsetY )
      ///   Sets the sprite's origins.
      ///
      /// Parameters:
      ///   aOffsetX: New X origin.
      ///   aOffsetY: New Y origin.
      ///
      void SetOffset( int aOffsetX, int aOffsetY );

      /// GetPreciseCollision()
      ///   Check whether sprite has enabled "Precise collision" option.
      ///   The function is not available in GM8.
      ///
      /// Returns:
      ///    Precise collision option state.
      ///
      bool GetPreciseCollision() {
        return m_sprite->structOld.preciseCollision;
      }

      /// SetPreciseCollision( bool aEnable )
      ///   Enables or disables precise collision checking.
      ///   The function is not available in GM8.
      ///
      /// Parameters:
      ///   aEnable: Specifies whether to enable or disable precise
      ///            collision checking.
      ///
      void SetPreciseCollision( bool aEnable ) {
        m_sprite->structOld.preciseCollision = aEnable;
      }

      /// GetTransparent()
      ///   Check whether sprite has enabled option "Transparent".
      ///   The function is not available in GM8.
      ///
      /// Returns:
      ///   "Transparent" option state.
      ///
      bool GetTransparent() {
        return m_sprite->structOld.transparent;
      }

      /// GetSmoothEdges()
      ///   Check whether sprite has enabled option "Smooth edges".
      ///   The function is not available in GM8.
      ///
      /// Returns:
      ///   "Smooth edges" option state.
      ///
      bool GetSmoothEdges() {
        return m_sprite->structOld.smoothEdges;
      }

      /// GetPreload()
      ///   Check whether sprite has enabled option "Preload".
      ///   The function is not available in GM8.
      ///
      /// Returns:
      ///   "Preload" option state.
      ///
      bool GetPreload() {
        return m_sprite->structOld.preload;
      }

      /// GetBoundingBoxType()
      ///   Gets type of the sprite bounding box.
      ///   The function is not available in GM8.
      ///
      /// Returns:
      ///   Type of the bounding box.
      ///
      BoundingBoxType GetBoundingBoxType() {
        return m_sprite->structOld.bboxType;
      }

      /// SetBoundingBoxType( BoundingBoxType aType )
      ///   Changes type of the sprite bounding box.
      ///   The function is not available in GM8.
      ///
      /// Parameters:
      ///   aType: New type of bounding box.
      ///
      void SetBoundingBoxType( BoundingBoxType aType ) {
        m_sprite->structOld.bboxType = aType;
      }

      /// GetBoundingBoxLeft()
      ///   Gets sprite's left side of the bounding box.
      ///
      /// Returns:
      ///   Left side of the bounding box.
      ///
      int GetBoundingBoxLeft() {
        return ( CGlobals::UseNewStructs() ? m_sprite->structNew.bboxLeft : m_sprite->structOld.bboxLeft );
      }

      /// GetBoundingBoxRight()
      ///   Gets sprite's right side of the bounding box.
      ///
      /// Returns:
      ///   Right side of the bounding box.
      ///
      int GetBoundingBoxRight() {
        return ( CGlobals::UseNewStructs() ? m_sprite->structNew.bboxRight : m_sprite->structOld.bboxRight );
      }

      /// GetBoundingBoxTop()
      ///   Gets sprite's top side of the bounding box.
      ///
      /// Returns:
      ///   Top side of the bounding box.
      ///
      int GetBoundingBoxTop() {
        return ( CGlobals::UseNewStructs() ? m_sprite->structNew.bboxTop : m_sprite->structOld.bboxTop );
      }

      /// GetBoundingBoxBottom()
      ///   Gets sprite's bottom side of the bounding box.
      ///
      /// Returns:
      ///   Bottom side of the bounding box.
      ///
      int GetBoundingBoxBottom() {
        return ( CGlobals::UseNewStructs() ? m_sprite->structNew.bboxBottom : m_sprite->structOld.bboxBottom );
      }

      /// SetBoundingBox( int aLeft, int aRight, int aTop, int aBottom )
      ///   Sets the sprite bounding box.
      ///
      /// Parameters:
      ///   aLeft: New left side of bbox.
      ///   aRight: New right side of bbox.
      ///   aTop: New top side of bbox.
      ///   aBottom: New bottom side of bbox.
      ///
      void SetBoundingBox( int aLeft, int aRight, int aTop, int aBottom );

      /// SpritePtr()
      ///   Returns pointer to the GMSPRITE structure of the sprite
      ///
      /// Returns:
      ///   Pointer to the GMSPRITE structure of the sprite.
      ///
      static PGMSPRITE GetPtr() {
        return m_sprite;
      }

    private:
      static PGMSPRITE m_sprite;
      static int m_spriteId;
  };

  /// ISprites
  ///   Interface that provides simplier access to the game's sprites.
  ///   It should be accessed only from within the CGMAPI class.
  ///
  class ISprites {
    friend class CGMAPI;

    public:
      /// operator []
      ///   Provides access to the specified sprite. ID specified in
      ///   the brackets determines which sprite will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPISpriteNotExists object in case when the sprite of ID
      ///   specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an ISprite class instance.
      ///
      inline ISprite& operator[]( int aSpriteId );

      /// GetID( const char* aSpriteName )
      ///   Gets the ID of a specifed sprite.
      ///
      /// Parameters:
      ///   aSpriteName: Name of the sprite.
      ///
      /// Returns:
      ///   Specified sprite's ID. If sprite with specified name does
      ///   not exists, then return value will be -1.
      ///
      int GetID( const char* aSpriteName );

      /// Exists( int aSpriteId )
      ///   Checks whether a specified sprite exists.
      ///
      /// Parameters:
      ///   aSpriteId: ID of the sprite.
      ///
      /// Returns:
      ///   True if the sprite exists.
      ///
      bool Exists( int aSpriteId );

      /// GetCount()
      ///   Returns total number of sprites in the game.
      ///
      /// Returns:
      ///   Total number of sprites.
      ///
      int GetCount();

      /// GetArraySize()
      ///   Returns the size of dynamic arrays that holds pointers
      ///   to sprites' structures and names.
      ///
      /// Returns:
      ///   Number of elements in the arrays.
      ///
      inline int GetArraySize();

    private:
      ISprite m_iSprite;
  };

  /// IBackground
  ///   Interface that provides simplier access to background data.
  ///   It should be accessed only from within the IBackgrounds interface.
  ///
  class IBackground {
    friend class IBackgrounds;

    public:
      /// GetName()
      ///   Gets the name of the background.
      ///
      /// Returns
      ///   Pointer to name of this background.
      ///
      const char* GetName();

      /// GetWidth()
      ///   Returns width of the background.
      ///
      /// Returns:
      ///   Background's width.
      ///
      int GetWidth();

      /// GetHeight()
      ///   Returns height of the background.
      ///
      /// Returns:
      ///   Background's height.
      ///
      int GetHeight();

      /// GetBitmap()
      ///   Returns pointer to the background's bitmap. The color
      ///   format is 32bit ARGB.
      ///
      /// Returns:
      ///   Pointer to the bitmap or NULL if the bitmap has not been
      ///   loaded.
      ///
      unsigned char* GetBitmap();

      /// GetBitmapSize()
      ///   Returns the size of background's bitmap in bytes.
      ///
      /// Returns:
      ///  Background's bitmap size in bytes.
      ///
      unsigned long GetBitmapSize();

      /// GetTextureID()
      ///  Gets a texture ID of the background.
      ///
      /// Returns:
      ///   Texture ID of the background.
      ///
      int GetTextureID();

      /// GetTexture()
      ///  Retrieves a pointer to an IDirect3DTexture interface
      ///  associated with the background's texture.
      ///
      /// Returns:
      ///   Pointer to IDirect3DTexture8 associated with background's texture.
      ///
      inline IDirect3DTexture8* GetTexture();

      /// GetTransparent()
      ///   Check whether background has enabled option "Transparent".
      ///   The function is not available in GM8.
      ///
      /// Returns:
      ///  "Transparent" option state.
      ///
      inline bool GetTransparent();

      /// GetSmoothEdges()
      ///   Checks whether the background has enabled option "Smooth edges".
      ///   The function is not available in GM8.
      ///
      /// Returns:
      ///   "Smooth edges" option state.
      ///
      inline bool GetSmoothEdges();

      /// GetPreload()
      ///   Checks whether the background has enabled option "Preload".
      ///   The function is not available in GM8.
      ///
      /// Returns:
      ///   "Preload" option state.
      ///
      inline bool GetPreload();

    private:
      static int m_backgroundId;
      static PGMBACKGROUND m_background;
  };

  /// IBackgrounds
  ///   Interface that provides simplier access to the game's backgrounds.
  ///   It should be accessed only from within the CGMAPI class.
  ///
  class IBackgrounds {
    public:
      /// operator []
      ///   Provides access to the specified background. ID specified in
      ///   the brackets determines which background will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPIBackgroundNotExists object in case when background of ID
      ///   specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an IBackground class instance.
      ///
      inline IBackground& operator[]( int aBackgroundId );

      /// GetID( const char* aBackgroundName )
      ///   Gets the ID of a specifed background.
      ///
      /// Parameters:
      ///   aBackgroundName: Name of the background.
      ///
      /// Returns:
      ///   Specified background's ID. If background with specified name does
      ///   not exists, then return value will be -1.
      ///
      int GetID( const char* aBackgroundName );

      /// Exists( int aBackgroundId )
      ///   Checks whether specified background exists.
      ///
      /// Parameters:
      ///   aBackgroundId: ID of the background.
      ///
      /// Returns:
      ///   True if the background exists.
      ///
      bool Exists( int aBackgroundId );

      /// GetCount()
      ///   Returns total number of backgrounds in the game.
      ///
      /// Returns:
      ///   Total number of backgrounds.
      ///
      int GetCount();

      /// GetArraySize()
      ///   Returns the size of dynamic arrays that holds pointers
      ///   to backgrounds' structures and names.
      ///
      /// Returns:
      ///   Number of elements in the arrays.
      ///
      inline int GetArraySize();

    private:
      IBackground m_iBackground;
  };

  /// ISurface
  ///   Interface that provides simplier access to surface data.
  ///   It should be accessed only from within the ISurfaces interface.
  ///
  class ISurface {
    friend class ISurfaces;

    public:
      /// GetWidth()
      ///  Gets width of the surface.
      ///
      /// Returns:
      ///   Width of this surface.
      ///
      inline int GetWidth();

      /// GetHeight()
      ///  Gets height of the surface.
      ///
      /// Returns:
      ///   Height of this surface.
      ///
      inline int GetHeight();

      /// GetTextureID()
      ///  Gets a texture ID of the surface.
      ///
      /// Returns:
      ///   Texture ID of the surface.
      ///
      inline int GetTextureID();

      /// GetTexture()
      ///  Retrieves the pointer to an IDirect3DTexture interface
      ///  associated with the surface's texture.
      ///
      /// Returns:
      ///   Pointer to IDirect3DTexture interface associated with
      ///   the surface's texture.
      ///
      inline IDirect3DTexture8* GetTexture();

    private:
      static int m_surfaceId;
  };


  /// ISurfaces
  ///   Interface that provides simplier access to the game's surfaces.
  ///   It should be accessed only from within the CGMAPI class.
  ///
  class ISurfaces {
    friend class CGMAPI;

    public:
      /// operator []
      ///   Provides access to the specified surface. ID specified in
      ///   the brackets determines which surface will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPISurfaceNotExists object in case when surface of ID
      ///   specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an ISurface class instance.
      ///
      inline ISurface& operator[]( int aSurfaceId );

      /// Exists( int aSurfaceId )
      ///   Checks whether specified surface exists.
      ///
      /// Parameters:
      ///   aSurfaceId: ID of the surface.
      ///
      /// Returns:
      ///   True if the surface exists.
      ///
      inline bool Exists( int aSurfaceId );

      /// GetCount()
      ///   Returns total number of surfaces in the game.
      ///
      /// Returns:
      ///   Total number of surfaces.
      ///
      int GetCount();

      /// GetArraySize()
      ///   Returns the size of dynamic array that holds surfaces' data.
      ///
      /// Returns:
      ///   Number of elements in the array.
      ///
      inline int GetArraySize();

    private:
      ISurface m_iSurface;
  };

  /// IScript
  ///   Interface that provides simplier access to script data.
  ///   It should be accessed only from within the IScripts interface.
  ///
  class IScript {
    friend class IScripts;

    public:
      /// GetScriptLength()
      ///   Gets length in characters of the script.
      ///
      /// Returns:
      ///   Length of the script.
      ///
      unsigned long GetScriptLength();

      /// GetScript( char* aBuffer )
      ///   Gets the script's code.
      ///
      /// Parameters:
      ///   aBuffer: Pointer to an array of char. Buffer must be large
      ///            enough to hold the whole code - use the GetScriptLength()
      ///            method to find out the length of the script.
      ///
      /// Returns:
      ///   Pointer specified in aBuffer parameter.
      ///
      char* GetScript( char* aBuffer );

      /// GetName()
      ///   Gets the name of the script.
      ///
      /// Returns
      ///   Pointer to the script's name.
      ///
      inline const char* GetName();

    private:
      static int m_scriptId;
  };

  /// IScripts
  ///   Interface that provides simplier access to the game's scripts.
  ///   It should be accessed only from within the CGMAPI class.
  ///
  class IScripts {
    public:
      /// operator []
      ///   Provides access to the specified script. ID specified in
      ///   the brackets determines which script will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPIScriptNotExists object in case when script of ID
      ///   specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an IScript class instance.
      ///
      inline IScript& operator[]( int aScriptId );

      /// GetCount()
      ///   Returns total number of the scripts in the game.
      ///
      ///  Returns:
      ///    Total number of the scripts.
      int GetCount();

      /// Exists( int aScriptId )
      ///   Checks whether the specified script exists.
      ///
      /// Parameters:
      ///   aScriptId: ID of the script.
      ///
      /// Returns:
      ///   True if the script exists.
      ///
      inline bool Exists( int aScriptId );

      /// GetID( const char* aBackgroundName )
      ///   Gets the ID of a specifed script.
      ///
      /// Parameters:
      ///   aScriptName: Name of the script.
      ///
      /// Returns:
      ///   Specified script's ID. If script with specified name does
      ///   not exists, then return value will be -1.
      ///
      int GetID( const char* aScriptName );

      /// GetArraySize()
      ///   Returns the size of dynamic arrays that holds pointers
      ///   to scripts' structures and names.
      ///
      /// Returns:
      ///   Number of elements in the arrays.
      ///
      inline int GetArraySize();

    private:
      IScript m_iScript;
  };

  /// ISound
  ///   Interface that provides simplier access to sound data.
  ///   It should be accessed only from within the ISounds interface.
  ///
  class ISound {
    friend class ISounds;

    public:
      /// GetType()
      ///   Gets the type of the sound.
      ///
      /// Returns:
      ///   Type of the sound (Normal/Background music/3D sound/MM player).
      ///
      inline SoundType GetType();

      /// GetExtension()
      ///   Gets extension of the sound's file (.wav/.mid/.mp3 etc.).
      ///
      /// Returns:
      ///   File extension as string or NULL if no file was selected for the sound.
      ///
      inline const char* GetExtension();

      /// GetFilename()
      ///   Gets the sound's filename.
      ///
      /// Returns:
      ///   Sound's filename or NULL if no file was selected for this sound.
      ///
      inline const char* GetFilename();

      /// GetFilePath()
      ///   Gets the path to sound's temporary file.
      ///
      /// Returns:
      ///   Path to the sound file if using multimedia player to play the
      ///   sound & it is preloaded, otherwise NULL.
      ///
      inline const char* GetFilePath();

      /// GetName()
      ///   Gets the name of the sound.
      ///
      /// Returns:
      ///   Pointer to the name of this sound.
      ///
      inline const char* GetName();

      /// GetVolume()
      ///   Gets the volume of the sound.
      ///
      /// Returns:
      ///   Sound volume (0.00 == muted, 1.00 == full volume).
      ///
      inline double GetVolume();

      /// GetPanning()
      ///   Gets the panning of the sound.
      ///
      /// Returns:
      ///   Sound panning (-1.00 == left, 0 == center, 1.00 == right).
      ///
      inline double GetPanning();

      /// GetPreload()
      ///   Checks whether preload option is set.
      ///
      /// Returns:
      ///   Preload option state.
      ///
      inline bool GetPreload();

      /// GetEffectChorus()
      ///   Checks whether chorus effect is set.
      ///
      /// Returns:
      ///   Chorus effect option state.
      ///
      inline bool GetEffectChorus();

      /// GetEffectEcho()
      ///   Checks whether echo effect is set.
      ///
      /// Returns:
      ///   Echo effect option state.
      ///
      inline bool GetEffectEcho();

      /// GetEffectFlanger()
      ///   Checks whether flanger effect is set.
      ///
      /// Returns:
      ///   Flanger effect option state.
      ///
      inline bool GetEffectFlanger();

      /// GetEffectReverb()
      ///   Checks whether reverb effect is set.
      ///
      /// Returns:
      ///   Reverb effect option state.
      ///
      inline bool GetEffectReverb();

      /// GetEffectGargle()
      ///   Checks whether gargle effect is set.
      ///
      /// Returns:
      ///   Gargle effect option state.
      ///
      inline bool GetEffectGargle();

      /// GetData()
      ///   Returns pointer to sound's file loaded to memory.
      ///
      /// Returns:
      ///   Pointer to memory block that contains the whole sound file.
      ///   Use GetDataSize() method to check size of the file.
      ///   Returns NULL, if the sound has no file selected or using multimedia
      ///   player (sound type SND_MULTIMEDIA) to play the sound AND it is preloaded
      ///   (when it is not preloaded - the method returns valid pointer to file).
      ///
      inline unsigned char* GetData();

      /// GetDataSize()
      ///   Gets size of the sound's file loaded to memory.
      ///
      /// Returns:
      ///   Size of the sound's file.
      ///
      inline unsigned long GetDataSize();

    private:
      static int m_soundId;
  };

  /// ISounds
  ///   Interface that provides simplier access to the game's sounds.
  ///   It should be accessed only from within the CGMAPI class.
  ///
  class ISounds {
    public:
      /// operator []
      ///   Provides access to the specified sound. ID specified in
      ///   the brackets determines which sound will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPISoundNotExists object in case when script of ID
      ///   specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an ISound class instance.
      ///
      inline ISound& operator[]( int aSoundId );

      /// GetCount()
      ///   Returns total number of the sounds in the game.
      ///
      ///  Returns:
      ///    Total number of the sounds.
      ///
      int GetCount();

      /// GetArraySize()
      ///   Returns the size of dynamic arrays that holds pointers
      ///   to sounds' structures and names.
      ///
      /// Returns:
      ///   Number of elements in the arrays.
      ///
      inline int GetArraySize();

      /// Exists( int aSoundId )
      ///   Checks whether the specified sound exists.
      ///
      /// Parameters:
      ///   aSoundId: ID of the sound.
      ///
      /// Returns:
      ///   True if the sound exists.
      ///
      inline bool Exists( int aSoundId );

      /// GetID( const char* aSoundName )
      ///   Gets ID of the specifed sound.
      ///
      /// Parameters:
      ///   aSoundName: Name of the sound.
      ///
      /// Returns:
      ///   Specified sound's ID. If sound with specified name does
      ///   not exists, then return value will be -1.
      ///
      int GetID( const char* aSoundName );

    private:
      ISound m_iSound;
  };


  /// IFont
  ///   Interface that provides simplier access to font data.
  ///   It should be accessed only from within the IFonts interface.
  ///
  class IFont {
    friend class IFonts;

    public:
      /// IsSpriteBased()
      ///   Checks whether the font is created from a sprite (font_add_sprite).
      ///   Non sprite-based fonts uses a bitmap generated from specified typeface
      ///   instead of sprites.
      ///
      bool IsSpriteBased() {
        return ( GetSpriteID() != -1 );
      }

      /// GetFontTypefaceName()
      ///   Gets name of the typeface used to create the font.
      ///
      /// Returns:
      ///   Name of the typeface or NULL if the font is created from a sprite.
      ///
      inline const char* GetFontTypefaceName();

      /// GetFontSize()
      ///   Gets size of the font.
      ///
      /// Returns:
      ///   Size of the font or 0 if the font is created from a sprite.
      ///
      inline int GetFontSize();

      /// GetBold()
      ///   Checks whether the font is bolded.
      ///
      /// Returns:
      ///   True if the font is bolded. If the font is created from a sprite,
      ///   then function will return false.
      ///
      inline bool GetBold();

      /// GetItalic()
      ///   Checks whether the font is italicized.
      ///
      /// Returns:
      ///   True if the font is italicized. If the font is created from a sprite,
      ///   then function will return false.
      ///
      inline bool GetItalic();

      /// GetRangeLow()
      ///   Returns the beginning of a range of characters that font uses.
      ///
      /// Returns:
      ///   Beginning of the character range.
      ///
      inline int GetRangeLow();

      /// GetRangeHigh()
      ///   Returns the end of a range of characters that font uses.
      ///
      /// Returns:
      ///   End of the character range.
      ///
      inline int GetRangeHigh();

      /// GetSpriteID()
      ///   Gets ID of a sprite that is used to draw the font.
      ///
      /// Returns:
      ///   ID of sprite used to draw the font or -1 if it isn't a sprite-based font.
      ///
      inline int GetSpriteID();

      /// GetBitmap()
      ///   Returns a pointer to the bitmap generated for the font created from a typeface.
      ///   The color format is A8 (8-bit; alpha channel only).
      ///
      /// Returns:
      ///   Pointer to the bitmap or NULL if it is a font created from a sprite.
      ///
      inline unsigned char* GetBitmap();

      /// GetBitmapWidth()
      ///   Returns the width of the bitmap.
      ///
      /// Returns:
      ///   Width of the bitmap or 0 if it is a font created from a sprite.
      ///
      inline int GetBitmapWidth();

      /// GetBitmapHeight()
      ///   Returns the height of the bitmap.
      ///
      /// Returns:
      ///   Height of the bitmap or 0 if it is a font created from a sprite.
      ///
      inline int GetBitmapHeight();

      /// GetBitmapSize()
      ///   Returns the size in bytes of the bitmap.
      ///
      /// Returns:
      ///   Size of the bitmap or 0 if it is a font created from a sprite.
      ///
      inline unsigned long GetBitmapSize();

      /// GetTextureID()
      ///   Gets ID of a texture of the bitmap that is used to draw the font.
      ///
      /// Returns:
      ///   ID of texture used to draw the font or -1 if it is a sprite-based font.
      ///
      inline int GetTextureID();

      /// GetTexture()
      ///  Retrieves a pointer to a IDirect3DTexture interface associated
      ///  with font's texture.
      ///
      /// Returns:
      ///   Pointer to IDirect3DTexture8 interface or NULL of it is a
      ///   sprite-based font.
      ///
      inline IDirect3DTexture8* GetTexture();

      /// GetCharPositionX( unsigned char aCharacter )
      ///   Gets X position of specified character on the bitmap.
      ///
      /// Returns:
      ///   Position of the character or 0 if it is a sprite-based font.
      ///
      inline int GetCharPositionX( unsigned char aCharacter );

      /// GetCharPositionY( unsigned char aCharacter )
      ///   Gets Y position of specified character on the bitmap.
      ///
      /// Returns:
      ///   Position of the character or 0 if it is a sprite-based font.
      ///
      inline int GetCharPositionY( unsigned char aCharacter );

      /// GetCharBoundingBoxLeft( unsigned char aCharacter )
      ///   Returns offset of the left side of specified character's
      ///   bounding box. (used in proportional fonts)
      ///
      /// Returns:
      ///   Offset of the left side of character's bounding box.
      ///
      inline int GetCharBoundingBoxLeft( unsigned char aCharacter );

      /// GetCharBoundingBoxRight( unsigned char aCharacter )
      ///   Returns offset of the right side of specified character's
      ///   bounding box. (used in proportional fonts)
      ///
      /// Returns:
      ///   Offset of the right side of character's bounding box.
      ///
      inline int GetCharBoundingBoxRight( unsigned char aCharacter );

      /// GetCharBoundingBoxTop( unsigned char aCharacter )
      ///   Returns offset of the top side of specified character's
      ///   bounding box. (used in proportional fonts)
      ///
      /// Returns:
      ///   Offset of the top side of character's bounding box.
      ///
      inline int GetCharBoundingBoxTop( unsigned char aCharacter );

      /// GetCharBoundingBoxBottom( unsigned char aCharacter )
      ///   Returns offset of the bottom side of specified character's
      ///   bounding box. (used in proportional fonts)
      ///
      /// Returns:
      ///   Offset of the bottom side of character's bounding box.
      ///
      inline int GetCharBoundingBoxBottom( unsigned char aCharacter );

    private:
      static int m_fontId;
  };

  /// ISounds
  ///   Interface that provides simplier access to the game's fonts.
  ///   It should be accessed only from within the CGMAPI class.
  ///
  class IFonts {
    public:
      /// operator []
      ///   Provides access to the specified font. ID specified in
      ///   the brackets determines which font will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPIFontNotExists object in case when font of ID
      ///   specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an IFonts class instance.
      ///
      inline IFont& operator[]( int aFontId );

      /// GetCount()
      ///   Returns total number of the fonts in the game.
      ///
      ///  Returns:
      ///    Total number of the fonts.
      ///
      int GetCount();

      /// GetArraySize()
      ///   Returns the size of dynamic arrays that holds pointers
      ///   to fonts' structures and names.
      ///
      /// Returns:
      ///   Number of elements in the arrays.
      ///
      inline int GetArraySize();

      /// Exists( int aFontId )
      ///   Checks whether the specified font exists.
      ///
      /// Parameters:
      ///   aFontId: ID of the font.
      ///
      /// Returns:
      ///   True if the font exists.
      ///
      inline bool Exists( int aFontId );

      /// GetID( const char* aFontName )
      ///   Gets ID of the specified font.
      ///
      /// Parameters:
      ///   aFontName: Name of the font.
      ///
      /// Returns:
      ///   Specified font's ID. If the font with specified name
      ///   doesn't exists, then return value will be -1.
      ///
      int GetID( const char* aFontName );

  private:
    IFont m_iFont;
  };

  /// IEmitter
  ///   Interface that provides simplier access to emitter data.
  ///   It should be accessed only from within the IEmitters interface.
  ///
  class IEmitter {
    friend class IEmitters;

    public:
      /// GetStreamNumber()
      ///   Gets number of particles created per step.
      ///
      /// Returns:
      ///   Number of particles created per step.
      ///
      inline int GetStreamNumber();

      /// SetStreamNumber( int aNumber )
      ///   Sets the number of particles created per step.
      ///
      /// Parameters:
      ///   aNumber: Number of particles to create per step.
      ///
      inline void SetStreamNumber( int aNumber );

      /// GetMinX()
      ///   Gets the first X coordinate of the emitter region.
      ///
      /// Returns:
      ///   First X coordinate of the emitter region.
      ///
      inline double GetMinX();

      /// GetMaxX()
      ///   Gets the second X coordinate of the emitter region.
      ///
      /// Returns:
      ///   Second X coordinate of the emitter region.
      ///
      inline double GetMaxX();

      /// GetMinX()
      ///   Gets the first X coordinate of the emitter region.
      ///
      /// Returns:
      ///   First X coordinate of the emitter region.
      ///
      inline double GetMinY();

      /// GetMaxY()
      ///   Gets the second Y coordinate of the emitter region.
      ///
      /// Returns:
      ///   Second Y coordinate of the emitter region.
      ///
      inline double GetMaxY();

      /// SetMinX( double aX )
      ///   Sets the first X coordinate of the emitter region.
      ///
      /// Parameters:
      ///   aX: New X coordinate.
      ///
      inline void SetMinX( double aX );

      /// SetMaxX( double aX )
      ///   Sets the second X coordinate of the emitter region.
      ///
      /// Parameters:
      ///   aX: New X coordinate.
      ///
      inline void SetMaxX( double aX );

      /// SetMinY( double aY )
      ///   Sets the first Y coordinate of the emitter region.
      ///
      /// Parameters:
      ///   aY: New Y coordinate.
      ///
      inline void SetMinY( double aY );

      /// SetMaxY( double aY )
      ///   Sets the second Y coordinate of the emitter region.
      ///
      /// Parameters:
      ///   aY: New Y coordinate.
      ///
      inline void SetMaxY( double aY );

      /// GetDistribution()
      ///   Gets the emitter's distribution.
      ///
      /// Returns:
      ///   Distribution type (gm::ps_distr_*).
      ///
      inline int GetDistribution();

      /// GetShape()
      ///   Gets the shape of the emitter's region.
      ///
      /// Returns:
      ///   Shape of the region (gm::ps_shape_*)
      inline int GetShape();

      /// GetParticleTypeID()
      ///   Gets the particle type used to create the particles.
      ///
      /// Returns:
      ///   ID of the particle type.
      ///
      inline int GetParticleTypeID();

      /// SetDistribution( int aDistribution )
      ///   Sets the emitter's distribution.
      ///
      /// Parameters:
      ///   aDistribution: New type of the distribution (gm::ps_distr_*)
      ///
      inline void SetDistribution( int aDistribution );

      /// SetShape( int aShape )
      ///   Sets the shape of the emitter's region.
      ///
      /// Parameters: New shape (gm::ps_shape_*)
      ///
      inline void SetShape( int aShape );

      /// SetParticleType( int aParticleTypeId )
      ///   Sets the particle type used to create the particles.
      ///
      /// Parameters:
      ///   aParticleTypeId: ID of the particle type.
      ///
      inline void SetParticleType( int aParticleTypeId );

    private:
      int m_emitterId;
  };

  /// IEmitters
  ///   Interface that provides simplier access to particle system's emitters.
  ///   It should be accessed only from within the IParticleSystem interface.
  ///
  class IEmitters {
    public:
      /// operator []
      ///   Provides access to the specified emitter. ID specified in
      ///   the brackets determines which emitter will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPIEmitterNotExists object in case when emitter of ID
      ///   specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an IEmitter class instance.
      ///
      inline IEmitter& operator[]( int aEmitterId );

      /// GetCount()
      ///   Returns total number of the emitters in the particle system.
      ///
      ///  Returns:
      ///    Total number of the emitters.
      ///
      int GetCount();

      /// GetArraySize()
      ///   Returns the size of dynamic array that holds data of the
      ///   emitters.
      ///
      /// Returns:
      ///   Number of elements in the array.
      ///
      inline int GetArraySize();

      /// Exists( int aEmitterId )
      ///   Checks whether the specified emitter exists.
      ///
      /// Parameters:
      ///   aFontId: ID of the emitter.
      ///
      /// Returns:
      ///   True if the emitter exists.
      ///
      inline bool Exists( int aEmitterId );

    private:
      IEmitter m_iEmitter;
  };

  /// IAttractor
  ///   Interface that provides simplier access to attractor data.
  ///   It should be accessed only from within the IAttractors interface.
  ///
  class IAttractor {
    friend class IAttractors;

    public:
      /// GetX()
      ///   Gets X position of the attractor.
      ///
      /// Returns:
      ///   Emitter's X position.
      ///
      inline double GetX();

      /// GetY()
      ///   Gets Y position of the attractor.
      ///
      /// Returns:
      ///   Emitter's Y position.
      ///
      inline double GetY();

      /// SetX( double aX )
      ///   Sets X position of the attractor.
      ///
      /// Parameters:
      ///   aX: New X position.
      ///
      inline void SetX( double aX );

      /// SetY( double aY )
      ///   Sets Y position of the attractor.
      ///
      /// Parameters:
      ///   aY: New Y position.
      ///
      inline void SetY( double aY );

      /// GetForce()
      ///   Gets the force of the attractor.
      ///
      /// Returns:
      ///   Attractor's force.
      ///
      inline double GetForce();

      /// GetDistance()
      ///   Gets the distance of the attractor.
      ///
      /// Returns:
      ///   Attractor's distance.
      ///
      inline double GetDistance();

      /// SetForce( double aForce )
      ///   Sets the attractor's force.
      ///
      /// Parameters:
      ///   aForce: New force.
      ///
      inline void SetForce( double aForce );

      /// SetDistance( double aDistance )
      ///   Sets the attractor's distance.
      ///
      /// Parameters:
      ///   aDistance: New distance.
      ///
      inline void SetDistance( double aDistance );

      /// GetKind()
      ///   Gets the kind of the attractor.
      ///
      /// Returns:
      ///   Attractor's kind. (gm::ps_force_*)
      ///
      inline int GetKind();

      /// SetKind( int aKind )
      ///   Sets the attractor's kind.
      ///
      /// Parameters:
      ///   aDistance: New kind. (gm::ps_force_*)
      ///
      inline void SetKind( int aKind );

      /// IsAdditive()
      ///   Checks whether the attractor uses additive force.
      ///
      /// Returns:
      ///   "Additive" property state.
      ///
      inline bool IsAdditive();

      /// SetAdditive( bool aAdditive )
      ///   Enables or disables usage of the additive force property.
      ///
      /// Parameters:
      ///   aAdditive: Specifies whether to enable or disable the property.
      ///
      inline void SetAdditive( bool aAdditive );

    private:
      int m_attractorId;
  };

  /// IAttractors
  ///   Interface that provides simplier access to particle system's attractors.
  ///   It should be accessed only from within the IParticleSystem interface.
  ///
  class IAttractors {
    public:
      /// operator []
      ///   Provides access to the specified attractor. ID specified in
      ///   the brackets determines which attractor will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPIAttractorNotExists object in case when emitter of ID
      ///   specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an IAttractor class instance.
      ///
      inline IAttractor& operator[]( int aAttractorId );

      /// GetCount()
      ///   Returns total number of the attractors in the particle system.
      ///
      ///  Returns:
      ///    Total number of the attractors.
      ///
      int GetCount();

      /// GetArraySize()
      ///   Returns the size of dynamic array that holds data of the
      ///   attractors.
      ///
      /// Returns:
      ///   Number of elements in the array.
      ///
      inline int GetArraySize();

      /// Exists( int aAttractorId )
      ///   Checks whether the specified attractor exists.
      ///
      /// Parameters:
      ///   aFontId: ID of the attractor.
      ///
      /// Returns:
      ///   True if the attractor exists.
      ///
      inline bool Exists( int aAttractorId );

  private:
    IAttractor m_iAttractor;
  };

  /// IDeflector
  ///   Interface that provides simplier access to deflector data.
  ///   It should be accessed only from within the IDeflectors interface.
  ///
  class IDeflector {
    friend class IDeflectors;

    public:
      /// GetMinX()
      ///   Gets the first X coordinate of the deflector region.
      ///
      /// Returns:
      ///   First X coordinate of the deflector region.
      ///
      inline double GetMinX();

      /// GetMaxX()
      ///   Gets the second X coordinate of the deflector region.
      ///
      /// Returns:
      ///   Second X coordinate of the deflector region.
      ///
      inline double GetMaxX();

      /// GetMinX()
      ///   Gets the first X coordinate of the deflector region.
      ///
      /// Returns:
      ///   First X coordinate of the deflector region.
      ///
      inline double GetMinY();

      /// GetMaxY()
      ///   Gets the second Y coordinate of the deflector region.
      ///
      /// Returns:
      ///   Second Y coordinate of the deflector region.
      ///
      inline double GetMaxY();

      /// SetMinX( double aX )
      ///   Sets the first X coordinate of the deflector region.
      ///
      /// Parameters:
      ///   aX: New X coordinate.
      ///
      inline void SetMinX( double aX );

      /// SetMaxX( double aX )
      ///   Sets the second X coordinate of the deflector region.
      ///
      /// Parameters:
      ///   aX: New X coordinate.
      ///
      inline void SetMaxX( double aX );

      /// SetMinY( double aY )
      ///   Sets the first Y coordinate of the deflector region.
      ///
      /// Parameters:
      ///   aY: New Y coordinate.
      ///
      inline void SetMinY( double aY );

      /// SetMaxY( double aY )
      ///   Sets the second Y coordinate of the deflector region.
      ///
      /// Parameters:
      ///   aY: New Y coordinate.
      ///
      inline void SetMaxY( double aY );

      /// GetKind()
      ///   Gets the kind of the deflector.
      ///
      /// Returns:
      ///   Kind of the deflector. (gm::ps_deflect_*)
      ///
      inline int GetKind();

      /// SetKind( int aKind )
      ///   Sets the kind of the deflector.
      ///
      /// Parameters:
      ///   aKind: New kind. (gm::ps_deflect_*)
      ///
      inline void SetKind( int aKind );

      /// GetFriction()
      ///   Gets the friction of the deflector.
      ///
      /// Returns:
      ///   Friction of the deflector.
      ///
      inline double GetFriction();

      /// SetKind( int aFriction )
      ///   Sets the friction of the deflector.
      ///
      /// Parameters:
      ///   aFriction: New friction.
      ///
      inline void SetFriction( double aFriction );

    private:
      int m_deflectorId;
  };

  /// IDeflectors
  ///   Interface that provides simplier access to particle system's deflectors.
  ///   It should be accessed only from within the IParticleSystem interface.
  ///
  class IDeflectors {
    public:
      /// operator []
      ///   Provides access to the specified deflector. ID specified in
      ///   the brackets determines which deflector will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPIDeflectorNotExists object in case when deflector of ID
      ///   specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an IDeflector class instance.
      ///
      inline IDeflector& operator[]( int aDeflectorId );

      /// GetCount()
      ///   Returns total number of the deflectors in the particle system.
      ///
      ///  Returns:
      ///    Total number of the deflectors.
      ///
      int GetCount();

      /// GetArraySize()
      ///   Returns the size of dynamic array that holds data of the
      ///   deflectors.
      ///
      /// Returns:
      ///   Number of elements in the array.
      ///
      inline int GetArraySize();

      /// Exists( int aDeflectorId )
      ///   Checks whether the specified deflector exists.
      ///
      /// Parameters:
      ///   aFontId: ID of the deflector.
      ///
      /// Returns:
      ///   True if the deflector exists.
      ///
      inline bool Exists( int aDeflectorId );

  private:
    IDeflector m_iDeflector;
  };

  /// IDestroyer
  ///   Interface that provides simplier access to destroyer data.
  ///   It should be accessed only from within the IDestroyers interface.
  ///
  class IDestroyer {
    friend class IDestroyers;

    public:
      /// GetMinX()
      ///   Gets the first X coordinate of the destroyer region.
      ///
      /// Returns:
      ///   First X coordinate of the destroyer region.
      ///
      inline double GetMinX();

      /// GetMaxX()
      ///   Gets the second X coordinate of the destroyer region.
      ///
      /// Returns:
      ///   Second X coordinate of the destroyer region.
      ///
      inline double GetMaxX();

      /// GetMinX()
      ///   Gets the first X coordinate of the destroyer region.
      ///
      /// Returns:
      ///   First X coordinate of the destroyer region.
      ///
      inline double GetMinY();

      /// GetMaxY()
      ///   Gets the second Y coordinate of the destroyer region.
      ///
      /// Returns:
      ///   Second Y coordinate of the destroyer region.
      ///
      inline double GetMaxY();

      /// SetMinX( double aX )
      ///   Sets the first X coordinate of the destroyer region.
      ///
      /// Parameters:
      ///   aX: New X coordinate.
      ///
      inline void SetMinX( double aX );

      /// SetMaxX( double aX )
      ///   Sets the second X coordinate of the destroyer region.
      ///
      /// Parameters:
      ///   aX: New X coordinate.
      ///
      inline void SetMaxX( double aX );

      /// SetMinY( double aY )
      ///   Sets the first Y coordinate of the destroyer region.
      ///
      /// Parameters:
      ///   aY: New Y coordinate.
      ///
      inline void SetMinY( double aY );

      /// SetMaxY( double aY )
      ///   Sets the second Y coordinate of the destroyer region.
      ///
      /// Parameters:
      ///   aY: New Y coordinate.
      ///
      inline void SetMaxY( double aY );

      /// GetShape()
      ///   Gets the shape of the destroyer.
      ///
      /// Returns:
      ///   Shape of the deflector. (gm::ps_shape_*)
      ///
      inline int GetShape();

      /// SetShape( int aShape )
      ///   Sets the shape of the destroyer.
      ///
      /// Parameters:
      ///   aShape: New shape. (gm::ps_shape_*)
      ///
      inline void SetShape( int aShape );

    private:
      int m_destroyerId;
  };

  /// IDestroyers
  ///   Interface that provides simplier access to particle system's destroyers.
  ///   It should be accessed only from within the IParticleSystem interface.
  ///
  class IDestroyers {
    public:
      /// operator []
      ///   Provides access to the specified destroyer. ID specified in
      ///   the brackets determines which destroyer will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPIDestroyerNotExists object in case when destroyer of ID
      ///   specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an IDestroyer class instance.
      ///
      inline IDestroyer& operator[]( int aDestroyerId );

      /// GetCount()
      ///   Returns total number of the destroyers in the particle system.
      ///
      ///  Returns:
      ///    Total number of the destroyers.
      ///
      int GetCount();

      /// GetArraySize()
      ///   Returns the size of dynamic array that holds data of the
      ///   destroyers.
      ///
      /// Returns:
      ///   Number of elements in the array.
      ///
      inline int GetArraySize();

      /// Exists( int aDestroyerId )
      ///   Checks whether the specified destroyer exists.
      ///
      /// Parameters:
      ///   aFontId: ID of the destroyer.
      ///
      /// Returns:
      ///   True if the destroyer exists.
      ///
      inline bool Exists( int aDestroyerId );

  private:
    IDestroyer m_iDestroyer;
  };

  /// IChanger
  ///   Interface that provides simplier access to changer data.
  ///   It should be accessed only from within the IChangers interface.
  ///
  class IChanger {
    friend class IChangers;

    public:
      /// GetMinX()
      ///   Gets the first X coordinate of the changer region.
      ///
      /// Returns:
      ///   First X coordinate of the changer region.
      ///
      inline double GetMinX();

      /// GetMaxX()
      ///   Gets the second X coordinate of the changer region.
      ///
      /// Returns:
      ///   Second X coordinate of the changer region.
      ///
      inline double GetMaxX();

      /// GetMinX()
      ///   Gets the first X coordinate of the changer region.
      ///
      /// Returns:
      ///   First X coordinate of the changer region.
      ///
      inline double GetMinY();

      /// GetMaxY()
      ///   Gets the second Y coordinate of the changer region.
      ///
      /// Returns:
      ///   Second Y coordinate of the changer region.
      ///
      inline double GetMaxY();

      /// SetMinX( double aX )
      ///   Sets the first X coordinate of the changer region.
      ///
      /// Parameters:
      ///   aX: New X coordinate.
      ///
      inline void SetMinX( double aX );

      /// SetMaxX( double aX )
      ///   Sets the second X coordinate of the changer region.
      ///
      /// Parameters:
      ///   aX: New X coordinate.
      ///
      inline void SetMaxX( double aX );

      /// SetMinY( double aY )
      ///   Sets the first Y coordinate of the changer region.
      ///
      /// Parameters:
      ///   aY: New Y coordinate.
      ///
      inline void SetMinY( double aY );

      /// SetMaxY( double aY )
      ///   Sets the second Y coordinate of the changer region.
      ///
      /// Parameters:
      ///   aY: New Y coordinate.
      ///
      inline void SetMaxY( double aY );

      /// GetShape()
      ///   Gets the shape of the changer.
      ///
      /// Returns:
      ///   Shape of the changer. (gm::ps_shape_*)
      ///
      inline int GetShape();

      /// SetShape( int aShape )
      ///   Sets the shape of the changer.
      ///
      /// Parameters:
      ///   aShape: New shape. (gm::ps_shape_*)
      ///
      inline void SetShape( int aShape );

      /// GetKind()
      ///   Gets the kind of the changer.
      ///
      /// Returns:
      ///   Kind of the changer. (gm::ps_change_*)
      ///
      inline int GetKind();

      /// SetKind( int aKind )
      ///   Sets the kind of the changer.
      ///
      /// Parameters:
      ///    aKind: New kind. (gm::ps_change_*)
      ///
      inline void SetKind( int aKind );

      /// GetSourceParticleType()
      ///   Gets ID of a particle type that is changed by the changer.
      ///
      /// Returns:
      ///   ID of the particle type.
      ///
      inline int GetSourceParticleType();

      /// SetSourceParticleType( int aParticleTypeId )
      ///   Sets the particle type that is changed by the changer.
      ///
      /// Parameters:
      ///   aParticleTypeId: New particle type.
      ///
      inline void SetSourceParticleType( int aParticleTypeId );

      /// GetDestinationParticleType()
      ///   Gets ID of a particle type into which the changer changes the
      ///   source particle type.
      ///
      /// Returns:
      ///   ID of the particle type.
      ///
      inline int GetDestinationParticleType();

      /// SetDestinationParticleType( int aParticleTypeId )
      ///   Sets the particle type into which the changer changes the
      ///   source particle type.
      ///
      /// Parameters:
      ///   aParticleTypeId: New particle type.
      ///
      inline void SetDestinationParticleType( int aParticleTypeId );

    private:
      int m_changerId;
  };

  /// IChangers
  ///   Interface that provides simplier access to particle system's changers.
  ///   It should be accessed only from within the IParticleSystem interface.
  ///
  class IChangers {
    public:
      /// operator []
      ///   Provides access to the specified changer. ID specified in
      ///   the brackets determines which changer will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPIChangerNotExists object in case when changer of ID
      ///   specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an IChanger class instance.
      ///
      inline IChanger& operator[]( int aChangerId );

      /// GetCount()
      ///   Returns total number of the changers in the particle system.
      ///
      ///  Returns:
      ///    Total number of the changers.
      ///
      int GetCount();

      /// GetArraySize()
      ///   Returns the size of dynamic array that holds data of the
      ///   changers.
      ///
      /// Returns:
      ///   Number of elements in the array.
      ///
      inline int GetArraySize();

      /// Exists( int aChangerId )
      ///   Checks whether the specified changer exists.
      ///
      /// Parameters:
      ///   aFontId: ID of the changer.
      ///
      /// Returns:
      ///   True if the changer exists.
      ///
      inline bool Exists( int aChangerId );

  private:
    IChanger m_iChanger;
  };

  /// IParticleSystem
  ///   Interface that provides simplier access to particle system data.
  ///   It should be accessed only from within the IChangers interface.
  ///
  class IParticleSystem {
    friend class IParticleSystems;

    public:
      /// Emitter accessor interface object
      IEmitters Emitters;

      /// Attractor accessor interface object
      IAttractors Attractors;

      /// Deflector accessor interface object
      IDeflectors Deflectors;

      /// Destroyer accessor interface object
      IDestroyers Destroyers;

      /// Changer accessor interface object
      IChangers Changers;

      /// EnumerateParticles( PARTICLEENUMPROC aParticleEnumProc, void* aParam )
      ///   The function enumerates all of the particles in the particle system.
      ///   This works by executing user-defined callback function for each particle.
      ///
      /// Parameters:
      ///   aParticleEnumProc: User-defined PARTICLEENUMPROC callback function.
      ///   aParam: [optional] Value that will be passed to your callback function.
      ///
      /// Remarks:
      ///   Definition of PARTICLEENUMPROC function:
      ///     bool ParticleEnumProc( GMPARTICLE& aParticle, void* aParam );
      ///
      ///   aParticle parameter is a reference to structure that holds the particle data.
      ///   aParam is the value specified in EnumerateParticles function.
      ///   Enumeration will be stopped if the user-defined function will return false.
      ///
      void EnumerateParticles( PARTICLEENUMPROC aParticleEnumProc, void* aParam );

      /// IsAutoUpdateEnabled()
      ///   Checks whether the particle system is updated automatically.
      ///
      /// Returns:
      ///   True if the auto-update option is enabled.
      ///
      inline bool IsAutoUpdateEnabled();

      /// IsAutoDrawEnabled()
      ///   Checks whether the particle system is drawn automatically.
      ///
      /// Returns:
      ///   True if the auto-draw option is enabled.
      ///
      inline bool IsAutoDrawEnabled();

      /// IsDrawNewOverOldEnabled()
      ///   Checks whether new particles in the particle system are drawn
      ///   over the older particles.
      ///
      /// Returns:
      ///   True if the option is enabled.
      ///
      inline bool IsDrawNewOverOldEnabled();

      /// SetAutoUpdate( bool aEnabled )
      ///   Sets the particle system's automatic update option.
      ///
      /// Parameters:
      ///   aEnabled: Specifies whether to enable or disable the option.
      ///
      inline void SetAutoUpdate( bool aEnabled );

      /// SetAutoDraw( bool aEnabled )
      ///   Sets the particle system's automatic draw option.
      ///
      /// Parameters:
      ///   aEnabled: Specifies whether to enable or disable the option.
      ///
      inline void SetAutoDraw( bool aEnabled );

      /// SetAutoDraw( bool aEnabled )
      ///   Changes the particle system's draw order.
      ///
      /// Parameters:
      ///   aEnabled: Specifies whether the new particles must be drawn
      ///             over the older particles.
      ///
      inline void SetDrawOldOverNew( bool aEnabled );

      /// GetX()
      ///   Gets the X position of the particle system.
      ///
      /// Returns:
      ///   X position of the particle system.
      ///
      inline double GetX();

      /// GetY()
      ///   Gets the Y position of the particle system.
      ///
      /// Returns:
      ///   Y position of the particle system.
      ///
      inline double GetY();

      /// GetDepth()
      ///   Gets depth of the particle system.
      ///
      /// Returns:
      ///  Particle system's depth.
      ///
      inline double GetDepth();

      /// SetX( double aX )
      ///   Sets the X position of the particle system.
      ///
      /// Parameters:
      ///   aX: New X position.
      ///
      inline void SetX( double aX );

      /// SetY( double aY )
      ///   Sets the Y position of the particle system.
      ///
      /// Parameters:
      ///   aX: New Y position.
      ///
      inline void SetY( double aY );

      /// SetDepth( double aDepth )
      ///   Sets depth of the particle system.
      ///
      /// Parameters:
      ///   aDepth: New depth.
      ///
      inline void SetDepth( double aDepth );

      /// GetParticleCount()
      ///   Gets number of particles in the particle system.
      ///
      /// Returns:
      ///   Number of particles.
      ///
      inline int GetParticleCount();

      /// GetPtr()
      ///   Gets pointer to the GMPARTICLESYSTEM structure
      ///   associated currently with the interface.
      ///   Used internally.
      ///
      static PGMPARTICLESYSTEM GetPtr() {
        return m_particleSystem;
      }

    private:
      static PGMPARTICLESYSTEM m_particleSystem;
      static int m_particleSystemId;
  };

  /// IParticleSystems
  ///   Interface that provides simplier access to the game's particle systems.
  ///   It should be accessed only from within the CGMAPI class.
  ///
  class IParticleSystems {
    public:
      /// operator []
      ///   Provides access to the specified particle system. ID specified in
      ///   the brackets determines which particle system will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPIParticleSystemNotExists object in case when particle
      ///   system of ID specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an IParticleSystem class instance.
      ///
      inline IParticleSystem& operator[]( int aParticleSystemId );

      /// GetCount()
      ///   Returns total number of the particle systems in the game.
      ///
      ///  Returns:
      ///    Total number of the particle systems.
      ///
      int GetCount();

      /// GetArraySize()
      ///   Returns the size of dynamic array that holds data of the
      ///   particle systems.
      ///
      /// Returns:
      ///   Number of elements in the array.
      ///
      inline int GetArraySize();

      /// Exists( int aParticleSystemId )
      ///   Checks whether the specified particle system exists.
      ///
      /// Parameters:
      ///   aParticleSystemId: ID of the particle system.
      ///
      /// Returns:
      ///   True if the particle system exists.
      ///
      inline bool Exists( int aParticleSystemId );

    private:
      IParticleSystem m_iParticleSystem;
  };

  /// IParticleType
  ///   Interface that provides simplier access to particle type data.
  ///   It should be accessed only from within the IParticleTypes interface.
  ///
  class IParticleType {
    friend class IParticleTypes;

  public:
    /// GetSprite()
    ///   Gets a sprite used in the particle type.
    ///
    /// Returns:
    ///   ID of the sprite or -1 if sprite has not been set.
    ///
    inline int GetSprite();

    /// IsSpriteAnimated()
    ///   Checks whether the used sprite is animated when
    ///   drawing particles with the particle type.
    ///
    /// Returns:
    ///   True if that option is enabled.
    ///
    inline bool IsSpriteAnimated();

    /// IsSpriteStreched()
    ///   Checks whether the used sprite is streched when
    ///   drawing particles with the particle type.
    ///
    /// Returns:
    ///   True if that option is enabled.
    ///
    inline bool IsSpriteStreched();

    /// IsSpriteRandomized()
    ///   Checks whether the particles are drawn using
    ///   random subimages of the sprite used for the
    ///   particle type.
    ///
    /// Returns:
    ///   True if that option is enabled.
    ///
    inline bool IsSpriteRandomized();

    /// SetSprite()
    ///   Sets a sprite for the particle type.
    ///
    /// Parameters:
    ///   aSpriteId: ID of the sprite. By passing -1
    ///              no sprite will be used.
    ///
    inline void SetSprite( int aSpriteId );

    /// SetSpriteAnimated( bool aEnable )
    ///   Enables or disables sprite animation for the
    ///   particle type.
    ///
    /// Parameter:
    ///   aEnable: Specifies whether to enable or disable
    ///            the option.
    ///
    inline void SetSpriteAnimated( bool aEnable );

    /// SetSpriteStreched( bool aEnable )
    ///   Enables or disables sprite streching for the
    ///   particle type.
    ///
    /// Parameter:
    ///   aEnable: Specifies whether to enable or disable
    ///            the option.
    ///
    inline void SetSpriteStreched( bool aEnable );

    /// SetSpriteRandomized( bool aEnable )
    ///   Enables or disables random sprite subimage drawing
    ///   for the particle type.
    ///
    /// Parameter:
    ///   aEnable: Specifies whether to enable or disable
    ///            the option.
    ///
    inline void SetSpriteRandomized( bool aEnable );

    /// GetShape()
    ///   Gets a shape of the particle type.
    ///
    /// Returns:
    ///   Shape of the particle type. (gm::pt_shape_*)
    ///
    inline int GetShape();

    /// SetShape( int aShape )
    ///   Sets the shape of the particle type.
    ///
    /// Parameters:
    ///   aShape: New shape. (gm::pt_shape_*)
    ///
    inline void SetShape( int aShape );

    /// GetSizeMin()
    ///   Gets the minimum size of the particle type.
    ///
    /// Returns:
    ///   Minimum size of the particle type.
    ///
    inline double GetSizeMin();

    /// GetSizeMax()
    ///   Gets the maximum size of the particle type.
    ///
    /// Returns:
    ///   Maximum size of the particle type.
    ///
    inline double GetSizeMax();

    /// GetSizeIncrease()
    ///   Gets the value used to increasing the size of
    ///   the particle type.
    ///
    /// Returns:
    ///   Size increase property value.
    ///
    inline double GetSizeIncrease();

    /// GetSizeIncrease()
    ///   Gets the value used to wiggle the size of
    ///   the particle type.
    ///
    /// Returns:
    ///   Size wiggle property value.
    ///
    inline double GetSizeWiggle();

    /// SetSizeMin( double aSize )
    ///   Sets the minimum size of the particle type.
    ///
    /// Parameters:
    ///   aSize: New minimum size.
    ///
    inline void SetSizeMin( double aSize );

    /// SetSizeMax( double aSize )
    ///   Sets the maximum size of the particle type.
    ///
    /// Parameters:
    ///   aSize: New maximum size.
    ///
    inline void SetSizeMax( double aSize );

    /// SetSizeIncrease( double aIncrease )
    ///   Sets the size increase ammount of the particle type.
    ///
    /// Parameters:
    ///   aSize: New size increase ammount.
    ///
    inline void SetSizeIncrease( double aIncrease );

    /// SetSizeWiggle( double aWiggle )
    ///   Sets the size wiggling ammount of the particle type.
    ///
    /// Parameters:
    ///   aSize: New size wiggling ammount.
    ///
    inline void SetSizeWiggle( double aWiggle );

    /// SetSize( double aMin, double aMax, double aIncrease, double aWiggle )
    ///   Sets size properties of the particle type.
    ///
    /// Parameters:
    ///   aMin: Minimum size.
    ///   aMax: Maximum size.
    ///   aIncrease: Size increase ammount.
    ///   aWiggle: Size wiggling ammount.
    ///
    inline void SetSize( double aMin, double aMax, double aIncrease, double aWiggle );

    /// GetSpeedMin()
    ///   Gets the minimum speed of the particle type.
    ///
    /// Returns:
    ///   Minimum speed of the particle type.
    ///
    inline double GetSpeedMin();

    /// GetSpeedMax()
    ///   Gets the maximum speed of the particle type.
    ///
    /// Returns:
    ///   Maximum speed of the particle type.
    ///
    inline double GetSpeedMax();

    /// GetSpeedIncrease()
    ///   Gets the ammount of speed increase of the particle
    ///   type.
    ///
    /// Returns:
    ///   Speed increase ammount.
    ///
    inline double GetSpeedIncrease();

    /// GetSpeedWiggle()
    ///   Gets the ammount of speed wiggling of the particle
    ///   type.
    ///
    /// Returns:
    ///   Speed wiggling ammount.
    ///
    inline double GetSpeedWiggle();

    /// SetSpeedMin( double aSpeed )
    ///   Sets the minimum speed of the particle type.
    ///
    /// Parameters:
    ///   aSpeed: New minimum speed.
    ///
    inline void SetSpeedMin( double aSpeed );

    /// SetSpeedMax( double aSpeed )
    ///   Sets the maximum speed of the particle type.
    ///
    /// Parameters:
    ///   aSpeed: New maximum speed.
    ///
    inline void SetSpeedMax( double aSpeed );

    /// SetSpeedIncrease( double aIncrease )
    ///   Sets the ammount of speed increase of the particle
    ///   type.
    ///
    /// Parameters:
    ///   aIncrease: New speed increase ammount.
    ///
    inline void SetSpeedIncrease( double aIncrease );

    /// SetSpeedWiggle( double aWiggle )
    ///   Sets the ammount of speed wiggling of the particle
    ///   type.
    ///
    /// Parameters:
    ///   aWiggle: New speed wiggling ammount.
    ///
    inline void SetSpeedWiggle( double aWiggle );

    /// SetSpeed( double aMin, double aMax, double aIncrease, double aWiggle )
    ///   Sets speed properties of the particle type.
    ///
    /// Parameters:
    ///   aMin: Minimum speed.
    ///   aMax: Maximum speed.
    ///   aIncrease: Speed increase ammount.
    ///   aWiggle: Speed wiggling ammount.
    ///
    inline void SetSpeed( double aMin, double aMax, double aIncrease, double aWiggle );

    /// GetDirectionMin()
    ///   Gets the minimum direction of the particle type.
    ///
    /// Returns:
    ///   Minimum direction of the particle type.
    ///
    inline double GetDirectionMin();

    /// GetDirectionMax()
    ///   Gets the maximum direction of the particle type.
    ///
    /// Returns:
    ///   Maximum direction of the particle type.
    ///
    inline double GetDirectionMax();

    /// GetDirectionIncrease()
    ///   Gets the ammount of direction increase of the particle
    ///   type.
    ///
    /// Returns:
    ///   Direction increase ammount.
    ///
    inline double GetDirectionIncrease();

    /// GetDirectionWiggle()
    ///   Gets the ammount of direction wiggling of the particle
    ///   type.
    ///
    /// Returns:
    ///   Direction wiggling ammount.
    ///
    inline double GetDirectionWiggle();

    /// SetDirectionMin( double aDirection )
    ///   Sets the minimum direction of the particle type.
    ///
    /// Parameters:
    ///   aDirection: New minimum direction.
    ///
    inline void SetDirectionMin( double aDirection );

    /// SetDirectionMax( double aDirection )
    ///   Sets the maximum direction of the particle type.
    ///
    /// Parameters:
    ///   aDirection: New maximum direction.
    ///
    inline void SetDirectionMax( double aDirection );

    /// SetDirectionIncrease( double aIncrease )
    ///   Sets the ammount of direction increase of the particle
    ///   type.
    ///
    /// Parameters:
    ///   aIncrease: New direction increase ammount.
    ///
    inline void SetDirectionIncrease( double aIncrease );

    /// SetDirectionWiggle( double aWiggle )
    ///   Sets the ammount of direction wiggling of the particle
    ///   type.
    ///
    /// Parameters:
    ///   aWiggle: New direction wiggling ammount.
    ///
    inline void SetDirectionWiggle( double aWiggle );

    /// SetDirection( double aMin, double aMax, double aIncrease, double aWiggle )
    ///   Sets direction properties of the particle type.
    ///
    /// Parameters:
    ///   aMin: Minimum direction.
    ///   aMax: Maximum direction.
    ///   aIncrease: Direction increase ammount.
    ///   aWiggle: Direction wiggling ammount.
    ///
    inline void SetDirection( double aMin, double aMax, double aIncrease, double aWiggle );

    /// GetAngleMin()
    ///   Gets the minimum angle of the particle type.
    ///
    /// Returns:
    ///   Minimum angle of the particle type.
    ///
    inline double GetAngleMin();

    /// GetAngleMax()
    ///   Gets the maximum angle of the particle type.
    ///
    /// Returns:
    ///   Maximum angle of the particle type.
    ///
    inline double GetAngleMax();

    /// GetAngleIncrease()
    ///   Gets the ammount of angle increase of the particle
    ///   type.
    ///
    /// Returns:
    ///   Angle increase ammount.
    ///
    inline double GetAngleIncrease();

    /// GetAngleWiggle()
    ///   Gets the ammount of angle wiggling of the particle
    ///   type.
    ///
    /// Returns:
    ///   Angle wiggling ammount.
    ///
    inline double GetAngleWiggle();

    /// SetAngleMin( double aAngle )
    ///   Sets the minimum angle of the particle type.
    ///
    /// Parameters:
    ///   aAngle: New minimum angle.
    ///
    inline void SetAngleMin( double aAngle );

    /// SetAngleMax( double aAngle )
    ///   Sets the maximum angle of the particle type.
    ///
    /// Parameters:
    ///   aAngle: New maximum angle.
    ///
    inline void SetAngleMax( double aAngle );

    /// SetAngleIncrease( double aIncrease )
    ///   Sets the ammount of angle increase of the particle
    ///   type.
    ///
    /// Parameters:
    ///   aIncrease: New angle increase ammount.
    ///
    inline void SetAngleIncrease( double aIncrease );

    /// SetAngleWiggle( double aWiggle )
    ///   Sets the ammount of angle wiggling of the particle
    ///   type.
    ///
    /// Parameters:
    ///   aWiggle: New angle wiggling ammount.
    ///
    inline void SetAngleWiggle( double aWiggle );

    /// SetAngle( double aMin, double aMax, double aIncrease, double aWiggle, bool aRelative )
    ///   Sets angle properties of the particle type.
    ///
    /// Parameters:
    ///   aMin: Minimum angle.
    ///   aMax: Maximum angle.
    ///   aIncrease: Angle increase ammount.
    ///   aWiggle: Angle wiggling ammount.
    ///   aRelative: Specifies whether the angle should be
    ///              relative to particles' direction.
    ///
    inline void SetAngle( double aMin, double aMax, double aIncrease, double aWiggle, bool aRelative );

    /// IsAngleRelative()
    ///   Checks whether the angle is relative to particle
    ///   direction.
    ///
    /// Returns:
    ///   True if angle is relative.
    ///
    inline bool IsAngleRelative();

    /// SetAngleRelative( bool aEnabled )
    ///   Enables or disables the relativity of angle to
    ///   the direction of the particles.
    ///
    /// Parameters:
    ///   aEnabled: Specifies whether the angle should be
    ///             relative.
    ///
    inline void SetAngleRelative( bool aEnabled );

    /// GetScaleX()
    ///   Gets the X scale of the particle type.
    ///
    /// Returns:
    ///   X scale of the particle type.
    ///
    inline double GetScaleX();

    /// GetScaleY()
    ///   Gets the Y scale of the particle type.
    ///
    /// Returns:
    ///   Y scale of the particle type.
    ///
    inline double GetScaleY();

    /// SetScaleX( double aScale )
    ///   Sets the X scale of the particle type.
    ///
    /// Parameters:
    ///   aScale: New X scale.
    ///
    inline void SetScaleX( double aScale );

    /// SetScaleY( double aScale )
    ///   Sets the Y scale of the particle type.
    ///
    /// Parameters:
    ///   aScale: New Y scale.
    ///
    inline void SetScaleY( double aScale );

    /// SetScale( double aScaleX, double aScaleY )
    ///   Sets the scale of the particle type.
    ///
    /// Parameters:
    ///   aScaleX: New X scale.
    ///   aScaleX: New Y scale.
    ///
    inline void SetScale( double aScaleX, double aScaleY );

    /// GetGravityAmmount()
    ///   Gets the ammount of gravity of the particle type.
    ///
    /// Returns:
    ///   Ammount of gravity.
    ///
    inline double GetGravityAmmount();

    /// GetGravityDirection()
    ///   Gets the direction of gravity of the particle type.
    ///
    /// Returns:
    ///   Direction of gravity.
    ///
    inline double GetGravityDirection();

    /// SetGravityAmmount( double aAmmount )
    ///   Sets the ammount of gravity of the particle type.
    ///
    /// Parameters:
    ///   aAmmount: New ammount of gravity.
    ///
    inline void SetGravityAmmount( double aAmmount );

    /// SetGravityDirection( double aDirection )
    ///   Sets the direction of gravity of the particle type.
    ///
    /// Parameters:
    ///   aDirection: New direction of gravity.
    ///
    inline void SetGravityDirection( double aDirection );

    /// SetGravityDirection( double aDirection )
    ///   Sets the gravity of the particle type.
    ///
    /// Parameters:
    ///   aAmmount: Ammount of gravity.
    ///   aDirection: Direction of gravity.
    ///
    inline void SetGravity( double aAmmount, double aDirection );

    /// GetLifeMin()
    ///   Gets the minimum lifetime of the particle type.
    ///
    /// Returns:
    ///   Minimum lifetime of the particle type.
    ///
    inline int GetLifeMin();

    /// GetLifeMax()
    ///   Gets the maximum lifetime of the particle type.
    ///
    /// Returns:
    ///   Maximum lifetime of the particle type.
    ///
    inline int GetLifeMax();

    /// SetLifeMin( int aLife )
    ///   Sets the minimum lifetime of the particle type.
    ///
    /// Parameters:
    ///   aLife: New lifetime.
    ///
    inline void SetLifeMin( int aLife );

    /// SetLifeMax( int aLife )
    ///   Sets the maximum lifetime of the particle type.
    ///
    /// Parameters:
    ///   aLife: New lifetime.
    ///
    inline void SetLifeMax( int aLife );

    /// SetLife( int aMin, int aMax )
    ///   Sets the lifetime of the particle type.
    ///
    /// Parameters:
    ///   aMin: Miniumum lifetime.
    ///   aMax: Maximum lifetime.
    ///
    inline void SetLife( int aMin, int aMax );

    /// GetDeathParticleType()
    ///   Gets a particle type used to burst particles
    ///   when the particles of the particle type dies.
    ///
    /// Returns:
    ///   ID of a particle type.
    ///
    inline int GetDeathParticleType();

    /// GetDeathParticleType()
    ///   Gets a number of particles burst when the
    ///   particles of the particle type dies.
    ///
    /// Returns:
    ///   Number of particles.
    ///
    inline int GetDeathParticleNumber();

    /// SetDeathParticleType( int aParticleTypeId )
    ///   Sets a particle type used to burst particles
    ///   when the particles of the particle type dies.
    ///
    /// Parameters:
    ///   aParticleTypeId: ID of a particle type.
    ///
    inline void SetDeathParticleType( int aParticleTypeId );

    /// SetDeathParticleNumber( int aNumber )
    ///   Sets the number of particles burst when the
    ///   particles of the particle type dies.
    ///
    /// Parameters:
    ///   aNumber: Number of the particles.
    ///
    inline void SetDeathParticleNumber( int aNumber );

    /// SetDeathParticle( int aParticleTypeId, int aNumber )
    ///   Sets a number of particles and a particle type
    ///   used to burst particles when the particles of
    ///   the particle type dies.
    ///
    /// Parameters:
    ///   aParticleTypeId: ID of a particle type.
    ///   aNumber: Number of the particles.
    ///
    inline void SetDeathParticle( int aParticleTypeId, int aNumber );

    /// GetStepParticleType()
    ///   Gets a particle type used to burst particles
    ///   per step of the particle type.
    ///
    /// Returns:
    ///   ID of a particle type.
    ///
    inline int GetStepParticleType();

    /// GetStepParticleNumber()
    ///   Gets a number of particles burst per step
    ///   of the particle type.
    ///
    /// Returns:
    ///   Number of particles.
    ///
    inline int GetStepParticleNumber();

    /// SetStepParticleType( int aParticleTypeId )
    ///   Sets a particle type used to burst particles
    ///   per step of the particle type.
    ///
    /// Parameters:
    ///   aParticleTypeId: ID of a particle type.
    ///
    inline void SetStepParticleType( int aParticleTypeId );

    /// SetStepParticleNumber( int aNumber )
    ///   Sets a number of particles burst per step
    ///   of the particle type.
    ///
    /// Parameters:
    ///   aNumber: Number of particles.
    ///
    inline void SetStepParticleNumber( int aNumber );

    /// SetStepParticle( int aParticleTypeId, int aNumber )
    ///   Sets a number of particles and a particle type
    ///   used to burst particles per step of the particle
    ///   type.
    ///
    /// Parameters:
    ///   aParticleTypeId: ID of a particle type.
    ///   aNumber: Number of the particles.
    ///
    inline void SetStepParticle( int aParticleTypeId, int aNumber );

    /// GetColorType()
    ///   Gets type of the particle coloring.
    ///
    /// Returns:
    ///   PCT_COLOR1 - particle type uses a single color for the particles.
    ///   PCT_COLOR2 - particle type interpolates between two colors.
    ///   PCT_COLOR3 - particle type interpolates between three colors.
    ///   PCT_RGB - particle type chooses a color for the particle from
    ///             a RGB range.
    ///   PCT_HSV - particle type chooses a color for the particle from
    ///             a HSV range.
    ///   PCT_MIX - particle type chooses a color for the particle by
    ///             randomly mixing two colors.
    ///
    inline ParticleColorType GetColorType();

    /// SetColorType( ParticleColorType aColorType )
    ///   Sets type of the particle coloring.
    ///
    /// Parameters:
    ///   aColorType: Type of the coloring. You can specify the following values:
    ///     PCT_COLOR1 - particle type uses a single color for the particles.
    ///     PCT_COLOR2 - particle type interpolates between two colors.
    ///     PCT_COLOR3 - particle type interpolates between three colors.
    ///     PCT_RGB - particle type chooses a color for the particle from
    ///               a RGB range.
    ///     PCT_HSV - particle type chooses a color for the particle from
    ///               a HSV range.
    ///     PCT_MIX - particle type chooses a color for the particle by
    ///               randomly mixing two colors.
    ///
    inline void SetColorType( ParticleColorType aColorType );

    /// GetColorComponent1()
    ///   Gets the first value used in particle coloring.
    ///
    /// Returns:
    ///   The return value depends on a coloring type:
    ///     PCT_COLOR1 - Color
    ///     PCT_COLOR2 - 1st color
    ///     PCT_COLOR3 - 1st color
    ///     PCT_RGB - Minimum red
    ///     PCT_HSV - Minimum hue
    ///     PCT_MIX - 1st color
    ///
    inline int GetColorComponent1();

    /// GetColorComponent2()
    ///   Gets the second value used in particle coloring.
    ///
    /// Returns:
    ///   The return value depends on a coloring type:
    ///     PCT_COLOR1 - Undefined
    ///     PCT_COLOR2 - 2nd color
    ///     PCT_COLOR3 - 2nd color
    ///     PCT_RGB - Maximum red
    ///     PCT_HSV - Maximum hue
    ///     PCT_MIX - 2nd color
    ///
    inline int GetColorComponent2();

    /// GetColorComponent3()
    ///   Gets the third value used in particle coloring.
    ///
    /// Returns:
    ///   The return value depends on a coloring type:
    ///     PCT_COLOR1 - Undefined
    ///     PCT_COLOR2 - Undefined
    ///     PCT_COLOR3 - 3rd color
    ///     PCT_RGB - Minimum green
    ///     PCT_HSV - Minimum saturation
    ///     PCT_MIX - Undefined
    ///
    inline int GetColorComponent3();

    /// GetColorComponent4()
    ///   Gets the fourth value used in particle coloring.
    ///
    /// Returns:
    ///   The return value depends on a coloring type:
    ///     PCT_COLOR1 - Undefined
    ///     PCT_COLOR2 - Undefined
    ///     PCT_COLOR3 - Undefined
    ///     PCT_RGB - Maximum green
    ///     PCT_HSV - Maximum saturation
    ///     PCT_MIX - Undefined
    ///
    inline int GetColorComponent4();

    /// GetColorComponent5()
    ///   Gets the fifth value used in particle coloring.
    ///
    /// Returns:
    ///   The return value depends on a coloring type:
    ///     PCT_COLOR1 - Undefined
    ///     PCT_COLOR2 - Undefined
    ///     PCT_COLOR3 - Undefined
    ///     PCT_RGB - Minimum blue
    ///     PCT_HSV - Minimum value
    ///     PCT_MIX - Undefined
    ///
    inline int GetColorComponent5();

    /// GetColorComponent6()
    ///   Gets the sixth value used in particle coloring.
    ///
    /// Returns:
    ///   The return value depends on a coloring type:
    ///     PCT_COLOR1 - Undefined
    ///     PCT_COLOR2 - Undefined
    ///     PCT_COLOR3 - Undefined
    ///     PCT_RGB - Maximum blue
    ///     PCT_HSV - Maximum value
    ///     PCT_MIX - Undefined
    ///
    inline int GetColorComponent6();

    /// SetColorComponent1( int aValue )
    ///   Sets the first value used in particle coloring.
    ///
    /// Parameters:
    ///   aValue: Meaning of the parameter depends on a coloring
    ///           type:
    ///     PCT_COLOR1 - Color
    ///     PCT_COLOR2 - 1st color
    ///     PCT_COLOR3 - 1st color
    ///     PCT_RGB - Minimum red
    ///     PCT_HSV - Minimum hue
    ///     PCT_MIX - 1st color
    ///
    inline void SetColorComponent1( int aValue );

    /// SetColorComponent2( int aValue )
    ///   Sets the second value used in particle coloring.
    ///
    /// Parameters:
    ///   aValue: Meaning of the parameter depends on a coloring
    ///           type:
    ///     PCT_COLOR1 - Undefined
    ///     PCT_COLOR2 - 2nd color
    ///     PCT_COLOR3 - 2nd color
    ///     PCT_RGB - Maximum red
    ///     PCT_HSV - Maximum hue
    ///     PCT_MIX - 2nd color
    ///
    inline void SetColorComponent2( int aValue );

    /// SetColorComponent3( int aValue )
    ///   Sets the third value used in particle coloring.
    ///
    /// Parameters:
    ///   aValue: Meaning of the parameter depends on a coloring
    ///           type:
    ///     PCT_COLOR1 - Undefined
    ///     PCT_COLOR2 - Undefined
    ///     PCT_COLOR3 - 3rd color
    ///     PCT_RGB - Minimum green
    ///     PCT_HSV - Minimum saturation
    ///     PCT_MIX - Undefined
    ///
    inline void SetColorComponent3( int aValue );

    /// SetColorComponent4( int aValue )
    ///   Sets the fourth value used in particle coloring.
    ///
    /// Parameters:
    ///   aValue: Meaning of the parameter depends on a coloring
    ///           type:
    ///     PCT_COLOR1 - Undefined
    ///     PCT_COLOR2 - Undefined
    ///     PCT_COLOR3 - Undefined
    ///     PCT_RGB - Maximum green
    ///     PCT_HSV - Maximum saturation
    ///     PCT_MIX - Undefined
    ///
    inline void SetColorComponent4( int aValue );

    /// SetColorComponent5( int aValue )
    ///   Sets the fifth value used in particle coloring.
    ///
    /// Parameters:
    ///   aValue: Meaning of the parameter depends on a coloring
    ///           type:
    ///     PCT_COLOR1 - Undefined
    ///     PCT_COLOR2 - Undefined
    ///     PCT_COLOR3 - Undefined
    ///     PCT_RGB - Minimum blue
    ///     PCT_HSV - Minimum value
    ///     PCT_MIX - Undefined
    ///
    inline void SetColorComponent5( int aValue );

    /// SetColorComponent6( int aValue )
    ///   Sets the sixth value used in particle coloring.
    ///
    /// Parameters:
    ///   aValue: Meaning of the parameter depends on a coloring
    ///           type:
    ///     PCT_COLOR1 - Undefined
    ///     PCT_COLOR2 - Undefined
    ///     PCT_COLOR3 - Undefined
    ///     PCT_RGB - Maximum blue
    ///     PCT_HSV - Maximum value
    ///     PCT_MIX - Undefined
    ///
    inline void SetColorComponent6( int aValue );

    /// SetColorSingle( int aColor )
    ///   Equivalent of gm::part_type_color1 function.
    ///   Changes coloring type to PCT_COLOR1.
    ///
    /// Parameters:
    ///   aValue: Color of the particles.
    ///
    inline void SetColorSingle( int aColor );

    /// SetColorInterpolation2( int aColor1, int aColor2 )
    ///   Equivalent of gm::part_type_color2 function.
    ///   Changes coloring type to PCT_COLOR2.
    ///
    /// Parameters:
    ///   aColor1: First color used in interpolation.
    ///   aColor2: Second color used in interpolation.
    ///
    inline void SetColorInterpolation2( int aColor1, int aColor2 );

    /// SetColorInterpolation3( int aColor1, int aColor2, int aColor3 )
    ///   Equivalent of gm::part_type_color3 function.
    ///   Changes coloring type to PCT_COLOR3.
    ///
    /// Parameters:
    ///   aColor1: First color used in interpolation.
    ///   aColor2: Second color used in interpolation.
    ///   aColor3: Third color used in interpolation.
    ///
    inline void SetColorInterpolation3( int aColor1, int aColor2, int aColor3 );

    /// SetColorRGB( aRedMin, aRedMax, aGreenMin, aGreenMax, aBlueMin, aBlueMax );
    ///   Equivalent of gm::part_type_color_rgb function.
    ///   Changes coloring type to PCT_RGB.
    ///
    /// Parameters:
    ///   aRedMin: Minimum red.
    ///   aRedMax: Maximum red.
    ///   aGreenMin: Minimum green.
    ///   aGreenMax: Maximum green.
    ///   aBlueMin: Minimum blue.
    ///   aBlueMax: Maximum blue.
    ///
    inline void SetColorRGB( unsigned char aRedMin, unsigned char aRedMax,
                             unsigned char aGreenMin, unsigned char aGreenMax,
                             unsigned char aBlueMin, unsigned char aBlueMax );

    /// SetColorHSV( aHueMin, aHueMax, aSaturationMin, aSaturationMax, aValueMin, aValueMax );
    ///   Equivalent of gm::part_type_color_hsv function.
    ///   Changes coloring type to PCT_RGB.
    ///
    /// Parameters:
    ///   aHueMin: Minimum hue.
    ///   aHueMax: Maximum hue.
    ///   aSaturationMin: Minimum saturation.
    ///   aSaturationMax: Maximum saturation.
    ///   aValueMin: Minimum value.
    ///   aValueMax: Maximum value.
    ///
    inline void SetColorHSV( unsigned char aHueMin, unsigned char aHueMax,
                             unsigned char aSaturationMin, unsigned char aSaturationMax,
                             unsigned char aValueMin, unsigned char aValueMax );

    /// SetColorMix( int aColor1, int aColor2 )
    ///   Equivalent of gm::part_type_color_mix function.
    ///   Changes coloring type to PCT_MIX.
    ///
    /// Parameters:
    ///   aColor1: First color used in mixing.
    ///   aColor2: Second color used in mixing.
    ///
    inline void SetColorMix( int aColor1, int aColor2 );

    /// GetAlpha1()
    ///   Gets the first value used in particle type's
    ///   alpha fading.
    ///
    /// Returns:
    ///   Alpha value.
    ///
    inline double GetAlpha1();

    /// GetAlpha2()
    ///   Gets the second value used in particle type's
    ///   alpha fading.
    ///
    /// Returns:
    ///   Alpha value.
    ///
    inline double GetAlpha2();

    /// GetAlpha3()
    ///   Gets the third value used in particle type's
    ///   alpha fading.
    ///
    /// Returns:
    ///   Alpha value.
    ///
    inline double GetAlpha3();

    /// SetAlpha1( double aAlpha )
    ///   Sets the first value used in particle type's
    ///   alpha fading.
    ///
    /// Parameters:
    ///   aAlpha: New alpha value.
    ///
    inline void SetAlpha1( double aAlpha );

    /// SetAlpha2( double aAlpha )
    ///   Sets the second value used in particle type's
    ///   alpha fading.
    ///
    /// Parameters:
    ///   aAlpha: New alpha value.
    ///
    inline void SetAlpha2( double aAlpha );

    /// SetAlpha3( double aAlpha )
    ///   Sets the third value used in particle type's
    ///   alpha fading.
    ///
    /// Parameters:
    ///   aAlpha: New alpha value.
    ///
    inline void SetAlpha3( double aAlpha );

    /// SetAlpha( double aAlpha1, double aAlpha2, double aAlpha3 )
    ///   Equivalent of gm::part_type_alpha3 function.
    ///
    /// Parameters:
    ///   aAlpha1: First alpha value.
    ///   aAlpha2: Second alpha value.
    ///   aAlpha3: Third alpha value.
    ///
    inline void SetAlpha( double aAlpha1, double aAlpha2, double aAlpha3 );

    /// IsBlendingAdditive()
    ///   Checks whether the particle type uses additive
    ///   blending.
    ///
    /// Returns:
    ///   True if the particle type uses additive blending,
    ///   false if it uses normal blending.
    ///
    inline bool IsBlendingAdditive();

    /// SetBlendingAdditive( bool aEnabled )
    ///   Enables or disables use of an additive blending.
    ///
    /// Parameters:
    ///   aEnabled: Specifies whether to use additive (true),
    ///             or normal blending (false).
    ///
    inline void SetBlendingAdditive( bool aEnabled );

  private:
    int m_particleTypeId;
  };

  /// IParticleTypes
  ///   Interface that provides simplier access to the game's particle types.
  ///   It should be accessed only from within the CGMAPI class.
  ///
  class IParticleTypes {
    public:
      /// operator []
      ///   Provides access to the specified particle type. ID specified in
      ///   the brackets determines which particle type will be accessed.
      ///
      /// Exceptions:
      ///   Throws EGMAPIParticleTypeNotExists object in case when particle
      ///   type of ID specified in brackets does not exist.
      ///
      /// Returns:
      ///   Reference to an IParticleType class instance.
      ///
      inline IParticleType& operator[]( int aParticleTypeId );

      /// GetCount()
      ///   Returns total number of the particle types in the game.
      ///
      ///  Returns:
      ///    Total number of the particle types.
      ///
      int GetCount();

      /// GetArraySize()
      ///   Returns the size of dynamic array that holds data of the
      ///   particle types.
      ///
      /// Returns:
      ///   Number of elements in the array.
      ///
      inline int GetArraySize();

      /// Exists( int aParticleTypeId )
      ///   Checks whether the specified particle type exists.
      ///
      /// Parameters:
      ///   aParticleTypeId: ID of the particle type.
      ///
      /// Returns:
      ///   True if the particle type exists.
      ///
      inline bool Exists( int aParticleTypeId );

    private:
      IParticleType m_iParticleType;
  };

  /// IProperties
  ///   Interface that provides access to the game's built-in variables.
  ///   It should be accessed only from within the CGMAPI class.
  ///
  class IProperties {
    friend class CGMAPI;

    public:
      /// Read game_id
      int GetGameID() {
        return *m_pGameId;
      }

      /// Read working_directory
      const char* GetWorkingDirectory();

      /// Read program_directory
      const char* GetProgramDirectory();

      /// Read temp_directory
      /// The function will return NULL if the string is empty
      const char* GetTempDirectory() {
        return *m_pTempDirectory;
      }

      /// Read fps
      int GetFPS() {
        return *m_pFps;
      }

      /// Read room
      int GetRoomID() {
        return *m_pRoom;
      }

      /// Read room_speed
      static inline int GetRoomSpeed();

      /// Read room_first
      static inline int GetRoomFirst();

      /// Read room_last
      static inline int GetRoomLast();

      /// Read room_width
      static inline int GetRoomWidth();

      /// Read room_height
      static inline int GetRoomHeight();

      /// Set room_speed
      static inline void SetRoomSpeed( int aSpeed );

      /// Read room_caption
      /// The function will return NULL if the string is empty
      static inline const char* GetRoomCaption();

      /// Set room_caption
      void SetRoomCaption( const char* aCaption );

      /// Read room_persistent
      static inline bool GetRoomPersistent();

      /// Set room_persistent
      static inline void SetRoomPersistent( bool aPersistent );

      /// Read score
      int GetScore() {
        return *m_pScore;
      }

      /// Set score
      void SetScore( int aScore ) {
        *m_pScore = aScore;
      }

      /// Read lives
      int GetLives() {
        return *m_pLives;
      }

      /// Set lives
      void SetLives( int aLives ) {
        *m_pLives = aLives;
      }

      /// Read health
      double GetHealth() {
        return *m_pHealth;
      }

      /// Set health
      void SetHealth( double aHealth ) {
        *m_pHealth = aHealth;
      }

      /// Read show_score
      bool GetShowScore() {
        return *m_pShowScore;
      }

      /// Set show_score
      void SetShowScore( bool aShow ) {
        *m_pShowScore = aShow;
      }

      /// Read show_lives
      bool GetShowLives() {
        return *m_pShowLives;
      }

      /// Set show_lives
      void SetShowLives( bool aShow ) {
        *m_pShowLives = aShow;
      }

      /// Read show_health
      bool GetShowHealth() {
        return *m_pShowHealth;
      }

      /// Set show_health
      void SetShowHealth( bool aShow ) {
        *m_pShowHealth = aShow;
      }

      /// Read event_type
      int GetEventType() {
        return *m_pEventType;
      }

      /// Read event_number
      int GetEventNumber() {
        return *m_pEventNumber;
      }

      /// Read event_object
      int GetEventObject() {
        return *m_pEventObject;
      }

      /// Read event_action
      int GetEventAction() {
        return *m_pEventAction;
      }

      /// Read error_last
      /// The function will return NULL if the string is empty
      const char* GetErrorLast() {
        return *m_pErrorLast;
      }

      /// Read error_occured
      bool GetErrorOccured() {
        return *m_pErrorOccured;
      }

      /// Read keyboard_key
      char GetKeyboardKey() {
        return (char) *m_pKeyboardKey;
      }

      /// Read keyboard_lastkey
      char GetKeyboardLastKey() {
        return (char) *m_pKeyboardLastKey;
      }

      /// Set keyboard_key
      void SetKeyboardKey( char aKey ) {
        *m_pKeyboardKey = aKey;
      }

      /// Set keyboard_lastkey
      void SetKeyboardLastKey( char aKey ) {
        *m_pKeyboardLastKey = aKey;
      }

      /// Read keyboard_string
      /// The function will return NULL if the string is empty
      const char* GetKeyboardString() {
        return *m_pKeyboardString;
      }

      /// Set keyboard_string
      void SetKeyboardString( const char* aString );

      /// Read mouse_button
      int GetMouseButton() {
        return *m_pMouseButton;
      }

      /// Set mouse_button
      void SetMouseButton( int aButton ) {
        *m_pMouseButton = aButton;
      }

      /// Read mouse_lastbutton
      int GetMouseLastButton() {
        return *m_pMouseLastButton;
      }

      /// Set mouse_lastbutton
      void SetMouseLastButton( int aButton ) {
        *m_pMouseLastButton = aButton;
      }

      /// Read mouse_x
      int GetMouseX();

      /// Read mouse_y
      int GetMouseY();

      /// Read background_color
      static inline int GetBackgroundColor();

      /// Read background_showcolor
      static inline bool GetBackgroundShowColor();

      /// Read background_visible[0..7]
      bool GetBackgroundVisible( int aIndex );

      /// Read background_foreground[0..7]
      bool GetBackgroundForeground( int aIndex );

      /// Read background_index[0..7]
      int GetBackgroundIndex( int aIndex );

      /// Read background_x[0..7]
      double GetBackgroundX( int aIndex );

      /// Read background_y[0..7]
      double GetBackgroundY( int aIndex );

      /// Read background_htiled[0..7]
      bool GetBackgroundHTiled( int aIndex );

      /// Read background_vtiled[0..7]
      bool GetBackgroundVTiled( int aIndex );

      /// Read background_xscale[0..7]
      double GetBackgroundXScale( int aIndex );

      /// Read background_yscale[0..7]
      double GetBackgroundYScale( int aIndex );

      /// Read background_hspeed[0..7]
      double GetBackgroundHSpeed( int aIndex );

      /// Read background_visible[0..7]
      double GetBackgroundVSpeed( int aIndex );

      /// Read background_blend[0..7]
      int GetBackgroundBlend( int aIndex );

      /// Read background_alpha[0..7]
      double GetBackgroundAlpha( int aIndex );

      /// Set background_color
      static inline void SetBackgroundColor( int aColor );

      /// Set background_showcolor
      static inline void SetBackgroundShowColor( bool aShow );

      /// Set background_visible[0..7]
      void SetBackgroundVisible( int aIndex, bool aVisible );

      /// Set background_foreground[0..7]
      void SetBackgroundForeground( int aIndex, bool aForeground );

      /// Set background_index[0..7]
      void SetBackgroundIndex( int aIndex, int aBackground );

      /// Set background_x[0..7]
      void SetBackgroundX( int aIndex, double aX );

      /// Set background_y[0..7]
      void SetBackgroundY( int aIndex, double aY );

      /// Set background_htiled[0..7]
      void SetBackgroundHTiled( int aIndex, bool aTiled );

      /// Set background_vtiled[0..7]
      void SetBackgroundVTiled( int aIndex, bool aTiled );

      /// Set background_xscale[0..7]
      void SetBackgroundXScale( int aIndex, double aScale );

      /// Set background_yscale[0..7]
      void SetBackgroundYScale( int aIndex, double aScale );

      /// Set background_hspeed[0..7]
      void SetBackgroundHSpeed( int aIndex, double aSpeed );

      /// Set background_vspeed[0..7]
      void SetBackgroundVSpeed( int aIndex, double aSpeed );

      /// Set background_blend[0..7]
      void SetBackgroundBlend( int aIndex, int aColor );

      /// Set background_alpha[0..7]
      void SetBackgroundAlpha( int aIndex, double aAlpha );

      /// Read view_enabled
      static inline bool GetViewEnabled();

      /// Read view_current
      int GetViewCurrent() {
        return *m_pViewCurrent;
      }

      /// Read view_visible[0..7]
      bool GetViewVisible( int aIndex );

      /// Read view_xview[0..7]
      int GetViewXView( int aIndex );

      /// Read view_yview[0..7]
      int GetViewYView( int aIndex );

      /// Read view_wview[0..7]
      int GetViewWView( int aIndex );

      /// Read view_hview[0..7]
      int GetViewHView( int aIndex );

      /// Read view_xport[0..7]
      int GetViewXPort( int aIndex );

      /// Read view_yport[0..7]
      int GetViewYPort( int aIndex );

      /// Read view_wport[0..7]
      int GetViewWPort( int aIndex );

      /// Read view_hport[0..7]
      int GetViewHPort( int aIndex );

      /// Read view_angle[0..7]
      double GetViewAngle( int aIndex );

      /// Read view_hborder[0..7]
      int GetViewHBorder( int aIndex );

      /// Read view_vborder[0..7]
      int GetViewVBorder( int aIndex );

      /// Read view_hspeed[0..7]
      int GetViewHSpeed( int aIndex );

      /// Read view_vspeed[0..7]
      int GetViewVSpeed( int aIndex );

      /// Read view_object[0..7]
      int GetViewObject( int aIndex );

      /// Set view_enabled
      static inline void SetViewEnabled( bool aEnabled );

      /// Set view_visible[0..7]
      void SetViewVisible( int aIndex, bool aVisible );

      /// Set view_xview[0..7]
      void SetViewXView( int aIndex, int aX );

      /// Set view_yview[0..7]
      void SetViewYView( int aIndex, int aY );

      /// Set view_wview[0..7]
      void SetViewWView( int aIndex, int aWidth );

      /// Set view_hview[0..7]
      void SetViewHView( int aIndex, int aHeight );

      /// Set view_xport[0..7]
      void SetViewXPort( int aIndex, int aX );

      /// Set view_yport[0..7]
      void SetViewYPort( int aIndex, int aY );

      /// Set view_wport[0..7]
      void SetViewWPort( int aIndex, int aWidth );

      /// Set view_hport[0..7]
      void SetViewHPort( int aIndex, int aHeight );

      /// Set view_angle[0..7]
      void SetViewAngle( int aIndex, double aAngle );

      /// Set view_hborder[0..7]
      void SetViewHBorder( int aIndex, int aWidth );

      /// Set view_vborder[0..7]
      void SetViewVBorder( int aIndex, int aWidth );

      /// Set view_hspeed[0..7]
      void SetViewHSpeed( int aIndex, int aSpeed );

      /// Set view_vspeed[0..7]
      void SetViewVSpeed( int aIndex, int aSpeed );

      /// Set view_object[0..7]
      void SetViewObject( int aIndex, int aObject );

      /// Read trasition_kind (n/a in GM6)
      static inline int GetTrasitionKind();

      /// Set trasition_kind (n/a in GM6)
      static inline void SetTrasitionKind( int aKind );

      /// Read trasition_steps (n/a in GM6)
      static inline int GetTransitionSteps();

      /// Set trasition_steps (n/a in GM6)
      static inline void SetTransitionSteps( int aSteps );

      /// Read cursor_sprite (n/a in GM6)
      static inline int GetCursorSprite();

      /// Set cursor_sprite (n/a in GM6)
      static inline void SetCursorSprite( int aSprite );

    private:
      inline void* GetPointerToRoomBackgroundData( int aIndex );
      inline void* GetPointerToRoomViewData( int aIndex );

      std::string m_tempString;

      int* m_pGameId;
      const char** m_pTempDirectory;
      int* m_pFps;
      int* m_pRoom;
      int* m_pScore;
      int* m_pLives;
      double* m_pHealth;
      bool* m_pShowScore;
      bool* m_pShowLives;
      bool* m_pShowHealth;
      int* m_pEventType;
      int* m_pEventNumber;
      int* m_pEventObject;
      int* m_pEventAction;
      const char** m_pErrorLast;
      bool* m_pErrorOccured;
      int* m_pKeyboardKey;
      int* m_pKeyboardLastKey;
      const char** m_pKeyboardString;
      int* m_pMouseButton;
      int* m_pMouseLastButton;
      int* m_pViewCurrent;

      static int* m_pTransitionKind;
      static int* m_pTransitionSteps;
      static int* m_pCursorSprite;
  };

  /// CGMAPI
  ///   Initializes the GMAPI engine and provides direct access to GM's resources.
  ///
  /// Notes:
  ///   Only one instance of this class is allowed at a runtime.
  ///   CGMAPI should be initialized before calling any GM function.
  ///
  class CGMAPI {
    public:
      /// Create( unsigned long* aResult )
      ///   Creates an instance of CGMAPI class and initializes the GMAPI engine.
      ///   Only one instance of this class is allowed at a runtime.
      ///
      /// Parameters:
      ///   aResult: pointer to a variable of type unsigned long which will be set
      ///            to one of the following values:
      ///     GMAPI_INITIALIZATION_SUCCESS - GMAPI has been initialized successfully
      ///     GMAPI_INITIALIZATION_FAILED - Failed to initialize GMAPI
      ///     GMAPI_ALREADY_INITIALIZED - An instance of the CGMAPI class already exists
      ///
      /// Returns:
      ///   Pointer to the CGMAPI class instance, or NULL if failed to initialize.
      ///
      static CGMAPI* Create( unsigned long* aResult );

      /// Destroy()
      ///   Destroys instance of the CGMAPI class and deinitializes the engine.
      ///
      static void Destroy();

      /// Sprite accessor interface object
      ISprites Sprites;

      /// Background accessor interface object
      IBackgrounds Backgrounds;

      /// Surface accessor interface object
      ISurfaces Surfaces;

      /// Script accessor interface object
      IScripts Scripts;

      /// Sound accessor interface object
      ISounds Sounds;

      /// Font accessor interface object
      IFonts Fonts;

      /// Particle system accessor interface object
      IParticleSystems ParticleSystems;

      /// Particle type accessor interface object
      IParticleTypes ParticleTypes;

      /// Built-in GM variables/properties accessor interface object
      IProperties Properties;

      /// GetGMVersion()
      ///   Gets the Game Maker version in which the game was created
      ///
      /// Returns:
      ///   Following values can be returned:
      ///     GM_VERSION_61 - Game Maker 6.1
      ///     GM_VERSION_70 - Game Maker 7.0
      ///     GM_VERSION_80 - Game Maker 8.0
      ///     GM_VERSION_INCOMPATIBLE - Unknown GM version
      ///
      static unsigned long GetGMVersion() {
        return m_gmVersion;
      }

      /// GetGMFunctionAddress( const char* aFunctionName )
      ///   Gets address of the specified GM function.
      ///
      /// Parameters:
      ///   aFunctionName: Name of the GM function.
      ///
      /// Returns:
      ///   Address of the GM function. If function cannot be found
      ///   then the return value will be NULL.
      ///
      static GMFUCTION GetGMFunctionAddress( const char* aFunctionName );

      /// GMFunctionRegister( const char* aName, int aNumberOfArguments, GMFUCTION aFunction )
      ///   Modifies or registers a new GM function.
      ///   That method actually should not be used explicitly, it should be called
      ///   via GMAPI_GMFUNCTION_REGISTER macro.
      ///
      ///   Note: Changes does not affect GMAPI's wrapped GM functions.
      ///
      ///  Parameters:
      ///    aFunctionName: Name of the GM function to register. If you specify a
      ///                   name of an existing function, it will be modified.
      ///
      ///    aNumberOfArguments: Number of the function arguments. If -1 is specifed
      ///                        then the function will have a variable number
      ///                        of arguments. If you are modifying an existing
      ///                        GM function, you can pass -2 to the parameter to
      ///                        indicate that you don't want to change the number
      ///                        of arguments.
      ///
      ///    aNewFunction: New address of the GM function. The function must use the
      ///                  GM runner's calling convention. See the remarks for more info.
      ///
      /// Remarks:
      ///   You can define your own "GM" functions by using the GMAPI_GMFUNCTION_GENERATEHANDLER
      ///   macro which generates a function that takes care of GM runner's calling convention
      ///   and passes the parameters to the specified function. The macro takes as parameter
      ///   function of type GMAPIFUNCTION which should be defined as follows:
      ///
      ///   void MyGmFunction( PGMINSTANCE aInstance,
      ///                      PGMINSTANCE aOtherInstance,
      ///                      GMVALUE* aArguments,
      ///                      int aNumberOfArgs,
      ///                      PGMVALUE aResult );
      ///
      ///   aNumberOfArgs specifies how many arguments has been passed to function in aArguments
      ///   parameter (which is an array of values in GM's "format"). aInstance parameter holds a
      ///   pointer to an instance that called the function, whereas aOtherInstance is pointer to
      ///   the instance addressed by GM's "other" keyword. aResult is a pointer to GMVALUE structure,
      ///   which is used to determine result of the function. Use its "Set" method to safely change
      ///   the value.
      ///
      ///   The GMAPI_GMFUNCTION_GENERATEHANDLER should be used below your function definition or
      ///   declaration. Once the handler is generated you can use GMAPI_GMFUNCTION_REGISTER
      ///   somewhere in the code. It has the same parameters as the GMFunctionRegister method -
      ///   all it does is add a postfix "_gmapi_handler" to your specified function, which causes
      ///   to pass pointer to the handler.
      ///
      static void GMFunctionRegister( const char* aName, int aNumberOfArguments, GMFUCTION aFunction );

      /// PatchIdentifierTypeCheckOrder()
      ///   Patches the GM7/GM8 runner in a way that the scripts with the same name as GM functions
      ///   will be ignored when compiling game's GML code (useful when registering new GML functions).
      ///   The function does nothing in GM6.
      ///
      void PatchIdentifierTypeCheckOrder();

      /// GetDirect3DTexture( int aTextureId )
      ///   Retrieves pointer to an IDirect3DTexture8 interface of specifed GM texture.
      ///
      /// Parameters:
      ///   aTextureId: ID of the GM texture.
      ///
      /// Returns:
      ///   If texture ID is valid then pointer to IDirect3DTexture8 will be
      ///   returned, otherwise function will return NULL.
      ///
      static IDirect3DTexture8* GetDirect3DTexture( int aTextureId ) {
        return ( (*m_pTextures)[aTextureId].isValid == TRUE ? (*m_pTextures)[aTextureId].texture : NULL );
      }

      /// GetDirect3DInterface()
      ///   Returns pointer to the IDirect3D8 interface, initialized
      ///   by a runner.
      ///
      /// Returns:
      ///   Pointer to IDirect3D8 interface.
      ///
      IDirect3D8* GetDirect3DInterface() {
        return m_pDirect3dData->direct3dInterface;
      }

      /// GetDirect3DDevice()
      ///   Returns pointer to the IDirect3DDevice8 interface, initialized
      ///   by a runner.
      ///
      /// Returns:
      ///   Pointer to IDirect3DDevice8 interface.
      ///
      IDirect3DDevice8* GetDirect3DDevice() {
        return m_pDirect3dData->direct3dDevice;
      }

      /// GetBitmapSize( GMBITMAP* aBitmap )
      ///   Returns size of the specified bitmap, in bytes.
      ///
      /// Parameters:
      ///   aBitmap: Pointer to GM's GMBITMAP structure
      ///
      /// Returns:
      ///   Size of bitmap in bytes.
      ///
      static unsigned long GetBitmapSize( GMBITMAP* aBitmap );

      /// FunctionData()
      ///   Returns pointer to runner's GMFUNCTIONINFOSTORAGE structure.
      ///
      /// Returns:
      ///   Pointer to GMFUNCTIONINFOSTORAGE structure.
      ///
      static PGMFUNCTIONINFOSTORAGE FunctionData() {
        return m_pFunctionData;
      }

      /// BackgroundData()
      ///   Returns pointer to runner's GMBACKGROUNDSTORAGE structure.
      ///
      /// Returns:
      ///   Pointer to GMBACKGROUNDSTORAGE structure.
      ///
      static PGMBACKGROUNDSTORAGE BackgroundData() {
        return m_pBackgroundData;
      }

      /// SpriteData()
      ///   Returns pointer to runner's GMSPRITESTORAGE structure.
      ///
      /// Returns:
      ///   Pointer to GMSPRITESTORAGE structure.
      ///
      static PGMSPRITESTORAGE SpriteData() {
        return m_pSpriteData;
      }

      /// ScriptData()
      ///   Returns pointer to runner's GMSCRIPTSTORAGE structure.
      ///
      /// Returns:
      ///   Pointer to GMSCRIPTSTORAGE structure.
      ///
      static PGMSCRIPTSTORAGE ScriptData() {
        return m_pScriptData;
      }

      /// SoundData()
      ///   Returns pointer to runner's GMSOUNDSTORAGE structure.
      ///
      /// Returns:
      ///   Pointer to GMSOUNDSTORAGE structure.
      ///
      static PGMSOUNDSTORAGE SoundData() {
        return m_pSoundData;
      }

      /// FontData()
      ///   Returns pointer to runner's GMFONTSTORAGE structure.
      ///
      /// Returns:
      ///   Pointer to GMFONTSTORAGE structure.
      ///
      static PGMFONTSTORAGE FontData() {
        return m_pFontData;
      }

      /// Direct3DData()
      ///   Returns pointer to runner's GMDIRECT3DDATA structure.
      ///
      /// Returns:
      ///   Pointer to GMDIRECT3DDATA structure.
      ///
      static PGMDIRECT3DDATA Direct3DData() {
        return m_pDirect3dData;
      }

      /// ParticleData()
      ///   Returns pointer to runner's PGMPARTICLESTORAGE structure.
      ///
      /// Returns:
      ///   Pointer to PGMPARTICLESTORAGE structure.
      ///
      static PGMPARTICLESTORAGE ParticleData() {
        return m_pParticleData;
      }

      /// GetSurfaceArray()
      ///   Returns pointer to runner's array of GMSURFACE structures.
      ///
      /// Returns:
      ///   Pointer to an array of GMSURFACE structures.
      ///
      static GMSURFACE* GetSurfaceArray() {
        return *m_pSurfaces;
      }

      /// GetTextureArray()
      ///   Returns pointer to runner's array of GMTEXTURE structures.
      ///
      /// Returns:
      ///   Pointer to an array of GMTEXTURE structures.
      ///
      static GMTEXTURE* GetTextureArray() {
        return *m_pTextures;
      }

      /// ScriptSwapTable()
      ///   Returns pointer to an array of bytes that is used to
      ///   decrypt/encrypt scripts displayed in error messages in GM7/GM8.
      ///
      /// Example:
      ///   const char* swapTable = pGmapi->ScriptSwapTable();
      ///
      ///   char script[1024];
      ///   pGmapi->Scripts[scriptID].GetCode( script );
      ///
      ///   int scriptLength = sizeof( script ); // 1024
      ///
      ///   // GM's encrypting/decrypting routine:
      ///   for ( unsigned long i = 0; i < scriptLength; i++ )
      ///     script[i] = swapTable[ script[i] ];
      ///
      /// Returns:
      ///   Pointer to the swap table.
      ///
      static const char* ScriptSwapTable() {
        return m_pSwapTable;
      }

      /// SurfaceArraySizePtr()
      ///   Returns a pointer to variable that holds the size
      ///   of dynamic arrays that holds data of surfaces.
      ///
      /// Returns:
      ///   Pointer to "ArraySize" variable.
      ///
      static int* SurfaceArraySizePtr() {
        return m_pSurfaceArraySize;
      }

      /// GetMainWindowHandle()
      ///   Returns main game window handle.
      ///
      /// Returns:
      ///   Handle of the game's main window
      ///
      HWND GetMainWindowHandle();

      /// GetDebugWindowHandle()
      ///   Returns debug window handle.
      ///
      /// Returns:
      ///   Debug window handle. In GM7/GM8 function can return
      ///   NULL in case when game doesn't run in debug mode.
      ///
      HWND GetDebugWindowHandle();

      /// GetHighscoreWindowHandle()
      ///   Returns high-score window handle.
      ///   The function doesn't work in GM6.
      ///
      /// Returns:
      ///   High-score window handle.
      ///
      HWND GetHighscoreWindowHandle();

      /// Ptr()
      ///   Returns pointer to the instance of CGMAPI class.
      ///
      static CGMAPI* Ptr() {
        return m_self;
      }

      /// GetCurrentInstancePtr()
      ///   Gets pointer to the current instance, that is,
      ///   instance that called your DLL function.
      ///
      /// Returns:
      ///   Pointer to GMINSTANCE structure. If you try to
      ///   get the pointer in the same function where the
      ///   GMAPI has just been initialized, it'll return NULL.
      ///
      PGMINSTANCE GetCurrentInstancePtr() {
        return *GMAPI_ADDRESS_PTR_CURRENTINSTANCE;
      }

      /// GetCurrentInstanceID()
      ///   Gets ID of the current instance.
      ///
      /// Returns:
      ///   ID of the current instance. If you try to get the ID
      ///   in the same function where the GMAPI has just been
      ///   initialized, it'll return gm::noone constant.
      ///
      int GetCurrentInstanceID() {
        if ( !*GMAPI_ADDRESS_PTR_CURRENTINSTANCE )
          return gm::noone;
        return (*GMAPI_ADDRESS_PTR_CURRENTINSTANCE)->structNew.id;
      }

      /// SetCurrentInstance( PGMINSTANCE aInstance )
      ///   Sets the current instance. Current instance is used
      ///   when calling the GM functions from GMAPI. You can change
      ///   the pointer to call the functions with a specifed instance.
      ///
      /// Parameters:
      ///   aInstance: Pointer to the instance.
      ///
      void SetCurrentInstance( PGMINSTANCE aInstance ) {
        *GMAPI_ADDRESS_PTR_CURRENTINSTANCE = aInstance;
      }

      /// GetOtherInstancePtr()
      ///   Gets pointer to an instance that is addressed
      ///   with GM's "other" keyword in an instance that have
      ///   called your DLL function.
      ///
      /// Returns:
      ///   Pointer to GMINSTANCE structure. If you try to
      ///   get the pointer in the same function where the
      ///   GMAPI has just been initialized, it'll return NULL.
      ///
      PGMINSTANCE GetOtherInstancePtr() {
        return *GMAPI_ADDRESS_PTR_OTHERINSTANCE;
      }

      /// GetOtherInstanceID()
      ///   Gets ID of an instance that is addressed with GM's
      ///   "other" keyword in an instance that have called
      ///   your DLL function.
      ///
      /// Returns:
      ///   "other" instance ID. If you try to get the ID in the same
      ///   function where the GMAPI has just been initialized, it'll
      ///   return gm::noone constant.
      ///
      int GetOtherInstanceID() {
        if ( !*GMAPI_ADDRESS_PTR_OTHERINSTANCE )
          return noone;
        return (*GMAPI_ADDRESS_PTR_OTHERINSTANCE)->structNew.id;
      }

      /// SetOtherInstance( PGMINSTANCE aInstance )
      ///   Sets pointer to the "other" instance. "other" instance
      ///   is used when calling GM functions from GMAPI.
      ///
      /// Parameters:
      ///   aInstance: Pointer to the instance.
      ///
      void SetOtherInstance( PGMINSTANCE aInstance ) {
        *GMAPI_ADDRESS_PTR_OTHERINSTANCE = aInstance;
      }

      /// GetInstancePtr( int aInstanceId )
      ///   Gets the pointer to specified instance of GM's object.
      ///
      /// Parameters:
      ///   aInstanceId: ID of an instance.
      ///
      /// Returns:
      ///   Pointer to specified instance. If instance doesn't exists
      ///   function will return NULL.
      ///
      PGMINSTANCE GetInstancePtr( int aInstanceId ) {
        INSTANCEENUMGETID ieGetId = { aInstanceId, NULL };
        EnumerateInstances( InstanceEnumGetID, &ieGetId );

        return ieGetId.result;
      }

      /// EnumerateInstances( INSTANCEENUMPROC aInstanceEnumProc, void* aParam )
      ///   Enumerates all instances in the room. This works by executing
      ///   user-defined callback function for each instance.
      ///
      /// Parameters:
      ///   aInstanceEnumProc: Pointer to INSTANCEENUMPROC callback function.
      ///   aParam: Optional value that will be passed to the callback function.
      ///
      /// Remarks:
      ///   INSTANCEENUMPROC callback function should be defined like following:
      ///     bool InstanceEnumProc( GMINSTANCE& aInstance, void* aParam );
      ///
      ///   EnumerateInstances method will pass reference to instance via aInstance
      ///   parameter and additional given value to aParam parameter. The
      ///   enumeration will be stopped if your function will return false.
      ///
      void EnumerateInstances( INSTANCEENUMPROC aInstanceEnumProc, void* aParam );

      /// With( int aId, bool aCheckInheritance, bool aIncludeDeactivated, WITHPROC aProc, void* aParam )
      ///   Executes specified callback function with specified instance(s), that is,
      ///   the function changes current instance pointer which GMAPI uses in calling GM's functions
      ///   and calls your callback function - for each instance.
      ///
      /// Parameters:
      ///   aId: ID of an object/instance with which your callback function will be executed.
      ///        You can also use gm::all and gm::self constant here.
      ///
      ///   aCheckInheritance: Specifies whether the method should execute
      ///                      callback function with objects that are descendants
      ///                      of object given in aId parameter. This has no effect
      ///                      if specifed aId parameter is not an object ID.
      ///
      ///   aIncludeDeactivated: Specifies whether the function should call your callback
      ///                        function also with deactivated instances.
      ///
      ///   aProc: Pointer to your WITHPROC procedure.
      ///
      ///   aParam: Optional value which will be passed to your callback function.
      ///
      /// Remarks:
      ///   WITHPROC callback function should be defined like following:
      ///     void WithProc( void* aParam );
      ///
      void With( int aId, bool aCheckInheritance, bool aIncludeDeactivated, WITHPROC aProc, void* aParam );

      /// GetSymbolID( const char* aSymbol )
      ///   Gets ID of the specified symbol (variable name).
      ///
      /// Parameters:
      ///   aSymbol: Name of the variable.
      ///
      /// Returns:
      ///   If the specified variable symbol exists, function will return
      ///   its ID, otherwise 0.
      ///
      int GetSymbolID( const char* aSymbol );

      /// GetLocalVariablePtr( int aInstanceId, int aSymbolId )
      ///   Gets pointer to a specified instance's variable.
      ///
      /// Parameters:
      ///   aInstanceId: ID of the instance that holds the variable.
      ///                You can also use "self" constant here.
      ///   aSymbolId: Symbol ID that identifies the variable. Use
      ///              the "GetSymbolID" method to find the ID of a symbol.
      ///
      /// Returns:
      ///   Pointer to the variable (GMVARIABLE structure). If variable doesn't
      ///   exists, return value will be NULL.
      ///
      PGMVARIABLE GetLocalVariablePtr( int aInstanceId, int aSymbolId );

      /// GetLocalVariablePtr( PGMINSTANCE aInstancePtr, int aSymbolId )
      ///   Gets pointer to a specified instance's variable.
      ///
      /// Parameters:
      ///   aInstancePtr: Pointer to an instance that holds the variable.
      ///   aSymbolId: Symbol ID that identifies the variable. Use
      ///              the "GetSymbolID" method to find the ID of a symbol.
      ///
      /// Returns:
      ///   Pointer to the variable (GMVARIABLE structure). If variable doesn't
      ///   exists, return value will be NULL.
      ///
      PGMVARIABLE GetLocalVariablePtr( PGMINSTANCE aInstancePtr, int aSymbolId );

      /// GetGlobalVariablePtr( int aSymbolId )
      ///   Gets the pointer to a specified global variable.
      ///
      /// Parameters:
      ///   aSymbolId: Symbol ID that identifies the variable. Use
      ///              the "GetSymbolID" method to find the ID of a symbol.
      ///
      /// Returns:
      ///   Pointer to the variable (GMVARIABLE structure). If variable doesn't
      ///   exists, return value will be NULL.
      ///
      PGMVARIABLE GetGlobalVariablePtr( int aSymbolId );

      /// PreserveFunctionData();
      ///   Preserves data of the GM function table. Useful when modifying
      ///   GM functions.
      ///
      /// Returns:
      ///   Pointer to a structure that holds GM function table. It is
      ///   used in CGMAPI::RestoreFunctionData method to restore
      ///   the table.
      ///
      PFUNCTIONDATA PreserveFunctionData();

      /// RestoreFunctionData( GMFUNCTIONINFO* aData );
      ///   Restores the GM's function table.
      ///
      /// Returns:
      ///   aData: Pointer to FUNCTIONDATA structure that holds preserved GM function table.
      ///          (check PreserveFunctionData method)
      ///
      void RestoreFunctionData( PFUNCTIONDATA aData );

      //////////////////////////////////////////////////////////////////////////

      /// Used internally
      static int ResourceFindID( const char* aName, char** aResourceNames, int aArraySize );

      /// Used internally
      static int ResourceGetCount( void** aResourceInstances, int aArraySize );

      /// Used internally
      static void* GetCurrentRoomPtr() {
        return *m_pCurrentRoom;
      }

      /// Used internally
      static int* GetRoomIdentifierArrayPtr() {
        return m_pRoomIdArray;
      }

      /// Used internally
      static int GetRoomCount() {
        return *m_pRoomCount;
      }

      /// Used internally
      static const void* GMAPIGMFunctionTable( int aId ) {
        return m_gmFunctions[aId];
      }

    private:
      CGMAPI( bool* aSuccess );
      ~CGMAPI();

      static CGMAPI* m_self;
      static unsigned long m_gmVersion;

      static PGMFUNCTIONINFOSTORAGE m_pFunctionData;
      static PGMBACKGROUNDSTORAGE   m_pBackgroundData;
      static PGMSPRITESTORAGE       m_pSpriteData;
      static PGMSURFACE*            m_pSurfaces;
      static PGMTEXTURE*            m_pTextures;
      static PGMDIRECT3DDATA        m_pDirect3dData;
      static PGMSCRIPTSTORAGE       m_pScriptData;
      static PGMSOUNDSTORAGE        m_pSoundData;
      static PGMFONTSTORAGE         m_pFontData;
      static PGMPARTICLESTORAGE     m_pParticleData;

      static HWND** m_pFormMain;
      static HWND** m_pFormDebug;
      static HWND** m_pFormScore;

      static PGMVARIABLELIST* m_pGlobalVarList;
      static const char* m_pSwapTable;
      static void** m_pCurrentRoom;
      static int* m_pRoomIdArray;
      static int* m_pSurfaceArraySize;
      static int* m_pRoomCount;
      static void* m_pPatchIdTypeCheck;
      static const BYTE* m_pPatchDataIdTypeCheck;

      static void* m_gmFunctions[1000];

      struct INSTANCEENUMGETID {
        int id;
        GMINSTANCE* result;
      };

      static bool InstanceEnumGetID( GMINSTANCE& aInstance, void* aParam ) {
        if ( aInstance.structNew.id == ((INSTANCEENUMGETID*) aParam)->id ) {
          ((INSTANCEENUMGETID*) aParam)->result = &aInstance;
          return false;
        }

        return true;
      }

      PGMVARIABLELIST GetGlobalVariableListPtr() {
        return *m_pGlobalVarList;
      }

      void RetrieveFunctionPointers();
      void RetrieveDataPointers();

  };


  /************************************************************************/
  /* Inlined methods                                                      */
  /************************************************************************/

  /************************************************************************/
  /* ISprites inlined methods                                             */
  /************************************************************************/

  ISprite& ISprites::operator[]( int aSpriteId ) {
    if ( !Exists( aSpriteId ) )
      throw EGMAPISpriteNotExist( aSpriteId );

    m_iSprite.m_spriteId = aSpriteId;
    m_iSprite.m_sprite = CGMAPI::SpriteData()->sprites[aSpriteId];

    return m_iSprite;
  }

  int ISprites::GetArraySize() {
    return CGMAPI::SpriteData()->arraySize;
  }

  /************************************************************************/
  /* ISprite inlined methods                                              */
  /************************************************************************/

  const char* ISprite::GetName() {
    return CGMAPI::SpriteData()->names[m_spriteId];
  }

  /************************************************************************/
  /* ISpriteSubimages inlined methods                                     */
  /************************************************************************/

  ISpriteSubimage& ISpriteSubimages::operator[]( int aSubimage ) {
    if ( aSubimage < 0 || aSubimage > GetCount() )
      throw EGMAPIInvalidSubimage( ISprite::m_spriteId, aSubimage );

    m_subimage.m_subimage = aSubimage;

    return m_subimage;
  }

  int ISpriteSubimages::GetCount() {
    return ( CGlobals::UseNewStructs() ? ISprite::GetPtr()->structNew.subimageCount :
                                         ISprite::GetPtr()->structOld.subimageCount );
  }

  /************************************************************************/
  /* ISpriteSubimage inlined methods                                      */
  /************************************************************************/

  unsigned char* ISpriteSubimage::GetBitmap() {
    return ( CGlobals::UseNewStructs() ? ISprite::GetPtr()->structNew.bitmaps[m_subimage]->structNew.bits :
                                         ISprite::GetPtr()->structOld.bitmaps[m_subimage]->structOld.bits );
  }

  unsigned long ISpriteSubimage::GetBitmapSize() {
    return CGMAPI::GetBitmapSize( ( CGlobals::UseNewStructs() ? ISprite::GetPtr()->structNew.bitmaps[m_subimage] :
                                                                ISprite::GetPtr()->structOld.bitmaps[m_subimage] ) );
  }

  int ISpriteSubimage::GetTextureID() {
    return ( CGlobals::UseNewStructs() ? ISprite::GetPtr()->structNew.textureIds[m_subimage] :
                                         ISprite::GetPtr()->structOld.textureIds[m_subimage] );
  }

  IDirect3DTexture8* ISpriteSubimage::GetTexture() {
    return CGMAPI::GetDirect3DTexture( GetTextureID() );
  }

  /************************************************************************/
  /* IBackgrounds inlined methods                                         */
  /************************************************************************/

  IBackground& IBackgrounds::operator[]( int aBackgroundId ) {
    if ( !Exists( aBackgroundId ) )
      throw EGMAPIBackgroundNotExist( aBackgroundId );

    m_iBackground.m_backgroundId = aBackgroundId;
    m_iBackground.m_background = CGMAPI::BackgroundData()->backgrounds[aBackgroundId];

    return m_iBackground;
  }

  int IBackgrounds::GetArraySize() {
    return CGMAPI::BackgroundData()->arraySize;
  }

  /************************************************************************/
  /* IBackground inlined methods                                          */
  /************************************************************************/

  IDirect3DTexture8* IBackground::GetTexture() {
    return CGMAPI::GetDirect3DTexture( GetTextureID() );
  }

  bool IBackground::GetTransparent() {
    return m_background->structOld.transparent;
  }

  bool IBackground::GetSmoothEdges() {
    return m_background->structOld.smoothEdges;
  }

  bool IBackground::GetPreload() {
    return m_background->structOld.preload;
  }

  /************************************************************************/
  /* ISurfaces inlined methods                                            */
  /************************************************************************/

  ISurface& ISurfaces::operator[]( int aSurfaceId ) {
    if ( !Exists( aSurfaceId ) )
      throw EGMAPISurfaceNotExist( aSurfaceId );

    m_iSurface.m_surfaceId = aSurfaceId;

    return m_iSurface;
  }

  bool ISurfaces::Exists( int aTextureId ) {
    if ( aTextureId >= GetArraySize() || aTextureId < 0 )
      return false;
    if ( CGMAPI::GetSurfaceArray() )
      return CGMAPI::GetSurfaceArray()[aTextureId].exists;

    return false;
  }

  int ISurfaces::GetArraySize() {
    return *CGMAPI::SurfaceArraySizePtr();
  }

  /************************************************************************/
  /* ISurface inlined methods                                             */
  /************************************************************************/

  int ISurface::GetTextureID() {
    return CGMAPI::GetSurfaceArray()[m_surfaceId].textureId;
  }

  IDirect3DTexture8* ISurface::GetTexture() {
    return CGMAPI::GetDirect3DTexture( GetTextureID() );
  }

  int ISurface::GetWidth() {
    return CGMAPI::GetSurfaceArray()[m_surfaceId].width;
  }

  int ISurface::GetHeight() {
    return CGMAPI::GetSurfaceArray()[m_surfaceId].height;
  }

  /************************************************************************/
  /* IScripts inlined methods                                             */
  /************************************************************************/

  IScript& IScripts::operator[]( int aScriptId ) {
    if ( !Exists( aScriptId ) )
      throw EGMAPIScriptNotExist( aScriptId );

    m_iScript.m_scriptId = aScriptId;

    return m_iScript;
  }

  bool IScripts::Exists( int aScriptId ) {
    if ( aScriptId >= GetArraySize() || aScriptId < 0 || !CGMAPI::ScriptData()->scripts )
      return false;
    else
      return ( CGMAPI::ScriptData()->scripts[aScriptId] != NULL );
  }

  int IScripts::GetArraySize() {
    return CGMAPI::ScriptData()->arraySize;
  }

  /************************************************************************/
  /* IScript inlined methods                                              */
  /************************************************************************/

  const char* IScript::GetName() {
    return CGMAPI::ScriptData()->names[m_scriptId];
  }

  /************************************************************************/
  /* ISounds inlined methods                                              */
  /************************************************************************/

  ISound& ISounds::operator[]( int aSoundId ) {
    if ( !Exists( aSoundId ) )
      throw EGMAPISoundNotExist( aSoundId );

    m_iSound.m_soundId = aSoundId;

    return m_iSound;
  }

  bool ISounds::Exists( int aSoundId ) {
    if ( aSoundId >= GetArraySize() || aSoundId < 0 || !CGMAPI::SoundData()->sounds )
      return false;
    else
      return ( CGMAPI::SoundData()->sounds[aSoundId] != NULL );
  }

  int ISounds::GetArraySize() {
    return CGMAPI::SoundData()->arraySize;
  }

  /************************************************************************/
  /* ISound inlined methods                                               */
  /************************************************************************/

  const char* ISound::GetName() {
    return CGMAPI::SoundData()->names[m_soundId];
  }

  const char* ISound::GetExtension() {
    return CGMAPI::SoundData()->sounds[m_soundId]->fileExt;
  }

  const char* ISound::GetFilename() {
    return CGMAPI::SoundData()->sounds[m_soundId]->filename;
  }

  const char* ISound::GetFilePath() {
    return CGMAPI::SoundData()->sounds[m_soundId]->filePath;
  }

  SoundType ISound::GetType() {
    return CGMAPI::SoundData()->sounds[m_soundId]->type;
  }

  double ISound::GetVolume() {
    return CGMAPI::SoundData()->sounds[m_soundId]->volume;
  }

  double ISound::GetPanning() {
    return CGMAPI::SoundData()->sounds[m_soundId]->pan;
  }

  bool ISound::GetPreload() {
    return CGMAPI::SoundData()->sounds[m_soundId]->preload;
  }

  bool ISound::GetEffectChorus() {
    return CGMAPI::SoundData()->sounds[m_soundId]->effectsBitmask & 1;
  }

  bool ISound::GetEffectEcho() {
    return ( CGMAPI::SoundData()->sounds[m_soundId]->effectsBitmask >> 1 ) & 1;
  }

  bool ISound::GetEffectFlanger() {
    return ( CGMAPI::SoundData()->sounds[m_soundId]->effectsBitmask >> 2 ) & 1;
  }

  bool ISound::GetEffectGargle() {
    return ( CGMAPI::SoundData()->sounds[m_soundId]->effectsBitmask >> 3 ) & 1;
  }

  bool ISound::GetEffectReverb() {
    return ( CGMAPI::SoundData()->sounds[m_soundId]->effectsBitmask >> 4 ) & 1;
  }

  unsigned char* ISound::GetData() {
    if ( CGMAPI::SoundData()->sounds[m_soundId]->sndData )
      return CGMAPI::SoundData()->sounds[m_soundId]->sndData->file;
    else
      return NULL;
  }

  unsigned long ISound::GetDataSize() {
    return CGMAPI::SoundData()->sounds[m_soundId]->sndData->fileSize;
  }

  /************************************************************************/
  /* IFonts inlined methods                                               */
  /************************************************************************/

  IFont& IFonts::operator[]( int aFontId ) {
    if ( !Exists( aFontId ) )
      throw EGMAPIFontNotExist( aFontId );

    m_iFont.m_fontId = aFontId;

    return m_iFont;
  }

  bool IFonts::Exists( int aFontId ) {
    if ( aFontId >= GetArraySize() || aFontId < 0 || !CGMAPI::FontData()->fonts )
      return false;
    else
      return ( CGMAPI::FontData()->fonts[aFontId] != NULL );
  }

  int IFonts::GetArraySize() {
    return CGMAPI::FontData()->arraySize;
  }

  /************************************************************************/
  /* IFont inlined methods                                                */
  /************************************************************************/

  const char* IFont::GetFontTypefaceName() {
    return CGMAPI::FontData()->fonts[m_fontId]->fontFamilyName;
  }

  int IFont::GetFontSize() {
    return CGMAPI::FontData()->fonts[m_fontId]->size;
  }

  bool IFont::GetBold() {
    return CGMAPI::FontData()->fonts[m_fontId]->bold;
  }

  bool IFont::GetItalic() {
    return CGMAPI::FontData()->fonts[m_fontId]->italic;
  }

  int IFont::GetRangeLow() {
    return CGMAPI::FontData()->fonts[m_fontId]->rangeMin;
  }

  int IFont::GetRangeHigh() {
    return CGMAPI::FontData()->fonts[m_fontId]->rangeMax;
  }

  int IFont::GetSpriteID() {
    return CGMAPI::FontData()->fonts[m_fontId]->spriteId;
  }

  BYTE* IFont::GetBitmap() {
    return CGMAPI::FontData()->fonts[m_fontId]->bitmap;
  }

  int IFont::GetBitmapWidth() {
    return CGMAPI::FontData()->fonts[m_fontId]->bitmapWidth;
  }

  int IFont::GetBitmapHeight() {
    return CGMAPI::FontData()->fonts[m_fontId]->bitmapHeight;
  }

  unsigned long IFont::GetBitmapSize() {
    return ( CGMAPI::FontData()->fonts[m_fontId]->bitmap ?
             ((DWORD*) (CGMAPI::FontData()->fonts[m_fontId]->bitmap))[-1] :
             0 );
  }

  int IFont::GetTextureID() {
    return CGMAPI::FontData()->fonts[m_fontId]->textureId;
  }

  IDirect3DTexture8* IFont::GetTexture() {
    return CGMAPI::GetDirect3DTexture( CGMAPI::FontData()->fonts[m_fontId]->textureId );
  }

  int IFont::GetCharPositionX( unsigned char aCharacter ) {
    return CGMAPI::FontData()->fonts[m_fontId]->charXOffset[aCharacter];
  }

  int IFont::GetCharPositionY( unsigned char aCharacter ) {
    return CGMAPI::FontData()->fonts[m_fontId]->charYOffset[aCharacter];
  }

  int IFont::GetCharBoundingBoxLeft( unsigned char aCharacter ) {
    return CGMAPI::FontData()->fonts[m_fontId]->charBboxLeft[aCharacter];
  }

  int IFont::GetCharBoundingBoxRight( unsigned char aCharacter ) {
    return CGMAPI::FontData()->fonts[m_fontId]->charBboxRight[aCharacter];
  }

  int IFont::GetCharBoundingBoxTop( unsigned char aCharacter ) {
    return CGMAPI::FontData()->fonts[m_fontId]->charBboxTop[aCharacter];
  }

  int IFont::GetCharBoundingBoxBottom( unsigned char aCharacter ) {
    return CGMAPI::FontData()->fonts[m_fontId]->charBboxBottom[aCharacter];
  }

  /************************************************************************/
  /* IParticleTypes inlined methods                                       */
  /************************************************************************/

  IParticleType& IParticleTypes::operator[]( int aParticleTypeId ) {
    if ( !Exists( aParticleTypeId ) )
      throw EGMAPIParticleTypeNotExist( aParticleTypeId );

    m_iParticleType.m_particleTypeId = aParticleTypeId;

    return m_iParticleType;
  }

  int IParticleTypes::GetArraySize() {
    return CGMAPI::ParticleData()->particleTypeCount;
  }

  bool IParticleTypes::Exists( int aParticleTypeId ) {
    if ( aParticleTypeId >= GetArraySize() || aParticleTypeId < 0 )
      return false;
    if ( CGMAPI::ParticleData()->particleTypes )
      return CGMAPI::ParticleData()->particleTypes[aParticleTypeId].isValid;

    return false;
  }

  /************************************************************************/
  /* IParticleType inlined methods                                        */
  /************************************************************************/

  int IParticleType::GetSprite() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].sprite;
  }

  bool IParticleType::IsSpriteAnimated() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].spriteAnimated;
  }

  bool IParticleType::IsSpriteStreched() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].spriteStretched;
  }

  bool IParticleType::IsSpriteRandomized() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].spriteRandomized;
  }

  void IParticleType::SetSprite( int aSpriteId ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].sprite = aSpriteId;
  }

  void IParticleType::SetSpriteAnimated( bool aEnable ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].spriteAnimated = aEnable;
  }

  void IParticleType::SetSpriteStreched( bool aEnable ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].spriteStretched = aEnable;
  }

  void IParticleType::SetSpriteRandomized( bool aEnable ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].spriteRandomized = aEnable;
  }

  int IParticleType::GetShape() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].shape;
  }

  void IParticleType::SetShape( int aShape ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].shape = aShape;
  }

  double IParticleType::GetSizeMin() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].sizeMin;
  }

  double IParticleType::GetSizeMax() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].sizeMax;
  }

  double IParticleType::GetSizeIncrease() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].sizeIncrease;
  }

  double IParticleType::GetSizeWiggle() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].sizeWiggle;
  }

  void IParticleType::SetSizeMin( double aSize ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].sizeMin = aSize;
  }

  void IParticleType::SetSizeMax( double aSize ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].sizeMax = aSize;
  }

  void IParticleType::SetSizeIncrease( double aIncrease ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].sizeIncrease = aIncrease;
  }

  void IParticleType::SetSizeWiggle( double aWiggle ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].sizeWiggle = aWiggle;
  }

  void IParticleType::SetSize( double aMin, double aMax, double aIncrease, double aWiggle ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.sizeMin = aMin;
    pt.sizeMax = aMax;
    pt.sizeIncrease = aIncrease;
    pt.sizeWiggle = aWiggle;
  }

  double IParticleType::GetDirectionMin() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].directionMin;
  }

  double IParticleType::GetDirectionMax() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].directionMax;
  }

  double IParticleType::GetDirectionIncrease() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].directionIncrease;
  }

  double IParticleType::GetDirectionWiggle() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].directionWiggle;
  }

  void IParticleType::SetDirectionMin( double aDirection ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].directionMin = aDirection;
  }

  void IParticleType::SetDirectionMax( double aDirection ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].directionMax = aDirection;
  }

  void IParticleType::SetDirectionIncrease( double aIncrease ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].directionIncrease = aIncrease;
  }

  void IParticleType::SetDirectionWiggle( double aWiggle ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].directionWiggle = aWiggle;
  }

  void IParticleType::SetDirection( double aMin, double aMax, double aIncrease, double aWiggle ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.directionMin = aMin;
    pt.directionMax = aMax;
    pt.directionIncrease = aIncrease;
    pt.directionWiggle = aWiggle;
  }

  double IParticleType::GetAngleMin() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].angleMin;
  }

  double IParticleType::GetAngleMax() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].angleMax;
  }

  double IParticleType::GetAngleIncrease() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].angleIncrease;
  }

  double IParticleType::GetAngleWiggle() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].angleWiggle;
  }

  void IParticleType::SetAngleMin( double aAngle ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].angleMin = aAngle;
  }

  void IParticleType::SetAngleMax( double aAngle ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].angleMax = aAngle;
  }

  void IParticleType::SetAngleIncrease( double aIncrease ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].angleIncrease = aIncrease;
  }

  void IParticleType::SetAngleWiggle( double aWiggle ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].angleWiggle = aWiggle;
  }

  bool IParticleType::IsAngleRelative() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].angleRelative;
  }

  void IParticleType::SetAngleRelative( bool aEnabled ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].angleRelative = aEnabled;
  }

  void IParticleType::SetAngle( double aMin, double aMax, double aIncrease, double aWiggle, bool aRelative ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.angleMin = aMin;
    pt.angleMax = aMax;
    pt.angleIncrease = aIncrease;
    pt.angleWiggle = aWiggle;
    pt.angleRelative = aRelative;
  }

  double IParticleType::GetScaleX() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].scaleX;
  }

  double IParticleType::GetScaleY() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].scaleY;
  }

  void IParticleType::SetScaleX( double aScale ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].scaleX = aScale;
  }

  void IParticleType::SetScaleY( double aScale ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].scaleY = aScale;
  }

  void IParticleType::SetScale( double aScaleX, double aScaleY ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.scaleX = aScaleX;
    pt.scaleY = aScaleY;
  }

  double IParticleType::GetSpeedMin() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].speedMin;
  }

  double IParticleType::GetSpeedMax() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].speedMax;
  }

  double IParticleType::GetSpeedIncrease() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].speedIncrease;
  }

  double IParticleType::GetSpeedWiggle() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].speedWiggle;
  }

  void IParticleType::SetSpeedMin( double aSpeed ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].speedMin = aSpeed;
  }

  void IParticleType::SetSpeedMax( double aSpeed ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].speedMax = aSpeed;
  }

  void IParticleType::SetSpeedIncrease( double aIncrease ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].speedIncrease = aIncrease;
  }

  void IParticleType::SetSpeedWiggle( double aWiggle ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].speedWiggle = aWiggle;
  }

  void IParticleType::SetSpeed( double aMin, double aMax, double aIncrease, double aWiggle ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.speedMin = aMin;
    pt.speedMax = aMax;
    pt.speedIncrease = aIncrease;
    pt.speedWiggle = aWiggle;
  }

  double IParticleType::GetGravityAmmount() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].gravityAmmount;
  }

  double IParticleType::GetGravityDirection() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].gravityDirection;
  }

  void IParticleType::SetGravityAmmount( double aAmmount ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].gravityAmmount = aAmmount;
  }

  void IParticleType::SetGravityDirection( double aDirection ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].gravityDirection = aDirection;
  }

  void IParticleType::SetGravity( double aAmmount, double aDirection ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.gravityAmmount = aAmmount;
    pt.gravityDirection = aDirection;
  }

  int IParticleType::GetLifeMin() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].lifeMin;
  }

  int IParticleType::GetLifeMax() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].lifeMax;
  }

  void IParticleType::SetLifeMin( int aLife ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].lifeMin = aLife;
  }

  void IParticleType::SetLifeMax( int aLife ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].lifeMax = aLife;
  }

  void IParticleType::SetLife( int aMin, int aMax ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.lifeMin = aMin;
    pt.lifeMax = aMax;
  }

  int IParticleType::GetDeathParticleType() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].deathParticleType;
  }

  int IParticleType::GetDeathParticleNumber() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].deathParticleNumber;
  }

  void IParticleType::SetDeathParticleType( int aParticleTypeId ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].deathParticleType = aParticleTypeId;
  }

  void IParticleType::SetDeathParticleNumber( int aNumber ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].deathParticleNumber = aNumber;
  }

  void IParticleType::SetDeathParticle( int aMin, int aMax ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.deathParticleType = aMin;
    pt.deathParticleNumber = aMax;
  }

  int IParticleType::GetStepParticleType() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].stepParticleType;
  }

  int IParticleType::GetStepParticleNumber() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].stepParticleNumber;
  }

  void IParticleType::SetStepParticleType( int aParticleTypeId ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].stepParticleType = aParticleTypeId;
  }

  void IParticleType::SetStepParticleNumber( int aNumber ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].stepParticleNumber = aNumber;
  }

  void IParticleType::SetStepParticle( int aMin, int aMax ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.stepParticleType = aMin;
    pt.stepParticleNumber = aMax;
  }

  ParticleColorType IParticleType::GetColorType() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorType;
  }

  int IParticleType::GetColorComponent1() {
    return (int) CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorComponent1;
  }

  int IParticleType::GetColorComponent2() {
    return (int) CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorComponent2;
  }

  int IParticleType::GetColorComponent3() {
    return (int) CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorComponent3;
  }

  int IParticleType::GetColorComponent4() {
    return (int) CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorComponent4;
  }

  int IParticleType::GetColorComponent5() {
    return (int) CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorComponent5;
  }

  int IParticleType::GetColorComponent6() {
    return (int) CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorComponent6;
  }

  void IParticleType::SetColorSingle( int aColor ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.colorType = PCT_COLOR1;
    pt.colorComponent1 = aColor;
    pt.colorComponent2 = pt.colorComponent3 = gm::c_white;
    pt.colorComponent4 = pt.colorComponent5 = pt.colorComponent6 = 0.0;
  }

  void IParticleType::SetColorInterpolation2( int aColor1, int aColor2 ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.colorType = PCT_COLOR2;
    pt.colorComponent1 = aColor1;
    pt.colorComponent2 = aColor2;
    pt.colorComponent3 = gm::c_white;
    pt.colorComponent4 = pt.colorComponent5 = pt.colorComponent6 = 0.0;
  }

  void IParticleType::SetColorInterpolation3( int aColor1, int aColor2, int aColor3 ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.colorType = PCT_COLOR3;
    pt.colorComponent1 = aColor1;
    pt.colorComponent2 = aColor2;
    pt.colorComponent3 = aColor3;
    pt.colorComponent4 = pt.colorComponent5 = pt.colorComponent6 = 0.0;
  }

  void IParticleType::SetColorComponent1( int aValue ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorComponent1 = aValue;
  }

  void IParticleType::SetColorComponent2( int aValue ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorComponent2 = aValue;
  }

  void IParticleType::SetColorComponent3( int aValue ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorComponent3 = aValue;
  }

  void IParticleType::SetColorComponent4( int aValue ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorComponent4 = aValue;
  }

  void IParticleType::SetColorComponent5( int aValue ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorComponent5 = aValue;
  }

  void IParticleType::SetColorComponent6( int aValue ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].colorComponent6 = aValue;
  }

  void IParticleType::SetColorRGB( unsigned char aRedMin, unsigned char aRedMax,
                                   unsigned char aGreenMin, unsigned char aGreenMax,
                                   unsigned char aBlueMin, unsigned char aBlueMax ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.colorType = PCT_RGB;
    pt.colorComponent1 = aRedMin;
    pt.colorComponent2 = aRedMax;
    pt.colorComponent3 = aGreenMin;
    pt.colorComponent4 = aGreenMax;
    pt.colorComponent5 = aBlueMin;
    pt.colorComponent6 = aBlueMax;
  }

  void IParticleType::SetColorHSV( unsigned char aHueMin, unsigned char aHueMax,
                                   unsigned char aSaturationMin, unsigned char aSaturationMax,
                                   unsigned char aValueMin, unsigned char aValueMax ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.colorType = PCT_RGB;
    pt.colorComponent1 = aHueMin;
    pt.colorComponent2 = aHueMax;
    pt.colorComponent3 = aSaturationMin;
    pt.colorComponent4 = aSaturationMax;
    pt.colorComponent5 = aValueMin;
    pt.colorComponent6 = aValueMax;
  }

  void IParticleType::SetColorMix( int aColor1, int aColor2 ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.colorType = PCT_MIX;
    pt.colorComponent1 = aColor1;
    pt.colorComponent2 = aColor2;
    pt.colorComponent3 = gm::c_white;
    pt.colorComponent4 = pt.colorComponent5 = pt.colorComponent6 = 0.0;
  }

  double IParticleType::GetAlpha1() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].alpha1;
  }

  double IParticleType::GetAlpha2() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].alpha2;
  }

  double IParticleType::GetAlpha3() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].alpha3;
  }

  void IParticleType::SetAlpha1( double aAlpha ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].alpha1 = aAlpha;
  }

  void IParticleType::SetAlpha2( double aAlpha ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].alpha2 = aAlpha;
  }

  void IParticleType::SetAlpha3( double aAlpha ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].alpha3 = aAlpha;
  }

  void IParticleType::SetAlpha( double aAlpha1, double aAlpha2, double aAlpha3 ) {
    GMPARTICLETYPE& pt = CGMAPI::ParticleData()->particleTypes[m_particleTypeId];
    pt.colorComponent1 = aAlpha1;
    pt.colorComponent2 = aAlpha2;
    pt.colorComponent3 = aAlpha3;
  }

  bool IParticleType::IsBlendingAdditive() {
    return CGMAPI::ParticleData()->particleTypes[m_particleTypeId].additiveBlend;
  }

  void IParticleType::SetBlendingAdditive( bool aEnabled ) {
    CGMAPI::ParticleData()->particleTypes[m_particleTypeId].additiveBlend = aEnabled;
  }

  /************************************************************************/
  /* IParticleSystems inlined methods                                     */
  /************************************************************************/

  IParticleSystem& IParticleSystems::operator[]( int aParticleSystemId ) {
    if ( !Exists( aParticleSystemId ) )
      throw EGMAPIParticleSystemNotExist( aParticleSystemId );

    m_iParticleSystem.m_particleSystemId = aParticleSystemId;
    m_iParticleSystem.m_particleSystem = CGMAPI::ParticleData()->particleSystems + aParticleSystemId;

    return m_iParticleSystem;
  }

  bool IParticleSystems::Exists( int aParticleSystemId ) {
    if ( aParticleSystemId >= GetArraySize() || aParticleSystemId < 0 )
      return false;
    if ( CGMAPI::ParticleData()->particleSystems )
      return CGMAPI::ParticleData()->particleSystems[aParticleSystemId].isValid;

    return false;
  }

  int IParticleSystems::GetArraySize() {
    return CGMAPI::ParticleData()->particleSystemCount;
  }

  /************************************************************************/
  /* IParticleSystem inlined methods                                      */
  /************************************************************************/

  bool IParticleSystem::IsAutoUpdateEnabled() {
    return CGMAPI::ParticleData()->particleSystems[m_particleSystemId].autoUpdate;
  }

  bool IParticleSystem::IsAutoDrawEnabled() {
    return CGMAPI::ParticleData()->particleSystems[m_particleSystemId].autoDraw;
  }

  bool IParticleSystem::IsDrawNewOverOldEnabled() {
    return CGMAPI::ParticleData()->particleSystems[m_particleSystemId].drawNewOverOld;
  }

  void IParticleSystem::SetAutoUpdate( bool aEnabled ) {
    CGMAPI::ParticleData()->particleSystems[m_particleSystemId].autoUpdate = aEnabled;
  }

  void IParticleSystem::SetAutoDraw( bool aEnabled ) {
    CGMAPI::ParticleData()->particleSystems[m_particleSystemId].autoDraw = aEnabled;
  }

  void IParticleSystem::SetDrawOldOverNew( bool aEnabled ) {
    CGMAPI::ParticleData()->particleSystems[m_particleSystemId].drawNewOverOld = aEnabled;
  }

  double IParticleSystem::GetX() {
    return CGMAPI::ParticleData()->particleSystems[m_particleSystemId].x;
  }

  double IParticleSystem::GetY() {
    return CGMAPI::ParticleData()->particleSystems[m_particleSystemId].y;
  }

  double IParticleSystem::GetDepth() {
    return CGMAPI::ParticleData()->particleSystems[m_particleSystemId].depth;
  }

  void IParticleSystem::SetX( double aX ) {
    CGMAPI::ParticleData()->particleSystems[m_particleSystemId].x = aX;
  }

  void IParticleSystem::SetY( double aY) {
    CGMAPI::ParticleData()->particleSystems[m_particleSystemId].y = aY;
  }

  void IParticleSystem::SetDepth( double aDepth ) {
    CGMAPI::ParticleData()->particleSystems[m_particleSystemId].depth = aDepth;
  }

  int IParticleSystem::GetParticleCount() {
    return CGMAPI::ParticleData()->particleSystems[m_particleSystemId].particleCount;
  }

  /************************************************************************/
  /* IEmitters inlined methods                                            */
  /************************************************************************/

  IEmitter& IEmitters::operator[]( int aEmitterId ) {
    if ( !Exists( aEmitterId ) )
      throw EGMAPIEmitterNotExist( aEmitterId );

    m_iEmitter.m_emitterId = aEmitterId;

    return m_iEmitter;
  }

  bool IEmitters::Exists( int aEmitterId ) {
    if ( aEmitterId >= GetArraySize() || aEmitterId < 0 )
      return false;
    if ( IParticleSystem::GetPtr()->emitters )
      return IParticleSystem::GetPtr()->emitters[aEmitterId].isValid;

    return false;
  }

  int IEmitters::GetArraySize() {
    return IParticleSystem::GetPtr()->emitterCount;
  }

  /************************************************************************/
  /* IEmitter inlined methods                                             */
  /************************************************************************/

  int IEmitter::GetStreamNumber() {
    return IParticleSystem::GetPtr()->emitters[m_emitterId].streamNumber;
  }

  void IEmitter::SetStreamNumber( int aNumber ) {
    IParticleSystem::GetPtr()->emitters[m_emitterId].streamNumber = aNumber;
  }

  double IEmitter::GetMinX() {
    return IParticleSystem::GetPtr()->emitters[m_emitterId].xMin;
  }

  double IEmitter::GetMaxX() {
    return IParticleSystem::GetPtr()->emitters[m_emitterId].xMax;
  }

  double IEmitter::GetMinY() {
    return IParticleSystem::GetPtr()->emitters[m_emitterId].yMin;
  }

  double IEmitter::GetMaxY() {
    return IParticleSystem::GetPtr()->emitters[m_emitterId].yMax;
  }

  void IEmitter::SetMinX( double aX ) {
    IParticleSystem::GetPtr()->emitters[m_emitterId].xMin = aX;
  }

  void IEmitter::SetMaxX( double aX ) {
    IParticleSystem::GetPtr()->emitters[m_emitterId].xMax = aX;
  }

  void IEmitter::SetMinY( double aY ) {
    IParticleSystem::GetPtr()->emitters[m_emitterId].yMin = aY;
  }

  void IEmitter::SetMaxY( double aY ) {
    IParticleSystem::GetPtr()->emitters[m_emitterId].yMax = aY;
  }

  int IEmitter::GetDistribution() {
    return IParticleSystem::GetPtr()->emitters[m_emitterId].ditribution;
  }

  int IEmitter::GetShape() {
    return IParticleSystem::GetPtr()->emitters[m_emitterId].shape;
  }

  int IEmitter::GetParticleTypeID() {
    return IParticleSystem::GetPtr()->emitters[m_emitterId].particleType;
  }

  void IEmitter::SetDistribution( int aDistribution ) {
    IParticleSystem::GetPtr()->emitters[m_emitterId].ditribution = aDistribution;
  }

  void IEmitter::SetShape( int aShape ) {
    IParticleSystem::GetPtr()->emitters[m_emitterId].shape = aShape;
  }

  void IEmitter::SetParticleType( int aParticleTypeId ) {
    IParticleSystem::GetPtr()->emitters[m_emitterId].particleType = aParticleTypeId;
  }

  /************************************************************************/
  /* IAttractors inlined methods                                          */
  /************************************************************************/

  IAttractor& IAttractors::operator[]( int aAttractorId ) {
    if ( !Exists( aAttractorId ) )
      throw EGMAPIAttractorNotExist( aAttractorId );

    m_iAttractor.m_attractorId = aAttractorId;

    return m_iAttractor;
  }

  bool IAttractors::Exists( int aAttractorId ) {
    if ( aAttractorId >= GetArraySize() || aAttractorId < 0 )
      return false;
    if ( IParticleSystem::GetPtr()->attractors )
      return IParticleSystem::GetPtr()->attractors[aAttractorId].isValid;

    return false;
  }

  int IAttractors::GetArraySize() {
    return IParticleSystem::GetPtr()->attractorCount;
  }

  /************************************************************************/
  /* IAttractor inlined methods                                           */
  /************************************************************************/

  double IAttractor::GetX() {
    return IParticleSystem::GetPtr()->attractors[m_attractorId].x;
  }

  double IAttractor::GetY() {
    return IParticleSystem::GetPtr()->attractors[m_attractorId].y;
  }

  void IAttractor::SetX( double aX ) {
    IParticleSystem::GetPtr()->attractors[m_attractorId].x = aX;
  }

  void IAttractor::SetY( double aY ) {
    IParticleSystem::GetPtr()->attractors[m_attractorId].y = aY;
  }

  double IAttractor::GetForce() {
    return IParticleSystem::GetPtr()->attractors[m_attractorId].force;
  }

  double IAttractor::GetDistance() {
    return IParticleSystem::GetPtr()->attractors[m_attractorId].distance;
  }

  void IAttractor::SetForce( double aForce ) {
    IParticleSystem::GetPtr()->attractors[m_attractorId].force = aForce;
  }

  void IAttractor::SetDistance( double aDistance ) {
    IParticleSystem::GetPtr()->attractors[m_attractorId].distance = aDistance;
  }

  int IAttractor::GetKind() {
    return IParticleSystem::GetPtr()->attractors[m_attractorId].kind;
  }

  void IAttractor::SetKind( int aKind ) {
    IParticleSystem::GetPtr()->attractors[m_attractorId].kind = aKind;
  }

  bool IAttractor::IsAdditive() {
    return IParticleSystem::GetPtr()->attractors[m_attractorId].additive;
  }

  void IAttractor::SetAdditive( bool aAdditive ) {
    IParticleSystem::GetPtr()->attractors[m_attractorId].additive = aAdditive;
  }

  /************************************************************************/
  /* IDeflectors inlined methods                                          */
  /************************************************************************/

  IDeflector& IDeflectors::operator[]( int aDeflectorId ) {
    if ( !Exists( aDeflectorId ) )
      throw EGMAPIDeflectorNotExist( aDeflectorId );

    m_iDeflector.m_deflectorId = aDeflectorId;

    return m_iDeflector;
  }

  bool IDeflectors::Exists( int aDeflectorId ) {
    if ( aDeflectorId >= GetArraySize() || aDeflectorId < 0 )
      return false;
    if ( IParticleSystem::GetPtr()->deflectors )
      return IParticleSystem::GetPtr()->deflectors[aDeflectorId].isValid;

    return false;
  }

  int IDeflectors::GetArraySize() {
    return IParticleSystem::GetPtr()->deflectorCount;
  }

  /************************************************************************/
  /* IDeflector inlined methods                                           */
  /************************************************************************/

  double IDeflector::GetMinX() {
    return IParticleSystem::GetPtr()->deflectors[m_deflectorId].xMin;
  }

  double IDeflector::GetMaxX() {
    return IParticleSystem::GetPtr()->deflectors[m_deflectorId].xMax;
  }

  double IDeflector::GetMinY() {
    return IParticleSystem::GetPtr()->deflectors[m_deflectorId].yMin;
  }

  double IDeflector::GetMaxY() {
    return IParticleSystem::GetPtr()->deflectors[m_deflectorId].yMax;
  }

  void IDeflector::SetMinX( double aX ) {
    IParticleSystem::GetPtr()->deflectors[m_deflectorId].xMin = aX;
  }

  void IDeflector::SetMaxX( double aX ) {
    IParticleSystem::GetPtr()->deflectors[m_deflectorId].xMax = aX;
  }

  void IDeflector::SetMinY( double aY ) {
    IParticleSystem::GetPtr()->deflectors[m_deflectorId].yMin = aY;
  }

  void IDeflector::SetMaxY( double aY ) {
    IParticleSystem::GetPtr()->deflectors[m_deflectorId].yMax = aY;
  }

  int IDeflector::GetKind() {
    return IParticleSystem::GetPtr()->deflectors[m_deflectorId].kind;
  }

  void IDeflector::SetKind( int aKind ) {
    IParticleSystem::GetPtr()->deflectors[m_deflectorId].kind = aKind;
  }

  double IDeflector::GetFriction() {
    return IParticleSystem::GetPtr()->deflectors[m_deflectorId].friction;
  }

  void IDeflector::SetFriction( double aFriction ) {
    IParticleSystem::GetPtr()->deflectors[m_deflectorId].friction = aFriction;
  }

  /************************************************************************/
  /* IDestroyers inlined methods                                          */
  /************************************************************************/

  IDestroyer& IDestroyers::operator[]( int aDestroyerId ) {
    if ( !Exists( aDestroyerId ) )
      throw EGMAPIDestroyerNotExist( aDestroyerId );

    m_iDestroyer.m_destroyerId = aDestroyerId;

    return m_iDestroyer;
  }

  bool IDestroyers::Exists( int aDestroyerId ) {
    if ( aDestroyerId >= GetArraySize() || aDestroyerId < 0 )
      return false;
    if ( IParticleSystem::GetPtr()->destroyers )
      return IParticleSystem::GetPtr()->destroyers[aDestroyerId].isValid;

    return false;
  }

  int IDestroyers::GetArraySize() {
    return IParticleSystem::GetPtr()->destroyerCount;
  }

  /************************************************************************/
  /* IDestroyer inlined methods                                           */
  /************************************************************************/

  double IDestroyer::GetMinX() {
    return IParticleSystem::GetPtr()->destroyers[m_destroyerId].xMin;
  }

  double IDestroyer::GetMaxX() {
    return IParticleSystem::GetPtr()->destroyers[m_destroyerId].xMax;
  }

  double IDestroyer::GetMinY() {
    return IParticleSystem::GetPtr()->destroyers[m_destroyerId].yMin;
  }

  double IDestroyer::GetMaxY() {
    return IParticleSystem::GetPtr()->destroyers[m_destroyerId].yMax;
  }

  void IDestroyer::SetMinX( double aX ) {
    IParticleSystem::GetPtr()->destroyers[m_destroyerId].xMin = aX;
  }

  void IDestroyer::SetMaxX( double aX ) {
    IParticleSystem::GetPtr()->destroyers[m_destroyerId].xMax = aX;
  }

  void IDestroyer::SetMinY( double aY ) {
    IParticleSystem::GetPtr()->destroyers[m_destroyerId].yMin = aY;
  }

  void IDestroyer::SetMaxY( double aY ) {
    IParticleSystem::GetPtr()->destroyers[m_destroyerId].yMax = aY;
  }

  int IDestroyer::GetShape() {
    return IParticleSystem::GetPtr()->destroyers[m_destroyerId].shape;
  }

  void IDestroyer::SetShape( int aShape ) {
    IParticleSystem::GetPtr()->destroyers[m_destroyerId].shape = aShape;
  }

  /************************************************************************/
  /* IChangers inlined methods                                            */
  /************************************************************************/

  IChanger& IChangers::operator[]( int aChangerId ) {
    if ( !Exists( aChangerId ) )
      throw EGMAPIChangerNotExist( aChangerId );

    m_iChanger.m_changerId = aChangerId;

    return m_iChanger;
  }

  bool IChangers::Exists( int aChangerId ) {
    if ( aChangerId >= GetArraySize() || aChangerId < 0 )
      return false;
    if ( IParticleSystem::GetPtr()->changers )
      return IParticleSystem::GetPtr()->changers[aChangerId].isValid;

    return false;
  }

  int IChangers::GetArraySize() {
    return IParticleSystem::GetPtr()->changerCount;
  }

  /************************************************************************/
  /* IChanger inlined methods                                             */
  /************************************************************************/

  double IChanger::GetMinX() {
    return IParticleSystem::GetPtr()->changers[m_changerId].xMin;
  }

  double IChanger::GetMaxX() {
    return IParticleSystem::GetPtr()->changers[m_changerId].xMax;
  }

  double IChanger::GetMinY() {
    return IParticleSystem::GetPtr()->changers[m_changerId].yMin;
  }

  double IChanger::GetMaxY() {
    return IParticleSystem::GetPtr()->changers[m_changerId].yMax;
  }

  void IChanger::SetMinX( double aX ) {
    IParticleSystem::GetPtr()->changers[m_changerId].xMin = aX;
  }

  void IChanger::SetMaxX( double aX ) {
    IParticleSystem::GetPtr()->changers[m_changerId].xMax = aX;
  }

  void IChanger::SetMinY( double aY ) {
    IParticleSystem::GetPtr()->changers[m_changerId].yMin = aY;
  }

  void IChanger::SetMaxY( double aY ) {
    IParticleSystem::GetPtr()->changers[m_changerId].yMax = aY;
  }

  int IChanger::GetShape() {
    return IParticleSystem::GetPtr()->changers[m_changerId].shape;
  }

  void IChanger::SetShape( int aShape ) {
    IParticleSystem::GetPtr()->changers[m_changerId].shape = aShape;
  }

  int IChanger::GetKind() {
    return IParticleSystem::GetPtr()->changers[m_changerId].kind;
  }

  void IChanger::SetKind( int aKind ) {
    IParticleSystem::GetPtr()->changers[m_changerId].kind = aKind;
  }

  int IChanger::GetSourceParticleType() {
    return IParticleSystem::GetPtr()->changers[m_changerId].particleType1;
  }

  void IChanger::SetSourceParticleType( int aParticleTypeId ) {
    IParticleSystem::GetPtr()->changers[m_changerId].particleType1 = aParticleTypeId;
  }

  int IChanger::GetDestinationParticleType() {
    return IParticleSystem::GetPtr()->changers[m_changerId].particleType2;
  }

  void IChanger::SetDestinationParticleType( int aParticleTypeId ) {
    IParticleSystem::GetPtr()->changers[m_changerId].particleType2 = aParticleTypeId;
  }

  /************************************************************************/
  /* IProperties inlined methods                                          */
  /************************************************************************/

  void* IProperties::GetPointerToRoomBackgroundData( int aIndex ) {
    if ( aIndex < 0 || aIndex >= 8 )
      return NULL;

    return ((void**) CGMAPI::GetCurrentRoomPtr())[8 + aIndex];
  }

  void* IProperties::GetPointerToRoomViewData( int aIndex ) {
    if ( aIndex < 0 || aIndex >= 8 )
      return NULL;

    return ((void**) CGMAPI::GetCurrentRoomPtr())[17 + aIndex];
  }

  int IProperties::GetRoomSpeed() {
    return ((int*) CGMAPI::GetCurrentRoomPtr())[2];
  }

  void IProperties::SetRoomSpeed( int aSpeed ) {
    ((int*) CGMAPI::GetCurrentRoomPtr())[2] = aSpeed;
  }

  int IProperties::GetRoomFirst() {
    return CGMAPI::GetRoomIdentifierArrayPtr()[0];
  }

  int IProperties::GetRoomLast() {
    return CGMAPI::GetRoomIdentifierArrayPtr()[CGMAPI::GetRoomCount() - 1];
  }

  int IProperties::GetRoomWidth() {
    return ((int*) CGMAPI::GetCurrentRoomPtr())[3];
  }

  int IProperties::GetRoomHeight() {
    return ((int*) CGMAPI::GetCurrentRoomPtr())[4];
  }

  const char* IProperties::GetRoomCaption() {
    return ((char**) CGMAPI::GetCurrentRoomPtr())[1];
  }

  bool IProperties::GetRoomPersistent() {
    return ((bool*) CGMAPI::GetCurrentRoomPtr())[0x14];
  }

  void IProperties::SetRoomPersistent( bool aPersistent ) {
    ((bool*) CGMAPI::GetCurrentRoomPtr())[0x14] = aPersistent;
  }

  int IProperties::GetBackgroundColor() {
    return ((int*) CGMAPI::GetCurrentRoomPtr())[6];
  }

  bool IProperties::GetBackgroundShowColor() {
    return ((bool*) CGMAPI::GetCurrentRoomPtr())[0x1C];
  }

  void IProperties::SetBackgroundColor( int aColor ) {
    ((int*) CGMAPI::GetCurrentRoomPtr())[6] = aColor;
  }

  void IProperties::SetBackgroundShowColor( bool aShow ) {
    ((bool*) CGMAPI::GetCurrentRoomPtr())[0x1C] = aShow;
  }

  bool IProperties::GetViewEnabled() {
    return ((bool*) CGMAPI::GetCurrentRoomPtr())[0x40];
  }

  void IProperties::SetViewEnabled( bool aEnabled ) {
    ((bool*) CGMAPI::GetCurrentRoomPtr())[0x40] = aEnabled;
  }

  int IProperties::GetTrasitionKind() {
    if ( CGMAPI::GetGMVersion() <= GM_VERSION_61 )
      return 0;

    return *m_pTransitionKind;
  }

  void IProperties::SetTrasitionKind( int aKind ) {
    if ( CGMAPI::GetGMVersion() <= GM_VERSION_61 )
      return;

    *m_pTransitionKind = aKind;
  }

  int IProperties::GetTransitionSteps() {
    if ( CGMAPI::GetGMVersion() <= GM_VERSION_61 )
      return 0;

    return *m_pTransitionSteps;
  }

  void IProperties::SetTransitionSteps( int aSteps ) {
    if ( CGMAPI::GetGMVersion() <= GM_VERSION_61 )
      return;

    *m_pTransitionSteps = aSteps;
  }

  int IProperties::GetCursorSprite() {
    if ( CGMAPI::GetGMVersion() <= GM_VERSION_61 )
      return 0;

    return *m_pCursorSprite;
  }

  void IProperties::SetCursorSprite( int aSprite ) {
    if ( CGMAPI::GetGMVersion() <= GM_VERSION_61 )
      return;

    *m_pCursorSprite = aSprite;
  }

  /************************************************************************/
  /* CGlobals inlined methods                                             */
  /************************************************************************/

  PGMVARIABLELIST CGlobals::InstanceVarList( PGMINSTANCE aInstance ) {
    return ( UseNewStructs() ? aInstance->structNew.variableListPtr : aInstance->structOld.variableListPtr );
  }

  int CGlobals::InstanceID( PGMINSTANCE aInstance ) {
    return ( UseNewStructs() ? aInstance->structNew.id : aInstance->structOld.id );
  }

  int CGlobals::InstanceObjectID( PGMINSTANCE aInstance ) {
    return ( UseNewStructs() ? aInstance->structNew.object_index : aInstance->structOld.object_index );
  }

  bool CGlobals::IsInstanceDeactivated( PGMINSTANCE aInstance ) {
    return ( UseNewStructs() ? aInstance->structNew.deactivated : aInstance->structOld.deactivated );
  }

}
