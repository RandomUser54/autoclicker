#include "Header.h"
int timesleep = 10;
string inp;
HANDLE thread;
int main() {
	clickon.dwFlags = MOUSEEVENTF_LEFTDOWN;
	clickoff.dwFlags = MOUSEEVENTF_LEFTUP;
	on[0].type,off[0].type = INPUT_MOUSE;
	on[0].mi = clickon;
	off[0].mi = clickoff;
	cout << "help - Display list of commands" << endl << "cauto - Autoclicker with equal timings between each click (Keybind is ` or the ~ key)" << endl << "auto - Autoclicker optimized for fastest clicking (Keybind is ` or the ~ key)" << endl << "stop - Stops the autoclicker thread making the keybind do nothing until further input" << endl << "exit - Closes the program" << endl;
	while (true) {
		cout << "> ";
		cin >> inp;
		if (inp == "help") {
			cout << "help - Display list of commands" << endl << "sauto - Autoclicker with equal timings between each click (Keybind is ` or the ~ key)" << endl << "auto - Autoclicker optimized for fastest clicking (Keybind is ` or the ~ key)" << endl << "stop - Stops the autoclicker thread making the keybind do nothing until further input" << endl << "exit - Closes the program" << endl;
		}
		else if (inp == "cauto") {
			if (thread) {
				stop();
			}
			thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&consistent, NULL, 0, NULL);
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
			thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&fast, NULL, 0, NULL);
			if (thread) {
				cout << "Successfully created thread" << endl;
			}
			else {
				cout << "Error creating thread" << endl;
			}
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
