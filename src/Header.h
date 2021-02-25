#pragma once
#include <Windows.h>
#include <iostream>
using namespace std;
extern int timesleep;
extern HANDLE thread;
void consistent();
void fast();
void stop();
