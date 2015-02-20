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
/*  GmapiConsts.h                                                       */
/*   - Constants used by GMAPI                                          */
/*                                                                      */
/*  Copyright (C) 2009-2010, Snake (http://www.sgames.ovh.org)          */
/************************************************************************/

#pragma once
#include "GmapiDefs.h"

namespace gm {
  extern unsigned long const GM_VERSION_INCOMPATIBLE;
  extern unsigned long const GM_VERSION_61;
  extern unsigned long const GM_VERSION_70;
  extern unsigned long const GM_VERSION_80;

  extern unsigned const long GMAPI_INITIALIZATION_SUCCESS;
  extern unsigned const long GMAPI_INITIALIZATION_FAILED;
  extern unsigned const long GMAPI_ALREADY_INITIALIZED;

  extern const char* const STR_GMAPI_ERROR;
  extern const char* const STR_GMAPI_DEBUG;
  extern const char* const STR_GMAPI_NOACCESS;

  extern const char* const STR_EXC_UNKNOWN;
  extern const char* const STR_EXC_SPRITENOTEXISTS;
  extern const char* const STR_EXC_BACKGROUNDNOTEXISTS;
  extern const char* const STR_EXC_SCRIPTNOTEXISTS;
  extern const char* const STR_EXC_SOUNDNOTEXISTS;
  extern const char* const STR_EXC_SURFACENOTEXISTS;
  extern const char* const STR_EXC_INVALIDSUBIMAGE;
  extern const char* const STR_EXC_FONTNOTEXISTS;
  extern const char* const STR_EXC_PARTICLETYPENOTEXISTS;
  extern const char* const STR_EXC_PARTICLESYSTEMNOTEXISTS;
  extern const char* const STR_EXC_DEFLECTORNOTEXISTS;
  extern const char* const STR_EXC_CHANGERNOTEXISTS;
  extern const char* const STR_EXC_DESTROYERNOTEXISTS;
  extern const char* const STR_EXC_EMITTERNOTEXISTS;
  extern const char* const STR_EXC_ATTRACTORNOTEXISTS;

  extern const char* const GM70_ADDRESS_PTR_SWAPTABLE;
  extern const char* const GM80_ADDRESS_PTR_SWAPTABLE;
  extern void** const GM61_ADDRESS_PTR_CURRENTROOM;
  extern void** const GM70_ADDRESS_PTR_CURRENTROOM;
  extern void** const GM80_ADDRESS_PTR_CURRENTROOM;
  extern int* const GM61_ADDRESS_PTR_ROOMCOUNT;
  extern int* const GM70_ADDRESS_PTR_ROOMCOUNT;
  extern int* const GM80_ADDRESS_PTR_ROOMCOUNT;
  extern PGMVARIABLELIST* const GM61_ADDRESS_PTR_GLOBALVARLIST;
  extern PGMVARIABLELIST* const GM70_ADDRESS_PTR_GLOBALVARLIST;
  extern PGMVARIABLELIST* const GM80_ADDRESS_PTR_GLOBALVARLIST;

  extern int* const GM61_ADDRESS_ARRAY_ROOMIDS;
  extern int* const GM70_ADDRESS_ARRAY_ROOMIDS;
  extern int* const GM80_ADDRESS_ARRAY_ROOMIDS;
  extern PGMFUNCTIONINFOSTORAGE const GM61_ADDRESS_ARRAY_GMFUNCTIONS;
  extern PGMFUNCTIONINFOSTORAGE const GM70_ADDRESS_ARRAY_GMFUNCTIONS;
  extern PGMFUNCTIONINFOSTORAGE const GM80_ADDRESS_ARRAY_GMFUNCTIONS;
  extern PGMSURFACE* const GM61_ADDRESS_ARRAY_SURFACES;
  extern PGMSURFACE* const GM70_ADDRESS_ARRAY_SURFACES;
  extern PGMSURFACE* const GM80_ADDRESS_ARRAY_SURFACES;
  extern PGMTEXTURE* const GM61_ADDRESS_ARRAY_TEXTURES;
  extern PGMTEXTURE* const GM70_ADDRESS_ARRAY_TEXTURES;
  extern PGMTEXTURE* const GM80_ADDRESS_ARRAY_TEXTURES;
  extern int* const GM61_ADDRESS_ARRAYSIZE_SURFACES;
  extern int* const GM70_ADDRESS_ARRAYSIZE_SURFACES;
  extern int* const GM80_ADDRESS_ARRAYSIZE_SURFACES;

  extern PGMSPRITESTORAGE const GM61_ADDRESS_STORAGE_SPRITES;
  extern PGMSPRITESTORAGE const GM70_ADDRESS_STORAGE_SPRITES;
  extern PGMSPRITESTORAGE const GM80_ADDRESS_STORAGE_SPRITES;
  extern PGMBACKGROUNDSTORAGE const GM61_ADDRESS_STORAGE_BACKGROUNDS;
  extern PGMBACKGROUNDSTORAGE const GM70_ADDRESS_STORAGE_BACKGROUNDS;
  extern PGMBACKGROUNDSTORAGE const GM80_ADDRESS_STORAGE_BACKGROUNDS;
  extern PGMSCRIPTSTORAGE const GM61_ADDRESS_STORAGE_SCRIPTS;
  extern PGMSCRIPTSTORAGE const GM70_ADDRESS_STORAGE_SCRIPTS;
  extern PGMSCRIPTSTORAGE const GM80_ADDRESS_STORAGE_SCRIPTS;
  extern PGMDIRECT3DDATA const GM61_ADDRESS_STORAGE_DIRECTX;
  extern PGMDIRECT3DDATA const GM70_ADDRESS_STORAGE_DIRECTX;
  extern PGMDIRECT3DDATA const GM80_ADDRESS_STORAGE_DIRECTX;
  extern PGMSOUNDSTORAGE const GM61_ADDRESS_STORAGE_SOUNDS;
  extern PGMSOUNDSTORAGE const GM70_ADDRESS_STORAGE_SOUNDS;
  extern PGMSOUNDSTORAGE const GM80_ADDRESS_STORAGE_SOUNDS;
  extern PGMFONTSTORAGE const GM61_ADDRESS_STORAGE_FONTS;
  extern PGMFONTSTORAGE const GM70_ADDRESS_STORAGE_FONTS;
  extern PGMFONTSTORAGE const GM80_ADDRESS_STORAGE_FONTS;
  extern PGMPARTICLESTORAGE const GM61_ADDRESS_STORAGE_PARTICLES;
  extern PGMPARTICLESTORAGE const GM70_ADDRESS_STORAGE_PARTICLES;
  extern PGMPARTICLESTORAGE const GM80_ADDRESS_STORAGE_PARTICLES;

  extern HWND** const GM61_ADDRESS_FORM_TRUNNER;
  extern HWND** const GM61_ADDRESS_FORM_TDEBUG;
  extern HWND** const GM70_ADDRESS_FORM_TRUNNER;
  extern HWND** const GM70_ADDRESS_FORM_TDEBUG;
  extern HWND** const GM70_ADDRESS_FORM_TSCORE;
  extern HWND** const GM80_ADDRESS_FORM_TRUNNER;
  extern HWND** const GM80_ADDRESS_FORM_TDEBUG;
  extern HWND** const GM80_ADDRESS_FORM_TSCORE;

  extern int* const GM61_ADDRESS_PROPERTY_GAMEID;
  extern int* const GM70_ADDRESS_PROPERTY_GAMEID;
  extern int* const GM80_ADDRESS_PROPERTY_GAMEID;
  extern const char** const GM61_ADDRESS_PROPERTY_TEMPDIRECTORY;
  extern const char** const GM70_ADDRESS_PROPERTY_TEMPDIRECTORY;
  extern const char** const GM80_ADDRESS_PROPERTY_TEMPDIRECTORY;
  extern int* const GM61_ADDRESS_PROPERTY_FPS;
  extern int* const GM70_ADDRESS_PROPERTY_FPS;
  extern int* const GM80_ADDRESS_PROPERTY_FPS;
  extern int* const GM61_ADDRESS_PROPERTY_ROOM;
  extern int* const GM70_ADDRESS_PROPERTY_ROOM;
  extern int* const GM80_ADDRESS_PROPERTY_ROOM;
  extern int* const GM61_ADDRESS_PROPERTY_SCORE;
  extern int* const GM70_ADDRESS_PROPERTY_SCORE;
  extern int* const GM80_ADDRESS_PROPERTY_SCORE;
  extern int* const GM61_ADDRESS_PROPERTY_LIVES;
  extern int* const GM70_ADDRESS_PROPERTY_LIVES;
  extern int* const GM80_ADDRESS_PROPERTY_LIVES;
  extern double* const GM61_ADDRESS_PROPERTY_HEALTH;
  extern double* const GM70_ADDRESS_PROPERTY_HEALTH;
  extern double* const GM80_ADDRESS_PROPERTY_HEALTH;
  extern bool* const GM61_ADDRESS_PROPERTY_SHOWSCORE;
  extern bool* const GM70_ADDRESS_PROPERTY_SHOWSCORE;
  extern bool* const GM80_ADDRESS_PROPERTY_SHOWSCORE;
  extern bool* const GM61_ADDRESS_PROPERTY_SHOWLIVES;
  extern bool* const GM70_ADDRESS_PROPERTY_SHOWLIVES;
  extern bool* const GM80_ADDRESS_PROPERTY_SHOWLIVES;
  extern bool* const GM61_ADDRESS_PROPERTY_SHOWHEALTH;
  extern bool* const GM70_ADDRESS_PROPERTY_SHOWHEALTH;
  extern bool* const GM80_ADDRESS_PROPERTY_SHOWHEALTH;
  extern int* const GM61_ADDRESS_PROPERTY_EVENTTYPE;
  extern int* const GM70_ADDRESS_PROPERTY_EVENTTYPE;
  extern int* const GM80_ADDRESS_PROPERTY_EVENTTYPE;
  extern int* const GM61_ADDRESS_PROPERTY_EVENTNUMBER;
  extern int* const GM70_ADDRESS_PROPERTY_EVENTNUMBER;
  extern int* const GM80_ADDRESS_PROPERTY_EVENTNUMBER;
  extern int* const GM61_ADDRESS_PROPERTY_EVENTOBJECT;
  extern int* const GM70_ADDRESS_PROPERTY_EVENTOBJECT;
  extern int* const GM80_ADDRESS_PROPERTY_EVENTOBJECT;
  extern int* const GM61_ADDRESS_PROPERTY_EVENTACTION;
  extern int* const GM70_ADDRESS_PROPERTY_EVENTACTION;
  extern int* const GM80_ADDRESS_PROPERTY_EVENTACTION;
  extern const char** const GM61_ADDRESS_PROPERTY_ERRORLAST;
  extern const char** const GM70_ADDRESS_PROPERTY_ERRORLAST;
  extern const char** const GM80_ADDRESS_PROPERTY_ERRORLAST;
  extern bool* const GM61_ADDRESS_PROPERTY_ERROROCCURED;
  extern bool* const GM70_ADDRESS_PROPERTY_ERROROCCURED;
  extern bool* const GM80_ADDRESS_PROPERTY_ERROROCCURED;
  extern int* const GM61_ADDRESS_PROPERTY_KEYBOARDKEY;
  extern int* const GM70_ADDRESS_PROPERTY_KEYBOARDKEY;
  extern int* const GM80_ADDRESS_PROPERTY_KEYBOARDKEY;
  extern int* const GM61_ADDRESS_PROPERTY_KEYBOARDLASTKEY;
  extern int* const GM70_ADDRESS_PROPERTY_KEYBOARDLASTKEY;
  extern int* const GM80_ADDRESS_PROPERTY_KEYBOARDLASTKEY;
  extern const char** const GM61_ADDRESS_PROPERTY_KEYBOARDSTRING;
  extern const char** const GM70_ADDRESS_PROPERTY_KEYBOARDSTRING;
  extern const char** const GM80_ADDRESS_PROPERTY_KEYBOARDSTRING;
  extern int* const GM61_ADDRESS_PROPERTY_MOUSEBUTTON;
  extern int* const GM70_ADDRESS_PROPERTY_MOUSEBUTTON;
  extern int* const GM80_ADDRESS_PROPERTY_MOUSEBUTTON;
  extern int* const GM61_ADDRESS_PROPERTY_MOUSELASTBUTTON;
  extern int* const GM70_ADDRESS_PROPERTY_MOUSELASTBUTTON;
  extern int* const GM80_ADDRESS_PROPERTY_MOUSELASTBUTTON;
  extern int* const GM61_ADDRESS_PROPERTY_VIEWCURRENT;
  extern int* const GM70_ADDRESS_PROPERTY_VIEWCURRENT;
  extern int* const GM80_ADDRESS_PROPERTY_VIEWCURRENT;
  extern int* const GM70_ADDRESS_PROPERTY_TRANSITIONKIND;
  extern int* const GM80_ADDRESS_PROPERTY_TRANSITIONKIND;
  extern int* const GM70_ADDRESS_PROPERTY_TRANSITIONSTEPS;
  extern int* const GM80_ADDRESS_PROPERTY_TRANSITIONSTEPS;
  extern int* const GM70_ADDRESS_PROPERTY_CURSORSPRITE;
  extern int* const GM80_ADDRESS_PROPERTY_CURSORSPRITE;

  extern PGMINSTANCE* const GMAPI_ADDRESS_PTR_CURRENTINSTANCE;
  extern PGMINSTANCE* const GMAPI_ADDRESS_PTR_OTHERINSTANCE;

  extern void* const GM70_ADDRESS_PATCH_IDENTIFIERTYPECHECKING;
  extern void* const GM80_ADDRESS_PATCH_IDENTIFIERTYPECHECKING;
  extern BYTE const GM70_PATCH_IDENTIFIERTYPECHECKING[];
  extern BYTE const GM80_PATCH_IDENTIFIERTYPECHECKING[];
  extern int const GM_PATCHSIZE_IDENTIFIERTYPECHECKING;

  extern const char* const GM_FUNCTION_NAMES[];
  extern int const GM_FUNCTION_COUNT;

  enum GMFunctionPtrID {
    id_show_message,
    id_show_message_ext,
    id_show_question,
    id_get_integer,
    id_get_string,
    id_message_background,
    id_message_alpha,
    id_message_button,
    id_message_button_font,
    id_message_text_font,
    id_message_input_font,
    id_message_input_color,
    id_message_mouse_color,
    id_message_caption,
    id_message_position,
    id_message_size,
    id_show_menu,
    id_show_menu_pos,
    id_get_color,
    id_get_open_filename,
    id_get_save_filename,
    id_get_directory,
    id_get_directory_alt,
    id_splash_show_video,
    id_splash_show_text,
    id_splash_show_image,
    id_splash_show_web,
    id_splash_set_main,
    id_splash_set_scale,
    id_splash_set_cursor,
    id_splash_set_color,
    id_splash_set_caption,
    id_splash_set_fullscreen,
    id_splash_set_border,
    id_splash_set_size,
    id_splash_set_adapt,
    id_splash_set_top,
    id_splash_set_interrupt,
    id_splash_set_stop_key,
    id_splash_set_stop_mouse,
    id_splash_set_position,
    id_splash_set_close_button,
    id_show_info,
    id_load_info,
    id_show_error,
    id_highscore_show,
    id_highscore_set_background,
    id_highscore_set_border,
    id_highscore_set_font,
    id_highscore_set_colors,
    id_highscore_set_strings,
    id_highscore_show_ext,
    id_highscore_clear,
    id_highscore_add,
    id_highscore_add_current,
    id_highscore_value,
    id_highscore_name,
    id_draw_highscore,
    id_mplay_init_ipx,
    id_mplay_init_tcpip,
    id_mplay_init_modem,
    id_mplay_init_serial,
    id_mplay_connect_status,
    id_mplay_end,
    id_mplay_ipaddress,
    id_mplay_session_create,
    id_mplay_session_find,
    id_mplay_session_name,
    id_mplay_session_join,
    id_mplay_session_mode,
    id_mplay_session_status,
    id_mplay_session_end,
    id_mplay_player_find,
    id_mplay_player_name,
    id_mplay_player_id,
    id_mplay_data_write,
    id_mplay_data_read,
    id_mplay_data_mode,
    id_mplay_message_send,
    id_mplay_message_send_guaranteed,
    id_mplay_message_receive,
    id_mplay_message_id,
    id_mplay_message_value,
    id_mplay_message_player,
    id_mplay_message_name,
    id_mplay_message_count,
    id_mplay_message_clear,
    id_ds_set_precision,
    id_ds_list_create,
    id_ds_list_destroy,
    id_ds_list_clear,
    id_ds_list_copy,
    id_ds_list_size,
    id_ds_list_empty,
    id_ds_list_add,
    id_ds_list_insert,
    id_ds_list_replace,
    id_ds_list_delete,
    id_ds_list_find_index,
    id_ds_list_find_value,
    id_ds_list_sort,
    id_ds_list_shuffle,
    id_ds_list_write,
    id_ds_list_read,
    id_ds_stack_create,
    id_ds_stack_destroy,
    id_ds_stack_clear,
    id_ds_stack_copy,
    id_ds_stack_size,
    id_ds_stack_empty,
    id_ds_stack_push,
    id_ds_stack_pop,
    id_ds_stack_top,
    id_ds_stack_write,
    id_ds_stack_read,
    id_ds_queue_create,
    id_ds_queue_destroy,
    id_ds_queue_clear,
    id_ds_queue_copy,
    id_ds_queue_size,
    id_ds_queue_empty,
    id_ds_queue_enqueue,
    id_ds_queue_dequeue,
    id_ds_queue_head,
    id_ds_queue_tail,
    id_ds_queue_write,
    id_ds_queue_read,
    id_ds_map_create,
    id_ds_map_destroy,
    id_ds_map_clear,
    id_ds_map_copy,
    id_ds_map_size,
    id_ds_map_empty,
    id_ds_map_add,
    id_ds_map_replace,
    id_ds_map_delete,
    id_ds_map_exists,
    id_ds_map_find_value,
    id_ds_map_find_previous,
    id_ds_map_find_next,
    id_ds_map_find_first,
    id_ds_map_find_last,
    id_ds_map_write,
    id_ds_map_read,
    id_ds_priority_create,
    id_ds_priority_destroy,
    id_ds_priority_clear,
    id_ds_priority_copy,
    id_ds_priority_size,
    id_ds_priority_empty,
    id_ds_priority_add,
    id_ds_priority_change_priority,
    id_ds_priority_find_priority,
    id_ds_priority_delete_value,
    id_ds_priority_delete_min,
    id_ds_priority_find_min,
    id_ds_priority_delete_max,
    id_ds_priority_find_max,
    id_ds_priority_write,
    id_ds_priority_read,
    id_ds_grid_create,
    id_ds_grid_destroy,
    id_ds_grid_delete,
    id_ds_grid_copy,
    id_ds_grid_resize,
    id_ds_grid_width,
    id_ds_grid_height,
    id_ds_grid_clear,
    id_ds_grid_set,
    id_ds_grid_add,
    id_ds_grid_multiply,
    id_ds_grid_set_region,
    id_ds_grid_add_region,
    id_ds_grid_multiply_region,
    id_ds_grid_set_disk,
    id_ds_grid_add_disk,
    id_ds_grid_multiply_disk,
    id_ds_grid_set_grid_region,
    id_ds_grid_add_grid_region,
    id_ds_grid_multiply_grid_region,
    id_ds_grid_get,
    id_ds_grid_get_sum,
    id_ds_grid_get_max,
    id_ds_grid_get_min,
    id_ds_grid_get_mean,
    id_ds_grid_get_disk_sum,
    id_ds_grid_get_disk_min,
    id_ds_grid_get_disk_max,
    id_ds_grid_get_disk_mean,
    id_ds_grid_value_exists,
    id_ds_grid_value_x,
    id_ds_grid_value_y,
    id_ds_grid_value_disk_exists,
    id_ds_grid_value_disk_x,
    id_ds_grid_value_disk_y,
    id_ds_grid_shuffle,
    id_ds_grid_write,
    id_ds_grid_read,
    id_place_free,
    id_place_empty,
    id_place_meeting,
    id_place_snapped,
    id_move_random,
    id_move_snap,
    id_move_wrap,
    id_move_towards_point,
    id_move_bounce_solid,
    id_move_bounce_all,
    id_move_contact_solid,
    id_move_contact_all,
    id_move_outside_solid,
    id_move_outside_all,
    id_distance_to_point,
    id_distance_to_object,
    id_position_empty,
    id_position_meeting,
    id_path_start,
    id_path_end,
    id_mp_linear_step,
    id_mp_linear_step_object,
    id_mp_potential_step,
    id_mp_potential_step_object,
    id_mp_potential_settings,
    id_mp_linear_path,
    id_mp_linear_path_object,
    id_mp_potential_path,
    id_mp_potential_path_object,
    id_mp_grid_create,
    id_mp_grid_destroy,
    id_mp_grid_clear_all,
    id_mp_grid_clear_cell,
    id_mp_grid_clear_rectangle,
    id_mp_grid_add_cell,
    id_mp_grid_add_rectangle,
    id_mp_grid_add_instances,
    id_mp_grid_path,
    id_mp_grid_draw,
    id_collision_point,
    id_collision_rectangle,
    id_collision_circle,
    id_collision_ellipse,
    id_collision_line,
    id_instance_find,
    id_instance_exists,
    id_instance_number,
    id_instance_position,
    id_instance_nearest,
    id_instance_furthest,
    id_instance_place,
    id_instance_create,
    id_instance_copy,
    id_instance_destroy,
    id_instance_change,
    id_position_destroy,
    id_position_change,
    id_instance_deactivate_all,
    id_instance_deactivate_object,
    id_instance_deactivate_region,
    id_instance_activate_all,
    id_instance_activate_object,
    id_instance_activate_region,
    id_room_goto,
    id_room_goto_previous,
    id_room_goto_next,
    id_room_restart,
    id_room_previous,
    id_room_next,
    id_game_end,
    id_game_restart,
    id_game_save,
    id_game_load,
    id_transition_define,
    id_transition_exists,
    id_event_perform,
    id_event_perform_object,
    id_event_user,
    id_event_inherited,
    id_show_debug_message,
    id_variable_global_exists,
    id_variable_local_exists,
    id_variable_global_get,
    id_variable_global_array_get,
    id_variable_global_array2_get,
    id_variable_local_get,
    id_variable_local_array_get,
    id_variable_local_array2_get,
    id_variable_global_set,
    id_variable_global_array_set,
    id_variable_global_array2_set,
    id_variable_local_set,
    id_variable_local_array_set,
    id_variable_local_array2_set,
    id_set_program_priority,
    id_set_application_title,
    id_sound_play,
    id_sound_loop,
    id_sound_stop,
    id_sound_stop_all,
    id_sound_isplaying,
    id_sound_volume,
    id_sound_global_volume,
    id_sound_fade,
    id_sound_pan,
    id_sound_background_tempo,
    id_sound_set_search_directory,
    id_sound_effect_set,
    id_sound_effect_chorus,
    id_sound_effect_echo,
    id_sound_effect_flanger,
    id_sound_effect_gargle,
    id_sound_effect_reverb,
    id_sound_effect_compressor,
    id_sound_effect_equalizer,
    id_sound_3d_set_sound_position,
    id_sound_3d_set_sound_velocity,
    id_sound_3d_set_sound_distance,
    id_sound_3d_set_sound_cone,
    id_cd_init,
    id_cd_present,
    id_cd_number,
    id_cd_playing,
    id_cd_paused,
    id_cd_track,
    id_cd_length,
    id_cd_track_length,
    id_cd_position,
    id_cd_track_position,
    id_cd_play,
    id_cd_stop,
    id_cd_pause,
    id_cd_resume,
    id_cd_set_position,
    id_cd_set_track_position,
    id_cd_open_door,
    id_cd_close_door,
    id_MCI_command,
    id_script_execute,
    id_execute_string,
    id_execute_file,
    id_external_define,
    id_external_call,
    id_external_free,
    id_sprite_set_offset,
    id_sprite_set_bbox_mode,
    id_sprite_set_bbox,
    id_sprite_set_precise,
    id_sprite_duplicate,
    id_sprite_assign,
    id_sprite_merge,
    id_sprite_add,
    id_sprite_add_sprite,
    id_sprite_add_alpha,
    id_sprite_replace,
    id_sprite_replace_sprite,
    id_sprite_replace_alpha,
    id_sprite_create_from_screen,
    id_sprite_add_from_screen,
    id_sprite_create_from_surface,
    id_sprite_add_from_surface,
    id_sprite_delete,
    id_sprite_set_alpha_from_sprite,
    id_sprite_collision_mask,
    id_sound_add,
    id_sound_replace,
    id_sound_delete,
    id_background_duplicate,
    id_background_assign,
    id_background_add,
    id_background_add_background,
    id_background_add_alpha,
    id_background_replace,
    id_background_replace_background,
    id_background_replace_alpha,
    id_background_create_color,
    id_background_create_gradient,
    id_background_create_from_screen,
    id_background_create_from_surface,
    id_background_delete,
    id_background_set_alpha_from_background,
    id_font_add,
    id_font_add_sprite,
    id_font_replace,
    id_font_replace_sprite,
    id_font_delete,
    id_path_set_kind,
    id_path_set_closed,
    id_path_set_precision,
    id_path_add,
    id_path_delete,
    id_path_duplicate,
    id_path_assign,
    id_path_append,
    id_path_add_point,
    id_path_insert_point,
    id_path_change_point,
    id_path_delete_point,
    id_path_clear_points,
    id_path_reverse,
    id_path_mirror,
    id_path_flip,
    id_path_rotate,
    id_path_scale,
    id_path_shift,
    id_timeline_add,
    id_timeline_delete,
    id_timeline_moment_add,
    id_timeline_moment_clear,
    id_timeline_clear,
    id_object_set_sprite,
    id_object_set_solid,
    id_object_set_visible,
    id_object_set_depth,
    id_object_set_persistent,
    id_object_set_mask,
    id_object_set_parent,
    id_object_add,
    id_object_delete,
    id_object_event_add,
    id_object_event_clear,
    id_room_set_width,
    id_room_set_height,
    id_room_set_caption,
    id_room_set_persistent,
    id_room_set_code,
    id_room_set_background_color,
    id_room_set_background,
    id_room_set_view,
    id_room_set_view_enabled,
    id_room_add,
    id_room_duplicate,
    id_room_assign,
    id_room_instance_add,
    id_room_instance_clear,
    id_room_tile_add,
    id_room_tile_add_ext,
    id_room_tile_clear,
    id_sprite_exists,
    id_sprite_get_name,
    id_sprite_get_number,
    id_sprite_get_width,
    id_sprite_get_height,
    id_sprite_get_transparent,
    id_sprite_get_smooth,
    id_sprite_get_preload,
    id_sprite_get_xoffset,
    id_sprite_get_yoffset,
    id_sprite_get_bbox_left,
    id_sprite_get_bbox_right,
    id_sprite_get_bbox_top,
    id_sprite_get_bbox_bottom,
    id_sprite_get_bbox_mode,
    id_sprite_get_precise,
    id_sprite_save,
    id_sprite_save_strip,
    id_sound_exists,
    id_sound_get_name,
    id_sound_get_kind,
    id_sound_get_preload,
    id_sound_discard,
    id_sound_restore,
    id_background_exists,
    id_background_get_name,
    id_background_get_width,
    id_background_get_height,
    id_background_get_transparent,
    id_background_get_smooth,
    id_background_get_preload,
    id_background_save,
    id_font_exists,
    id_font_get_name,
    id_font_get_fontname,
    id_font_get_bold,
    id_font_get_italic,
    id_font_get_first,
    id_font_get_last,
    id_path_exists,
    id_path_get_name,
    id_path_get_length,
    id_path_get_kind,
    id_path_get_closed,
    id_path_get_precision,
    id_path_get_number,
    id_path_get_point_x,
    id_path_get_point_y,
    id_path_get_point_speed,
    id_path_get_x,
    id_path_get_y,
    id_path_get_speed,
    id_script_exists,
    id_script_get_name,
    id_script_get_text,
    id_timeline_exists,
    id_timeline_get_name,
    id_object_exists,
    id_object_get_name,
    id_object_get_sprite,
    id_object_get_solid,
    id_object_get_visible,
    id_object_get_depth,
    id_object_get_persistent,
    id_object_get_mask,
    id_object_get_parent,
    id_object_is_ancestor,
    id_room_exists,
    id_room_get_name,
    id_draw_sprite,
    id_draw_sprite_stretched,
    id_draw_sprite_tiled,
    id_draw_sprite_part,
    id_draw_background,
    id_draw_background_stretched,
    id_draw_background_tiled,
    id_draw_background_part,
    id_draw_sprite_ext,
    id_draw_sprite_stretched_ext,
    id_draw_sprite_tiled_ext,
    id_draw_sprite_part_ext,
    id_draw_sprite_general,
    id_draw_background_ext,
    id_draw_background_stretched_ext,
    id_draw_background_tiled_ext,
    id_draw_background_part_ext,
    id_draw_background_general,
    id_draw_clear,
    id_draw_clear_alpha,
    id_draw_point,
    id_draw_line,
    id_draw_line_width,
    id_draw_rectangle,
    id_draw_roundrect,
    id_draw_triangle,
    id_draw_circle,
    id_draw_ellipse,
    id_draw_set_circle_precision,
    id_draw_arrow,
    id_draw_button,
    id_draw_path,
    id_draw_healthbar,
    id_draw_set_color,
    id_draw_set_alpha,
    id_draw_get_color,
    id_draw_get_alpha,
    id_make_color_rgb,
    id_make_color_hsv,
    id_color_get_red,
    id_color_get_green,
    id_color_get_blue,
    id_color_get_hue,
    id_color_get_saturation,
    id_color_get_value,
    id_merge_color,
    id_draw_getpixel,
    id_screen_save,
    id_screen_save_part,
    id_draw_set_font,
    id_draw_set_halign,
    id_draw_set_valign,
    id_draw_text,
    id_draw_text_ext,
    id_string_width,
    id_string_height,
    id_string_width_ext,
    id_string_height_ext,
    id_draw_text_transformed,
    id_draw_text_ext_transformed,
    id_draw_text_color,
    id_draw_text_ext_color,
    id_draw_text_transformed_color,
    id_draw_text_ext_transformed_color,
    id_draw_point_color,
    id_draw_line_color,
    id_draw_line_width_color,
    id_draw_rectangle_color,
    id_draw_roundrect_color,
    id_draw_triangle_color,
    id_draw_circle_color,
    id_draw_ellipse_color,
    id_draw_primitive_begin,
    id_draw_vertex,
    id_draw_vertex_color,
    id_draw_primitive_end,
    id_sprite_get_texture,
    id_background_get_texture,
    id_texture_preload,
    id_texture_set_priority,
    id_texture_get_width,
    id_texture_get_height,
    id_draw_primitive_begin_texture,
    id_draw_vertex_texture,
    id_draw_vertex_texture_color,
    id_texture_set_interpolation,
    id_texture_set_blending,
    id_texture_set_repeat,
    id_draw_set_blend_mode,
    id_draw_set_blend_mode_ext,
    id_surface_create,
    id_surface_free,
    id_surface_exists,
    id_surface_get_width,
    id_surface_get_height,
    id_surface_get_texture,
    id_surface_set_target,
    id_surface_reset_target,
    id_surface_getpixel,
    id_surface_save,
    id_surface_save_part,
    id_draw_surface,
    id_draw_surface_stretched,
    id_draw_surface_tiled,
    id_draw_surface_part,
    id_draw_surface_ext,
    id_draw_surface_stretched_ext,
    id_draw_surface_tiled_ext,
    id_draw_surface_part_ext,
    id_draw_surface_general,
    id_surface_copy,
    id_surface_copy_part,
    id_tile_add,
    id_tile_delete,
    id_tile_exists,
    id_tile_get_x,
    id_tile_get_y,
    id_tile_get_left,
    id_tile_get_top,
    id_tile_get_width,
    id_tile_get_height,
    id_tile_get_depth,
    id_tile_get_visible,
    id_tile_get_xscale,
    id_tile_get_yscale,
    id_tile_get_background,
    id_tile_get_blend,
    id_tile_get_alpha,
    id_tile_set_position,
    id_tile_set_region,
    id_tile_set_background,
    id_tile_set_visible,
    id_tile_set_depth,
    id_tile_set_scale,
    id_tile_set_blend,
    id_tile_set_alpha,
    id_tile_layer_hide,
    id_tile_layer_show,
    id_tile_layer_delete,
    id_tile_layer_shift,
    id_tile_layer_find,
    id_tile_layer_delete_at,
    id_tile_layer_depth,
    id_display_get_width,
    id_display_get_height,
    id_display_get_colordepth,
    id_display_get_frequency,
    id_display_set_size,
    id_display_set_colordepth,
    id_display_set_frequency,
    id_display_set_all,
    id_display_test_all,
    id_display_reset,
    id_display_mouse_get_x,
    id_display_mouse_get_y,
    id_display_mouse_set,
    id_window_set_visible,
    id_window_get_visible,
    id_window_set_fullscreen,
    id_window_get_fullscreen,
    id_window_set_showborder,
    id_window_get_showborder,
    id_window_set_showicons,
    id_window_get_showicons,
    id_window_set_stayontop,
    id_window_get_stayontop,
    id_window_set_sizeable,
    id_window_get_sizeable,
    id_window_set_caption,
    id_window_get_caption,
    id_window_set_cursor,
    id_window_get_cursor,
    id_window_set_color,
    id_window_get_color,
    id_window_set_region_scale,
    id_window_get_region_scale,
    id_window_set_position,
    id_window_set_size,
    id_window_set_rectangle,
    id_window_center,
    id_window_default,
    id_window_get_x,
    id_window_get_y,
    id_window_get_width,
    id_window_get_height,
    id_window_mouse_get_x,
    id_window_mouse_get_y,
    id_window_mouse_set,
    id_window_set_region_size,
    id_window_get_region_width,
    id_window_get_region_height,
    id_window_view_mouse_get_x,
    id_window_view_mouse_get_y,
    id_window_view_mouse_set,
    id_window_views_mouse_get_x,
    id_window_views_mouse_get_y,
    id_window_views_mouse_set,
    id_screen_redraw,
    id_screen_refresh,
    id_set_automatic_draw,
    id_set_synchronization,
    id_screen_wait_vsync,
    id_window_handle,
    id_keyboard_set_map,
    id_keyboard_get_map,
    id_keyboard_unset_map,
    id_keyboard_check,
    id_keyboard_check_pressed,
    id_keyboard_check_released,
    id_keyboard_check_direct,
    id_keyboard_get_numlock,
    id_keyboard_set_numlock,
    id_keyboard_key_press,
    id_keyboard_key_release,
    id_keyboard_clear,
    id_io_clear,
    id_io_handle,
    id_keyboard_wait,
    id_mouse_check_button,
    id_mouse_check_button_pressed,
    id_mouse_check_button_released,
    id_mouse_wheel_up,
    id_mouse_wheel_down,
    id_mouse_clear,
    id_mouse_wait,
    id_joystick_exists,
    id_joystick_name,
    id_joystick_axes,
    id_joystick_buttons,
    id_joystick_has_pov,
    id_joystick_direction,
    id_joystick_check_button,
    id_joystick_xpos,
    id_joystick_ypos,
    id_joystick_zpos,
    id_joystick_rpos,
    id_joystick_upos,
    id_joystick_vpos,
    id_joystick_pov,
    id_file_text_open_read,
    id_file_text_open_write,
    id_file_text_open_append,
    id_file_text_close,
    id_file_text_write_string,
    id_file_text_write_real,
    id_file_text_writeln,
    id_file_text_read_string,
    id_file_text_read_real,
    id_file_text_readln,
    id_file_text_eof,
    id_file_text_eoln,
    id_file_exists,
    id_file_delete,
    id_file_rename,
    id_file_copy,
    id_directory_exists,
    id_directory_create,
    id_file_find_first,
    id_file_find_next,
    id_file_find_close,
    id_file_attributes,
    id_filename_name,
    id_filename_path,
    id_filename_dir,
    id_filename_drive,
    id_filename_ext,
    id_filename_change_ext,
    id_file_bin_open,
    id_file_bin_rewrite,
    id_file_bin_close,
    id_file_bin_size,
    id_file_bin_position,
    id_file_bin_seek,
    id_file_bin_write_byte,
    id_file_bin_read_byte,
    id_export_include_file,
    id_export_include_file_location,
    id_discard_include_file,
    id_parameter_count,
    id_parameter_string,
    id_environment_get_variable,
    id_disk_free,
    id_disk_size,
    id_registry_write_string,
    id_registry_write_real,
    id_registry_read_string,
    id_registry_read_real,
    id_registry_exists,
    id_registry_write_string_ext,
    id_registry_write_real_ext,
    id_registry_read_string_ext,
    id_registry_read_real_ext,
    id_registry_exists_ext,
    id_registry_set_root,
    id_ini_open,
    id_ini_close,
    id_ini_read_string,
    id_ini_read_real,
    id_ini_write_string,
    id_ini_write_real,
    id_ini_key_exists,
    id_ini_section_exists,
    id_ini_key_delete,
    id_ini_section_delete,
    id_execute_program,
    id_execute_shell,
    id_effect_create_below,
    id_effect_create_above,
    id_effect_clear,
    id_part_type_create,
    id_part_type_destroy,
    id_part_type_exists,
    id_part_type_clear,
    id_part_type_shape,
    id_part_type_sprite,
    id_part_type_size,
    id_part_type_scale,
    id_part_type_orientation,
    id_part_type_color1,
    id_part_type_color2,
    id_part_type_color3,
    id_part_type_color_mix,
    id_part_type_color_rgb,
    id_part_type_color_hsv,
    id_part_type_alpha1,
    id_part_type_alpha2,
    id_part_type_alpha3,
    id_part_type_blend,
    id_part_type_life,
    id_part_type_step,
    id_part_type_death,
    id_part_type_speed,
    id_part_type_direction,
    id_part_type_gravity,
    id_part_system_create,
    id_part_system_destroy,
    id_part_system_exists,
    id_part_system_clear,
    id_part_system_draw_order,
    id_part_system_depth,
    id_part_system_position,
    id_part_system_automatic_update,
    id_part_system_automatic_draw,
    id_part_system_update,
    id_part_system_drawit,
    id_part_particles_create,
    id_part_particles_create_color,
    id_part_particles_clear,
    id_part_particles_count,
    id_part_emitter_create,
    id_part_emitter_destroy,
    id_part_emitter_destroy_all,
    id_part_emitter_exists,
    id_part_emitter_clear,
    id_part_emitter_region,
    id_part_emitter_burst,
    id_part_emitter_stream,
    id_part_attractor_create,
    id_part_attractor_destroy,
    id_part_attractor_destroy_all,
    id_part_attractor_exists,
    id_part_attractor_clear,
    id_part_attractor_position,
    id_part_attractor_force,
    id_part_destroyer_create,
    id_part_destroyer_destroy,
    id_part_destroyer_destroy_all,
    id_part_destroyer_exists,
    id_part_destroyer_clear,
    id_part_destroyer_region,
    id_part_deflector_create,
    id_part_deflector_destroy,
    id_part_deflector_destroy_all,
    id_part_deflector_exists,
    id_part_deflector_clear,
    id_part_deflector_region,
    id_part_deflector_kind,
    id_part_deflector_friction,
    id_part_changer_create,
    id_part_changer_destroy,
    id_part_changer_destroy_all,
    id_part_changer_exists,
    id_part_changer_clear,
    id_part_changer_region,
    id_part_changer_types,
    id_part_changer_kind,
    id_d3d_start,
    id_d3d_end,
    id_d3d_set_hidden,
    id_d3d_set_perspective,
    id_d3d_set_depth,
    id_d3d_set_culling,
    id_d3d_primitive_begin,
    id_d3d_primitive_begin_texture,
    id_d3d_vertex,
    id_d3d_vertex_color,
    id_d3d_vertex_texture,
    id_d3d_vertex_texture_color,
    id_d3d_primitive_end,
    id_d3d_draw_block,
    id_d3d_draw_cylinder,
    id_d3d_draw_cone,
    id_d3d_draw_ellipsoid,
    id_d3d_draw_wall,
    id_d3d_draw_floor,
    id_d3d_set_projection,
    id_d3d_set_projection_ext,
    id_d3d_set_projection_ortho,
    id_d3d_set_projection_perspective,
    id_d3d_transform_set_identity,
    id_d3d_transform_set_translation,
    id_d3d_transform_set_scaling,
    id_d3d_transform_set_rotation_x,
    id_d3d_transform_set_rotation_y,
    id_d3d_transform_set_rotation_z,
    id_d3d_transform_set_rotation_axis,
    id_d3d_transform_add_translation,
    id_d3d_transform_add_scaling,
    id_d3d_transform_add_rotation_x,
    id_d3d_transform_add_rotation_y,
    id_d3d_transform_add_rotation_z,
    id_d3d_transform_add_rotation_axis,
    id_d3d_transform_stack_clear,
    id_d3d_transform_stack_empty,
    id_d3d_transform_stack_push,
    id_d3d_transform_stack_pop,
    id_d3d_transform_stack_top,
    id_d3d_transform_stack_discard,
    id_d3d_set_fog,
    id_d3d_set_lighting,
    id_d3d_set_shading,
    id_d3d_light_define_direction,
    id_d3d_light_define_point,
    id_d3d_light_enable,
    id_d3d_vertex_normal,
    id_d3d_vertex_normal_color,
    id_d3d_vertex_normal_texture,
    id_d3d_vertex_normal_texture_color,
    id_d3d_model_create,
    id_d3d_model_destroy,
    id_d3d_model_clear,
    id_d3d_model_save,
    id_d3d_model_load,
    id_d3d_model_draw,
    id_d3d_model_primitive_begin,
    id_d3d_model_vertex,
    id_d3d_model_vertex_color,
    id_d3d_model_vertex_texture,
    id_d3d_model_vertex_texture_color,
    id_d3d_model_vertex_normal,
    id_d3d_model_vertex_normal_color,
    id_d3d_model_vertex_normal_texture,
    id_d3d_model_vertex_normal_texture_color,
    id_d3d_model_primitive_end,
    id_d3d_model_block,
    id_d3d_model_cylinder,
    id_d3d_model_cone,
    id_d3d_model_ellipsoid,
    id_d3d_model_wall,
    id_d3d_model_floor
  };

  extern int const self;
  extern int const other;
  extern int const all;
  extern int const noone;
  extern int const global;
  extern int const local;
  extern double const pi;
  extern int const ev_create;
  extern int const ev_destroy;
  extern int const ev_step;
  extern int const ev_alarm;
  extern int const ev_keyboard;
  extern int const ev_mouse;
  extern int const ev_collision;
  extern int const ev_other;
  extern int const ev_draw;
  extern int const ev_keypress;
  extern int const ev_keyrelease;
  extern int const ev_trigger;
  extern int const ev_left_button;
  extern int const ev_right_button;
  extern int const ev_middle_button;
  extern int const ev_no_button;
  extern int const ev_left_press;
  extern int const ev_right_press;
  extern int const ev_middle_press;
  extern int const ev_left_release;
  extern int const ev_right_release;
  extern int const ev_middle_release;
  extern int const ev_mouse_enter;
  extern int const ev_mouse_leave;
  extern int const ev_mouse_wheel_up;
  extern int const ev_mouse_wheel_down;
  extern int const ev_global_left_button;
  extern int const ev_global_right_button;
  extern int const ev_global_middle_button;
  extern int const ev_global_left_press;
  extern int const ev_global_right_press;
  extern int const ev_global_middle_press;
  extern int const ev_global_left_release;
  extern int const ev_global_right_release;
  extern int const ev_global_middle_release;
  extern int const ev_joystick1_left;
  extern int const ev_joystick1_right;
  extern int const ev_joystick1_up;
  extern int const ev_joystick1_down;
  extern int const ev_joystick1_button1;
  extern int const ev_joystick1_button2;
  extern int const ev_joystick1_button3;
  extern int const ev_joystick1_button4;
  extern int const ev_joystick1_button5;
  extern int const ev_joystick1_button6;
  extern int const ev_joystick1_button7;
  extern int const ev_joystick1_button8;
  extern int const ev_joystick2_left;
  extern int const ev_joystick2_right;
  extern int const ev_joystick2_up;
  extern int const ev_joystick2_down;
  extern int const ev_joystick2_button1;
  extern int const ev_joystick2_button2;
  extern int const ev_joystick2_button3;
  extern int const ev_joystick2_button4;
  extern int const ev_joystick2_button5;
  extern int const ev_joystick2_button6;
  extern int const ev_joystick2_button7;
  extern int const ev_joystick2_button8;
  extern int const ev_outside;
  extern int const ev_boundary;
  extern int const ev_game_start;
  extern int const ev_game_end;
  extern int const ev_room_start;
  extern int const ev_room_end;
  extern int const ev_no_more_lives;
  extern int const ev_animation_end;
  extern int const ev_end_of_path;
  extern int const ev_no_more_health;
  extern int const ev_close_button;
  extern int const ev_user0;
  extern int const ev_user1;
  extern int const ev_user2;
  extern int const ev_user3;
  extern int const ev_user4;
  extern int const ev_user5;
  extern int const ev_user6;
  extern int const ev_user7;
  extern int const ev_user8;
  extern int const ev_user9;
  extern int const ev_user10;
  extern int const ev_user11;
  extern int const ev_user12;
  extern int const ev_user13;
  extern int const ev_user14;
  extern int const ev_user15;
  extern int const ev_step_normal;
  extern int const ev_step_begin;
  extern int const ev_step_end;
  extern int const vk_nokey;
  extern int const vk_anykey;
  extern int const vk_enter;
  extern int const vk_return;
  extern int const vk_shift;
  extern int const vk_control;
  extern int const vk_alt;
  extern int const vk_escape;
  extern int const vk_space;
  extern int const vk_backspace;
  extern int const vk_tab;
  extern int const vk_pause;
  extern int const vk_printscreen;
  extern int const vk_left;
  extern int const vk_right;
  extern int const vk_up;
  extern int const vk_down;
  extern int const vk_home;
  extern int const vk_end;
  extern int const vk_delete;
  extern int const vk_insert;
  extern int const vk_pageup;
  extern int const vk_pagedown;
  extern int const vk_f1;
  extern int const vk_f2;
  extern int const vk_f3;
  extern int const vk_f4;
  extern int const vk_f5;
  extern int const vk_f6;
  extern int const vk_f7;
  extern int const vk_f8;
  extern int const vk_f9;
  extern int const vk_f10;
  extern int const vk_f11;
  extern int const vk_f12;
  extern int const vk_numpad0;
  extern int const vk_numpad1;
  extern int const vk_numpad2;
  extern int const vk_numpad3;
  extern int const vk_numpad4;
  extern int const vk_numpad5;
  extern int const vk_numpad6;
  extern int const vk_numpad7;
  extern int const vk_numpad8;
  extern int const vk_numpad9;
  extern int const vk_divide;
  extern int const vk_multiply;
  extern int const vk_subtract;
  extern int const vk_add;
  extern int const vk_decimal;
  extern int const vk_lshift;
  extern int const vk_lcontrol;
  extern int const vk_lalt;
  extern int const vk_rshift;
  extern int const vk_rcontrol;
  extern int const vk_ralt;
  extern int const mb_any;
  extern int const mb_none;
  extern int const mb_left;
  extern int const mb_right;
  extern int const mb_middle;
  extern int const c_aqua;
  extern int const c_black;
  extern int const c_blue;
  extern int const c_dkgray;
  extern int const c_fuchsia;
  extern int const c_gray;
  extern int const c_green;
  extern int const c_lime;
  extern int const c_ltgray;
  extern int const c_maroon;
  extern int const c_navy;
  extern int const c_olive;
  extern int const c_purple;
  extern int const c_red;
  extern int const c_silver;
  extern int const c_teal;
  extern int const c_white;
  extern int const c_yellow;
  extern int const c_orange;
  extern int const fa_left;
  extern int const fa_center;
  extern int const fa_right;
  extern int const fa_top;
  extern int const fa_middle;
  extern int const fa_bottom;
  extern int const pr_pointlist;
  extern int const pr_linelist;
  extern int const pr_linestrip;
  extern int const pr_trianglelist;
  extern int const pr_trianglestrip;
  extern int const pr_trianglefan;
  extern int const bm_normal;
  extern int const bm_add;
  extern int const bm_max;
  extern int const bm_subtract;
  extern int const bm_zero;
  extern int const bm_one;
  extern int const bm_src_color;
  extern int const bm_inv_src_color;
  extern int const bm_src_alpha;
  extern int const bm_inv_src_alpha;
  extern int const bm_dest_alpha;
  extern int const bm_inv_dest_alpha;
  extern int const bm_dest_color;
  extern int const bm_inv_dest_color;
  extern int const bm_src_alpha_sat;
  extern int const cr_default;
  extern int const cr_none;
  extern int const cr_arrrow;
  extern int const cr_cross;
  extern int const cr_beam;
  extern int const cr_size_nesw;
  extern int const cr_size_ns;
  extern int const cr_size_nwse;
  extern int const cr_size_we;
  extern int const cr_uparrow;
  extern int const cr_hourglass;
  extern int const cr_drag;
  extern int const cr_nodrop;
  extern int const cr_hsplit;
  extern int const cr_vsplit;
  extern int const cr_multidrag;
  extern int const cr_sqlwait;
  extern int const cr_no;
  extern int const cr_appstart;
  extern int const cr_help;
  extern int const cr_handpoint;
  extern int const cr_size_all;
  extern int const se_none;
  extern int const se_chorus;
  extern int const se_echo;
  extern int const se_flanger;
  extern int const se_gargle;
  extern int const se_reverb;
  extern int const se_compressor;
  extern int const se_equalizer;
  extern int const fa_readonly;
  extern int const fa_hidden;
  extern int const fa_sysfile;
  extern int const fa_volumeid;
  extern int const fa_directory;
  extern int const fa_archive;
  extern int const ef_explosion;
  extern int const ef_ring;
  extern int const ef_ellipse;
  extern int const ef_firework;
  extern int const ef_smoke;
  extern int const ef_smokeup;
  extern int const ef_star;
  extern int const ef_spark;
  extern int const ef_flare;
  extern int const ef_cloud;
  extern int const ef_rain;
  extern int const ef_snow;
  extern int const pt_shape_pixel;
  extern int const pt_shape_disk;
  extern int const pt_shape_square;
  extern int const pt_shape_line;
  extern int const pt_shape_star;
  extern int const pt_shape_circle;
  extern int const pt_shape_ring;
  extern int const pt_shape_sphere;
  extern int const pt_shape_flare;
  extern int const pt_shape_spark;
  extern int const pt_shape_explosion;
  extern int const pt_shape_cloud;
  extern int const pt_shape_smoke;
  extern int const pt_shape_snow;
  extern int const ps_distr_linear;
  extern int const ps_distr_gaussian;
  extern int const ps_distr_invgaussian;
  extern int const ps_shape_rectangle;
  extern int const ps_shape_ellipse;
  extern int const ps_shape_diamond;
  extern int const ps_shape_line;
  extern int const ps_force_constant;
  extern int const ps_force_linear;
  extern int const ps_force_quadratic;
  extern int const ps_deflect_vertical;
  extern int const ps_deflect_horizontal;
  extern int const ps_change_all;
  extern int const ps_change_shape;
  extern int const ps_change_motion;
  extern int const ty_real;
  extern int const ty_string;
  extern int const dll_cdecl;
  extern int const dll_stdcall;

}
