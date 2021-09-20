#pragma once
#include <Windows.h>
using namespace std;
extern int timesleep;
extern HANDLE thread;
extern int code;
void consistent();
void fast();
void stop();
extern INPUT on[1];
extern INPUT off[1];
extern MOUSEINPUT clickon;
extern MOUSEINPUT clickoff;
extern LARGE_INTEGER frequency;
