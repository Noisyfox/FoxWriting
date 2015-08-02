#define fw_init
//void fw_init(sprite)
// Noisyfox's Writing
// Initialize the variables using by these script.

/*
globalvar FontStyleRegular;
globalvar FontStyleBold;
globalvar FontStyleItalic;
globalvar FontStyleUnderline;
globalvar FontStyleStrikeout;

FontStyleRegular    = 0;
FontStyleBold       = 1;
FontStyleItalic     = 2;
FontStyleUnderline  = 4;
FontStyleStrikeout  = 8;
*/

global.__NF_W_DLL = "FoxWriting.dll";

global.__NF_W_ED_Init = external_define(global.__NF_W_DLL, "FWInit", dll_stdcall, ty_real, 1, ty_real);
global.__NF_W_ED_ReleaseCache = external_define(global.__NF_W_DLL, "FWReleaseCache", dll_stdcall, ty_real, 0);
global.__NF_W_ED_Cleanup = external_define(global.__NF_W_DLL, "FWCleanup", dll_stdcall, ty_real, 0);

global.__NF_W_ED_AddFont = external_define(global.__NF_W_DLL, "FWAddFont", dll_stdcall, ty_real, 3, ty_string, ty_real, ty_real);
global.__NF_W_ED_AddFontFromFile = external_define(global.__NF_W_DLL, "FWAddFontFromFile", dll_stdcall, ty_real, 3, ty_string, ty_real, ty_real);
global.__NF_W_ED_DeleteFont = external_define(global.__NF_W_DLL, "FWDeleteFont", dll_stdcall, ty_real, 1, ty_real);
global.__NF_W_ED_SetFontOffset = external_define(global.__NF_W_DLL, "FWSetFontOffset", dll_stdcall, ty_real, 3, ty_real, ty_real, ty_real);
global.__NF_W_ED_PreloadFont = external_define(global.__NF_W_DLL, "FWPreloadFont", dll_stdcall, ty_real, 3, ty_real, ty_real, ty_real);
global.__NF_W_ED_SetFont = external_define(global.__NF_W_DLL, "FWSetFont", dll_stdcall, ty_real, 1, ty_real);
global.__NF_W_ED_EnablePixelAlignment = external_define(global.__NF_W_DLL, "FWEnablePixelAlignment", dll_stdcall, ty_real, 1, ty_real);

global.__NF_W_ED_StringWidth = external_define(global.__NF_W_DLL, "FWStringWidth", dll_stdcall, ty_real, 1, ty_string);
global.__NF_W_ED_StringHeight = external_define(global.__NF_W_DLL, "FWStringHeight", dll_stdcall, ty_real, 1, ty_string);
global.__NF_W_ED_StringWidthExt = external_define(global.__NF_W_DLL, "FWStringWidthEx", dll_stdcall, ty_real, 3, ty_string, ty_real, ty_real);
global.__NF_W_ED_StringHeightExt = external_define(global.__NF_W_DLL, "FWStringHeightEx", dll_stdcall, ty_real, 3, ty_string, ty_real, ty_real);

global.__NF_W_ED_SetHAlign = external_define(global.__NF_W_DLL, "FWSetHAlign", dll_stdcall, ty_real, 1, ty_real);
global.__NF_W_ED_SetVAlign = external_define(global.__NF_W_DLL, "FWSetVAlign", dll_stdcall, ty_real, 1, ty_real);

global.__NF_W_ED_SetLineSpacing = external_define(global.__NF_W_DLL, "FWSetLineSpacing", dll_stdcall, ty_real, 1, ty_real);

global.__NF_W_ED_DrawText = external_define(global.__NF_W_DLL, "FWDrawText", dll_stdcall, ty_real, 3, ty_real, ty_real, ty_string);
global.__NF_W_ED_DrawTextExt = external_define(global.__NF_W_DLL, "FWDrawTextEx", dll_stdcall, ty_real, 4, ty_real, ty_real, ty_string, ty_string);

global.__NF_W_ED_DrawTextTransformed = external_define(global.__NF_W_DLL, "FWDrawTextTransformed", dll_stdcall, ty_real, 4, ty_real, ty_real, ty_string, ty_string);
global.__NF_W_ED_DrawTextTransformedExt = external_define(global.__NF_W_DLL, "FWDrawTextTransformedEx", dll_stdcall, ty_real, 4, ty_real, ty_real, ty_string, ty_string);

global.__NF_W_ED_DrawTextColor = external_define(global.__NF_W_DLL, "FWDrawTextColor", dll_stdcall, ty_real, 4, ty_real, ty_real, ty_string, ty_string);
global.__NF_W_ED_DrawTextColorExt = external_define(global.__NF_W_DLL, "FWDrawTextColorEx", dll_stdcall, ty_real, 4, ty_real, ty_real, ty_string, ty_string);

global.__NF_W_ED_DrawTextTransformedColor = external_define(global.__NF_W_DLL, "FWDrawTextTransformedColor", dll_stdcall, ty_real, 4, ty_real, ty_real, ty_string, ty_string);
global.__NF_W_ED_DrawTextTransformedColorExt = external_define(global.__NF_W_DLL, "FWDrawTextTransformedColorEx", dll_stdcall, ty_real, 4, ty_real, ty_real, ty_string, ty_string);

result = external_call(global.__NF_W_ED_Init, argument0);

if(!result){
    show_error("FowWriting ≥ı ºªØ ß∞‹£°", true);
}


#define fw_release_cache
//void fw_release_cache()
// Noisyfox's Writing
// Restore the sprite to init state for gm to use

external_call(global.__NF_W_ED_ReleaseCache);


#define fw_cleanup
//void fw_cleanup()
// Noisyfox's Writing
// Cleanup and free memory.

external_call(global.__NF_W_ED_Cleanup);
external_free(global.__NF_W_DLL);

global.__NF_W_DLL = 0;

global.__NF_W_ED_Init = 0;
global.__NF_W_ED_ReleaseCache = 0;
global.__NF_W_ED_Cleanup = 0;

global.__NF_W_ED_AddFont = 0;
global.__NF_W_ED_AddFontFromFile = 0;
global.__NF_W_ED_DeleteFont = 0;
global.__NF_W_ED_SetFontOffset = 0;
global.__NF_W_ED_PreloadFont = 0;
global.__NF_W_ED_SetFont = 0;
global.__NF_W_ED_EnablePixelAlignment = 0;

global.__NF_W_ED_StringWidth = 0;
global.__NF_W_ED_StringHeight = 0;
global.__NF_W_ED_StringWidthExt = 0;
global.__NF_W_ED_StringHeightExt = 0;

global.__NF_W_ED_SetHAlign = 0;
global.__NF_W_ED_SetVAlign = 0;

global.__NF_W_ED_SetLineSpacing = 0;

global.__NF_W_ED_DrawText = 0;
global.__NF_W_ED_DrawTextExt = 0;

global.__NF_W_ED_DrawTextTransformed = 0;
global.__NF_W_ED_DrawTextTransformedExt = 0;

global.__NF_W_ED_DrawTextColor = 0;
global.__NF_W_ED_DrawTextColorExt = 0;

global.__NF_W_ED_DrawTextTransformedColor = 0;
global.__NF_W_ED_DrawTextTransformedColorExt = 0;


#define fw_add_font
// int fw_add_font(string name, real size, bool bold, bool italic, bool stroke)
// Noisyfox's Writing
// Register a font to draw
// Returns the font's index if success, -1 otherwise

var style;
style = 0;
if(argument2){
    style = style | 1;
}
if(argument3){
    style = style | 2;
}
if(argument4){
    style = style | 4;
}
return external_call(global.__NF_W_ED_AddFont, argument0, argument1, style);


#define fw_add_font_from_file
// int fw_add_font_from_file(string ttf, real size, bool bold, bool italic, bool stroke)
// Noisyfox's Writing
// Register a font to draw
// Returns the font's index if success, -1 otherwise

var style;
style = 0;
if(argument2){
    style = style | 1;
}
if(argument3){
    style = style | 2;
}
if(argument4){
    style = style | 4;
}
return external_call(global.__NF_W_ED_AddFontFromFile, argument0, argument1, style);


#define fw_set_font_offset
// boolean fw_set_font_offset(int font, real xOffset, real yOffset)
// Noisyfox's Writing
// Set the font's offset
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_SetFontOffset, argument0, argument1, argument2);


#define fw_preload_font
// boolean fw_preload_font(int font, int from, int to)
// Noisyfox's Writing
// Preload characters between from and to.
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_PreloadFont, argument0, argument1, argument2);


#define fw_delete_font
// boolean fw_delete_font(int font)
// Noisyfox's Writing
// Unregister the given font and free memory
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_DeleteFont, argument0);


#define fw_draw_set_font
// boolean fw_draw_set_font(int font)
// Noisyfox's Writing
// Set a font to draw
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_SetFont, argument0);


#define fw_draw_set_halign
// boolean fw_draw_set_halign(int align)
// Noisyfox's Writing
// Set the horizontal alignment
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_SetHAlign, argument0);


#define fw_draw_set_valign
// boolean fw_draw_set_valign(int align)
// Noisyfox's Writing
// Set the vertical alignment
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_SetVAlign, argument0);


#define fw_draw_set_line_spacing
// boolean fw_draw_set_line_spacing(real sep)
// Noisyfox's Writing
// Set the line spacing used in DrawText***
// Use -1 for default value
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_SetLineSpacing, argument0);


#define fw_enable_pixel_alignment
// boolean fw_enable_pixel_alignment(boolean enable)
// Noisyfox's Writing
// Set whether we should align the drawing based on pixel
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_EnablePixelAlignment, argument0);


#define fw_string_width
// real fw_string_width(string str)
// Noisyfox's Writing
// Compute the width of given string
// Returns width

return external_call(global.__NF_W_ED_StringWidth, argument0);


#define fw_string_height
// real fw_string_height(string str)
// Noisyfox's Writing
// Compute the height of given string
// Returns height

return external_call(global.__NF_W_ED_StringHeight, argument0);


#define fw_string_width_ext
// real fw_string_width_ext(string str, real sep, real w)
// Noisyfox's Writing
// Compute the width of given string, with sep and w specific
// Returns width

return external_call(global.__NF_W_ED_StringWidthExt, argument0, argument1, argument2);


#define fw_string_height_ext
// real fw_string_height_ext(string str, real sep, real w)
// Noisyfox's Writing
// Compute the height of given string, with sep and w specific
// Returns height

return external_call(global.__NF_W_ED_StringHeightExt, argument0, argument1, argument2);


#define fw_draw_text
// boolean fw_draw_text(real x, real y, string str)
// Noisyfox's Writing
// Draw text
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_DrawText, argument0, argument1, argument2);


#define fw_draw_text_ext
// boolean fw_draw_text_ext(real x, real y, string str, real w)
// Noisyfox's Writing
// Draw text with w specific
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_DrawTextExt, argument0, argument1, argument2, _NF_W_CreateArgs(1, argument3));


#define fw_draw_text_transformed
// boolean fw_draw_text_transformed(real x, real y, string str, real xscale, real yscale, real angle)
// Noisyfox's Writing
// Draw text
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_DrawTextTransformed, argument0, argument1, argument2, _NF_W_CreateArgs(3, argument3, argument4, argument5));


#define fw_draw_text_ext_transformed
// boolean fw_draw_text_ext_transformed(real x, real y, string str, real w, real xscale, real yscale, real angle)
// Noisyfox's Writing
// Draw text
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_DrawTextTransformedExt, argument0, argument1, argument2, _NF_W_CreateArgs(4, argument3, argument4, argument5, argument6));


#define fw_draw_text_color
// boolean fw_draw_text_color(real x, real y, string str, real c1, real c2, real alpha)
// Noisyfox's Writing
// Draw text
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_DrawTextColor, argument0, argument1, argument2, _NF_W_CreateArgs(3, argument3, argument4, argument5));


#define fw_draw_text_ext_color
// boolean fw_draw_text_ext_color(real x, real y, string str, real w, real c1, real c2, real alpha)
// Noisyfox's Writing
// Draw text
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_DrawTextColorExt, argument0, argument1, argument2, _NF_W_CreateArgs(4, argument3, argument4, argument5, argument6));


#define fw_draw_text_transformed_color
// boolean fw_draw_text_transformed_color(real x, real y, string str, real xscale, real yscale, real angle, real c1, real c2, real alpha)
// Noisyfox's Writing
// Draw text
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_DrawTextTransformedColor, argument0, argument1, argument2, _NF_W_CreateArgs(6, argument3, argument4, argument5, argument6, argument7, argument8));


#define fw_draw_text_ext_transformed_color
// boolean fw_draw_text_ext_transformed_color(real x, real y, string str, real w, real xscale, real yscale, real angle, real c1, real c2, real alpha)
// Noisyfox's Writing
// Draw text
// Returns true if success, false otherwise

return external_call(global.__NF_W_ED_DrawTextTransformedColorExt, argument0, argument1, argument2, _NF_W_CreateArgs(7, argument3, argument4, argument5, argument6, argument7, argument8, argument9));


#define _NF_W_CreateArgs
//string _NF_W_CreateArgs(int argCount, arg...)
// Noisyfox's Writing
// Create args for dll call
// DO NOT use it manually!

var count;
var i, first;
var str;

count = argument0;
i = 0;
str = "";
first = true;

for(i = 1; i <= count; i+=1){
    if(!first){
        str = str + ";";
    }
    first = false;
    str = str + string(argument[i]);
}

return str;


