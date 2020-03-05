// Visual Studio 2019���� �ۼ��� �ڵ��Դϴ�.

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Adhere");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	// ���� ������ Ŭ���� ���
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

	// ���ϵ� ������ Ŭ���� ���
	WndClass.lpfnWndProc = ChildProc;
	WndClass.lpszClassName = TEXT("Ad");
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH); // ȸ�� ������ �ش�.
	WndClass.style = CS_VREDRAW | CS_NOCLOSE; // �ݱ� ��ư(X) ��� �Ұ�
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
		// ���ϵ� ������ ����
		CreateWindow(TEXT("Ad"), TEXT("Tool"),
			WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE,
			// �˾� ������� | Ÿ��Ʋ �� | �ý��� �޴� | ũ�� ���� ������ �β��� ��輱 | �ٷ� ���̱�
			200, 250, 200, 200, hWnd, (HMENU)0, g_hInst, NULL);
		hWndMain = hWnd;
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	LPMINMAXINFO pmmi;
	RECT mainWndRect;
	LPWINDOWPOS wp;
	int t, height;

	switch (iMessage)
	{
	case WM_GETMINMAXINFO:
		pmmi = (LPMINMAXINFO)lParam;
		// �˾� �������� ���� 200 �ȼ��� �����Ѵ�.
		pmmi->ptMaxPosition.x = 200;
		pmmi->ptMaxSize.x = 200;
		pmmi->ptMaxTrackSize.x = 200;
		return 0;

	case WM_WINDOWPOSCHANGING:
		GetWindowRect(hWndMain, &mainWndRect);
		height = mainWndRect.bottom - mainWndRect.top;
		wp = (LPWINDOWPOS)lParam;

		// �˾� �������� ���̴� (�θ� ������ ���� / 4) < cy < �θ� ������ ����
		wp->cy = min(max(wp->cy, height / 4), height);

		t = wp->x;
		// ���� ������ �۾����� x ��ǥ - �˾� �������� x ��ǥ�� ������ 30 �ȼ� �̸�
		if (abs(mainWndRect.left - t) < 30)
			t = mainWndRect.left;
		if (abs(mainWndRect.right - (t + (wp->cx))) < 30)
			// ���� ������ ������ �۾����� x ��ǥ - �� �˾� �������� ��(200 �ȼ�)
			t = mainWndRect.right - (wp->cx);
		wp->x = t;

		t = wp->y;
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}