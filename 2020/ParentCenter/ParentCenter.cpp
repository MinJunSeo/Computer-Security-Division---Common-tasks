// Visual Studio 2019 version 16.4.6

#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("ParentCenter");

void MoveToParentCenter(HWND);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	switch (iMessage)
	{
	case WM_CREATE:
		hWndMain = hWnd;
		return 0;

	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		MoveToParentCenter(hDlg);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg, IDOK);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return FALSE;
		}
		break;
	}

	return FALSE;
}

void MoveToParentCenter(HWND hDlg)
{
	int x, y;
	RECT rtMain, rtDlg; // main window�� ��ȭ���� ��ǥ�� ���Ѵ�.

	if (!IsWindowVisible(hWndMain)) // window�� �ּ�ȭ�Ǿ� �ִ� ���
		ShowWindow(hWndMain, SW_SHOW);

	// �� window�� ȭ����� ��ǥ�� ���Ѵ�.
	GetWindowRect(hWndMain, &rtMain);
	GetWindowRect(hDlg, &rtDlg);

	// main window�� �߾� ��ǥ�� ���Ѵ�.
	x = (rtMain.left + rtMain.right) / 2;
	y = (rtMain.top + rtMain.bottom) / 2;

	// ��ȭ������ ���� ����ŭ x, y�� �����ؾ� �Ѵ�.
	x -= (rtDlg.right - rtDlg.left) / 2;
	y -= (rtDlg.bottom - rtDlg.top) / 2;

	// ũ��� �������� �ʰ� ��ġ�� �ű�� ���� SWP_NOSIZE ���
	SetWindowPos(hDlg, hWndMain, x, y, 0, 0, SWP_NOSIZE);
}