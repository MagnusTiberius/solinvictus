#pragma once
#include "stdafx.h"
#include "MsiConfig.h"
#include <assert.h>
#include "DirChange.h"
#include "Constants.h"
#include "ConfigWorker.h"


HANDLE hWorkerThread[2];
DWORD dwExitCode = 0;


void ReadDirChangeWorkerThread()
{
	DirChange dirChange;
	dirChange.AddDirectory(_T(FILEPATH1), false, DirChange::dwNotificationFlags);;
	dirChange.Run();
}

void ConfigWorkerThread()
{
	ConfigWorker worker;
	worker.Install();
	TerminateThread(hWorkerThread[0], dwExitCode);
}


int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwId;
	DWORD dwId2;

	hWorkerThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadDirChangeWorkerThread, 0, 0, &dwId);
	hWorkerThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ConfigWorkerThread, 0, 0, &dwId2);

	assert(hWorkerThread[0] != NULL);
	assert(hWorkerThread[1] != NULL);

	WaitForMultipleObjects(2, hWorkerThread, TRUE, INFINITE);

	std::cout << "Done" << std::endl;
	Sleep(1000);

	CloseHandle(hWorkerThread[0]);

	return 0;
}

