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
/*   - Definitions and declarations of types used by GMAPI              */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once

#ifdef GMAPI_USE_D3D
  #include <d3d8.h>
#else
  #include <windows.h>
  typedef void IDirect3D8, IDirect3DDevice8, IDirect3DTexture8;
#endif

namespace gm {

  struct GMVALUE;
  typedef GMVALUE* PGMVALUE;

  struct GMINSTANCE;
  typedef GMINSTANCE* PGMINSTANCE;

  struct GMVARIABLE;
  typedef GMVARIABLE* PGMVARIABLE;

  enum BoundingBoxType { BBOX_UNKNOWN = -1, BBOX_AUTOMATIC, BBOX_FULLIMAGE, BBOX_MANUAL };
  enum SoundType { SND_UNKNOWN = -1, SND_NORMAL, SND_BGMUSIC, SND_3DSOUND, SND_MULTIMEDIA };
  enum GMValueType { VT_REAL, VT_STRING };
  enum ParticleColorType { PCT_COLOR1, PCT_COLOR2, PCT_COLOR3, PCT_RGB, PCT_HSV, PCT_MIX };

  typedef char __PADDING1;
  typedef long __PADDING4;

  typedef struct __GMDIRECT3DINFO {
    IDirect3D8* direct3dInterface;
    IDirect3DDevice8* direct3dDevice;

    int renderWidth;
    int renderHeight;
  } GMDIRECT3DINFO, *PGMDIRECT3DDATA;

  typedef struct __GMBITMAP_NEW {
    void* _rttiData;

    int width;
    int height;

    BYTE* bits;
  } GMBITMAP_NEW, *PGMBITMAP_NEW;
  typedef struct __GMBITMAP_OLD {
    void* _rttiData;

    bool exists;

    int width;
    int height;

    BYTE* bits;
  } GMBITMAP_OLD, *PGMBITMAP_OLD;

  typedef union __GMBITMAP {
    GMBITMAP_NEW structNew;
    GMBITMAP_OLD structOld;
  } GMBITMAP, *PGMBITMAP;

  typedef struct __GMTEXTURE {
    IDirect3DTexture8* texture;

    int imageWidth;
    int imageHeight;

    int textureWidth;
    int textureHeight;

    bool isValid;
  } GMTEXTURE, *PGMTEXTURE;

  typedef struct GMSPRITE_NEW {
    void* _rttiInfo;

    int subimageCount;
    PGMBITMAP* bitmaps;

    int originX;
    int originY;

    int bboxLeft;
    int bboxTop;
    int bboxRight;
    int bboxBottom;

    void* masks;
    bool seperateMasks;

    int* textureIds;
  } GMSPRITE_NEW, *PGMSPRITE_NEW;

  typedef struct __GMSPRITE_OLD {
    void* _rttiData;

    BoundingBoxType bboxType;
    int bboxLeft;
    int bboxTop;
    int bboxRight;
    int bboxBottom;

    int subimageCount;

    int width;
    int height;

    int originX;
    int originY;

    bool maskExists;
    void* _collisionMask;
    bool preciseCollision;

    PGMBITMAP* bitmaps;

    bool transparent;
    bool smoothEdges;
    bool preload;

    DWORD* textureIds;
  } GMSPRITE_OLD, *PGMSPRITE_OLD;

  typedef union __GMSPRITE {
    GMSPRITE_OLD structOld;
    GMSPRITE_NEW structNew;
  } GMSPRITE, *PGMSPRITE;

  typedef struct __GMSPRITESTORAGE {
    PGMSPRITE* sprites;
    char** names;

    int arraySize;
  } GMSPRITESTORAGE, *PGMSPRITESTORAGE;

  typedef struct __GMBACKGROUND_NEW {
    void* _rttiData;

    GMBITMAP* bitmap;
    int textureId;
  } GMBACKGROUND_NEW, *PGMBACKGROUND_NEW;

  typedef struct __GMBACKGROUND_OLD {
    void* _rttiData;

    int width;
    int height;

    GMBITMAP* bitmap;

    bool transparent;
    bool smoothEdges;
    bool preload;

    int textureId;
    __PADDING4 _padding;
  } GMBACKGROUND_OLD, *PGMBACKGROUND_OLD;

  typedef union __GMBACKGROUND {
    GMBACKGROUND_OLD structOld;
    GMBACKGROUND_NEW structNew;
  } GMBACKGROUND, *PGMBACKGROUND;

  typedef struct __GMBACKGROUNDSTORAGE {
    PGMBACKGROUND* backgrounds;
    char** names;

    int arraySize;
  } GMBACKGROUNDSTORAGE, *PGMBACKGROUNDSTORAGE;

  typedef struct __GMSURFACE {
    int textureId;

    int width;
    int height;

    bool exists;
  } GMSURFACE, *PGMSURFACE;

  typedef struct __GMSCRIPTCONTENT {
    void* _rttiData;
    char* code;

    __PADDING4 _padding[3];
  } GMSCRIPTCONTENT, *PGMSCRIPTCONTENT;

  typedef struct __GMSCRIPTDEBUGINFO {
    void* _rttiData;
    __PADDING4 _padding;

    bool isCompiled;

    char* code;

    DWORD type;
  } GMSCRIPTDEBUGINFO, *PGMSCRIPTDEBUGINFO;

  typedef struct __GMSCRIPT_NEW {
    void* _rttiData;
    char* code;

    PGMSCRIPTDEBUGINFO debugInfo;
  } GMSCRIPT_NEW, *PGMSCRIPT_NEW;

  typedef struct __GMSCRIPT_OLD {
    void* _rttiData;

    GMSCRIPTCONTENT* pScriptContent;
    GMSCRIPTDEBUGINFO* debugInfo;
  } GMSCRIPT_OLD, *PGMSCRIPT_OLD;

  typedef union __GMSCRIPT {
    GMSCRIPT_OLD structOld;
    GMSCRIPT_NEW structNew;
  } GMSCRIPT, *PGMSCRIPT;

  typedef struct __GMSCRIPTSTORAGE {
    char** symbols;
    int symbolCount;

    PGMSCRIPT* scripts;
    char** names;

    int arraySize;
  } GMSCRIPTSTORAGE, *PGMSCRIPTSTORAGE;

  typedef struct __GMSOUNDDATA {
    void* _rttiData;

    BYTE* file;
    DWORD fileSize;
  } GMSOUNDDATA, *PGMSOUNDDATA;

  typedef struct __GMSOUND {
    void* _rttiData;

    SoundType type;

    char* fileExt;
    char* filename;

    GMSOUNDDATA* sndData;

    bool preload;
    DWORD effectsBitmask;

    __PADDING4 unknown;

    double volume;
    double pan;

    int soundId;

    char* filePath;
  } GMSOUND, *PGMSOUND;

  typedef struct __GMSOUNDSTORAGE {
    PGMSOUND* sounds;
    char** names;

    int arraySize;
  } GMSOUNDSTORAGE, *PGMSOUNDSTORAGE;

  typedef struct __GMVARIABLELIST {
    void* _rttiData;

    GMVARIABLE* variables;
    int count;
  } GMVARIABLELIST, *PGMVARIABLELIST;

  typedef struct __GMINSTANCE_OLD {
    void* _rttiData;
    int id;
    int sprite_index;
    double image_index;
    double image_speed;
    double image_xscale;
    double image_yscale;
    double image_angle;
    double image_alpha;
    int image_blend;
    int mask_index;
    double depth;

    __PADDING4 _padding1[2];

    double x;
    double y;
    double xstart;
    double ystart;
    double xprevious;
    double yprevious;
    double direction;
    double speed;
    double friction;
    double gravity_direction;
    double gravity;
    double hspeed;
    double vspeed;
    int bbox_left;
    int bbox_top;
    int bbox_right;
    int bbox_bottom;
    bool visible, solid, persistent;
    int object_index;

    __PADDING4 _padding2;

    int alarm[12];
    PGMVARIABLELIST variableListPtr;

    __PADDING1 _padding3;
    bool deactivated;
    __PADDING1 _padding4[2];

    int path_index;
    double path_position;
    double path_positionprevious;
    double path_speed;
    double path_scale;
    double path_orientation;
    int path_endaction;

    __PADDING4 _padding5[5];

    int timeline_index;

    __PADDING4 _padding6;

    double timeline_position;
    double timeline_speed;
  } GMINSTANCE_OLD, *PGMINSTANCE_OLD;

  typedef struct __GMINSTANCE_NEW {
    void* _rttiData;
    int id;
    int sprite_index;
    double image_index;
    double image_speed;
    double image_xscale;
    double image_yscale;
    double image_angle;
    double image_alpha;
    int image_blend;
    int mask_index;
    double depth;
    double x;
    double y;
    double xstart;
    double ystart;
    double xprevious;
    double yprevious;
    double direction;
    double speed;
    double friction;
    double gravity_direction;
    double gravity;
    double hspeed;
    double vspeed;
    int bbox_left;
    int bbox_top;
    int bbox_right;
    int bbox_bottom;
    bool visible, solid, persistent;
    int object_index;

    __PADDING4 _padding2;

    int alarm[12];
    PGMVARIABLELIST variableListPtr;

    __PADDING1 _padding3;
    bool deactivated;
    __PADDING1 _padding4[2];

    int path_index;
    double path_position;
    double path_positionprevious;
    double path_speed;
    double path_scale;
    double path_orientation;
    int path_endaction;

    __PADDING4 _padding5[5];

    int timeline_index;

    __PADDING4 _padding6;

    double timeline_position;
    double timeline_speed;
    bool timeline_running, timeline_loop;
  } GMINSTANCE_NEW, *PGMINSTANCE_NEW;

  typedef struct __GMFONT {
    void* _rtti;

    char* fontFamilyName;

    int size;
    bool bold;
    bool italic;

    int rangeMin;
    int rangeMax;

    int spriteId;

    int charXOffset[256];
    int charYOffset[256];

    int charBboxTop[256];
    int charBboxBottom[256];
    int charBboxRight[256];
    int charBboxLeft[256];

    int bitmapWidth;
    int bitmapHeight;
    BYTE* bitmap;
    int textureId;
  } GMFONT, *PGMFONT;

  typedef struct __GMFONTSTORAGE {
    PGMFONT* fonts;
    char** names;

    int arraySize;
  } GMFONTSTORAGE, *PGMFONTSTORAGE;

  typedef DECLSPEC_ALIGN( 1 ) struct __GMFUNCTIONINFO {
    BYTE nameLength;
    char name[67];

    void* address;
    int argumentNumber;
    BOOL requiresPro;
  } GMFUNCTIONINFO, *PGMFUNCTIONINFO;

  typedef struct __GMFUNCTIONINFOSTORAGE {
    GMFUNCTIONINFO* functions;
    DWORD functionCount;
  } GMFUNCTIONINFOSTORAGE, *PGMFUNCTIONINFOSTORAGE;

  typedef struct __GMPARTICLE {
    bool isValid;

    int particleTypeID;

    int lifeTimeElapsed;
    int lifeTimeTotal;

    double x;
    double y;
    double xPrevious;
    double yPrevious;
    double speed;
    double direction;
    double angle;
    int color;

    __PADDING4 _padding1;

    double alpha;
    double size;

    __PADDING4 _padding2[2];
  } GMPARTICLE, *PGMPARTICLE;

  typedef struct __GMPARTICLEEMITTER {
    bool isValid;

    int streamNumber;

    double xMin;
    double xMax;
    double yMin;
    double yMax;

    int ditribution;
    int shape;
    int particleType;

    __PADDING4 _padding;
  } GMPARTICLEEMITTER, *PGMPARTICLEEMITTER;

  typedef struct __GMPARTICLEATTRACTOR {
    bool isValid;

    double x;
    double y;
    double force;
    double distance;

    int kind;
    bool additive;
  } GMPARTICLEATTRACTOR, *PGMPARTICLEATTRACTOR;

  typedef struct __GMPARTICLEDESTROYER {
    bool isValid;

    double xMin;
    double xMax;
    double yMin;
    double yMax;

    int shape;

    __PADDING4 _padding;
  } GMPARTICLEDESTROYER, *PGMPARTICLEDESTROYER;

  typedef struct __GMPARTICLEDEFLECTOR {
    bool isValid;

    double xMin;
    double xMax;
    double yMin;
    double yMax;

    int kind;

    double friction;
  } GMPARTICLEDEFLECTOR, *PGMPARTICLEDEFLECTOR;

  typedef struct __GMPARTICLECHANGER {
    bool isValid;

    double xMin;
    double xMax;
    double yMin;
    double yMax;

    int shape;

    int particleType1;
    int particleType2;

    int kind;
  } GMPARTICLECHANGER, *PGMPARTICLECHANGER;

  typedef struct __GMPARTICLETYPE {
    bool isValid;

    int sprite;
    bool spriteAnimated, spriteStretched, spriteRandomized;

    int shape;

    double sizeMin;
    double sizeMax;
    double sizeIncrease;
    double sizeWiggle;

    double scaleX;
    double scaleY;

    int lifeMin;
    int lifeMax;

    int deathParticleType;
    int deathParticleNumber;

    int stepParticleType;
    int stepParticleNumber;

    double speedMin;
    double speedMax;
    double speedIncrease;
    double speedWiggle;

    double directionMin;
    double directionMax;
    double directionIncrease;
    double directionWiggle;

    double gravityAmmount;
    double gravityDirection;

    double angleMin;
    double angleMax;
    double angleIncrease;
    double angleWiggle;
    bool angleRelative;

    ParticleColorType colorType;

    double colorComponent1;
    double colorComponent2;
    double colorComponent3;
    double colorComponent4;
    double colorComponent5;
    double colorComponent6;

    double alpha1;
    double alpha2;
    double alpha3;

    bool additiveBlend;

    __PADDING4 _padding;
  } GMPARTICLETYPE, *PGMPARTICLETYPE;

  typedef struct __GMPARTICLESYSTEM {
    bool isValid;

    GMPARTICLE* particles;
    int particleCount;

    GMPARTICLEEMITTER* emitters;
    int emitterCount;
    GMPARTICLEATTRACTOR* attractors;
    int attractorCount;
    GMPARTICLEDESTROYER* destroyers;
    int destroyerCount;
    GMPARTICLEDEFLECTOR* deflectors;
    int deflectorCount;
    GMPARTICLECHANGER* changers;
    int changerCount;

    bool drawNewOverOld;

    double depth;
    double x;
    double y;

    bool autoUpdate, autoDraw;
    __PADDING4 _padding;
  } GMPARTICLESYSTEM, *PGMPARTICLESYSTEM;

  typedef struct __GMPARTICLESTORAGE {
    GMPARTICLETYPE* particleTypes;
    int particleTypeCount;
    GMPARTICLESYSTEM* particleSystems;
    int particleSystemCount;
  } GMPARTICLESTORAGE, *PGMPARTICLESTORAGE;

  typedef struct __FUNCTIONDATA {
    int functionCount;
    GMFUNCTIONINFO* functions;
  } FUNCTIONDATA, *PFUNCTIONDATA;

}
