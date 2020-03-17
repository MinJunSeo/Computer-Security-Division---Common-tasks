// Visual Studio 2019 version 16.4.6

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("SimplePaint");

enum { ID_RED = 101, ID_BLUE, ID_YELLOW, ID_BLACK }; // ���� ID
#define ID_THICK 200 // �� �����ϴ� ID
#define ID_REDRAW 201 // ȭ�� �ٽ� �׸��� ID

// �� ��ɵ��� �������� �ڵ�
HWND hRed, hBlue, hYellow, hBlack, hThick, hReDraw;

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

	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
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
	static int nWidth = 1;
	static BOOL bNowDraw = FALSE;
	static COLORREF dwColor = RGB(0, 0, 0); // ���� ���� ������ ����. �ʱ���� ����

	switch (iMessage)
	{
	case WM_CREATE:
		// ������ư�� ���� �׷�ڽ� ����
		CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			10, 10, 70, 150, hWnd, (HMENU)0, g_hInst, NULL);
		hRed = CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			17, 27, 55, 30, hWnd, (HMENU)ID_RED, g_hInst, NULL);
		hBlue = CreateWindow(TEXT("button"), TEXT("�Ķ�"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			17, 57, 55, 30, hWnd, (HMENU)ID_BLUE, g_hInst, NULL);
		hYellow = CreateWindow(TEXT("button"), TEXT("���"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			17, 87, 55, 30, hWnd, (HMENU)ID_YELLOW, g_hInst, NULL);
		hBlack = CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			17, 117, 55, 30, hWnd, (HMENU)ID_BLACK, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_RED, ID_BLACK, ID_BLACK);
		hThick = CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX | WS_BORDER,
			10, 170, 55, 30, hWnd, (HMENU)ID_THICK, g_hInst, NULL);
		hReDraw = CreateWindow(TEXT("button"), TEXT("�ٽ� �׸���"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 210, 100, 30, hWnd, (HMENU)ID_REDRAW, g_hInst, NULL);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_THICK:
			if (SendMessage(hThick, BM_GETCHECK, 0, 0) == BST_UNCHECKED) // üũ�Ǿ� ���� �ʴٸ�
			{
				SendMessage(hThick, BM_SETCHECK, BST_CHECKED, 0); // üũ�� ���·� �����Ѵ�.
				nWidth = 5; // ���⸦ ���� �Ѵ�.
			}
			else
			{
				SendMessage(hThick, BM_SETCHECK, BST_UNCHECKED, 0);
				nWidth = 1;
			}
			break;

		case ID_RED:
			dwColor = RGB(255, 0, 0);
			break;

		case ID_BLUE:
			dwColor = RGB(0, 0, 255);
			break;

		case ID_YELLOW:
			dwColor = RGB(255, 255, 0);
			break;

		case ID_BLACK:
			dwColor = RGB(0, 0, 0);
			break;

		case ID_REDRAW:
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

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}