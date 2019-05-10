//TakeOutForm.c
#include"TakeOutForm.h"
#include"BusinessCardBook.h"
#include"resource.h"

BOOL CALLBACK TakeOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG:
		ret = TakeOutForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = TakeOutForm_OnClose(hWnd, wParam, lParam);
		break;

	default: ret = FALSE; break;
	}
	return ret;
}

//1. 빼기 윈도우가 생성될때
BOOL TakeOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND hBusinessCardBookForm;
	BusinessCardBook *businessCardBook;
	BusinessCard businessCard;
	BusinessCard *index;

	//1.1. 명함철 윈도우를 찾는다.
	hBusinessCardBookForm = FindWindow("#32770", "명함철");
	//1.2. 명함철 윈도우의 명함철에서 빼다.
	businessCardBook = (BusinessCardBook*)GetWindowLong(hBusinessCardBookForm, GWL_USERDATA);
	businessCard = TakeOut(businessCardBook, businessCardBook->current);
	//1.3. 명함을 쓴다.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.personal.position);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.personal.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.personal.emailAddress);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.faxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.url);
	//1.4. 현재 명함이 있으면 명함철 윈도우에 명함을 쓴다.
	if (businessCardBook->current != NULL) {
		index = businessCardBook->current;
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.emailAddress);

		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.url);
	}
	//1.5. 현재 명함이 없으면 명함철 윈도우에 빈칸을 쓴다.
	else {
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)"");

		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)"");
	}
	return TRUE;
}

//2. 닫기 버튼을 클릭했을때
BOOL TakeOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	int check;
	BusinessCard businessCard;
	HWND hBusinessCardBookForm;
	BusinessCardBook *businessCardBook;
	BusinessCard *index;

	//2.1. 메시지창을 출력한다.
	check = MessageBox(hWnd, "다시 끼우시겠습니다?", "확인창", MB_YESNOCANCEL);
	switch (check) {
	
	//2.2. "예" 버튼을 클릭했을때
	case IDYES:
		//2.2.1. 명함을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_GETTEXT, (WPARAM)32, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.personal.emailAddress);

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.url);
		businessCard.next = NULL;
		//2.2.2. 명함철 윈도우를 찾는다.
		hBusinessCardBookForm = FindWindow("#32770", "명함철");
		//2.2.3. 명함철 윈도우의 명함철에서 끼운다.
		businessCardBook = (BusinessCardBook*)GetWindowLong(hBusinessCardBookForm, GWL_USERDATA);
		index = TakeIn(businessCardBook, businessCard);
		//2.2.4. 명함철 윈도우에 명함에 쓴다. 
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.emailAddress);

		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.url);
		//2.2.5. 빼기 윈도우를 닫는다.
		EndDialog(hWnd, 0);
		break;
	//2.3. "아니오" 버튼을 클릭했을때
	case IDNO:
		//2.3.1. 빼기 윈도우를 닫는다.
		EndDialog(hWnd, 0);
		break;
	}
	return TRUE;
}