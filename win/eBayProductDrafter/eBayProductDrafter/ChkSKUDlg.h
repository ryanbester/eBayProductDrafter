#pragma once

#ifndef CHK_SKU_DLG_H

#define CHK_SKU_DLG_H

#ifndef _WINDOWS_

#include <Windows.h>

#endif

BOOL CALLBACK CheckSKUDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif