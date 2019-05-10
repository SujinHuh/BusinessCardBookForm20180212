//BusinessCardBookForm.h
#ifndef _BUSINESSCARDBOOKFORM_H
#define _BUSINESSCARDBOOKFORM_H
#include<windows.h>

BOOL CALLBACK BusinessCardBookFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL BusinessCardBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);

BOOL BusinessCardBookForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnTakeOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);

BOOL BusinessCardBookForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif //_BUSINESSCARDBOOKFORM_H