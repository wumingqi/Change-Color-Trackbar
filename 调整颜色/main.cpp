#include "Function.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//声明这两个参数未引用
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//注册窗口类
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLS_NAME;

	RegisterClassW(&wc);

	HWND hWnd = CreateWindowW(CLS_NAME, WIN_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	SetProcessDPIAware();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//快捷键表
	ACCEL accel[ACCEL_NUM];
	accel[0].cmd = CMD_CLOSE;
	accel[0].fVirt = FVIRTKEY | FCONTROL|FSHIFT;
	accel[0].key = 'W';
	HACCEL hAccelTable=CreateAcceleratorTable(accel,ACCEL_NUM);

	MSG msg;

	// 主消息循环: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}