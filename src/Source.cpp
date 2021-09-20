#include "Window.h"
int timesleep = 10;
HANDLE thread = NULL;
int code = 0xC0;
bool getkey = false;
int CALLBACK WinMain(HINSTANCE hinst, HINSTANCE prehinst, LPSTR cmdline, int showcmd) {
	HWND window;
	WNDCLASS wc;
	MSG msg;
	QueryPerformanceFrequency(&frequency);
	clickon.dwFlags = MOUSEEVENTF_LEFTDOWN;
	clickoff.dwFlags = MOUSEEVENTF_LEFTUP;
	on[0].type, off[0].type = INPUT_MOUSE;
	on[0].mi = clickon;
	off[0].mi = clickoff;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = &WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hinst;
	wc.hIcon = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("Autoclicker");
	RegisterClass(&wc);
	window = CreateWindowA("Autoclicker", "Autoclicker", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 450, 200, 500, 550, NULL, NULL, hinst, NULL);
	button = CreateWindowA("BUTTON", "Initiate autoclicker", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 50, 250, 80, 40, window, NULL, hinst, NULL);
	button1 = CreateWindowA("BUTTON", "Initiate consistent autoclicker", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 150, 250, 80, 60, window, NULL, hinst, NULL);
	button2 = CreateWindowA("BUTTON", "Change wait time between each click", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 250, 250, 80, 70, window, NULL, hinst, NULL);
	txtbox = CreateWindowA("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 250, 330, 80, 20, window, NULL, hinst, NULL);
	button3 = CreateWindowA("BUTTON", "Change keybind", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 350, 250, 80, 40, window, NULL, hinst, NULL);
	if (!window) {
		MessageBoxA(NULL, "Couldn't create window", NULL, MB_OK);
		return 1;
	}
	while (GetMessage(&msg, window, 0, 0) == 1) {
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
		TextOutA(hdc, 115, 25, "Autoclicker written by Random_User54", sizeof("Autoclicker written by Random_User54"));
		TextOutA(hdc, 235, 350, "(In milliseconds)", sizeof("(In milliseconds)"));
		TextOutA(hdc, 325, 225, "Default keybind is ~ key", sizeof("Default keybind is ~ key"));
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_COMMAND:
	{
		int cstate = state;
		if ((HWND)lparam == button) {
			if (thread) {
				stop();
				state = 0;
				SetWindowTextA(button, "Initiate autoclicker");
				SetWindowTextA(button1, "Initiate consistent autoclicker");
			}
			if (!cstate || cstate == 2) {
				thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&fast, NULL, 0, NULL);
				if (!thread) {
					MessageBoxA(hwnd, "Error creating thread", "Autoclicker initiation", MB_OK);
				}
				SetWindowTextA(button, "Stop autoclicker");
				state = 1;
			}
			SetFocus(hwnd);
		}
		else if ((HWND)lparam == button1) {
			if (thread) {
				stop();
				state = 0;
				SetWindowTextA(button, "Initiate autoclicker");
				SetWindowTextA(button1, "Initiate consistent autoclicker");
			}
			if (!cstate || cstate == 1) {
				thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&consistent, NULL, 0, NULL);
				if (!thread) {
					MessageBoxA(hwnd, "Error creating thread", "Autoclicker initiation", MB_OK);
				}
				SetWindowTextA(button1, "Stop autoclicker");
				state = 2;
			}
			SetFocus(hwnd);
		}
		else if((HWND)lparam == button2) {
			char txt[12] = {};
			GetWindowTextA(txtbox, txt, sizeof(txt));
			int t = atoi(txt);
			if (t == 0) {
				MessageBoxA(hwnd, "Error: Invalid input nothing has changed", "Timesleep change", MB_OK);
			}else if (txt[10]) {
				MessageBoxA(hwnd, "Error: Input greater than 10 characters nothing has changed", "Timesleep change", MB_OK);
			}
			else {
				timesleep = t;
			}
			SetWindowText(txtbox, NULL);
			SetFocus(hwnd);
		}
		else if ((HWND)lparam == button3) {
			getkey = true;
			SetWindowTextA(button3, "Press a key");
			SetFocus(hwnd);
		}
		break;
	}
	case WM_KEYDOWN:
		if (getkey) {
			if (code != int(wparam)) {
				code = int(wparam);
				getkey = false;
				MessageBoxA(hwnd, "Keybind changed", "Keybind change", MB_OK);
			}
			else {
				getkey = false;
				MessageBoxA(hwnd, "Keybind already set to the key you pressed. Nothing has changed.", "Keybind change", MB_OK);
			}
			SetWindowTextA(button3, "Change keybind");
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
