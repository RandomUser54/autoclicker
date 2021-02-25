#include "Header.h"
void consistent() {
	while (true) {
		if (GetAsyncKeyState(0xC0)) {
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(timesleep);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(timesleep);
		}
	}
}
void fast() {
	while (true) {
		if (GetAsyncKeyState(0xC0)) {
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(timesleep);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
	}
}
void stop() {
	if (!TerminateThread(thread, 0)) {
		cout << "Error terminating thread" << endl;
	}
	thread = NULL;
}
