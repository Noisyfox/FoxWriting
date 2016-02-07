/*
	一个用来从把字符串分割成DOUBLE[]的辅助函数
	解析分号分割的参数串
*/

#ifndef __FOXARGS_H__
#define __FOXARGS_H__

extern int g_iArgListIndex;

template <int _Size>
int ParseArgs(DOUBLE (&dst)[_Size])
{
    int list = g_iArgListIndex;
    int count = gm::ds_list_size(list);

    int max_count = min(_Size, count);

    int i = 0;
    for (; i < max_count; i++)
    {
        auto value = gm::ds_list_find_value(list, i);
        if(value.IsString())
        {
            break;
        }
        dst[i] = value.real();
    }

    return i;
}

#endif
