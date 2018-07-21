#include <Windows.h>
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

using namespace std;

const TCHAR szAppName[] = TEXT("eBayProductDrafter");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wcex;

#pragma comment(lib, "comctl32.lib")
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
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
	return 0;
}