#pragma once

#ifndef FORM_H

#define FORM_H

#ifndef _WINDOWS_

#include <Windows.h>

#endif

bool CreateProductForm(HWND hWnd, LPCTSTR title, LPCTSTR con, LPCTSTR conDes, LPCTSTR des, PSTR SKU, LPCTSTR price, LPCTSTR currency);

#endif
