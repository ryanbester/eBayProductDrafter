#pragma once

#ifndef RESOURCE_H

#define RESOURCE_H

const TCHAR szAppName[] = TEXT("eBayProductDrafter");

bool isCreatingProduct = false;

HWND hToolbar, hStatusbar;

HWND hFormTitle, hFormCon, hFormConDes, hFormDes, hFormSKU, hFormChkSKU, hFormPrice, hFormCurrency, hFormTitleLbl, hFormConLbl, hFormConDesLbl, hFormDesLbl, hFormSKULbl, hFormPriceLbl;

HMENU hMenu, hSubMenu;

#define CREATEPROCESS_MANIFEST_RESOURCE_ID RT_MANIFEST "eBayProductDrafter.exe.manifest"

#define IDI_APPICON 201
#define IDI_APPICONSM 202

#define IDM_FILE_NEW 9001
#define IDM_FILE_OPEN_REC 9002
#define IDM_FILE_OPEN_REC_FILE 9003
#define IDM_FILE_CLOSE 9004
#define IDM_FILE_SAVE 9005
#define IDM_FILE_EXPORT 9006
#define IDM_FILE_EXIT 9007
#define IDM_EDIT_UNDO 9101
#define IDM_EDIT_REDO 9102
#define IDM_EDIT_CUT 9103
#define IDM_EDIT_COPY 9104
#define IDM_EDIT_PASTE 9105
#define IDM_EDIT_DELETE 9106
#define IDM_EDIT_SELECTALL 9107
#define IDM_EDIT_FIND 9108
#define IDM_EDIT_PREF 9109
#define IDM_REC_COPY 9201
#define IDM_REC_DEL 9202
#define IDM_HELP_HELP 9301
#define IDM_HELP_ABOUT 9302

#define IDC_MAIN_TOOL 8001
#define IDC_MAIN_STATUS 8002

#endif
