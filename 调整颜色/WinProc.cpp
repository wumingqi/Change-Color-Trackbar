#include "Function.h"
//changes

#define TRACKBAR_WIDTH	30					//滑块宽度

BYTE Color_R, Color_G, Color_B;				//三种颜色值
HWND TrackBar_R, TrackBar_G, TrackBar_B;	//三个滑块
RECT ClientRect;							//客户区矩形

//创建滑块函数
HWND CreateTrack(HWND hWnd, HINSTANCE hInst)
{
	HWND hwndTrack = CreateWindowEx(
		0,TRACKBAR_CLASS,L"Trackbar Control",
		WS_CHILD |WS_VISIBLE|TBS_VERT|TBS_BOTH| TBS_NOTICKS| TBS_FIXEDLENGTH| TBS_TOOLTIPS| TBS_DOWNISLEFT,              // style 
		10, 10,100,200,hWnd,HMENU(1001),hInst,NULL);

	SendMessage(hwndTrack, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0, 255));  // min. & max. positions

	SendMessage(hwndTrack, TBM_SETTHUMBLENGTH, TRACKBAR_WIDTH-3, 0);

	//SendMessage(hwndTrack, TBM_SETTIPSIDE, TBS_LEFT, 0);
	HWND hbt = CreateWindow(L"button", NULL, WS_CHILD | WS_VISIBLE, 0, 0, 100, 40, hWnd, HMENU(1002), 0, 0);
	SendMessage(hwndTrack, TBM_SETBUDDY, 0, (LPARAM)hbt);
	SendMessage(hwndTrack, TBM_SETPAGESIZE, 0, 5);			//鼠标点击的调整大小
	return hwndTrack;
}

void ShowValue(HDC hdc, int x)
{
	/*wchar_t pr[4], pg[4], pb[4];

	ZeroMemory(pr, 4);
	ZeroMemory(pg, 4);
	ZeroMemory(pb, 4);

	int c1 = wsprintf(pr, L"%d", r);
	TextOut(hdc, x, 0, pr, c1);
	c1 = wsprintf(pg, L"%d", g);
	TextOut(hdc, x *2, 0, pg, c1);
	c1 = wsprintf(pb, L"%d", b);
	TextOut(hdc, x *3, 0, pb, c1);*/
	wchar_t cch[18];
	int c = wsprintf(cch, L"R:%d,G:%d,B:%d", Color_R, Color_G, Color_B);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255 - Color_R, 255 - Color_G, 255 - Color_B));
	DrawText(hdc, cch, c, &ClientRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

long _stdcall WinProc(HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		LPCREATESTRUCT lpCreateStruct = (LPCREATESTRUCT)lParam;
		TrackBar_R = CreateTrack(hWnd, lpCreateStruct->hInstance);
		TrackBar_G = CreateTrack(hWnd, lpCreateStruct->hInstance);
		TrackBar_B = CreateTrack(hWnd, lpCreateStruct->hInstance);
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		switch (wmId)
		{
			//关闭程序
		case CMD_CLOSE:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		break;
	}

	case WM_SIZE:
	{
		GetClientRect(hWnd, &ClientRect);
		ClientRect.left += (ClientRect.right / 2);

		WORD w = LOWORD(lParam), h = HIWORD(lParam);
		w /= 8;
		int y = h / 8;

		MoveWindow(TrackBar_R, w, y, TRACKBAR_WIDTH, h - 2 * y, 1);
		MoveWindow(TrackBar_G, w * 2, y, TRACKBAR_WIDTH, h - 2 * y, 1);
		MoveWindow(TrackBar_B, w * 3, y, TRACKBAR_WIDTH, h - 2 * y, 1);

		break;
	}

	//处理滑条值变消息
	case WM_VSCROLL:
	{
		Color_R = (BYTE)SendMessage(TrackBar_R, TBM_GETPOS, 0, 0);
		Color_G = (BYTE)SendMessage(TrackBar_G, TBM_GETPOS, 0, 0);
		Color_B = (BYTE)SendMessage(TrackBar_B, TBM_GETPOS, 0, 0);
		InvalidateRect(hWnd, &ClientRect, 1);
		break;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		HBRUSH hbr = CreateSolidBrush(RGB(Color_R, Color_G, Color_B));
		FillRect(hdc, &ClientRect, hbr);
		int w = ClientRect.left / 4;

		ShowValue(hdc, w);

		DeleteObject(hbr);

		

		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}