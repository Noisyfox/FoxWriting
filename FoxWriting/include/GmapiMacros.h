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
/*  GmapiMacros.h                                                       */
/*   - Macros used in GM function wrappers                              */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once

#define GMVARIABLE_LENGTH( aArray ) (sizeof( aArray ) / sizeof( gm::GMVALUE ))

#define GM_NORMAL_CALL( aFunctionID ) \
  gm::core::RunnerCallFunction( gm::CGMAPI::GMAPIGMFunctionTable( gm:: aFunctionID ), &argument,\
                                GMVARIABLE_LENGTH( argument ), &result )

#define GM_VOID_CALL( aFunctionID ) \
  gm::core::RunnerCallFunction( gm::CGMAPI::GMAPIGMFunctionTable( gm:: aFunctionID ), NULL, 0, &result )

#define GM_ARGS GMVALUE argument[] =
#define GM_NORMAL_RESULT gm::GMVALUE result;

#define GM_VAR_RESULT \
  gm::CGMVariable retval;\
  gm::GMVALUE result;\
  ZeroMemory( &result, sizeof( result ) )

#define GM_PRESERVE_INSTANCE_DATA \
  DWORD instanceSelf = *((DWORD*) 0x00400804);\
  DWORD instanceOther = *((DWORD*) 0x00400808)

#define GM_RESTORE_INSTANCE_DATA \
  *((DWORD*) 0x400804) = instanceSelf;\
  *((DWORD*) 0x400808) = instanceOther

#define GM_RETURN_REAL return result.real
#define GM_RETURN_INT return (int) result.real
#define GM_RETURN_BOOL return ( result.real != 0 )

#define GM_RETURN_VAR \
  retval = result;\
  gm::core::RunnerDeallocateResult( &result );\
  return retval

#define GMAPI_GMFUNCTION_GENERATEHANDLER( aFunction ) \
  void __declspec( naked ) aFunction##_gmapi_handler( gm::PGMVALUE aResult, int aMaxArgs, gm::GMVALUE* aArguments, int aNumberOfArgs, gm::PGMINSTANCE aInstanceSelf, gm::PGMINSTANCE aInstanceOther ) {\
    __asm { push  ebp }\
    __asm { mov   ebp, esp }\
    \
    __asm { mov   dword ptr ds:[0x00400804], edx }\
    __asm { mov   dword ptr ds:[0x00400808], eax }\
    \
    __asm { mov   aNumberOfArgs, ecx }\
    __asm { mov   aInstanceSelf, edx }\
    __asm { mov   aInstanceOther, eax }\
    \
    aFunction( aInstanceSelf, aInstanceOther, aArguments, aNumberOfArgs, aResult );\
    \
    __asm { pop   ebp }\
    __asm { ret   0x0C }\
  }

#define GMAPI_GMFUNCTION_REGISTER( aName, aNumberOfArguments, aFunction ) \
  gm::CGMAPI::GMFunctionRegister( aName, aNumberOfArguments, aFunction##_gmapi_handler )
