#include "WinReg.h"


WinReg::WinReg()
{
}


WinReg::~WinReg()
{
}


long WinReg::LocalMachineKey(HKEY *hk, wchar_t* path, std::wstring elements[])
{
	int count = 0;
	WCHAR Temp[255];
	DWORD TMP = 255;
	long n = RegOpenKeyEx(HKEY_LOCAL_MACHINE, path, 0, KEY_ENUMERATE_SUB_KEYS, hk);
	if (n == ERROR_SUCCESS)
	{
		while ((n = RegEnumKeyEx(*hk, count, Temp, &TMP, NULL, NULL, NULL, NULL)) == ERROR_SUCCESS){
			TMP = sizeof(Temp);
			elements[count] = Temp;
			count++;
			std::wcout << count << ". " << Temp << std::endl;
		}
	}
	return n;
}

long WinReg::GetRegValue(HKEY *hk, wchar_t* path, wchar_t* subkey, wchar_t* value, wchar_t* buffer, DWORD *dlen)
{
	wchar_t folder[4096];
	memset(folder, '\0', 4096);
	DWORD dwSize = 4096 - 1;
	DWORD regval = 0;
	DWORD lpType;
	long n = RegOpenKeyEx(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, hk);
	if (n == ERROR_SUCCESS)
	{
		//long m = RegGetValue(HKEY_LOCAL_MACHINE, path, subkey, RRF_RT_ANY, NULL, (PVOID)buffer, (LPDWORD)dlen);
		long m = RegQueryValueEx(*hk, subkey, NULL, &lpType, (LPBYTE)&folder, &dwSize);
		if (lpType == REG_BINARY) {
			std::wcout << "REG_BINARY" << std::endl;
		}
		if (lpType == REG_DWORD) {
			std::wcout << "REG_DWORD" << std::endl;
		}
		if (lpType == REG_EXPAND_SZ) {
			std::wcout << "REG_EXPAND_SZ" << std::endl;
		}
		if (lpType == REG_NONE) {
			std::wcout << "REG_NONE" << std::endl;
		}
		if (lpType == REG_LINK) {
			std::wcout << "REG_LINK" << std::endl;
		}
		if (lpType == REG_QWORD) {
			std::wcout << "REG_QWORD" << std::endl;
		}
		if (lpType == REG_SZ) {
			std::wcout << "REG_SZ" << std::endl;
		}
		if (m == ERROR_SUCCESS)
		{
			std::wcout << "ok" << std::endl;
		}
		else if (m == ERROR_ACCESS_DENIED)
		{
			std::wcout << "err:" << "ERROR_ACCESS_DENIED" << std::endl;
		}
		else if (m == ERROR_FILE_NOT_FOUND)
		{
			std::wcout << "err:" << "ERROR_FILE_NOT_FOUND" << std::endl;
		}
		
		else
		{
			std::wcout << "err:" << m << std::endl;
		}
	}
	return n;
}