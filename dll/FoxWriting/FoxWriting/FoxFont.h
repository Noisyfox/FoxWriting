/*
	字体类，储存了一个字体对应的配置以及贴图缓存
*/

#ifndef __FOXFONT_H__
#define __FOXFONT_H__
#include "stdafx.h"
#include <atlbase.h>
#include "FoxWriting.h"
#include <vector>
#include <unordered_map>

#include <d3d8.h>
#pragma comment (lib, "d3d8.lib")
#include <d3dx8.h>
#pragma comment (lib, "d3dx8.lib")

Gdiplus::REAL Point2Pixel(Gdiplus::REAL pt);

typedef struct
{
    IDirect3DTexture8* texture;

    INT imageWidth;
    INT imageHeight;

    INT textureWidth;
    INT textureHeight;

    FLOAT xOffset;
    FLOAT yOffset;

    FLOAT fontWidth;
    FLOAT fontHeight;

    FLOAT fontXOffset;
    FLOAT fontYOffset;
} FontTexture, *PFontTexture;

class FoxFont
{
private:
    Gdiplus::PrivateFontCollection* mFontCollection;
    Gdiplus::Font* mFont;
    Gdiplus::StringFormat* mStringFmt;
    Gdiplus::FontFamily* mFontFamily;
    Gdiplus::SolidBrush* mBrush;
    Gdiplus::SolidBrush* mStrokeBrush;
    Gdiplus::PointF mPoint;
    // Gdiplus::Pen* mDebugPen;

    BYTE* mBitmap4Measure;
    Gdiplus::Bitmap* mBmp4Measure;
    Gdiplus::Graphics* mGraphics4Measure;

    std::unordered_map<WCHAR, PFontTexture> mCaches;
    std::vector<std::pair<uint16_t, uint16_t>> mCharacterRange;

    PFontTexture GenerateCharTexture(WCHAR c);
    void CreateTextBitmap(WCHAR c, int width, int height, float xOffset, float yOffset, bool stroke, BYTE* bitmap);

public:
    FoxFont();
    ~FoxFont();

    Gdiplus::REAL mSizeInPoint; // 字号 pt
    Gdiplus::REAL mSizeInWorld; // 字号 px

    // 字体偏移
    DOUBLE mXOffset;
    DOUBLE mYOffset;

    bool mStroke;

    // 用一个字体和相应参数初始化该字体类
    BOOL SetFont(WCHAR* fontName, DOUBLE size, INT style, const Gdiplus::FontCollection* fontCollection = NULL);
    BOOL SetFontFile(WCHAR* ttf, DOUBLE size, INT style);

    PFontTexture GetCharTexture(WCHAR c);

    // 计算单个字符的尺寸
    BOOL MeasureChar(WCHAR c, Gdiplus::RectF* bound);

    void SetOffset(DOUBLE xOffset, DOUBLE yOffset);

    void FreeCache();

    void PreLoad(WCHAR from, WCHAR to);
};

#endif