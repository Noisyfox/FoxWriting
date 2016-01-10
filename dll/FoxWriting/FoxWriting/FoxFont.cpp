#include "stdafx.h"
#include "FoxFont.h"

#include <cmath>

// pt -> px
Gdiplus::REAL Point2Pixel(Gdiplus::REAL pt)
{
    return pt * xdpi / 72.0f;
}

FoxFont::FoxFont() :mPoint(0.0f, 0.0f)
{
    mFont = NULL;
    mFontCollection = NULL;

    mBitmap4Measure = NULL;
    mBmp4Measure = NULL;
    mGraphics4Measure = NULL;

    mXOffset = 0;
    mYOffset = 0;

    mStroke = true;

    mStringFmt = Gdiplus::StringFormat::GenericTypographic()->Clone();
    mStringFmt->SetAlignment(Gdiplus::StringAlignmentNear);
    mStringFmt->SetLineAlignment(Gdiplus::StringAlignmentNear);

    mFontFamily = NULL;
    mBrush = new Gdiplus::SolidBrush(Gdiplus::Color::White);
    mStrokeBrush = new Gdiplus::SolidBrush(Gdiplus::Color::Black);

    mDebugPen = new Gdiplus::Pen(Gdiplus::Color::Red);
}

FoxFont::~FoxFont()
{
    if (mFont)
    {
        delete mFont;
    }
    if (!mFontCollection && mFontFamily)
    {
        delete mFontFamily; // 这里可能导致内存泄漏
    }
    if (mFontCollection)
    {
        delete mFontCollection;
    }
    if (mStringFmt)
    {
        delete mStringFmt;
    }
    if (mBrush)
    {
        delete mBrush;
    }
    if (mStrokeBrush)
    {
        delete mStrokeBrush;
    }
    // if (mDebugPen)
    // {
    //     delete mDebugPen;
    // }
    if (mGraphics4Measure)
    {
        delete mGraphics4Measure;
    }
    if (mBmp4Measure)
    {
        delete mBmp4Measure;
    }
    if (mBitmap4Measure)
    {
        delete[] mBitmap4Measure;
    }

    // 释放缓存的texture
    FreeCache();
}

void FoxFont::FreeCache()
{
    // 释放缓存的texture
    std::unordered_map<WCHAR, PFontTexture>::iterator it = mCaches.begin();
    while (it != mCaches.end())
    {
        PFontTexture t = it->second;
        t->texture->Release();
        delete t;

        ++it;
    }

    mCaches.clear();
}

void FoxFont::PreLoad(WCHAR from, WCHAR to)
{
    if(to < from)
    {
        return;
    }

    std::vector<std::pair<uint16_t, uint16_t>>::iterator it;

    for (it = mCharacterRange.begin(); it != mCharacterRange.end(); ++it)
    {
        uint16_t b = it->first;
        uint16_t e = it->second - 1;
        
        if(e < from)
        {
            continue;
        }
        if(b > to)
        {
            break;
        }

        WCHAR s = max(from, b);
        WCHAR f = min(to, e);
        for (WCHAR c = s; c <= f; c++)
        {
            GetCharTexture(c);
        }
    }
}

BOOL FoxFont::SetFont(WCHAR* fontName, DOUBLE size, INT style, const Gdiplus::FontCollection* fontCollection)
{
    if (mFont)
    {
        return FALSE;
    }

    if (style & 0x4)
    {
        mStroke = true;
        style &= ~0x4;
    }
    else
    {
        mStroke = false;
    }

    mSizeInPoint = (Gdiplus::REAL)size;
    mSizeInWorld = Point2Pixel(mSizeInPoint);

    mFont = new Gdiplus::Font(fontName, mSizeInPoint, style, Gdiplus::UnitPoint, fontCollection);
    if (!mFont)
    {
        return FALSE;
    }

    mFontFamily = new Gdiplus::FontFamily();
    if (mFontFamily == NULL)
    {
        return FALSE;
    }

    mFont->GetFamily(mFontFamily);

    int max_size = (int)(mSizeInWorld * 4 * 2);

    mBitmap4Measure = new BYTE[max_size * max_size * 4];

    int stride = 4 * max_size;
    mBmp4Measure = new Gdiplus::Bitmap(max_size, max_size, stride, PixelFormat32bppARGB, mBitmap4Measure);
    mGraphics4Measure = new Gdiplus::Graphics(mBmp4Measure);
    mGraphics4Measure->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
    mGraphics4Measure->SetTextRenderingHint(mSizeInPoint <= 15 ? Gdiplus::TextRenderingHintClearTypeGridFit : Gdiplus::TextRenderingHintAntiAliasGridFit);
    mGraphics4Measure->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);

    { // 创建 unicode 范围向量
        HDC hdc = ::CreateCompatibleDC(NULL);
        Gdiplus::Graphics graphics(hdc);
        LOGFONTW logFont;
        mFont->GetLogFontW(&graphics, &logFont);
        HFONT hFont = ::CreateFontIndirectW(&logFont);
        //if (!hFont) return false;
        ::SelectObject(hdc, hFont);

        DWORD glyphSize = ::GetFontUnicodeRanges(hdc, NULL);

        std::vector<char> buffer(glyphSize);
        GLYPHSET *gs = (GLYPHSET*)(&buffer[0]);
        ::GetFontUnicodeRanges(hdc, gs);
        for (DWORD r = 0; r < gs->cRanges; ++r) {
            mCharacterRange.push_back(std::make_pair(gs->ranges[r].wcLow, gs->ranges[r].wcLow + gs->ranges[r].cGlyphs));
        }

        DeleteObject(hFont);
        ReleaseDC(NULL, hdc);
    }

    return TRUE;
}

BOOL FoxFont::SetFontFile(WCHAR* ttf, DOUBLE size, INT style)
{
    if (mFont)
    {
        return FALSE;
    }

    mSizeInPoint = (Gdiplus::REAL)size;
    mSizeInWorld = Point2Pixel(mSizeInPoint);

    mFontCollection = new Gdiplus::PrivateFontCollection();

    if (Gdiplus::Ok != mFontCollection->AddFontFile(ttf))
    {
        return FALSE;
    }

    int count = mFontCollection->GetFamilyCount();

    if (count <= 0)
    {
        return FALSE;
    }

    int found = 0;
    Gdiplus::FontFamily* pFontFamily = new Gdiplus::FontFamily[count];
    if (Gdiplus::Ok != mFontCollection->GetFamilies(count, pFontFamily, &found))
    {
        delete[] pFontFamily;
        return FALSE;
    }

    WCHAR fontName[1024];

    if (Gdiplus::Ok != pFontFamily[0].GetFamilyName(fontName))
    {
        delete[] pFontFamily;
        return FALSE;
    }

    delete[] pFontFamily;

    return SetFont(fontName, size, style, mFontCollection);
}

void FoxFont::SetOffset(DOUBLE xOffset, DOUBLE yOffset)
{
    mXOffset = xOffset;
    mYOffset = yOffset;
}

PFontTexture FoxFont::GetCharTexture(WCHAR c)
{
    std::unordered_map<WCHAR, PFontTexture>::iterator it = mCaches.find(c);
    if(it == mCaches.end())
    {
        PFontTexture t = GenerateCharTexture(c);
        if (t == NULL)
        {
            return NULL;
        }
        mCaches.insert(std::unordered_map<WCHAR, PFontTexture>::value_type(c, t));

        return t;
    }

    return it->second;
}

typedef struct
{
    bool stroke;
    int w, h;
    BYTE* bitmap;
    int count;
} FILLDATA, *PFILLDATA;

VOID Fill(D3DXVECTOR4* pOut, D3DXVECTOR2* pTexCoord, D3DXVECTOR2* pTexelSize, LPVOID pData)
{
    PFILLDATA data = (PFILLDATA)pData;
    int x = (int)(pTexCoord->x * data->w);
    int y = (int)(pTexCoord->y * data->h);
    int index = (y * data->w + x) * 4;

    if (data->stroke)
    {
        pOut->z = data->bitmap[index + 2] / 255.0f;
        pOut->y = data->bitmap[index + 1] / 255.0f;
        pOut->x = data->bitmap[index] / 255.0f;
        pOut->w = data->bitmap[index + 3] / 255.0f;
    }
    else
    {
        pOut->z = 1.0f;
        pOut->y = 1.0f;
        pOut->x = 1.0f;
        pOut->w = (data->bitmap[index] + data->bitmap[index + 1] + data->bitmap[index + 2]) / 255.0f / 3;
    }

    data->count++;
}

// 2的指数次幂对齐
int Pad2(int n)
{
    if (n == 1)
    {
        return 2;
    }

    bool isA = false;
    int s = 0;
    while (n > 1)
    {
        if (n % 1 == 1)
        {
            isA = true;
        }
        s++;
        n >>= 1;
    }
    if (isA)
    {
        s++;
    }
    s++;

    return 1 << s;
}

PFontTexture FoxFont::GenerateCharTexture(const WCHAR c)
{
    PFontTexture texture = new FontTexture;
    ZeroMemory(texture, sizeof(FontTexture));

    // 先计算文字尺寸
    Gdiplus::RectF stringRect;
    MeasureChar(c, &stringRect);

    Gdiplus::REAL x, y, w, h;
    x = stringRect.GetLeft() - 2;
    y = stringRect.GetTop() - 2;
    w = stringRect.Width + 4;
    h = stringRect.Height + 4;

    if (mStroke)
    {
        w += 2;
        h += 2;
        x -= 1;
        y -= 1;
    }

    texture->imageWidth = (int)ceil(w);
    texture->imageHeight = (int)ceil(h);
    texture->xOffset = -x;
    texture->yOffset = -y;
    texture->textureWidth = texture->imageWidth;
    texture->textureHeight = texture->imageHeight;
    texture->fontWidth = stringRect.Width;
    texture->fontHeight = stringRect.Height;
    texture->fontXOffset = -stringRect.GetLeft();
    texture->fontYOffset = -stringRect.GetTop();

    // 准备bitmap
    int size = texture->textureWidth * texture->textureHeight * 4;
    if(size <= 0)
    {
        delete texture;
        return NULL;
    }

    BYTE* bitmap = new BYTE[size];
    if (bitmap == NULL)
    {
        delete texture;
        return NULL;
    }

    CreateTextBitmap(c, texture->textureWidth, texture->textureHeight, texture->xOffset, texture->yOffset, mStroke, bitmap);

    // 创建 Texture
    LPDIRECT3DTEXTURE8 t;
    HRESULT rlt = D3DXCreateTexture(workbench.device, texture->textureWidth, texture->textureHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
                                    D3DPOOL_DEFAULT, &t);
    if (rlt != D3D_OK)
    {
        delete[] bitmap;
        delete texture;
        return NULL;
    }

    texture->texture = t;

    FILLDATA bitmapData = {mStroke , texture->textureWidth, texture->textureHeight, bitmap, 0};

    // 填充 Texture
    rlt = D3DXFillTexture(texture->texture, Fill, &bitmapData);
    if (rlt != D3D_OK)
    {
        t->Release();
        delete[] bitmap;
        delete texture;
        return NULL;
    }

    delete[] bitmap;

    return texture;
}

void FoxFont::CreateTextBitmap(WCHAR c, int width, int height, float xOffset, float yOffset, bool stroke, BYTE* bitmap)
{
    int stride = 4 * width;
    Gdiplus::Bitmap bmp(width, height, stride, PixelFormat32bppARGB, bitmap);
    Gdiplus::Graphics g(&bmp);

    if (stroke)
    {
        g.Clear(Gdiplus::Color::Transparent);
        // g.DrawRectangle(mDebugPen, 0, 0, width - 1, height - 1);

        g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
        g.SetTextRenderingHint(mSizeInPoint <= 20 ? Gdiplus::TextRenderingHintClearTypeGridFit : Gdiplus::TextRenderingHintAntiAliasGridFit);
        g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);

        {
            int nOffsetX[8] = {1,1,1,0,-1,-1,-1,0};
            int nOffsetY[8] = {-1,0,1,1,1,0,-1,-1};

            for (int i = 0; i < 8; i++)
            {
                mPoint.X = xOffset + nOffsetX[i];
                mPoint.Y = yOffset + nOffsetY[i];
                g.DrawString(&c, 1, mFont, mPoint, mStringFmt, mStrokeBrush);
            }
        }

        mPoint.X = xOffset;
        mPoint.Y = yOffset;
        g.DrawString(&c, 1, mFont, mPoint, mStringFmt, mBrush);
    }
    else
    {
        g.Clear(Gdiplus::Color::Black);
        // g.DrawRectangle(mDebugPen, 0, 0, width - 1, height - 1);

        g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
        g.SetTextRenderingHint(mSizeInPoint <= 20 ? Gdiplus::TextRenderingHintClearTypeGridFit : Gdiplus::TextRenderingHintAntiAliasGridFit);
        g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);

        mPoint.X = xOffset;
        mPoint.Y = yOffset;
        g.DrawString(&c, 1, mFont, mPoint, mStringFmt, mBrush);
    }
}

BOOL FoxFont::MeasureChar(WCHAR c, Gdiplus::RectF* bound)
{
    /*int max_size = mSizeInWorld * 4 * 2;

	BYTE *bitmap = new BYTE[max_size * max_size * 4];

	int stride = 4 * max_size;
	Gdiplus::Bitmap bmp(max_size, max_size, stride, PixelFormat32bppARGB, bitmap);
	Gdiplus::Graphics g(&bmp);
	g.Clear(Gdiplus::Color::Black);

	g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	g.SetTextRenderingHint(mSizeInPoint <= 15 ? Gdiplus::TextRenderingHintClearTypeGridFit : Gdiplus::TextRenderingHintAntiAliasGridFit);
	g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
	*/
    //MessageBox(nullptr, _T("aaa"), nullptr, 0);

    Gdiplus::PointF origin(0, 0);
    Gdiplus::RectF tmpRect1(0, 0, 0, 0);
    Gdiplus::RectF tmpRect2(0, 0, 0, 0);
    Gdiplus::RectF tmpRect3(0, 0, 0, 0);

    WCHAR mStr1[] = {L'f', 0, L'f'};
    mStr1[1] = c;
    mGraphics4Measure->MeasureString(mStr1, 1, mFont, origin, mStringFmt, &tmpRect1);
    mGraphics4Measure->MeasureString(mStr1, 3, mFont, origin, mStringFmt, &tmpRect2);
    //g.MeasureString(&c, 1, mFont, origin, mStringFmt, &tmpRect3);

    Gdiplus::GraphicsPath path1;
    path1.AddString(&c, 1, mFontFamily, mFont->GetStyle(), mSizeInWorld, origin, mStringFmt);
    path1.GetBounds(&tmpRect3);

    FLOAT w = tmpRect2.Width - tmpRect1.Width * 2;
    FLOAT h = tmpRect3.Height;

    // bound->Width = w;
    // bound->Height = h;
    bound->X = ceil(tmpRect3.X / 2);//ceil(tmpRect3.X - w / 5.0f);
    bound->Y = ceil(tmpRect3.Y / 2);//ceil(tmpRect3.Y - h / 5.0f);
    bound->Width = w + bound->X;
    bound->Height = h + bound->Y;

    return TRUE;
}
