#ifndef _WINDOWS_

#include <Windows.h>

#endif

#include "form.h"
#include "resource.h"
#include "main.h"
#include <CommCtrl.h>


const TCHAR *conditions[] = { TEXT("Acceptable"), TEXT("Good"), TEXT("Very Good"), TEXT("Like New"), TEXT("New") };
const TCHAR *currencies[] = { TEXT("GBP"), TEXT("USD"), TEXT("EUR") };


HWND hFormTitle, hFormCon, hFormConDes, hFormDes, hFormSKU, hFormChkSKU, hFormPrice, hFormCurrency, hFormTitleLbl, hFormConLbl, hFormConDesLbl, hFormDesLbl, hFormSKULbl, hFormPriceLbl;

bool CreateProductForm(HWND hWnd, LPCTSTR title, LPCTSTR con, LPCTSTR conDes, LPCTSTR des, LPCTSTR SKU, LPCTSTR price, LPCTSTR currency)
{
	SetWindowText(hWnd, TEXT("New Record - eBay Product Drafter"));

	RECT rcTool;
	int toolbarHeight;

	hToolbar = GetDlgItem(hWnd, IDC_MAIN_TOOL);
	GetWindowRect(hToolbar, &rcTool);
	toolbarHeight = rcTool.bottom - rcTool.top;

	SendMessage(hToolbar, TB_AUTOSIZE, 0, 0);
	hFormTitleLbl = CreateWindowEx(0, TEXT("STATIC"), TEXT("Title:"), WS_CHILD | WS_VISIBLE, 5, 5 + toolbarHeight, 125, 23, hWnd, NULL, NULL, NULL);
	hFormTitle = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), title, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 135, 5 + toolbarHeight, 300, 23, hWnd, (HMENU)IDC_FORM_TITLE_TXT, NULL, NULL);
	hFormConLbl = CreateWindowEx(0, TEXT("STATIC"), TEXT("Condition:"), WS_CHILD | WS_VISIBLE, 5, 33 + toolbarHeight, 125, 23, hWnd, NULL, NULL, NULL);
	hFormCon = CreateWindowEx(0, TEXT("COMBOBOX"), NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST, 135, 33 + toolbarHeight, 300, 60, hWnd, (HMENU)IDC_FORM_CON_COMBO, NULL, NULL);
	hFormConDesLbl = CreateWindowEx(0, TEXT("STATIC"), TEXT("Condition Description:"), WS_CHILD | WS_VISIBLE, 5, 61 + toolbarHeight, 125, 23, hWnd, NULL, NULL, NULL);
	hFormConDes = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), conDes, WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_TABSTOP, 135, 61 + toolbarHeight, 300, 60, hWnd, (HMENU)IDC_FORM_CON_DES_TXT, NULL, NULL);
	hFormDesLbl = CreateWindowEx(0, TEXT("STATIC"), TEXT("Description"), WS_CHILD | WS_VISIBLE, 5, 126 + toolbarHeight, 125, 23, hWnd, NULL, NULL, NULL);
	hFormDes = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), des, WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_MULTILINE, 135, 126 + toolbarHeight, 300, 100, hWnd, (HMENU)IDC_FORM_DES_TXT, NULL, NULL);
	hFormSKULbl = CreateWindowEx(0, TEXT("STATIC"), TEXT("SKU:"), WS_CHILD | WS_VISIBLE, 5, 231 + toolbarHeight, 125, 23, hWnd, NULL, NULL, NULL);
	hFormSKU = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), SKU, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 135, 231 + toolbarHeight, 220, 23, hWnd, (HMENU)IDC_FORM_SKU_TXT, NULL, NULL);
	hFormChkSKU = CreateWindowEx(0, TEXT("BUTTON"), TEXT("Check SKU"), WS_CHILD | WS_VISIBLE | WS_TABSTOP, 360, 231 + toolbarHeight, 75, 23, hWnd, (HMENU)IDC_FORM_SKU_BTN, NULL, NULL);
	hFormPriceLbl = CreateWindowEx(0, TEXT("STATIC"), TEXT("Price:"), WS_CHILD | WS_VISIBLE, 5, 259 + toolbarHeight, 125, 23, hWnd, NULL, NULL, NULL);
	hFormPrice = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), price, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 135, 259 + toolbarHeight, 220, 23, hWnd, (HMENU)IDC_FORM_PRICE_TXT, NULL, NULL);
	hFormCurrency = CreateWindowEx(0, TEXT("COMBOBOX"), NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST, 360, 259 + toolbarHeight, 75, 60, hWnd, (HMENU)IDC_FORM_PRICE_COMBO, NULL, NULL);

	for (int count = 0; count < 5; count++) {
		SendMessage(hFormCon, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)conditions[count]));
	}
	for (int count = 0; count < 3; count++) {
		SendMessage(hFormCurrency, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)currencies[count]));
	}
	SendMessage(hFormCon, CB_SELECTSTRING, -1, (LPARAM)con);
	SendMessage(hFormCurrency, CB_SELECTSTRING, -1, (LPARAM)currency);

	EnumChildWindows(hWnd, (WNDENUMPROC)SetFont, (LPARAM)GetStockObject(DEFAULT_GUI_FONT));
	if (!hFormTitleLbl || !hFormTitle || !hFormConLbl || !hFormCon || !hFormConDesLbl || !hFormConDes || !hFormDes || !hFormDes || !hFormSKULbl || !hFormSKU || !hFormChkSKU || !hFormPriceLbl || !hFormPrice || !hFormCurrency) {
		return false;
	}

	return true;
}