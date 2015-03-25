#pragma once
#include <windows.h>
#include <stdlib.h>
#include <iostream>
class WinReg
{
public:
	WinReg();
	~WinReg();

public:
	long LocalMachineKey(HKEY *hk, const wchar_t* path, std::wstring elements[], int* size);
	long GetRegValue(HKEY *hk, wchar_t* path, wchar_t* subkey, wchar_t* value, wchar_t* buffer, DWORD *dlen);

private:
	HKEY hk;

};

