//BusinessCardBookForm.c
#include"BusinessCardBookForm.h"
#include"TakeInForm.h"
#include"FindForm.h"
#include"TakeOutForm.h"
#include"resource.h"
#include"BusinessCardBook.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {
	int nResponse;

	nResponse = DialogBox(hInstance, MAKEINTRESOURCE(IDD_BUSINESSCARDBOOKFORM), NULL, BusinessCardBookFormProc);
	return nResponse;
}
BOOL CALLBACK BusinessCardBookFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG:
		ret = BusinessCardBookForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = BusinessCardBookForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = BusinessCardBookForm_OnClose(hWnd, wParam, lParam);
		break;

	default: ret = FALSE; break;
	}
	return ret;
}


//1. ����ö �����찡 �����ɶ�
BOOL BusinessCardBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBook *businessCardBook;
	BusinessCard *index;

	//1.1. ����ö�� �����.
	businessCardBook = (BusinessCardBook*)malloc(sizeof(BusinessCardBook));
	Create(businessCardBook);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)businessCardBook);
	//1.2. �����Ѵ�.
	Load(businessCardBook);
	//1.3. ����ö���� ó���������� �̵��Ѵ�.
	index = First(businessCardBook);
	//1.4. ù ������ ���Կ� ����Ѵ�.
	if (index != NULL) {
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.url);
	}
	return TRUE;
}

//��ư�� Ŭ��������
BOOL BusinessCardBookForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_TAKEIN:	//2. ����� ��ư�� Ŭ��������
		ret = BusinessCardBookForm_OnTakeInButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIND:	//3. ã�� ��ư�� Ŭ��������
		ret = BusinessCardBookForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_TAKEOUT:	//4.���� ��ư�� Ŭ��������
		ret = BusinessCardBookForm_OnTakeOutButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_ARRANGE:	//5. �����ϱ� ��ư�� Ŭ��������
		ret = BusinessCardBookForm_OnArrangeButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIRST:	//6. ó�� ��ư�� Ŭ��������
		ret = BusinessCardBookForm_OnFirstButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_PREVIOUS:	//7. ���� ��ư�� Ŭ��������
		ret = BusinessCardBookForm_OnPreviousButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_NEXT:	//8. ���� ��ư�� Ŭ��������
		ret = BusinessCardBookForm_OnNextButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_LAST:	//9. �� ��ư�� Ŭ��������
		ret = BusinessCardBookForm_OnLastButtonClicked(hWnd, wParam, lParam);
		break;

	default: ret = FALSE; break;
	}
	return ret;
}

//2. ����� ��ư�� Ŭ��������
BOOL BusinessCardBookForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	if (HIWORD(wParam) == BN_CLICKED) {
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_TAKEINFORM), NULL, TakeInFormProc);
	}
	return TRUE;
}

//3. ã�� ��ư�� Ŭ��������
BOOL BusinessCardBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	if (HIWORD(wParam) == BN_CLICKED) {
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDFORM), NULL, FindFormProc);
	}
	return TRUE;
}

//4.���� ��ư�� Ŭ��������
BOOL BusinessCardBookForm_OnTakeOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	if (HIWORD(wParam) == BN_CLICKED) {
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_TAKEOUTFORM), NULL, TakeOutFormProc);
	}
	return TRUE;
}

//5. �����ϱ� ��ư�� Ŭ��������
BOOL BusinessCardBookForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBook *businessCardBook;
	BusinessCard *index;

	if (HIWORD(wParam) == BN_CLICKED) {
		//5.1. ����ö���� �����Ѵ�.
		businessCardBook = (BusinessCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(businessCardBook);
		//5.2. ����ö���� ó���������� �̵��Ѵ�.
		index = First(businessCardBook);
		//5.3. ������ ����.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.url);
	}
	return TRUE;
}

//6. ó�� ��ư�� Ŭ��������
BOOL BusinessCardBookForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBook *businessCardBook;
	BusinessCard *index;

	if (HIWORD(wParam) == BN_CLICKED) {
		//6.1. ����ö���� ó���������� �̵��Ѵ�.
		businessCardBook = (BusinessCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = First(businessCardBook);
		//6.2. ������ ����.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.emailAddress);

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.url);
	}
	return TRUE;
}

//7. ���� ��ư�� Ŭ��������
BOOL BusinessCardBookForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBook *businessCardBook;
	BusinessCard *index;

	if (HIWORD(wParam) == BN_CLICKED) {
		//7.1. ����ö���� ������������ �̵��Ѵ�.
		businessCardBook = (BusinessCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Previous(businessCardBook);
		//7.2. ������ ����.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.emailAddress);
		
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.url);
	}
	return TRUE;
}

//8. ���� ��ư�� Ŭ��������
BOOL BusinessCardBookForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBook *businessCardBook;
	BusinessCard *index;

	if (HIWORD(wParam) == BN_CLICKED) {
		//8.1. ����ö���� ������������ �̵��Ѵ�.
		businessCardBook = (BusinessCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Next(businessCardBook);
		//8.2. ������ ����.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.emailAddress);
		
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.url);
	}
	return TRUE;
}

//9. �� ��ư�� Ŭ��������
BOOL BusinessCardBookForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBook *businessCardBook;
	BusinessCard *index;

	if (HIWORD(wParam) == BN_CLICKED) {
		//9.1. ����ö���� ���������� �̵��Ѵ�.
		businessCardBook = (BusinessCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Last(businessCardBook);
		//9.2. ������ ����.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->personal.emailAddress);
		
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL_PRINT), WM_SETTEXT, 0, (LPARAM)index->company.url);
	}
	return TRUE;
}

//10. �ݱ� ��ư�� Ŭ��������
BOOL BusinessCardBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBook *businessCardBook;

	//10.1. ����ö�� �����.
	businessCardBook = (BusinessCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
	if (businessCardBook != NULL) {
		Save(businessCardBook);
		Destroy(businessCardBook);
		free(businessCardBook);
	}
	//10.2. ����ö �����츦 �ݴ´�.
	EndDialog(hWnd, 0);

	return TRUE;
}