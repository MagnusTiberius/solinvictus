#pragma once
#include <windows.h>

class IasVersion
{
public:
	IasVersion();
	~IasVersion();

public:
	BOOL WINAPI GetFileVersionInfo(LPCTSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
	BOOL WINAPI GetFileVersionInfoEx(DWORD dwFlags, LPCTSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
	DWORD WINAPI GetFileVersionInfoSizeEx( DWORD dwFlags, LPCTSTR lptstrFilename, LPDWORD lpdwHandle );
	BOOL WINAPI VerQueryValue(LPCVOID pBlock, LPCTSTR lpSubBlock, LPVOID *lplpBuffer, PUINT puLen );
	DWORD PrintFileVersion(const TCHAR *pszFilePath, TCHAR *pszFileVersion, TCHAR *pszProductVersion);

private:
	BOOL IasVersion::IsWow64();

	typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process;

};

