//TakeInForm.c
#include"TakeInForm.h"
#include"BusinessCardBook.h"
#include"resource.h"
#include<stdio.h>
#include<string.h>

BOOL CALLBACK TakeInFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG:
		ret = TakeInForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = TakeInForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = TakeInForm_OnClose(hWnd, wParam, lParam);
		break;

	default: ret = FALSE; break;
	}
	return ret;
}

//1. ����� �����찡 �����ɶ�
BOOL TakeInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	char position[10][32] = {"ȸ��", "����", "�̻�", "����", "����", "����", "�븮", "���", "����"};
	char domain[10][32] = {"naver.com", "daum.net", "nate.com", "google.com", "amazon.com", "apple.com", "facebook.com", "yahoo.co.kr"};
	Long i = 0;
	Long j = 0;

	//1.1. ��å����� �����.
	while (i < 9) {
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_POSITION), CB_ADDSTRING, 0, position[i]);
		i++;
	}

	//1.2. �����θ���� �����.
	while (j < 8) {
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), CB_ADDSTRING, 0, domain[j]);
		j++;
	}

	return TRUE;
}

//��ư�� Ŭ��������//��Ŀ���� �Ҿ�����
BOOL TakeInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_TAKEIN:	//2. ����� ��ư�� Ŭ��������
		ret = TakeInForm_OnTakeInButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_EDIT_COMPANY_NAME:	//3. ��ȣ EDIT ��Ŀ���� �Ҿ�����
		ret = TakeInForm_KillCompanyNameFocus(hWnd, wParam, lParam);
		break;

	default: ret = FALSE; break;
	}
	return ret;
}

//2. ����� ��ư�� Ŭ��������
BOOL TakeInForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard businessCard;
	HWND hBusinessCardBookForm;
	BusinessCardBook *businessCardBook;
	TCHAR emailID[32];
	TCHAR domainAddress[32];
	TCHAR emailAddress[64];
	BusinessCard *index;

	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. ������ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)32, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);

		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)32, (LPARAM)emailID);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)32, (LPARAM)domainAddress);
		sprintf(emailAddress, "%s@%s", emailID, domainAddress);
		strcpy(businessCard.personal.emailAddress, emailAddress);

		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_URL), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.url);

		//businessCard.next �� NULL ���� ������!! �������� �Է��ϱ� ���� �ȱ׷��� ������ ������־�!!
		businessCard.next = NULL;

		//2.2. ����ö �����츦 ã�´�.
		hBusinessCardBookForm = FindWindow("#32770", "����ö");
		//2.3. ����ö �������� ����ö���� �����.
		businessCardBook = (BusinessCardBook*)GetWindowLong(hBusinessCardBookForm, GWL_USERDATA);
		index = TakeIn(businessCardBook, businessCard);
		//2.4. ����ö �������� ���Կ� ����.
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.emailAddress);

		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.url);
		//2.5. ����� �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

//3. ��ȣ EDIT ��Ŀ���� �Ҿ�����
BOOL TakeInForm_KillCompanyNameFocus(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR companyName[64];
	HWND uBusinessCardBookForm;
	BusinessCardBook *businessCardBook;
	BusinessCard *index;

	if (HIWORD(wParam) == EN_KILLFOCUS) {
		//3.1. ��ȣ�� �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)companyName);
		//3.2. ����ö �����츦 ã�´�.
		uBusinessCardBookForm = FindWindow("#32770", "����ö");
		//3.3. ����ö �������� ����ö���� ��ȣ�� ã�´�.
		businessCardBook = (BusinessCardBook*)GetWindowLong(uBusinessCardBookForm, GWL_USERDATA);
		index = FindByCompanyName(businessCardBook, companyName);
		//3.4. ã�� ȸ�簡 ������ ȸ�縦 ����.
		if (index != NULL) {
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_SETTEXT, 0, (LPARAM)index->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_TELEPHONENUMBER), WM_SETTEXT, 0, (LPARAM)index->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAXNUMBER), WM_SETTEXT, 0, (LPARAM)index->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_URL), WM_SETTEXT, 0, (LPARAM)index->company.url);
		}
	}
	return TRUE;
}

//4. �ݱ� ��ư�� Ŭ��������
BOOL TakeInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//4.1. ����� �����츦 �ݴ´�.
	EndDialog(hWnd, 0);

	return TRUE;
}