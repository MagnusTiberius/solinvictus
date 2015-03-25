#pragma once
#include "stdafx.h"
#include "ReadDirectoryChanges.h"
#include "SharedFile.h"

class DirChange
{
public:
	DirChange();
	~DirChange();

	bool DirChange::TryGetKeyboardInput(HANDLE hStdIn, bool &bTerminate, char* buf, size_t siz);
	LPCWSTR DirChange::ExplainAction(DWORD dwAction);
	int DirChange::Run();

	void AddDirectory(std::wstring wszDirectory, BOOL bWatchSubtree, DWORD dwNotifyFilter);

public:
	static const DWORD dwNotificationFlags =
		FILE_NOTIFY_CHANGE_LAST_WRITE
		| FILE_NOTIFY_CHANGE_CREATION
		| FILE_NOTIFY_CHANGE_FILE_NAME;


private:
	CReadDirectoryChanges changes;
	SharedFile m_sharedFile;
	
	const wchar_t* m_fileName = L"SharedFile001.txt";
	const size_t bufsiz = 1024;
	char buffer[1024];

};

