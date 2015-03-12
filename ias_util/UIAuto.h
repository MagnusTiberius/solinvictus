#pragma once

#include "UIAutomation.h"

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
//#include <unistd.h>
#include <Psapi.h>
#include <strsafe.h>
#include <cstring>
//#include "atlstr.h"

using namespace std;

class UIAuto
{
public:
	UIAuto();
	~UIAuto();

	static void CALLBACK PrintWindowName(HWND hwnd, LPARAM callerText);
	static BOOL CALLBACK ClickButton(HWND hwnd, LPARAM buttonText);
	void selectMenuItem(HWND hwnd, HMENU menu, LPARAM menuText);
	void typeKey(short virtualKey);
	void typeKeys(LPARAM stringToType);
	HMENU findMenu(HMENU menu, LPARAM menuText);
	HWND findWindow(LPARAM windowTitle);
	bool isProcessRunning(LPARAM processText);
	DWORD startProcess(wchar_t* processPath);
	int Run(int argc, _TCHAR* argv[]);

};

