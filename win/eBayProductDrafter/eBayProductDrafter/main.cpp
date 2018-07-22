#ifndef _WINDOWS_

#include <Windows.h>

#endif

#include <CommCtrl.h>
#include <strsafe.h>
#include <Shlwapi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <ShlObj.h>
#include <sstream>
#include <vector>
#include <stdio.h>
#include "resource.h"
#include "main.h"
#include "form.h"
#include "record.h"

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK SetFont(HWND child, LPARAM font)
{
	SendMessage(child, WM_SETFONT, font, true);
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wcex;

	INITCOMMONCONTROLSEX icex;

	icex.dwSize = sizeof(icex);
	icex.dwICC = ICC_BAR_CLASSES | ICC_STANDARD_CLASSES | ICC_DATE_CLASSES;
	InitCommonControlsEx(&icex);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
	wcex.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szAppName;
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICONSM));

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, TEXT("Could not register the window class"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return 0;
	}

	hWnd = CreateWindowEx(0, szAppName, TEXT("eBay Product Drafter"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 456, 500, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL) {
		MessageBox(NULL, TEXT("Could not create the window"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		if (!IsDialogMessage(hWnd, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_CREATE:
	{
		CreateApplicationMenu(hWnd);
		CreateToolbar(hWnd);
		CreateStatusbar(hWnd);
		EnumChildWindows(hWnd, (WNDENUMPROC)SetFont, (LPARAM)GetStockObject(DEFAULT_GUI_FONT));
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case IDM_FILE_NEW:
		{
			CreateProductForm(hWnd, NULL, NULL, NULL, NULL, NULL, NULL, TEXT("GBP"));
			break;
		}
		}
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
	return 0;
}

void CreateApplicationMenu(HWND hWnd) {
	hMenu = CreateMenu();

	hSubMenu = CreatePopupMenu();
	AppendMenu(hSubMenu, MF_STRING, IDM_FILE_NEW, TEXT("New\tCtrl+T"));
	AppendMenu(hSubMenu, MF_STRING, IDM_FILE_OPEN_REC, TEXT("Open Record\tCtrl+O"));
	AppendMenu(hSubMenu, MF_STRING, IDM_FILE_OPEN_REC_FILE, TEXT("Open Record File\tCtrl+Shift+O"));
	AppendMenu(hSubMenu, MF_STRING | MF_DISABLED, IDM_FILE_CLOSE, TEXT("Close\tCtrl+W"));
	AppendMenu(hSubMenu, MF_STRING | MF_DISABLED, IDM_FILE_SAVE, TEXT("Save\tCtrl+S"));
	AppendMenu(hSubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hSubMenu, MF_STRING, IDM_FILE_EXPORT, TEXT("Export..."));
	AppendMenu(hSubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hSubMenu, MF_STRING, IDM_FILE_EXIT, TEXT("Exit\tAlt+F4"));
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, TEXT("File"));

	hSubMenu = CreatePopupMenu();
	AppendMenu(hSubMenu, MF_STRING | MF_DISABLED, IDM_EDIT_UNDO, TEXT("Undo\tCtrl+Z"));
	AppendMenu(hSubMenu, MF_STRING | MF_DISABLED, IDM_EDIT_REDO, TEXT("Redo\tCtrl+Y"));
	AppendMenu(hSubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hSubMenu, MF_STRING | MF_DISABLED, IDM_EDIT_CUT, TEXT("Cut\tCtrl+X"));
	AppendMenu(hSubMenu, MF_STRING | MF_DISABLED, IDM_EDIT_COPY, TEXT("Copy\tCtrl+C"));
	AppendMenu(hSubMenu, MF_STRING | MF_DISABLED, IDM_EDIT_PASTE, TEXT("Paste\tCtrl+V"));
	AppendMenu(hSubMenu, MF_STRING | MF_DISABLED, IDM_EDIT_DELETE, TEXT("Delete\tDel"));
	AppendMenu(hSubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hSubMenu, MF_STRING | MF_DISABLED, IDM_EDIT_SELECTALL, TEXT("Select All\tCtrl+A"));
	AppendMenu(hSubMenu, MF_STRING | MF_DISABLED, IDM_EDIT_FIND, TEXT("Find and Replace\tCtrl+F"));
	AppendMenu(hSubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hSubMenu, MF_STRING, IDM_EDIT_PREF, TEXT("Preferences..."));
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, TEXT("Edit"));

	hSubMenu = CreatePopupMenu();
	AppendMenu(hSubMenu, MF_STRING | MF_DISABLED, IDM_REC_COPY, TEXT("Copy"));
	AppendMenu(hSubMenu, MF_STRING | MF_DISABLED, IDM_REC_DEL, TEXT("Delete"));
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, TEXT("Record"));

	hSubMenu = CreatePopupMenu();
	AppendMenu(hSubMenu, MF_STRING, IDM_HELP_HELP, TEXT("Help\tF1"));
	AppendMenu(hSubMenu, MF_STRING, IDM_HELP_ABOUT, TEXT("About"));
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, TEXT("Help"));

	SetMenu(hWnd, hMenu);
}

void CreateToolbar(HWND hWnd)
{
	hToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_MAIN_TOOL, GetModuleHandle(NULL), NULL);
	
	SendMessage(hToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

	TBBUTTON tbb[8];
	TBADDBITMAP tbab;

	tbab.hInst = HINST_COMMCTRL;
	tbab.nID = IDB_STD_SMALL_COLOR;

	SendMessage(hToolbar, TB_ADDBITMAP, 0, LPARAM(&tbab));

	ZeroMemory(tbb, sizeof(tbb));

	tbb[0].iBitmap = STD_FILENEW;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = IDM_FILE_NEW;

	tbb[1].iBitmap = STD_FILEOPEN;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = IDM_FILE_OPEN_REC;

	tbb[2].iBitmap = STD_FILESAVE;
	tbb[2].fsState = TBSTATE_INDETERMINATE;
	tbb[2].fsStyle = TBSTYLE_BUTTON;
	tbb[2].idCommand = IDM_FILE_SAVE;

	tbb[3].iBitmap = NULL;
	tbb[3].fsState = NULL;
	tbb[3].fsStyle = TBSTYLE_SEP;
	tbb[3].idCommand = NULL;

	tbb[4].iBitmap = STD_CUT;
	tbb[4].fsState = TBSTATE_ENABLED | TBSTATE_INDETERMINATE;
	tbb[4].fsStyle = TBSTYLE_BUTTON;
	tbb[4].idCommand = IDM_EDIT_CUT;

	tbb[5].iBitmap = STD_COPY;
	tbb[5].fsState = TBSTATE_ENABLED | TBSTATE_INDETERMINATE;
	tbb[5].fsStyle = TBSTYLE_BUTTON;
	tbb[5].idCommand = IDM_EDIT_COPY;

	tbb[6].iBitmap = STD_PASTE;
	tbb[6].fsState = TBSTATE_ENABLED | TBSTATE_INDETERMINATE;
	tbb[6].fsStyle = TBSTYLE_BUTTON;
	tbb[6].idCommand = IDM_EDIT_PASTE;

	tbb[7].iBitmap = STD_DELETE;
	tbb[7].fsState = TBSTATE_ENABLED | TBSTATE_INDETERMINATE;
	tbb[7].fsStyle = TBSTYLE_BUTTON;
	tbb[7].idCommand = IDM_EDIT_DELETE;

	SendMessage(hToolbar, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);
}

void CreateStatusbar(HWND hWnd)
{
	hStatusbar = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);
}