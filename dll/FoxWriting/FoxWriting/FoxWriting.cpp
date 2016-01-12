// FoxWriting.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "FoxWriting.h"
#include "FoxFont.h"
#include "FoxArgs.h"
#include "CodePage.h"
#include <cmath>
#include <unordered_map>

#include <d3d8.h>
#pragma comment (lib, "d3d8.lib")

// 默认行间距
#define DEFAULT_SEP 0

gm::CGMAPI* gmapi;
FWorkbench workbench;
ULONG_PTR m_gdiplusToken;
INT xdpi, ydpi;
BOOL pixelAlign = FALSE;
INT valign, halign;
FoxFont* currentFont = NULL;
int fontCount = 0;
std::unordered_map<int, FoxFont*> fontMap;
float lineSpacing = DEFAULT_SEP;
UINT currentCodePage = CP_ACP;

int iEncodeBufferSize = 0;
LPWSTR strEncodeBuffer = nullptr;


inline LPCWSTR MultibyteToWildChar(LPCSTR input)
{
    //计算字符串 string 转成 wchar_t 之后占用的内存字节数
    int nBufSize = MultiByteToWideChar(currentCodePage, 0, input, -1, nullptr, 0);

    if(nBufSize <= 0)
    {
        return nullptr;
    }

    if (iEncodeBufferSize < nBufSize)
    {
        if (strEncodeBuffer)
        {
            delete[] strEncodeBuffer;
            strEncodeBuffer = nullptr;
        }
        strEncodeBuffer = new WCHAR[nBufSize];
        if (strEncodeBuffer)
        {
            iEncodeBufferSize = nBufSize;
        }
        else
        {
            iEncodeBufferSize = 0;
            return nullptr;
        }
    }

    //转化为 unicode 的 WideString
    int nSize = MultiByteToWideChar(currentCodePage, 0, input, -1, strEncodeBuffer, nBufSize);

    return nSize > 0 ? strEncodeBuffer : nullptr;
}

void SetSprite(PFontTexture t)
{
    gm::PGMTEXTURE texture = &gmapi->GetTextureArray()[workbench.workingSprite->Subimages[0].GetTextureID()];
    texture->texture = t->texture;
    texture->imageHeight = t->imageHeight;
    texture->imageWidth = t->imageWidth;
    texture->textureHeight = t->textureHeight;
    texture->textureWidth = t->textureWidth;
    texture->isValid = 1;

    if (gm::CGlobals::UseNewStructs())
    {
        gm::PGMBITMAP_NEW b = &workbench.workingSprite->GetPtr()->structNew.bitmaps[0]->structNew;
        b->width = t->imageWidth;
        b->height = t->imageHeight;
    }
    else
    {
        gm::PGMSPRITE_OLD b = &workbench.workingSprite->GetPtr()->structOld;
        b->width = t->imageWidth;
        b->height = t->imageHeight;
    }
}

void MeasureString(LPCWSTR str, Gdiplus::SizeF* size, DOUBLE sep = DEFAULT_SEP)
{
    float w = 0, h = 0;

    float lineHMax = currentFont->mSizeInWorld;
    float lineW = 0;
    int length = wcslen(str);
    bool rBefore = false;

    for (int i = 0; i < length; i++)
    {
        WCHAR c = str[i];
        if (c == L'\r')
        {
            rBefore = true;
            h += lineHMax;
            h += sep;
            w = max(w, lineW);
            lineHMax = currentFont->mSizeInWorld;
            lineW = 0;
        }
        else if (c == L'\n')
        {
            if (!rBefore)
            {
                h += lineHMax;
                h += sep;
                w = max(w, lineW);
                lineHMax = currentFont->mSizeInWorld;
                lineW = 0;
            }
            rBefore = false;
        }
        else
        {
            rBefore = false;
            PFontTexture t = currentFont->GetCharTexture(c);
            if (t != NULL)
            {
                lineW += t->fontWidth;
                lineHMax = max(lineHMax, t->fontHeight);
            }
        }
    }
    h += lineHMax;
    w = max(w, lineW);

    size->Width = w;
    size->Height = h;
}

void MeasureString(LPCWSTR str, Gdiplus::SizeF* size, DOUBLE sep, DOUBLE w)
{
    if (sep == -1)
    {
        sep = DEFAULT_SEP;
    }
    if (w <= 0)
    {
        MeasureString(str, size, sep);
        return;
    }

    float width = 0, height = 0;

    int length = wcslen(str);

    float currentLineWidth = 0;
    float lineHMax = currentFont->mSizeInWorld;
    bool rBefore = false;

    for (int i = 0; i < length; i++)
    {
        WCHAR c = str[i];
        if (c == L'\r')
        {
            rBefore = true;
            width = max(width, currentLineWidth);
            height += sep;
            height += lineHMax;

            lineHMax = currentFont->mSizeInWorld;
            currentLineWidth = 0;
        }
        else if (c == L'\n')
        {
            if (!rBefore)
            {
                width = max(width, currentLineWidth);
                height += sep;
                height += lineHMax;

                lineHMax = currentFont->mSizeInWorld;
                currentLineWidth = 0;
            }
            rBefore = false;
        }
        else
        {
            rBefore = false;
            PFontTexture t = currentFont->GetCharTexture(c);
            if (t != NULL)
            {
                float newWidth = currentLineWidth + t->fontWidth;
                if (newWidth > w)
                { // 换行
                    width = max(width, currentLineWidth);
                    height += sep;
                    height += lineHMax;

                    lineHMax = max(currentFont->mSizeInWorld, t->fontHeight);
                    currentLineWidth = t->fontWidth;
                }
                else
                {
                    currentLineWidth = newWidth;
                    lineHMax = max(lineHMax, t->fontHeight);
                }
            }
        }
    }
    width = max(width, currentLineWidth);
    height += lineHMax;

    size->Width = width;
    size->Height = height;
}

FLOAT DrawLine(LPCWSTR str, int start, int end, DOUBLE xOrig, DOUBLE yOrig, DOUBLE x, DOUBLE y, DOUBLE xscale, DOUBLE yscale, DOUBLE angle, DOUBLE alpha, FLOAT measuredWidth, int color1, int color2)
{
    float lineHeight = currentFont->mSizeInWorld;

    if (halign == gm::fa_center)
    {
        x -= measuredWidth / 2;
    }
    else if (halign == gm::fa_right)
    {
        x -= measuredWidth;
    }

    for (int i = start; i < end; i++)
    {
        PFontTexture t = currentFont->GetCharTexture(str[i]);
        if (t != NULL)
        {
            SetSprite(t);
            double xOffset = x - xOrig - t->fontXOffset + currentFont->mXOffset;
            double yOffset = y - yOrig - t->fontYOffset + currentFont->mYOffset;
            double rotInRad = angle / 360.0 * M_PI * 2;

            double x0 = xOffset * xscale;
            double y0 = yOffset * yscale;
            xOffset = x0 * cos(rotInRad) + y0 * sin(rotInRad);
            yOffset = x0 * sin(rotInRad) - y0 * cos(rotInRad);
            yOffset = -yOffset;
            //xOffset = -xOffset;
            //gm::sprite_set_offset(workbench.spriteIndex, xOffset, yOffset);
            if (pixelAlign)
            {
                gm::draw_sprite_general(workbench.spriteIndex, 0, 0, 0, t->imageWidth, t->imageHeight, round(xOrig + xOffset), round(yOrig + yOffset), xscale, yscale, angle, color1, color1, color2, color2, alpha);
            }
            else
            {
                gm::draw_sprite_general(workbench.spriteIndex, 0, 0, 0, t->imageWidth, t->imageHeight, xOrig + xOffset, yOrig + yOffset, xscale, yscale, angle, color1, color1, color2, color2, alpha);
            }
            x += t->fontWidth;
            lineHeight = max(lineHeight, t->fontHeight);
        }
    }

    return lineHeight;
}

inline DOUBLE DrawTextInner(DOUBLE x, DOUBLE y, LPCSTR str, DOUBLE w, DOUBLE xscale, DOUBLE yscale, DOUBLE angle, DOUBLE alpha, int color1, int color2)
{
    DOUBLE xOrig = x;
    DOUBLE yOrig = y;

    LPCWSTR pStr = MultibyteToWildChar(str);
    if (!pStr)
    {
        return FALSE;
    }

    Gdiplus::SizeF size;
    MeasureString(pStr, &size, lineSpacing, w);

    if (valign == gm::fa_middle)
    {
        y -= size.Height / 2;
    }
    else if (valign == gm::fa_bottom)
    {
        y -= size.Height;
    }

    //int color = gm::draw_get_color();

    int length = wcslen(pStr);

    int i = 0;
    int lineStart = 0;
    float lineWidth = 0;
    bool rBefore = false;
    while (i < length)
    {
        WCHAR c = pStr[i];
        if (c == L'\r')
        {
            y += DrawLine(pStr, lineStart, i, xOrig, yOrig, x, y, xscale, yscale, angle, alpha, lineWidth, color1, color2);
            y += lineSpacing;
            i++;
            lineStart = i;
            lineWidth = 0;
            rBefore = true;
        }
        else if (c == L'\n')
        {
            if (!rBefore)
            {
                y += DrawLine(pStr, lineStart, i, xOrig, yOrig, x, y, xscale, yscale, angle, alpha, lineWidth, color1, color2);
                y += lineSpacing;
            }
            i++;
            lineStart = i;
            lineWidth = 0;
            rBefore = false;
        }
        else
        {
            rBefore = false;
            PFontTexture t = currentFont->GetCharTexture(c);
            if (t != NULL)
            {
                float newWidth = lineWidth + t->fontWidth;
                if (w > 0 && newWidth > w)
                {
                    y += DrawLine(pStr, lineStart, i, xOrig, yOrig, x, y, xscale, yscale, angle, alpha, lineWidth, color1, color2);
                    y += lineSpacing;
                    lineStart = i;
                    lineWidth = 0;
                }
                else
                {
                    lineWidth = newWidth;
                    i++;
                }
            }
        }
    }

    if (i != lineStart)
    {
        DrawLine(pStr, lineStart, i, xOrig, yOrig, x, y, xscale, yscale, angle, alpha, lineWidth, color1, color2);
    }

    return TRUE;
}

void Restore()
{
    SpriteBackup* bkp = &workbench.sprBackup;
    gm::PGMTEXTURE texture = &gmapi->GetTextureArray()[workbench.workingSprite->Subimages[0].GetTextureID()];
    texture->texture = bkp->backupTexture.texture;
    texture->imageHeight = bkp->backupTexture.imageHeight;
    texture->imageWidth = bkp->backupTexture.imageWidth;
    texture->textureHeight = bkp->backupTexture.textureHeight;
    texture->textureWidth = bkp->backupTexture.textureWidth;
    texture->isValid = bkp->backupTexture.isValid;

    if (gm::CGlobals::UseNewStructs())
    {
        gm::PGMBITMAP_NEW b = &workbench.workingSprite->GetPtr()->structNew.bitmaps[0]->structNew;
        b->width = bkp->spriteWidth;
        b->height = bkp->spriteHeight;
    }
    else
    {
        gm::PGMSPRITE_OLD b = &workbench.workingSprite->GetPtr()->structOld;
        b->width = bkp->spriteWidth;
        b->height = bkp->spriteHeight;
    }
}

DOUBLE FWInit(DOUBLE sprite)
{
    int _spr = (int)sprite;
    if (!gmapi->Sprites.Exists(_spr))return FALSE;

    int imageCount = gmapi->Sprites[_spr].Subimages.GetCount();
    if (imageCount <= 0)return FALSE;

    workbench.spriteIndex = _spr;
    workbench.workingSprite = &gmapi->Sprites[_spr];

    // sprite backup doing here
    gm::PGMTEXTURE texture = &gmapi->GetTextureArray()[gmapi->Sprites[_spr].Subimages[0].GetTextureID()];
    memcpy(&workbench.sprBackup.backupTexture, texture, sizeof(gm::GMTEXTURE));
    if (gm::CGlobals::UseNewStructs())
    {
        gm::PGMBITMAP_NEW b = &workbench.workingSprite->GetPtr()->structNew.bitmaps[0]->structNew;
        workbench.sprBackup.spriteWidth = b->width;
        workbench.sprBackup.spriteHeight = b->height;
    }
    else
    {
        gm::PGMSPRITE_OLD b = &workbench.workingSprite->GetPtr()->structOld;
        workbench.sprBackup.spriteWidth = b->width;
        workbench.sprBackup.spriteHeight = b->height;
    }

    HRESULT rlt = texture->texture->GetDevice(&workbench.device);
    if (rlt != D3D_OK)
    {
        return FALSE;
    }

    pixelAlign = FALSE;
    halign = gm::fa_left;
    valign = gm::fa_top;

    return TRUE;
}

DOUBLE FWReleaseCache()
{
    Restore();
    // release all texture
    std::unordered_map<int, FoxFont*>::iterator it = fontMap.begin();
    while (it != fontMap.end())
    {
        FoxFont* f = it->second;
        f->FreeCache();

        ++it;
    }
    return TRUE;
}

DOUBLE FWCleanup()
{
    Restore();
    currentFont = NULL;

    // cleanup all fonts
    std::unordered_map<int, FoxFont*>::iterator it = fontMap.begin();
    while (it != fontMap.end())
    {
        FoxFont* f = it->second;
        delete f;

        ++it;
    }
    fontMap.clear();

    if (strEncodeBuffer)
    {
        delete[] strEncodeBuffer;
        strEncodeBuffer = nullptr;
        iEncodeBufferSize = 0;
    }

    return TRUE;
}

inline DOUBLE SetEncoding(UINT codePage)
{
    if (codePage != 0 && IsValidCodePage(codePage) == 0)
    {
        return FALSE;
    }

    currentCodePage = codePage;
    return TRUE;
}

DOUBLE FWSetEncoding(LPCSTR CPName)
{
    PCodePage cp = g_pCodePages;
    while(cp->code_page != 0)
    {
        if(strcmp(CPName, cp->name) == 0)
        {
            return SetEncoding(cp->code_page);
        }
        cp++;
    }
    return FALSE;
}

DOUBLE FWSetEncodingEx(DOUBLE codePage)
{
    UINT CP = (UINT)codePage;

    return SetEncoding(CP);
}

DOUBLE FWSetHAlign(DOUBLE align)
{
    halign = (int)align;
    return TRUE;
}

DOUBLE FWSetVAlign(DOUBLE align)
{
    valign = (int)align;
    return TRUE;
}

DOUBLE FWDrawText(DOUBLE x, DOUBLE y, LPCSTR str)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    int color = gm::draw_get_color();
    double alpha = gm::draw_get_alpha();
    return DrawTextInner(x, y, str, 0, 1, 1, 0, alpha, color, color);
}

DOUBLE FWDrawTextEx(DOUBLE x, DOUBLE y, LPCSTR str, LPCSTR args)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[1];
    if (ParseArgs(args, argsD) < 1)
    {
        return FALSE;
    }

    DOUBLE w = argsD[0];

    int color = gm::draw_get_color();
    double alpha = gm::draw_get_alpha();
    return DrawTextInner(x, y, str, w, 1, 1, 0, alpha, color, color);
}

DOUBLE FWDrawTextTransformed(DOUBLE x, DOUBLE y, LPCSTR str, LPCSTR args)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[3];
    if (ParseArgs(args, argsD) < 3)
    {
        return FALSE;
    }

    DOUBLE xscale = argsD[0];
    DOUBLE yscale = argsD[1];
    DOUBLE angle = argsD[2];

    int color = gm::draw_get_color();
    double alpha = gm::draw_get_alpha();
    return DrawTextInner(x, y, str, 0, xscale, yscale, angle, alpha, color, color);
}

DOUBLE FWDrawTextTransformedEx(DOUBLE x, DOUBLE y, LPCSTR str, LPCSTR args)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[4];
    if (ParseArgs(args, argsD) < 4)
    {
        return FALSE;
    }

    DOUBLE w = argsD[0];
    DOUBLE xscale = argsD[1];
    DOUBLE yscale = argsD[2];
    DOUBLE angle = argsD[3];

    int color = gm::draw_get_color();
    double alpha = gm::draw_get_alpha();
    return DrawTextInner(x, y, str, w, xscale, yscale, angle, alpha, color, color);
}

DOUBLE FWDrawTextColor(DOUBLE x, DOUBLE y, LPCSTR str, LPCSTR args)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[3];
    if (ParseArgs(args, argsD) < 3)
    {
        return FALSE;
    }

    int color1 = (int)argsD[0];
    int color2 = (int)argsD[1];
    DOUBLE alpha = argsD[2];

    return DrawTextInner(x, y, str, 0, 1, 1, 0, alpha, color1, color2);
}

DOUBLE FWDrawTextColorEx(DOUBLE x, DOUBLE y, LPCSTR str, LPCSTR args)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[4];
    if (ParseArgs(args, argsD) < 4)
    {
        return FALSE;
    }

    DOUBLE w = argsD[0];
    int color1 = (int)argsD[1];
    int color2 = (int)argsD[2];
    DOUBLE alpha = argsD[3];

    return DrawTextInner(x, y, str, w, 1, 1, 0, alpha, color1, color2);
}

DOUBLE FWDrawTextTransformedColor(DOUBLE x, DOUBLE y, LPCSTR str, LPCSTR args)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[6];
    if (ParseArgs(args, argsD) < 6)
    {
        return FALSE;
    }

    DOUBLE xscale = argsD[0];
    DOUBLE yscale = argsD[1];
    DOUBLE angle = argsD[2];
    int color1 = (int)argsD[3];
    int color2 = (int)argsD[4];
    DOUBLE alpha = argsD[5];

    return DrawTextInner(x, y, str, 0, xscale, yscale, angle, alpha, color1, color2);
}

DOUBLE FWDrawTextTransformedColorEx(DOUBLE x, DOUBLE y, LPCSTR str, LPCSTR args)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[7];
    if (ParseArgs(args, argsD) < 7)
    {
        return FALSE;
    }

    DOUBLE w = argsD[0];
    DOUBLE xscale = argsD[1];
    DOUBLE yscale = argsD[2];
    DOUBLE angle = argsD[3];
    int color1 = (int)argsD[4];
    int color2 = (int)argsD[5];
    DOUBLE alpha = argsD[6];

    return DrawTextInner(x, y, str, w, xscale, yscale, angle, alpha, color1, color2);
}

DOUBLE FWAddFont(LPCSTR name, DOUBLE pt, DOUBLE style)
{
    if (pt <= 0)
    {
        return -1;
    }

    LPCWSTR pName = MultibyteToWildChar(name);
    if (!pName)
    {
        return FALSE;
    }

    FoxFont* font = new FoxFont();
    if (!font->SetFont(pName, pt, (int)style))
    {
        delete font;
        return -1;
    }

    int index = fontCount;
    fontCount++;

    fontMap[index] = font;

    return index;
}

DOUBLE FWAddFontFromFile(LPCSTR ttf, DOUBLE pt, DOUBLE style)
{
    if (pt <= 0)
    {
        return -1;
    }

    LPCWSTR pName = MultibyteToWildChar(ttf);
    if (!pName)
    {
        return FALSE;
    }

    FoxFont* font = new FoxFont();
    if (!font->SetFontFile(pName, pt, (int)style))
    {
        delete font;
        return -1;
    }

    int index = fontCount;
    fontCount++;

    fontMap[index] = font;

    return index;
}

DOUBLE FWSetFontOffset(DOUBLE font, DOUBLE xOffset, DOUBLE yOffset)
{
    if (font < 0)
    {
        return FALSE;
    }

    std::unordered_map<int, FoxFont*>::iterator it = fontMap.find((int)font);
    if (it == fontMap.end())
    {
        return FALSE;
    }

    it->second->SetOffset(xOffset, yOffset);

    return TRUE;
}

DOUBLE FWSetFont(DOUBLE font)
{
    if (font < 0)
    {
        return FALSE;
    }

    std::unordered_map<int, FoxFont*>::iterator it = fontMap.find((int)font);
    if (it == fontMap.end())
    {
        return FALSE;
    }

    currentFont = it->second;

    return TRUE;
}

DOUBLE FWDeleteFont(DOUBLE font)
{
    if (font < 0)
    {
        return FALSE;
    }

    std::unordered_map<int, FoxFont*>::iterator it = fontMap.find((int)font);
    if (it == fontMap.end())
    {
        return FALSE;
    }

    FoxFont* f = it->second;
    if(currentFont == f)
    {
        currentFont = NULL;
    }

    delete f;
    fontMap.erase(it);

    return TRUE;
}

DOUBLE FWEnablePixelAlignment(DOUBLE enable)
{
    int en = (int)enable;
    pixelAlign = en;

    return TRUE;
}

DOUBLE FWStringWidth(LPCSTR str)
{
    if (currentFont == NULL)
    {
        return 0;
    }

    LPCWSTR pStr = MultibyteToWildChar(str);
    if (!pStr)
    {
        return 0;
    }

    Gdiplus::SizeF size;
    MeasureString(pStr, &size);

    return size.Width;
}

DOUBLE FWStringHeight(LPCSTR str)
{
    if (currentFont == NULL)
    {
        return 0;
    }

    LPCWSTR pStr = MultibyteToWildChar(str);
    if (!pStr)
    {
        return 0;
    }

    Gdiplus::SizeF size;
    MeasureString(pStr, &size);

    return size.Height;
}

DOUBLE FWStringWidthEx(LPCSTR str, DOUBLE sep, DOUBLE w)
{
    if (currentFont == NULL)
    {
        return 0;
    }

    LPCWSTR pStr = MultibyteToWildChar(str);
    if (!pStr)
    {
        return 0;
    }

    Gdiplus::SizeF size;
    MeasureString(pStr, &size, sep, w);

    return size.Width;
}

DOUBLE FWStringHeightEx(LPCSTR str, DOUBLE sep, DOUBLE w)
{
    if (currentFont == NULL)
    {
        return 0;
    }

    LPCWSTR pStr = MultibyteToWildChar(str);
    if (!pStr)
    {
        return 0;
    }

    Gdiplus::SizeF size;
    MeasureString(pStr, &size, sep, w);

    return size.Height;
}

DOUBLE FWSetLineSpacing(DOUBLE sep)
{
    lineSpacing = sep < 0 ? DEFAULT_SEP : (float)sep;

    return TRUE;
}

DOUBLE FWPreloadFont(DOUBLE font, DOUBLE from, DOUBLE to)
{
    if (font < 0)
    {
        return FALSE;
    }

    std::unordered_map<int, FoxFont*>::iterator it = fontMap.find((int)font);
    if (it == fontMap.end())
    {
        return FALSE;
    }

    it->second->PreLoad((WCHAR)from, (WCHAR)to);

    return TRUE;
}
