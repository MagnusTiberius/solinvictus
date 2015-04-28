#pragma once
#include "stdafx.h"

#include <windows.h>


class IasVersion
{
public:
	IasVersion();
	~IasVersion();

	typedef struct {
		WORD  wLength;
		WORD  wValueLength;
		WORD  wType;
		WCHAR szKey;
		WORD  Padding;
		DWORD Value;
	} Var1;

	typedef struct {
		WORD  wLength;
		WORD  wValueLength;
		WORD  wType;
		WCHAR szKey;
		WORD  Padding;
		WORD  Value;
	} String1;

	typedef struct {
		WORD   wLength;
		WORD   wValueLength;
		WORD   wType;
		WCHAR  szKey;
		WORD   Padding;
		String1 Children;
	} StringTable2;

	struct LANGANDCODEPAGE {
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;

public:
	BOOL WINAPI GetFileVersionInfo(LPCTSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
	BOOL WINAPI GetFileVersionInfoEx(DWORD dwFlags, LPCTSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
	DWORD WINAPI GetFileVersionInfoSizeEx(DWORD dwFlags, LPCTSTR lptstrFilename, LPDWORD lpdwHandle);
	BOOL WINAPI VerQueryValue(LPCVOID pBlock, LPCTSTR lpSubBlock, LPVOID *lplpBuffer, PUINT puLen);
	DWORD PrintFileVersion(const TCHAR *pszFilePath, TCHAR *pszFileVersion, TCHAR *pszProductVersion);
	DWORD PrintFileVersion2(const TCHAR *pszFilePath, std::vector<std::pair<std::wstring, std::wstring>> *wlist);

private:
	BOOL IasVersion::IsWow64();

	typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process;

};

