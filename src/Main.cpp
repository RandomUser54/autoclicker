#include "Header.h"
int timesleep = 10;
string inp;
HANDLE thread;
int main() {
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
			stop();
		}
		else if (inp == "exit") {
			stop();
			return 0;
		}
	}
	return 0;
}
