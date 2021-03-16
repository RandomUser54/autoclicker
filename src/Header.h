#pragma once
#include <Windows.h>
#include <iostream>
using namespace std;
extern int timesleep;
extern HANDLE thread;
void consistent();
void fast();
void stop();
extern INPUT on[1];
extern INPUT off[1];
extern MOUSEINPUT clickon;
extern MOUSEINPUT clickoff;
extern int code;
