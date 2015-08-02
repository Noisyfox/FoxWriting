// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "FoxWriting.h"

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        {
            { // 应对 vs2015 内联 sprintf 导致 d3d8.lib 找不到 _sprintf 的问题
                char f__kInline[1];
                sprintf(f__kInline, "");
            }

            // Initializing GMAPI library
            DWORD result = 0;
            gmapi = gm::CGMAPI::Create(&result);

            // Check the initialization
            if (result == gm::GMAPI_INITIALIZATION_FAILED)
            {
                MessageBox(NULL, L"Unable to initialize GMAPI.", NULL, MB_SYSTEMMODAL | MB_ICONERROR);
                return FALSE;
            }

            // 初始化 GDI+
            Gdiplus::GdiplusStartupInput gdiplusStartupInput;
            Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
            // 得到屏幕密度，用来计算 pt <-> px
            HDC dc = GetDC(0);
            xdpi = GetDeviceCaps(dc, LOGPIXELSX);
            ydpi = GetDeviceCaps(dc, LOGPIXELSY);
        }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        // 这里不能shutdown否则游戏会崩溃，原因不明
        //Gdiplus::GdiplusShutdown(m_gdiplusToken);
        break;
    }
    return TRUE;
}

