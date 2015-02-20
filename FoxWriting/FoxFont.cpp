#include "stdafx.h"
#include "FoxFont.h"

#include <cmath>

// pt -> px
Gdiplus::REAL Point2Pixel(Gdiplus::REAL pt){
	return pt * xdpi / 72.0f;
}

FoxFont::FoxFont() :mPoint(0.0f,0.0f){
	mFont = NULL;
	mFontCollection = NULL;

	mBitmap4Measure = NULL;
	mBmp4Measure = NULL;
	mGraphics4Measure = NULL;

	mXOffset = 0;
	mYOffset = 0;

	mStringFmt = Gdiplus::StringFormat::GenericTypographic()->Clone();
	mStringFmt->SetAlignment(Gdiplus::StringAlignmentNear);
	mStringFmt->SetLineAlignment(Gdiplus::StringAlignmentNear);

	mFontFamily = NULL;
	mBrush = new Gdiplus::SolidBrush(Gdiplus::Color::White);
	ZeroMemory(mCacheMap, MAP_SIZE * sizeof(PFMapNode));
}

FoxFont::~FoxFont(){
	if (mFont){
		delete mFont;
	}
	if (!mFontCollection && mFontFamily){
		delete mFontFamily; // 这里可能导致内存泄漏
	}
	if (mFontCollection){
		delete mFontCollection;
	}
	if (mStringFmt){
		delete mStringFmt;
	}
	if (mBrush){
		delete mBrush;
	}

	if (mGraphics4Measure){
		delete mGraphics4Measure;
	}
	if (mBmp4Measure){
		delete mBmp4Measure;
	}
	if (mBitmap4Measure){
		delete[] mBitmap4Measure;
	}

	// 释放缓存的texture
	FreeCache();
}

void FoxFont::FreeCache()
{
	// 释放缓存的texture
	for (int i = 0; i < MAP_SIZE; i++){
		PFMapNode node = mCacheMap[i];
		while (node != NULL){
			PFMapNode next = node->next;

			PFontTexture t = node->texture;
			t->texture->Release();
			delete t;
			delete node;
			node = next;
		}
	}
	ZeroMemory(mCacheMap, sizeof(mCacheMap));
}

BOOL FoxFont::SetFont(WCHAR * fontName, DOUBLE size, INT style, const Gdiplus::FontCollection * fontCollection){
	if (mFont){
		return FALSE;
	}

	mSizeInPoint = (Gdiplus::REAL)size;
	mSizeInWorld = Point2Pixel(mSizeInPoint);

	mFont = new Gdiplus::Font(fontName, mSizeInPoint, style, Gdiplus::UnitPoint, fontCollection);
	if (!mFont){
		return FALSE;
	}

	mFontFamily = new Gdiplus::FontFamily();
	if (mFontFamily == NULL){
		return FALSE;
	}

	mFont->GetFamily(mFontFamily);

	int max_size = mSizeInWorld * 4 * 2;

	mBitmap4Measure = new BYTE[max_size * max_size * 4];

	int stride = 4 * max_size;
	mBmp4Measure = new Gdiplus::Bitmap(max_size, max_size, stride, PixelFormat32bppARGB, mBitmap4Measure);
	mGraphics4Measure = new Gdiplus::Graphics(mBmp4Measure);
	mGraphics4Measure->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	mGraphics4Measure->SetTextRenderingHint(mSizeInPoint <= 15 ? Gdiplus::TextRenderingHintClearTypeGridFit : Gdiplus::TextRenderingHintAntiAliasGridFit);
	mGraphics4Measure->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);


	return TRUE;
}

BOOL FoxFont::SetFontFile(WCHAR * ttf, DOUBLE size, INT style){
	if (mFont){
		return FALSE;
	}

	mSizeInPoint = (Gdiplus::REAL)size;
	mSizeInWorld = Point2Pixel(mSizeInPoint);
	
	mFontCollection = new Gdiplus::PrivateFontCollection();

	if (Gdiplus::Ok != mFontCollection->AddFontFile(ttf)){
		return FALSE;
	}

	int count = mFontCollection->GetFamilyCount();

	if (count <= 0){
		return FALSE;
	}

	int found = 0;
	Gdiplus::FontFamily * pFontFamily = new Gdiplus::FontFamily[count];
	if (Gdiplus::Ok != mFontCollection->GetFamilies(count, pFontFamily, &found)){
		delete[] pFontFamily;
		return FALSE;
	}

	WCHAR fontName[1024];

	if (Gdiplus::Ok != pFontFamily[0].GetFamilyName(fontName)){
		delete[] pFontFamily;
		return FALSE;
	}

	delete[] pFontFamily;

	return SetFont(fontName, size, style, mFontCollection);
}

void FoxFont::SetOffset(DOUBLE xOffset, DOUBLE yOffset){
	mXOffset = xOffset;
	mYOffset = yOffset;
}

PFontTexture FoxFont::GetCharTextureCache(WCHAR c){
	UINT16 uc = c;
	int index = uc % 256;
	PFMapNode * node = &(mCacheMap[index]);
	while ((*node) != NULL && (*node)->c != c){
		node = &((*node)->next);
	}
	if ((*node) != NULL){
		return (*node)->texture;
	}

	return NULL;
}

PFontTexture FoxFont::GetCharTexture(WCHAR c){
	// 用当前char的值作为key，查找hashmap
	UINT16 uc = c;
	int index = uc % 256;
	PFMapNode * node = &(mCacheMap[index]);
	while ((*node) != NULL && (*node)->c != c){
		node = &((*node)->next);
	}
	if ((*node) != NULL){ // 缓存存在
		return (*node)->texture;
	}

	PFontTexture t = GenerateCharTexture(c);
	if (t == NULL){
		return NULL;
	}

	// 储存进 hashmap
	*node = new FMapNode();
	ZeroMemory(*node, sizeof(FMapNode));

	(*node)->c = c;
	(*node)->texture = t;

	return (*node)->texture;
}

typedef struct{
	int w, h;
	BYTE * bitmap;
	int count;
}FILLDATA, *PFILLDATA;

VOID Fill(D3DXVECTOR4 *pOut, D3DXVECTOR2 *pTexCoord, D3DXVECTOR2 *pTexelSize, LPVOID pData)
{
	PFILLDATA data = (PFILLDATA)pData;
	int x = (int)(pTexCoord->x * data->w);
	int y = (int)(pTexCoord->y * data->h);
	int index = (y * data->w + x) * 4;

	pOut->z = 1.0f;
	pOut->y = 1.0f;
	pOut->x = 1.0f;
	pOut->w = (data->bitmap[index] + data->bitmap[index + 1] + data->bitmap[index + 2]) / 255.0f / 3;

	data->count++;
}

// 2的指数次幂对齐
int Pad2(int n){
	if (n == 1){
		return 2;
	}

	bool isA = false;
	int s = 0;
	while (n > 1){
		if (n % 1 == 1){
			isA = true;
		}
		s++;
		n >>= 1;
	}
	if (isA){
		s++;
	}
	s++;

	return 1 << s;

}

PFontTexture FoxFont::GenerateCharTexture(const WCHAR c){
	PFontTexture texture = new FontTexture;
	ZeroMemory(texture, sizeof(FontTexture));

	// 先计算文字尺寸
	Gdiplus::RectF stringRect;
	MeasureChar(c, &stringRect);
	
	Gdiplus::REAL x, y, w, h;
	x = stringRect.GetLeft();
	y = stringRect.GetTop();
	w = stringRect.Width * 2;
	h = stringRect.Height * 2;

	texture->imageWidth = ceil(w);
	texture->imageHeight = ceil(h);
	texture->xOffset = -x;
	texture->yOffset = -y;
	texture->textureWidth = texture->imageWidth;
	texture->textureHeight = texture->imageHeight;
	texture->fontWidth = stringRect.Width;
	texture->fontHeight = stringRect.Height;
	texture->fontXOffset = -stringRect.GetLeft();
	texture->fontYOffset = -stringRect.GetTop();

	// 准备bitmap
	size_t size = texture->textureWidth * texture->textureHeight * 4;
	BYTE * bitmap = new BYTE[size];
	if (bitmap == NULL){
		delete texture;
		return NULL;
	}

	CreateTextBitmap(c, texture->textureWidth, texture->textureHeight, texture->xOffset, texture->yOffset, bitmap);

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

	FILLDATA bitmapData = { texture->textureWidth, texture->textureHeight, bitmap, 0 };

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

void FoxFont::CreateTextBitmap(WCHAR c, int width, int height, float xOffset, float yOffset, BYTE* bitmap)
{
	int stride = 4 * width;
	Gdiplus::Bitmap bmp(width, height, stride, PixelFormat32bppARGB, bitmap);
	Gdiplus::Graphics g(&bmp);
	g.Clear(Gdiplus::Color::Black);

	g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	g.SetTextRenderingHint(mSizeInPoint <= 20 ? Gdiplus::TextRenderingHintClearTypeGridFit : Gdiplus::TextRenderingHintAntiAliasGridFit);
	g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);

	//Gdiplus::PointF origin(0, 0);
	//Gdiplus::RectF tmpRect1(0, 0, 60000, 60000);
	//Gdiplus::RectF tmpRect2(0, 0, 60000, 60000);
	//Gdiplus::RectF tmpRect3(0, 0, 60000, 60000);
	//Gdiplus::RectF tmpRect4(0, 0, 60000, 60000);

	//WCHAR ssss[999];
	//wsprintfW(ssss, L"%c", c);
	//MessageBoxW(NULL, ssss, NULL, 0);

	//获得字体高度与宽度measuredSize
	//WCHAR mStr1[] = { L'f', 0, L'f' };
	//WCHAR mStr2[] = { 0, L'f' };
	//mStr1[1] = c;
	//mStr2[0] = c;
	//g.MeasureString(mStr1, 1, mFont, origin, mStringFmt, &tmpRect1);
	//g.MeasureString(mStr1, 3, mFont, origin, mStringFmt, &tmpRect2);

	//Gdiplus::GraphicsPath path1;
	//path1.AddString(mStr2, 2, mFontFamily, mFont->GetStyle(), mSizeInWorld, origin, mStringFmt);
	//path1.GetBounds(&tmpRect3);

	//path1.Reset();
	//path1.AddString(&c, 1, mFontFamily, mFont->GetStyle(), mSizeInWorld, origin, mStringFmt);
	//path1.GetBounds(&tmpRect4);

	//g.MeasureString(&c, 1, mFont, origin, mStringFmt, &tmpRect4);

	//FLOAT w = tmpRect2.Width - tmpRect1.Width * 2;
	//FLOAT xO = w - (tmpRect3.Width - tmpRect1.Width);
	//char sss[999];
	//sprintf_s(sss, "%f-%f=%f", tmpRect2.Width, tmpRect1.Width, w);
	//MessageBoxA(NULL, sss, NULL, 0);

	//measuredSize->X = -tmpRect4.GetLeft();
	//measuredSize->Y = -tmpRect4.GetTop();
	//measuredSize->Width = w;
	//measuredSize->Height = tmpRect2.Height;

	mPoint.X = xOffset;
	mPoint.Y = yOffset;
	g.DrawString(&c, 1, mFont, mPoint, mStringFmt, mBrush);
}

BOOL FoxFont::MeasureChar(WCHAR c, Gdiplus::RectF* bound){
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

	Gdiplus::PointF origin(0, 0);
	Gdiplus::RectF tmpRect1(0, 0, 0, 0);
	Gdiplus::RectF tmpRect2(0, 0, 0, 0);
	Gdiplus::RectF tmpRect3(0, 0, 0, 0);

	WCHAR mStr1[] = { L'f', 0, L'f' };
	mStr1[1] = c;
	mGraphics4Measure->MeasureString(mStr1, 1, mFont, origin, mStringFmt, &tmpRect1);
	mGraphics4Measure->MeasureString(mStr1, 3, mFont, origin, mStringFmt, &tmpRect2);
	//g.MeasureString(&c, 1, mFont, origin, mStringFmt, &tmpRect3);

	Gdiplus::GraphicsPath path1;
	path1.AddString(&c, 1, mFontFamily, mFont->GetStyle(), mSizeInWorld, origin, mStringFmt);
	path1.GetBounds(&tmpRect3);

	FLOAT w = tmpRect2.Width - tmpRect1.Width * 2;
	FLOAT h = tmpRect2.Height;

	bound->Width = w;
	bound->Height = mSizeInWorld;
	bound->X = ceil(tmpRect3.X - w / 5.0f);
	bound->Y = ceil(tmpRect3.Y - h / 5.0f);

	return TRUE;
}
