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

//1. ���� �����찡 �����ɶ�
BOOL TakeOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND hBusinessCardBookForm;
	BusinessCardBook *businessCardBook;
	BusinessCard businessCard;
	BusinessCard *index;

	//1.1. ����ö �����츦 ã�´�.
	hBusinessCardBookForm = FindWindow("#32770", "����ö");
	//1.2. ����ö �������� ����ö���� ����.
	businessCardBook = (BusinessCardBook*)GetWindowLong(hBusinessCardBookForm, GWL_USERDATA);
	businessCard = TakeOut(businessCardBook, businessCardBook->current);
	//1.3. ������ ����.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.personal.position);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.personal.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.personal.emailAddress);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.faxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.url);
	//1.4. ���� ������ ������ ����ö �����쿡 ������ ����.
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
	//1.5. ���� ������ ������ ����ö �����쿡 ��ĭ�� ����.
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

//2. �ݱ� ��ư�� Ŭ��������
BOOL TakeOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	int check;
	BusinessCard businessCard;
	HWND hBusinessCardBookForm;
	BusinessCardBook *businessCardBook;
	BusinessCard *index;

	//2.1. �޽���â�� ����Ѵ�.
	check = MessageBox(hWnd, "�ٽ� ����ðڽ��ϴ�?", "Ȯ��â", MB_YESNOCANCEL);
	switch (check) {
	
	//2.2. "��" ��ư�� Ŭ��������
	case IDYES:
		//2.2.1. ������ �д´�.
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
		//2.2.2. ����ö �����츦 ã�´�.
		hBusinessCardBookForm = FindWindow("#32770", "����ö");
		//2.2.3. ����ö �������� ����ö���� �����.
		businessCardBook = (BusinessCardBook*)GetWindowLong(hBusinessCardBookForm, GWL_USERDATA);
		index = TakeIn(businessCardBook, businessCard);
		//2.2.4. ����ö �����쿡 ���Կ� ����. 
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.emailAddress);

		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.url);
		//2.2.5. ���� �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
		break;
	//2.3. "�ƴϿ�" ��ư�� Ŭ��������
	case IDNO:
		//2.3.1. ���� �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
		break;
	}
	return TRUE;
}