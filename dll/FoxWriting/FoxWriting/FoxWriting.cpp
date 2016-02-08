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

MeasuredString g_measuredString;


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

inline void AddMeasuredLine(int start, int end, float w, float h)
{
    g_measuredString.lines.push_back(MeasuredLine(start, end, w, h));
}

void MeasureString(LPCWSTR str, DOUBLE sep = DEFAULT_SEP)
{
    float w = 0, h = 0;

    float lineHMax = currentFont->mSizeInWorld;
    float lineW = 0;
    bool rBefore = false;
    int lineStart = 0;
    int i;
    WCHAR c;

    g_measuredString.lines.clear();

    for (i = 0, c = str[0]; c != L'\0'; i++, c = str[i])
    {
        if (c == L'\r')
        {
            rBefore = true;
            h += lineHMax;
            h += sep;
            w = max(w, lineW);
            AddMeasuredLine(lineStart, i, lineW, lineHMax);

            lineHMax = currentFont->mSizeInWorld;
            lineW = 0;
            lineStart = i + 1;
        }
        else if (c == L'\n')
        {
            if (!rBefore)
            {
                h += lineHMax;
                h += sep;
                w = max(w, lineW);
                AddMeasuredLine(lineStart, i, lineW, lineHMax);

                lineHMax = currentFont->mSizeInWorld;
                lineW = 0;
            }
            rBefore = false;
            lineStart = i + 1;
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
    AddMeasuredLine(lineStart, i, lineW, lineHMax);

    g_measuredString.width = w;
    g_measuredString.height = h;
}

void MeasureString(LPCWSTR str, DOUBLE sep, DOUBLE w)
{
    if (sep == -1)
    {
        sep = DEFAULT_SEP;
    }
    if (w <= 0)
    {
        MeasureString(str, sep);
        return;
    }

    float width = 0, height = 0;

    float currentLineWidth = 0;
    float lineHMax = currentFont->mSizeInWorld;
    bool rBefore = false;
    int lineStart = 0;
    int i;
    WCHAR c;

    g_measuredString.lines.clear();

    for (i = 0, c = str[0]; c != L'\0'; i++, c = str[i])
    {
        if (c == L'\r')
        {
            rBefore = true;
            height += lineHMax;
            height += sep;
            width = max(width, currentLineWidth);
            AddMeasuredLine(lineStart, i, currentLineWidth, lineHMax);

            lineHMax = currentFont->mSizeInWorld;
            currentLineWidth = 0;
            lineStart = i + 1;
        }
        else if (c == L'\n')
        {
            if (!rBefore)
            {
                height += sep;
                height += lineHMax;
                width = max(width, currentLineWidth);
                AddMeasuredLine(lineStart, i, currentLineWidth, lineHMax);

                lineHMax = currentFont->mSizeInWorld;
                currentLineWidth = 0;
            }
            rBefore = false;
            lineStart = i + 1;
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
                    height += sep;
                    height += lineHMax;
                    width = max(width, currentLineWidth);
                    AddMeasuredLine(lineStart, i, currentLineWidth, lineHMax);

                    lineHMax = max(currentFont->mSizeInWorld, t->fontHeight);
                    currentLineWidth = t->fontWidth;
                    lineStart = i;
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
    AddMeasuredLine(lineStart, i, currentLineWidth, lineHMax);

    g_measuredString.width = width;
    g_measuredString.height = height;
}

void DrawLine(LPCWSTR str, int start, int end, DOUBLE xOrig, DOUBLE yOrig, DOUBLE x, DOUBLE y, DOUBLE xscale, DOUBLE yscale, DOUBLE angle, DOUBLE alpha, FLOAT measuredWidth, int color1, int color2)
{
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
        if (t)
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
        }
    }
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

    MeasureString(pStr, lineSpacing, w);

    auto& measuredString = g_measuredString;

    if (valign == gm::fa_middle)
    {
        y -= measuredString.height / 2;
    }
    else if (valign == gm::fa_bottom)
    {
        y -= measuredString.width;
    }

    for (auto& l : measuredString.lines)
    {
        int s = l.start;
        int e = l.end;
        if(s != e)
        {
            DrawLine(pStr, s, e, xOrig, yOrig, x, y, xscale, yscale, angle, alpha, l.width, color1, color2);
        }
        y += l.height;
        y += lineSpacing;
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

DOUBLE FWInit(DOUBLE sprite, DOUBLE argList)
{
    int _spr = (int)sprite;
    int _argList = (int)argList;
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

    g_iArgListIndex = _argList;

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

    g_iArgListIndex = 0;

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

DOUBLE FWDrawTextEx(DOUBLE x, DOUBLE y, LPCSTR str)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[1];
    if (ParseArgs(argsD) < 1)
    {
        return FALSE;
    }

    DOUBLE w = argsD[0];

    int color = gm::draw_get_color();
    double alpha = gm::draw_get_alpha();
    return DrawTextInner(x, y, str, w, 1, 1, 0, alpha, color, color);
}

DOUBLE FWDrawTextTransformed(DOUBLE x, DOUBLE y, LPCSTR str)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[3];
    if (ParseArgs(argsD) < 3)
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

DOUBLE FWDrawTextTransformedEx(DOUBLE x, DOUBLE y, LPCSTR str)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[4];
    if (ParseArgs(argsD) < 4)
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

DOUBLE FWDrawTextColor(DOUBLE x, DOUBLE y, LPCSTR str)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[3];
    if (ParseArgs(argsD) < 3)
    {
        return FALSE;
    }

    int color1 = (int)argsD[0];
    int color2 = (int)argsD[1];
    DOUBLE alpha = argsD[2];

    return DrawTextInner(x, y, str, 0, 1, 1, 0, alpha, color1, color2);
}

DOUBLE FWDrawTextColorEx(DOUBLE x, DOUBLE y, LPCSTR str)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[4];
    if (ParseArgs(argsD) < 4)
    {
        return FALSE;
    }

    DOUBLE w = argsD[0];
    int color1 = (int)argsD[1];
    int color2 = (int)argsD[2];
    DOUBLE alpha = argsD[3];

    return DrawTextInner(x, y, str, w, 1, 1, 0, alpha, color1, color2);
}

DOUBLE FWDrawTextTransformedColor(DOUBLE x, DOUBLE y, LPCSTR str)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[6];
    if (ParseArgs(argsD) < 6)
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

DOUBLE FWDrawTextTransformedColorEx(DOUBLE x, DOUBLE y, LPCSTR str)
{
    if (currentFont == NULL)
    {
        return FALSE;
    }

    DOUBLE argsD[7];
    if (ParseArgs(argsD) < 7)
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

    MeasureString(pStr);

    return g_measuredString.width;
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

    MeasureString(pStr);

    return g_measuredString.height;
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

    MeasureString(pStr, sep, w);

    return g_measuredString.width;
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

    MeasureString(pStr, sep, w);

    return g_measuredString.height;
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
