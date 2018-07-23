#include <strsafe.h>

#include "ChkSKUDlg.h"
#include "resource.h"

HWND hChkSKUText, hChkSKUSearchBtn, hChkSKUList, hChkSKULbl;

BOOL CALLBACK CheckSKUDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
	{
		char* SKU[1024];
		GetWindowText(hFormSKU, LPTSTR(SKU), GetWindowTextLength(hFormSKU) + 1);
		hChkSKUText = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), LPTSTR(SKU), WS_VISIBLE | WS_CHILD | WS_TABSTOP, 11, 11, 166, 23, hWnd, (HMENU)IDC_CHK_SKU_TEXT, NULL, NULL);
		hChkSKUSearchBtn = CreateWindowEx(0, TEXT("BUTTON"), TEXT("Search"), WS_VISIBLE | WS_CHILD, 184, 11, 75, 23, hWnd, (HMENU)IDC_CHK_SKU_SEARCH, NULL, NULL);
		hChkSKUList = CreateWindowEx(0, TEXT("LISTBOX"), NULL, WS_VISIBLE | WS_CHILD | LBS_STANDARD, 11, 41, 248, 207, hWnd, NULL, NULL, NULL);
		hChkSKULbl = CreateWindowEx(0, TEXT("STATIC"), TEXT("Enter an SKU into the box above"), WS_VISIBLE | WS_CHILD, 11, 234, 248, 13, hWnd, NULL, NULL, NULL);
		EnableWindow(GetDlgItem(hWnd, IDOK), false);
		int len = GetWindowTextLength(hChkSKUText);
		if (len == 0) {
			SetWindowText(hChkSKULbl, TEXT("Enter an SKU into the box above"));
			EnableWindow(GetDlgItem(hWnd, IDOK), false);
			EnableWindow(hChkSKUSearchBtn, false);
		}
		else {
			SetWindowText(hChkSKULbl, TEXT(""));
			EnableWindow(GetDlgItem(hWnd, IDOK), false);
			EnableWindow(hChkSKUSearchBtn, true);
		}
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case IDOK:
		{
			EndDialog(hWnd, IDOK);
			break;
		}
		case IDCANCEL:
		{
			EndDialog(hWnd, IDCANCEL);
			break;
		}
		case IDC_CHK_SKU_TEXT:
		{
			switch (HIWORD(wParam)) {
			case EN_CHANGE:

				break;
			}
			break;
		}
		case IDC_CHK_SKU_SEARCH:
		{
			break;
		}
		}
		return TRUE;
	}
	default: 
	{
		return FALSE;
	}
	}
}