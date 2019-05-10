//FindForm.c
#include"FindForm.h"
#include"BusinessCardBook.h"
#include"resource.h"

BOOL CALLBACK FindFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {

	case WM_COMMAND:
		ret = FindForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = FindForm_OnClose(hWnd, wParam, lParam);
		break;

	default: ret = FALSE; break;
	}
	return ret;
}

//��ư�� Ŭ��������
BOOL FindForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIND:	//1. ã�� ��ư�� Ŭ��������
		ret = FindForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIRST:	//2. ó�� ��ư�� Ŭ��������
		ret = FindForm_OnFirstButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_PREVIOUS:	//3. ���� ��ư�� Ŭ��������
		ret = FindForm_OnPreviousButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_NEXT:	//4. ���� ��ư�� Ŭ��������
		ret = FindForm_OnNextButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_LAST:	//5. �� ��ư�� Ŭ��������
		ret = FindForm_OnLastButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_SELECT:	//6. �����ϱ� ��ư�� Ŭ��������
		ret = FindForm_OnSelectButtonClicked(hWnd, wParam, lParam);
		break;

	default: ret = FALSE; break;
	}
	return ret;
}

//1. ã�� ��ư�� Ŭ��������
BOOL FindForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR name[11];
	HWND hBusinessCardBookForm;
	BusinessCardBook *businessCardBook;
	BusinessCard* (*indexes);
	Long count;
	Long current = 0;


	if (HIWORD(wParam) == BN_CLICKED) {
		//1.1. ������ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)name);
		//1.2. ����ö �����츦 ã�´�.
		hBusinessCardBookForm = FindWindow("#32770", "����ö");
		//1.3. ����ö �������� ����ö���� ã�´�.
		businessCardBook = (BusinessCardBook*)GetWindowLong(hBusinessCardBookForm, GWL_USERDATA);
		//indexes �Ҵ�����
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}
		Find(businessCardBook, name, &indexes, &count);
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes);
		SetProp(hWnd, "count", (HANDLE)count);
		SetProp(hWnd, "current", (HANDLE)current);
		//1.4. ã�� ó�������� ���Կ� ����.
		if (indexes != NULL) {
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.position);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.emailAddress);

			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.url);
		}
		else {
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)"");

			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)"");
		}
	}
	return TRUE;
}

//2. ó�� ��ư�� Ŭ��������
BOOL FindForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBook *businessCardBook;
	BusinessCard* (*indexes);
	Long current = 0;

	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. ã�� ���Կ��� ó���������� �̵��Ѵ�.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		//2.2. ó�������� ����.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.emailAddress);

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.url);

		SetProp(hWnd, "current", (HANDLE)current);
	}
	return TRUE;
}

//3. ���� ��ư�� Ŭ��������
BOOL FindForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBook *businessCardBook;
	BusinessCard* (*indexes);
	Long current;

	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. ã�� ���Կ��� ������������ �̵��Ѵ�.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "current");
		current--;
		if (current < 0) {
			current = 0;
		}
		//3.2. ���������� ����.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.emailAddress);

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.url);

		SetProp(hWnd, "current", (HANDLE)current);
	}
	return TRUE;
}

//4. ���� ��ư�� Ŭ��������
BOOL FindForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBook *businessCardBook;
	BusinessCard* (*indexes);
	Long current;
	Long count;

	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1. ã�� ���Կ��� ������������ �̵��Ѵ�.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "count");
		current = (Long)GetProp(hWnd, "current");
		current++;
		if (current >= count) {
			current = count-1;
		}
		//4.2. ���������� ����.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.emailAddress);

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.url);

		SetProp(hWnd, "current", (HANDLE)current);
	}
	return TRUE;
}

////5. �� ��ư�� Ŭ��������
BOOL FindForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBook *businessCardBook;
	BusinessCard* (*indexes);
	Long current;
	Long count;

	if (HIWORD(wParam) == BN_CLICKED) {
		//5.1. ã�� ���Կ��� ���������� �̵��Ѵ�.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "count");
		current = count - 1;

		//4.2. �������� ����.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->personal.emailAddress);

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)indexes[current]->company.url);

		SetProp(hWnd, "current", (HANDLE)current);
	}
	return TRUE;
}

//6. �����ϱ� ��ư�� Ŭ��������
BOOL FindForm_OnSelectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard businessCard;
	HWND hBusinessCardBookForm;
	BusinessCardBook *businessCardBook;
	BusinessCard* (*indexes);
	Long current;
	BusinessCard *index;

	if (HIWORD(wParam) == BN_CLICKED) {
		//6.1. ������ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_GETTEXT, (WPARAM)32, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.personal.emailAddress);

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.url);
		//businessCard.next = NULL;
		//6.2. ����ö �����츦 ã�´�.
		hBusinessCardBookForm = FindWindow("#32770", "����ö");
		//6.3. ����ö �������� ����ö���� �̵��Ѵ�.
		businessCardBook = (BusinessCardBook*)GetWindowLong(hBusinessCardBookForm, GWL_USERDATA);
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "current");
		index = Move(businessCardBook, indexes[current]);
		//6.4. ����ö �������� ���Կ� ����.
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.personal.emailAddress);

		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hBusinessCardBookForm, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)businessCard.company.url);

		//6.5. ã�� �����츦 �ݴ´�.
		if (indexes != NULL) {
			free(indexes);
			indexes = NULL;
		}
		RemoveProp(hWnd, "current");
		RemoveProp(hWnd, "count");
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

//7. �ݱ� ��ư�� Ŭ��������
BOOL FindForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);

	//7.1. ã�� �����츦 �ݴ´�.
	indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
	if (indexes != NULL) {
		free(indexes);
		indexes = NULL;
	}
	RemoveProp(hWnd, "current");
	RemoveProp(hWnd, "count");
	EndDialog(hWnd, 0);

	return TRUE;
}