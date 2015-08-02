/*
	一个用来从把字符串分割成DOUBLE[]的辅助函数
	解析分号分割的参数串
*/

#ifndef __FOXARGS_H__
#define __FOXARGS_H__

#include "stdafx.h"
#include <cstring>

template <int _Size>
int ParseArgs(CONST CHAR* args, DOUBLE (&dst)[_Size])
{
    int len = strlen(args);
    int index = 0;

    char* str = new char[len + 2];
    if (str == NULL)
    {
        return 0;
    }

    strncpy_s(str, (len + 2) * sizeof(char), args, len);
    str[len] = ';';
    str[len + 1] = '\0';

    len++;

    char* strP = str;
    for (int i = 0; i < len && index < _Size; i++)
    {
        if (str[i] == ';')
        {
            str[i] = '\0';
            double v = atof(strP);
            strP = &str[i + 1];
            dst[index] = v;
            index++;
        }
    }

    delete[] str;

    return index;
}

#endif
