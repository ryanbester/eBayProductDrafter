#pragma once

#ifndef MAIN_H

#define MAIN_H

#ifndef FORM_H

HWND hToolbar, hStatusbar;
HMENU hMenu, hSubMenu;

bool isCreatingProduct = false;

#endif

void CreateApplicationMenu(HWND hWnd);
void CreateToolbar(HWND hWnd);
void CreateStatusbar(HWND hWnd);

BOOL CALLBACK SetFont(HWND child, LPARAM font);

#endif
