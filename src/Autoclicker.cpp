#include "Header.h"
INPUT on[1];
INPUT off[1];
MOUSEINPUT clickon;
MOUSEINPUT clickoff;
void consistent() {
	while (true) {
		if (GetKeyState(code) >> 15) {
			SendInput(1, on, sizeof(on[0]));
			Sleep(timesleep);
			SendInput(1, off, sizeof(off[0]));
			Sleep(timesleep);
		}
	}
}
void fast() {
	while (true) {
		if (GetKeyState(code) >> 15) {
			SendInput(1, on, sizeof(on[0]));
			Sleep(timesleep);
			SendInput(1, off, sizeof(off[0]));
		}
	}
}
void stop() {
	if (!TerminateThread(thread, 0)) {
		cout << "Error terminating thread" << endl;
	}
	thread = NULL;
}
