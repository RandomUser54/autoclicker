#include "Autoclicker.h"
INPUT on[1];
INPUT off[1];
MOUSEINPUT clickon;
MOUSEINPUT clickoff;
LARGE_INTEGER frequency;
LARGE_INTEGER old;
LARGE_INTEGER n;
int timewait;
void wait(float time) {
	timewait = frequency.QuadPart * (time/1000);
	QueryPerformanceCounter(&old);
	while (n.QuadPart - old.QuadPart < timewait) {
		QueryPerformanceCounter(&n);
	}
}
void consistent() {
	while (true) {
		while (GetKeyState(code) < 0) {
			SendInput(1, on, sizeof(on[0]));
			wait(timesleep);
			SendInput(1, off, sizeof(off[0]));
			wait(timesleep);
		}
		Sleep(20);
	}
}
void fast() {
	while (true) {
		while (GetKeyState(code) < 0) {
			SendInput(1, on, sizeof(on[0]));
			wait(timesleep);
			SendInput(1, off, sizeof(off[0]));
		}
		Sleep(20);
	}
}
void stop() {
	if (!TerminateThread(thread, 0)) {
		MessageBoxA(NULL, "Error terminating thread", "Thread Termination", MB_OK);
	}
	thread = NULL;
}
