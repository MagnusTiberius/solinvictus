#pragma once
#include "stdafx.h"

#include <windows.h>
#include <string.h>
#include <stdio.h>

typedef int(__stdcall *f_funci)();

class Dll
{
public:
	Dll();
	~Dll();

public:
	HINSTANCE LoadDll(const wchar_t* lpszFilePath);
	BOOL UnloadDll();
	f_funci GetDllProcAddress(const char* pszProcName);
	void CommandApiVersion();
	void CommandHasSystemConsentFeature();
	void CommandInitialize();
	void CommandDeinitialize();
	void CommandRecordEvent();
private:
	
	const wchar_t* filepath;
	HINSTANCE dll_inst;
};

