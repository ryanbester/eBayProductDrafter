#pragma once

#ifndef MAIN_H

#define MAIN_H

void CreateApplicationMenu(HWND hWnd);
void CreateToolbar(HWND hWnd);
void CreateStatusbar(HWND hWnd);

BOOL CALLBACK SetFont(HWND child, LPARAM font);

#endif
