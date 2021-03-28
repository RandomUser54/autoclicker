#include "Window.h"
char a[50];
int timesleep = 10;
HANDLE thread = NULL;
int code = 0xC0;
int CALLBACK WinMain(HINSTANCE hinst, HINSTANCE prehinst, LPSTR cmdline, int showcmd) {
	clickon.dwFlags = MOUSEEVENTF_LEFTDOWN;
	clickoff.dwFlags = MOUSEEVENTF_LEFTUP;
	on[0].type, off[0].type = INPUT_MOUSE;
	on[0].mi = clickon;
	off[0].mi = clickoff;
	HICON hicon = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON1));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = &WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hinst;
	wc.hIcon = hicon;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("Autoclicker");
	RegisterClass(&wc);
	hwnd = CreateWindowA("Autoclicker", "Autoclicker", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 450, 200, 500, 550, NULL, NULL, hinst, NULL);
	button = CreateWindowA("BUTTON", "Initiate autoclicker", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 50, 250, 80, 40, hwnd, NULL, hinst, NULL);
	button1 = CreateWindowA("BUTTON", "Initiate consistent autoclicker", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 150, 250, 80, 60, hwnd, NULL, hinst, NULL);
	button2 = CreateWindowA("BUTTON", "Change wait time between each click", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 250, 250, 80, 70, hwnd, NULL, hinst, NULL);
	txtbox = CreateWindowA("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_NUMBER, 250, 330, 80, 20, hwnd, NULL, hinst, NULL);
	button3 = CreateWindowA("BUTTON", "Change keybind", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 350, 250, 80, 40, hwnd, NULL, hinst, NULL);
	txtbox1 = CreateWindowA("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LOWERCASE, 350, 300, 80, 20, hwnd, NULL, hinst, NULL);
	CreateWindowA("EDIT", "Get virtual keycodes from https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes (Default keybind is ~ key)", WS_CHILD | WS_VISIBLE | ES_READONLY | ES_MULTILINE, 275, 400, 200, 80, hwnd, NULL, hinst, NULL);
	if (!hwnd) {
		MessageBoxA(NULL, "Couldn't create window.", NULL, MB_OK);
		return 1;
	}
	imagelist = ImageList_Create(150, 150, NULL, 0, 1);
	img = (HBITMAP)LoadImageA(hinst, MAKEINTRESOURCEA(IDB_BITMAP1), IMAGE_BITMAP, 150, 150, LR_DEFAULTSIZE);
	ImageList_Add(imagelist, img, NULL);
	while (GetMessage(&msg, hwnd, 0, 0) == 1) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		int i = 0;
		hdc = BeginPaint(hwnd, &ps);
		TextOutA(hdc, 115, 175, "Autoclicker written by Random_User54", sizeof("Autoclicker written by Random_User54"));
		TextOutA(hdc, 240, 350, "(In milliseconds)", sizeof("(In milliseconds)"));
		ImageList_Draw(imagelist, 0, hdc, 160, 0, ILD_IMAGE);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_COMMAND:
	{
		char txt[50];
		char t1[] = "Stop autoclicker";
		char t2[] = "Initiate autoclicker";
		char t3[] = "Initiate consistent autoclicker";
		if ((HWND)lparam == button) {
			char title[17];
			int t = 0;
			GetWindowTextA(button, title, sizeof(title));
			for(int x = 0; x < sizeof(title); x++)
				if (title[x] != t1[x]) {
					t = 1;
					break;
				}
			if (thread) {
				stop();
				SetWindowTextA(button, t2);
				SetWindowTextA(button1, t3);
			}
			if (t == 1) {
				thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&fast, NULL, 0, NULL);
				if (!thread) {
					MessageBoxA(hwnd, "Error creating thread", "Autoclicker initiation", MB_OK);
				}
				SetWindowTextA(button, t1);
				SetWindowTextA(button1, t3);
			}
		}
		else if ((HWND)lparam == button1) {
			char title[17];
			int t = 0;
			GetWindowTextA(button1, title, sizeof(title));
			for (int x = 0; x < sizeof(title); x++)
				if (title[x] != t1[x]) {
					t = 1;
					break;
				}
			if (thread) {
				stop();
				SetWindowTextA(button, t2);
				SetWindowTextA(button1, t3);
			}
			if (t == 1) {
				thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&consistent, NULL, 0, NULL);
				if (!thread) {
					MessageBoxA(hwnd, "Error creating thread", "Autoclicker initiation", MB_OK);
				}
				SetWindowTextA(button, t2);
				SetWindowTextA(button1, t1);
			}
		}
		else if((HWND)lparam == button2) {
			GetWindowTextA(txtbox, txt, sizeof(txt));
			int t = atoi(txt);
			if (t == 0) {
				MessageBoxA(hwnd, "Invalid input. Nothing has changed.", "Timesleep change", MB_OK);
			}
			else {
				timesleep = t;
			}
			SetWindowText(txtbox, NULL);
		}
		else if ((HWND)lparam == button3) {
			GetWindowTextA(txtbox1, txt, sizeof(txt));
			stringstream ss;
			int key;
			ss << hex << txt;
			ss >> key;
			if (key < 0) {
				MessageBoxA(hwnd, "Invalid input. Nothing has changed.", "Keybind change", MB_OK);
			}
			else {
				code = key;
			}
			SetWindowText(txtbox1, NULL);
		}
		break;
	}
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
