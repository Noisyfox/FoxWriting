#ifdef FOXWRITING_EXPORTS
#define FOXWRITING_API __declspec(dllexport)
#else
#define FOXWRITING_API __declspec(dllimport)
#endif

#ifndef __FOXWRITING_H__
#define __FOXWRITING_H__

typedef struct
{
    gm::GMTEXTURE backupTexture;
    int spriteWidth;
    int spriteHeight;
} SpriteBackup;

typedef struct
{
    gm::ISprite* workingSprite;
    LPDIRECT3DDEVICE8 device;
    int spriteIndex;
    SpriteBackup sprBackup;
} FWorkbench;

extern gm::CGMAPI* gmapi;
extern ULONG_PTR m_gdiplusToken;
extern INT xdpi;
extern INT ydpi;
extern FWorkbench workbench;

extern "C"
{
    // 初始化 FowWriting, sprite 是工作精灵，所有绘制都在该精灵上完成
    FOXWRITING_API DOUBLE FWInit(DOUBLE sprite);
    FOXWRITING_API DOUBLE FWReleaseCache();
    FOXWRITING_API DOUBLE FWCleanup();
    // 设置多线程文字绘制
    FOXWRITING_API DOUBLE FWThreadingConfig(DOUBLE maxThread, DOUBLE linePreThread);
    // 注册字体
    FOXWRITING_API DOUBLE FWAddFont(CONST CHAR* name, DOUBLE pt, DOUBLE style);
    FOXWRITING_API DOUBLE FWAddFontFromFile(CONST CHAR* ttf, DOUBLE pt, DOUBLE style);
    FOXWRITING_API DOUBLE FWDeleteFont(DOUBLE font);
    // 设置字体偏移
    FOXWRITING_API DOUBLE FWSetFontOffset(DOUBLE font, DOUBLE xOffset, DOUBLE yOffset);
    // 设置字体
    FOXWRITING_API DOUBLE FWSetFont(DOUBLE font);
    // 设置对齐方式
    FOXWRITING_API DOUBLE FWSetHAlign(DOUBLE align);
    FOXWRITING_API DOUBLE FWSetVAlign(DOUBLE align);
    // 是否开启整数像素对齐
    FOXWRITING_API DOUBLE FWEnablePixelAlignment(DOUBLE enable);
    // 设置行间距
    FOXWRITING_API DOUBLE FWSetLineSpacing(DOUBLE sep);
    // 计算长宽
    FOXWRITING_API DOUBLE FWStringWidth(CONST CHAR* str);
    FOXWRITING_API DOUBLE FWStringHeight(CONST CHAR* str);
    FOXWRITING_API DOUBLE FWStringWidthEx(CONST CHAR* str, DOUBLE sep, DOUBLE w);
    FOXWRITING_API DOUBLE FWStringHeightEx(CONST CHAR* str, DOUBLE sep, DOUBLE w);
    // 文字绘制
    FOXWRITING_API DOUBLE FWDrawText(DOUBLE x, DOUBLE y, CONST CHAR* str);
    FOXWRITING_API DOUBLE FWDrawTextEx(DOUBLE x, DOUBLE y, CONST CHAR* str, CONST CHAR* args);

    FOXWRITING_API DOUBLE FWDrawTextTransformed(DOUBLE x, DOUBLE y, CONST CHAR* str, CONST CHAR* args);
    FOXWRITING_API DOUBLE FWDrawTextTransformedEx(DOUBLE x, DOUBLE y, CONST CHAR* str, CONST CHAR* args);

    FOXWRITING_API DOUBLE FWDrawTextColor(DOUBLE x, DOUBLE y, CONST CHAR* str, CONST CHAR* args);
    FOXWRITING_API DOUBLE FWDrawTextColorEx(DOUBLE x, DOUBLE y, CONST CHAR* str, CONST CHAR* args);

    FOXWRITING_API DOUBLE FWDrawTextTransformedColor(DOUBLE x, DOUBLE y, CONST CHAR* str, CONST CHAR* args);
    FOXWRITING_API DOUBLE FWDrawTextTransformedColorEx(DOUBLE x, DOUBLE y, CONST CHAR* str, CONST CHAR* args);
};

#endif
