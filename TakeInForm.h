//TakeInForm.h
#ifndef _TAKEINFORM_H
#define _TAKEINFORM_H
#include<windows.h>

BOOL CALLBACK TakeInFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL TakeInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TakeInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TakeInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);

BOOL TakeInForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TakeInForm_KillCompanyNameFocus(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif //_TAKEINFORM_H