// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>


// TODO:  在此处引用程序需要的其他头文件

#define _USE_MATH_DEFINES
#define GMAPI_USE_D3D
#include "Gmapi.h"
#include <WTypes.h>

#include <GdiPlus.h>
//using namespace Gdiplus;
#pragma comment(lib, "Gdiplus")
