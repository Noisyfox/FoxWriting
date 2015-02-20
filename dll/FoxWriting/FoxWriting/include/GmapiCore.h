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
/*  GmapiCore.h                                                         */
/*   - GMAPICore library header                                         */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

namespace gm {
  namespace core {
    extern "C" const char** __stdcall DelphiStringAllocate();
    extern "C" void __stdcall DelphiStringDeallocate( const char** aPtrString );
    extern "C" void __stdcall DelphiStringSetFromPChar( const char* aString, const char** aPtrString );
    extern "C" void __stdcall DelphiStringSet( const char* aSrcString, const char** aDestString );
    extern "C" void __stdcall DelphiStringClear( const char** aPtrString );

    extern "C" void __stdcall RunnerDeallocateResult( void* aPtrResult );
    extern "C" int __stdcall RunnerFindSymbolID( const char* aDelphiString );
    extern "C" void __stdcall RunnerGMFunctionAdd( const char* aDelphiString,
                                                   int aNumberOfArgs,
                                                   void* aFunctionAddress );
    extern "C" void __stdcall RunnerCallFunction( const void* aPtrFunction,
                                                  void* aArgArray,
                                                  int aArgCount,
                                                  void* aPtrResult );

    extern "C" unsigned long __stdcall GMAPIInitialize();
    extern "C" void __stdcall GMAPIHookInstall();
    extern "C" void __stdcall GMAPIHookUninstall();
  }
}
