// Visual Studio 2019 version 16.4.6

#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// �ɼ� ��ȭ���� ���ν��� ����
BOOL CALLBACK OptionDlgProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("SimplePaint version 2.0");

// �ɼ� ��ȭ���ڿ����� ����ؾ� �ϱ⿡ ���� ������ ����
int nWidth = 1;
COLORREF dwColor = RGB(0, 0, 0); // ���� ���� ������ ����. �ʱ���� ����

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

	// ȭ�鿡 ���ϵ尡 ������ WS_OVERLAPPEDWINDOW �Ӽ����θ� ����
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
	HDC hdc;
	PAINTSTRUCT ps;
	static int x, y;
	static BOOL bNowDraw = FALSE;

	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_SPACE: // ���� Ű�� ���� ���
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		return 0;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		bNowDraw = TRUE;
		return 0;

	case WM_MOUSEMOVE:
	{
		HPEN hPen, OldPen;

		if(bNowDraw)
		{
			hdc = GetDC(hWnd);
			// ���� ���� ������ ����� ����� �����.
			hPen = CreatePen(PS_SOLID, nWidth, dwColor);
			OldPen = (HPEN)SelectObject(hdc, hPen);

			// ���� �ߴ´�.
			MoveToEx(hdc, x, y, NULL);
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			LineTo(hdc, x, y);

			SelectObject(hdc, OldPen);
			DeleteObject(hPen);
			ReleaseDC(hWnd, hdc);
		}
		return 0;
	}

	case WM_LBUTTONUP:
		bNowDraw = FALSE;
		return 0;

	// ������ ���콺 ��ư�� ���� ��� �ɼ� ��ȭ���ڸ� ����.
	case WM_RBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, OptionDlgProc);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK OptionDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	// ��ȭ���ڸ� �� �� � ��ư�� üũ�Ǿ�� �ϴ��� �˻� �� üũ�Ѵ�.
	case WM_INITDIALOG:
		if (nWidth == 1)
			CheckDlgButton(hDlg, IDC_THICK, BST_UNCHECKED);
		else
			CheckDlgButton(hDlg, IDC_THICK, BST_CHECKED);

		if (dwColor == RGB(0, 0, 0))
			CheckDlgButton(hDlg, IDC_BLACK, BST_CHECKED);
		else if (dwColor == RGB(255, 0, 0))
			CheckDlgButton(hDlg, IDC_RED, BST_CHECKED);
		else if (dwColor == RGB(255, 255, 0))
			CheckDlgButton(hDlg, IDC_YELLOW, BST_CHECKED);
		else
			CheckDlgButton(hDlg, IDC_BLUE, BST_CHECKED);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			if (IsDlgButtonChecked(hDlg, IDC_THICK)) // ��ư�� üũ�Ǿ� �ִ°�?
				nWidth = 5;
			else
				nWidth = 1;

			// ���� ��ư�̱⿡ �� ��ư�� ��� if�� �˻��� �ʿ䰡 ����.
			if (IsDlgButtonChecked(hDlg, IDC_BLACK))
				dwColor = RGB(0, 0, 0);
			else if (IsDlgButtonChecked(hDlg, IDC_RED))
				dwColor = RGB(255, 0, 0);
			else if (IsDlgButtonChecked(hDlg, IDC_YELLOW))
				dwColor = RGB(255, 255, 0);
			else
				dwColor = RGB(0, 0, 255);
			
			EndDialog(hDlg, IDOK);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
		break;
	}
	
	return FALSE;
}