#include "Header.h"
int timesleep = 10;
string inp;
HANDLE thread;
int code = 0xC0;
int main() {
	clickon.dwFlags = MOUSEEVENTF_LEFTDOWN;
	clickoff.dwFlags = MOUSEEVENTF_LEFTUP;
	on[0].type,off[0].type = INPUT_MOUSE;
	on[0].mi = clickon;
	off[0].mi = clickoff;
	cout << "help - Display list of commands" << endl << endl << "cauto - Autoclicker with equal timings between each click (Default keybind is ` or the ~ key)" << endl << endl << "auto - Autoclicker optimized for fastest clicking (Default keybind is ` or the ~ key)" << endl << endl << "stop - Stops the autoclicker thread making the keybind do nothing until further input" << endl << endl << "changek - Change the keybind that will trigger the autoclicker. Make sure you enter a windows virtual keycode. (Found at https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)" << endl << endl << "changets - Changes the amount of time the program waits between each click in milliseconds. The fast autoclicker sleeps once per click. (Default is 10) Don't set to 0 or your computer won't function correctly with the consistent autoclicker. The consistent autoclicker waits twice with each click, so the consistent autoclicker will sleep for twice the time you enter." << endl << endl << "exit - Closes the program" << endl;
	while (true) {
		cout << "> ";
		cin >> inp;
		if (inp == "help") {
			cout << "help - Display list of commands" << endl << endl << "cauto - Autoclicker with equal timings between each click (Default keybind is ` or the ~ key)" << endl << endl << "auto - Autoclicker optimized for fastest clicking (Default keybind is ` or the ~ key)" << endl << endl << "stop - Stops the autoclicker thread making the keybind do nothing until further input" << endl << endl << "changek - Change the keybind that will trigger the autoclicker. Make sure you enter a windows virtual keycode. (Found at https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)" << endl << endl << "changets - Changes the amount of time the program waits between each click in milliseconds. The fast autoclicker sleeps once per click. (Default is 10) Don't set to 0 or your computer won't function correctly with the consistent autoclicker. The consistent autoclicker waits twice with each click, so the consistent autoclicker will sleep for twice the time you enter." << endl << endl << "exit - Closes the program" << endl;
		}
		else if (inp == "cauto") {
			if (thread) {
				stop();
			}
			thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&consistent, (LPVOID)code, 0, NULL);
			if (thread) {
				cout << "Successfully created thread" << endl;
			}
			else {
				cout << "Error creating thread" << endl;
			}
		}
		else if (inp == "auto") {
			if (thread) {
				stop();
			}
			thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&fast, (LPVOID)code, 0, NULL);
			if (thread) {
				cout << "Successfully created thread" << endl;
			}
			else {
				cout << "Error creating thread" << endl;
			}
		}
		else if (inp == "changek") {
			cout << "Enter the virtual keycode." << endl;
			cin >> hex >> code;
			cout << code << endl;
			cout << "Keybind changed" << endl;
		}
		else if(inp == "changets"){
			cout << "Enter the amount of time to sleep in milliseconds." << endl;
			cin >> dec >> timesleep;
			cout << "Changed timesleep to " << timesleep << "." << endl;
		}
		else if (inp == "stop") {
			if (!thread) {
				cout << "No thread to stop" << endl;
			}
			else {
				stop();
				cout << "Successfully terminated thread" << endl;
			}
		}
		else if (inp == "exit") {
			if (thread) {
				stop();
			}
			return 0;
		}
		else {
			cout << "Invalid input" << endl;
		}
	}
	return 0;
}
