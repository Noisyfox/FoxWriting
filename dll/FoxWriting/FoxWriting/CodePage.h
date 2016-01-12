#pragma once


typedef struct
{
    UINT code_page;
    CHAR name[32];
} CodePage, *PCodePage;

extern CodePage g_pCodePages[];
