#include "UIAuto.h"


UIAuto::UIAuto()
{
}


UIAuto::~UIAuto()
{
}


void CALLBACK UIAuto::PrintWindowName(HWND hwnd, LPARAM callerText)
{
	LPWSTR windowText = new TCHAR[2048];
	GetWindowText(hwnd, windowText, 2048);
	wcout << "CALLERTEXT:" << callerText << ":WINDOWTEXT:" << windowText << endl;
}

BOOL CALLBACK UIAuto::ClickButton(HWND hwnd, LPARAM buttonText)
{
	LPWSTR windowText = new TCHAR[2048];
	GetWindowText(hwnd, windowText, 2048);
	//cout << "WINDOWTEXT:" << windowText << endl;
	if (_tcsstr(windowText, LPCTSTR(buttonText)) != NULL)
	{
		SendMessage(hwnd, BM_CLICK, 0, 0);
		wcout << "BUTTONSELECTED:" << windowText << endl;
	}
	return true;
}

void UIAuto::selectMenuItem(HWND hwnd, HMENU menu, LPARAM menuText)
{
	int menuCount = GetMenuItemCount(menu);
	for (int i = 0; i<menuCount; i++)
	{
		LPWSTR menuString = new TCHAR[2048];
		GetMenuString(menu, i, menuString, 2048, MF_BYPOSITION);
		//cout << "MENUSTRING:" << menuString << endl;
		if (_tcsstr(menuString, LPCTSTR(menuText)) != NULL)
		{
			int menuItemID = GetMenuItemID(menu, i);
			PostMessage(hwnd, WM_COMMAND, menuItemID, 0);
			wcout << "MENUSELECTED:" << menuItemID << ":OF:" << menuCount << endl;
			return;
		}
	}
}

void UIAuto::typeKey(short virtualKey)
{
	// Set up a generic keyboard event.
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;// Press the "A" key
	ip.ki.wVk = virtualKey; // virtual-key code for the character
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));// Release the character key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
}

void UIAuto::typeKeys(LPARAM stringToType)
{
	LPTSTR stringToTypeMod = (LPTSTR)stringToType;
	for (int i = 0; i<_tcslen(stringToTypeMod); i++)
	{
		typeKey(VkKeyScan(stringToTypeMod[i]));
	}
}

HMENU UIAuto::findMenu(HMENU menu, LPARAM menuText) //TCHAR menuText[ 2048 ] = "File";
{
	int menuCount = GetMenuItemCount(menu);
	for (int i = 0; i<menuCount; i++)
	{
		LPWSTR menuString = new TCHAR[2048];
		GetMenuString(menu, i, menuString, 2048, MF_BYPOSITION);
		if (_tcsstr(menuString, LPCTSTR(menuText)) != NULL)
		{
			wcout << "FOUND:" << menuString << endl;
			return GetSubMenu(menu, i);
		}
	}
	return NULL;
}

HWND UIAuto::findWindow(LPARAM windowTitle) //TCHAR windowTitle[ 2048 ] = "Untitled - Notepad";
{ // Should iterate through all windows and find a window matching title without the need for an exact match.
	HWND notepadHandle = FindWindow(0, LPCTSTR(windowTitle));
	TCHAR title[250];
	GetWindowText(notepadHandle, title, 250);
	//wcout << "TITLE:" << title << endl;
	return notepadHandle;
}

bool UIAuto::isProcessRunning(LPARAM processText) //TCHAR processText[ 2048 ] = "notepad.exe";
{
	LPCTSTR pt = LPCTSTR(processText);
	bool retVal = false;
	DWORD aProcesses[2048];
	DWORD cbNeeded;
	//DWORD cProcesses;
	EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded); // Stores all processes in array aProcesses
	for (int i = 0; i < 2048; i++) // iterate over all processes in the array
	{
		DWORD processID = aProcesses[i];
		TCHAR processName[1024];
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ, FALSE, processID); // Get process handle from process id
		GetModuleFileNameEx(hProcess, NULL, processName, 2048);  // Get process name from process handle
		if (_tcsstr(processName, pt) != NULL) // Check if processName matches processText
		{
			wcout << ":PROCESSNAME:" << processName << endl;
			retVal = true;
		}
	}

	return retVal;
}

DWORD UIAuto::startProcess(wchar_t* processPath) //TCHAR processPath[ 2048 ] = "C:\\Windows\\System32\\notepad.exe";
{
	//
	// Read this article why processPath type is defined that way.
	// http://blogs.microsoft.co.il/pavely/2010/01/17/gotcha-createprocess-causes-access-violation/
	// http://blogs.msdn.com/b/oldnewthing/archive/2009/06/01/9673254.aspx
	//
	//HWND                hWnd;
	STARTUPINFO         sInfo;
	PROCESS_INFORMATION pInfo;

	ZeroMemory(&sInfo, sizeof(sInfo));
	sInfo.cb = sizeof(sInfo);
	ZeroMemory(&pInfo, sizeof(pInfo));

	auto res = CreateProcess(NULL, processPath, NULL, NULL, FALSE,
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
		NULL, NULL, &sInfo, &pInfo);

	if (res)
	{
		printf("Sleeping 500ms...\n");
		Sleep(500);

		DWORD dwExitCode;
		GetExitCodeProcess(pInfo.hProcess, &dwExitCode);
		printf("GetExitCodeProcess dwExitCode = 0x%x, = %d...\n", dwExitCode, dwExitCode);

		CloseHandle(pInfo.hThread);
		CloseHandle(pInfo.hProcess);
		return dwExitCode;
	}

	return 0;

	/*
	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;
	LPSECURITY_ATTRIBUTES lpProcessAttributes;
	SECURITY_ATTRIBUTES sa;

	PSECURITY_DESCRIPTOR pSD = NULL;
	pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
	InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION);

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;
	sa.lpSecurityDescriptor = NULL;
	CreateProcess(NULL, (LPTSTR)processPath, &sa, NULL, TRUE, 0, NULL, NULL, &info, &processInfo); // Creates a new process, storing information in info,processInfo
	::WaitForSingleObject(processInfo.hProcess, 1000); // Wait x seconds for process to start
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
	cout << "FINISHED OPENDING PROCESS:" << processPath << endl;
	*/
}


int UIAuto::Run(int argc, _TCHAR* argv[])
{
	if (isProcessRunning((LPARAM)TEXT("notepad.exe")))
	{
		cout << "YOU SHOULD STOP NOTEPAD BEFORE RUNNING THIS CODE" << endl;
		exit(0);
	}


	cout << "MAIN START VERSION 11" << endl;

	// Start notepad
	//startProcess((LPARAM)TEXT("C:\\Windows\\System32\\notepad.exe"));
	//startProcess((LPARAM)TEXT("C:\\Users\\bbgonzaX\\Documents\\Visual Studio 2012\\Projects\\MFCApplication1\\Debug\\MFCApplication1.exe"));
	TCHAR name1[] = _T("C:\\Windows\\System32\\notepad.exe");
	startProcess(name1);
	HWND notepadHandle = findWindow((LPARAM)TEXT("Untitled - Notepad"));

	// Type some keys in notepad
	typeKey(VK_TAB);
	Sleep(3000);

	// Type some more keys in notepad
	typeKeys((LPARAM)TEXT("The cat in the hat was running with a bat."));
	Sleep(3000);

	// Select File->Save As
	HMENU fileMenu = findMenu(GetMenu(notepadHandle), (LPARAM)TEXT("File"));
	selectMenuItem(notepadHandle, fileMenu, (LPARAM)TEXT("Save &As"));
	Sleep(3000);

	// Enter a filename
	typeKeys((LPARAM)TEXT("NewTextFile.txt"));
	Sleep(3000);

	// If file already exists, clicking Save will block the invoking thread, so we will click Save on a separate thread
	//DWORD dwThreadId;
	//CreateThread(NULL, 0, MyThreadFunction, NULL, 0, &dwThreadId);
	//Sleep(1000);

	// If file already exists, we will not confirm the Save As operation
	HWND alreadyExistsDialog = findWindow((LPARAM)TEXT("Confirm Save As"));
	if (alreadyExistsDialog != NULL)
	{
		cout << "Confirm Save As: ... already exists.  Do you want to replace it?...  Clicking No" << endl;
		EnumChildWindows(alreadyExistsDialog, ClickButton, (LPARAM)TEXT("No")); // Don't Save if the file already exists
		Sleep(1000);
	}

	// If file already exists, we will cancel the Save As operation
	alreadyExistsDialog = findWindow((LPARAM)TEXT("Save As"));
	if (alreadyExistsDialog != NULL)
	{
		cout << "Save As: ...  Clicking Cancel" << endl;
		EnumChildWindows(alreadyExistsDialog, ClickButton, (LPARAM)TEXT("Cancel")); // Don't Save if the file already exists
		Sleep(1000);
	}

	// Exit Notepad
	selectMenuItem(notepadHandle, fileMenu, (LPARAM)TEXT("E&xit"));
	Sleep(1000);

	// If file already exists, we will not save changes
	alreadyExistsDialog = findWindow((LPARAM)TEXT("Notepad"));
	if (alreadyExistsDialog != NULL)
	{
		cout << "Notepad: Do you want to save changes to Untitled...  Clicking Don't Save" << endl;
		EnumChildWindows(alreadyExistsDialog, ClickButton, (LPARAM)TEXT("Do&n't Save")); // Don't Save if the file already exists
		Sleep(1000);
	}

	cout << "MAIN FINISH" << endl;

	return 0;
}
