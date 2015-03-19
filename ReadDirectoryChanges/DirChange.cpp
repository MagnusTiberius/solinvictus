#include "stdafx.h"
#include "DirChange.h"


DirChange::DirChange()
{
}


DirChange::~DirChange()
{
}


void DirChange::AddDirectory(LPCTSTR szDirectory, BOOL bWatchSubtree, DWORD dwNotifyFilter)
{
	changes.AddDirectory(szDirectory, bWatchSubtree, dwNotifyFilter);
}


int DirChange::Run()
{


	HANDLE hStdIn = ::GetStdHandle(STD_INPUT_HANDLE);
	const HANDLE handles[] = { hStdIn, changes.GetWaitHandle() };

	char buf[MAX_PATH];
	bool bTerminate = false;

	while (!bTerminate)
	{
		DWORD rc = ::WaitForMultipleObjectsEx(_countof(handles), handles, false, INFINITE, true);
		switch (rc)
		{
		case WAIT_OBJECT_0 + 0:
			// hStdIn was signaled. This can happen due to mouse input, focus change,
			// Shift keys, and more.  Delegate to TryGetKeyboardInput().
			// TryGetKeyboardInput sets bTerminate to true if the user hits Esc.
			if (TryGetKeyboardInput(hStdIn, bTerminate, buf))
				changes.AddDirectory(CStringW(buf), false, dwNotificationFlags);
			break;
		case WAIT_OBJECT_0 + 1:
			// We've received a notification in the queue.
		{
			DWORD dwAction;
			CStringW wstrFilename;
			if (changes.CheckOverflow())
				wprintf(L"Queue overflowed.\n");
			else
			{
				changes.Pop(dwAction, wstrFilename);
				wprintf(L"%s %s\n", ExplainAction(dwAction), wstrFilename);
			}
		}
			break;
		case WAIT_IO_COMPLETION:
			// Nothing to do.
			break;
		}
	}

	// Just for sample purposes. The destructor will
	// call Terminate() automatically.
	changes.Terminate();

	return EXIT_SUCCESS;
}

LPCWSTR DirChange::ExplainAction(DWORD dwAction)
{
	switch (dwAction)
	{
	case FILE_ACTION_ADDED:
		return L"Added";
	case FILE_ACTION_REMOVED:
		return L"Deleted";
	case FILE_ACTION_MODIFIED:
		return L"Modified";
	case FILE_ACTION_RENAMED_OLD_NAME:
		return L"Renamed From";
	case FILE_ACTION_RENAMED_NEW_NAME:
		return L"Renamed To";
	default:
		return L"BAD DATA";
	}
}

bool DirChange::TryGetKeyboardInput(HANDLE hStdIn, bool &bTerminate, char* buf)
{
	DWORD dwNumberOfEventsRead = 0;
	INPUT_RECORD rec = { 0 };

	if (!::PeekConsoleInput(hStdIn, &rec, 1, &dwNumberOfEventsRead))
		return false;

	if (rec.EventType == KEY_EVENT)
	{
		if (rec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
			bTerminate = true;
		else if (rec.Event.KeyEvent.wVirtualKeyCode > VK_HELP)
		{
			if (!gets(buf))	// End of file, usually Ctrl-Z
				bTerminate = true;
			else
				return true;
		}
	}

	::FlushConsoleInputBuffer(hStdIn);

	return false;
}
