//FindForm.h
#ifndef _FINDFORM_H
#define _FINDFORM_H
#include<windows.h>

BOOL CALLBACK FindFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);

BOOL FindForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnSelectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);

BOOL FindForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif //_FINDFORM_H