#include "IasVersion.h"
#include "stdlib.h"
#include "stdio.h"


IasVersion::IasVersion()
{
}


IasVersion::~IasVersion()
{
}


BOOL WINAPI IasVersion::GetFileVersionInfo(LPCTSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
	BOOL res = ::GetFileVersionInfo(lptstrFilename, dwHandle, dwLen, lpData);
	return res;
}

BOOL WINAPI IasVersion::GetFileVersionInfoEx(DWORD dwFlags, LPCTSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
	BOOL res = ::GetFileVersionInfoEx(dwFlags, lptstrFilename, dwHandle, dwLen, lpData);
	return res;
}

DWORD WINAPI IasVersion::GetFileVersionInfoSizeEx(DWORD dwFlags, LPCTSTR lptstrFilename, LPDWORD lpdwHandle)
{
	DWORD res = ::GetFileVersionInfoSizeEx(dwFlags, lptstrFilename, lpdwHandle);
	return res;
}

BOOL WINAPI IasVersion::VerQueryValue(LPCVOID pBlock, LPCTSTR lpSubBlock, LPVOID *lplpBuffer, PUINT puLen)
{
	BOOL res = ::VerQueryValue(pBlock, lpSubBlock, lplpBuffer, puLen);
	return res;
}

DWORD IasVersion::PrintFileVersion(const TCHAR *pszFilePath, TCHAR *pszFileVersion, TCHAR *pszProductVersion)
{
	DWORD               dwSize = 0;
	BYTE                *pbVersionInfo = NULL;
	VS_FIXEDFILEINFO    *pFileInfo = NULL;
	UINT                puLenFileInfo = 0;

	// get the version info for the file requested
	dwSize = GetFileVersionInfoSize(pszFilePath, NULL);
	if (dwSize == 0)
	{
		printf("\nError in GetFileVersionInfoSize: %d\n", GetLastError());
		return 1;
	}

	pbVersionInfo = new BYTE[dwSize];
	memset(pbVersionInfo, '\0', dwSize);

	if (!GetFileVersionInfo(pszFilePath, 0, dwSize, pbVersionInfo))
	{
		printf("\nError in GetFileVersionInfo: %d\n", GetLastError());
		delete[] pbVersionInfo;
		return 1;
	}

	if (!VerQueryValue(pbVersionInfo, TEXT("\\"), (LPVOID*)&pFileInfo, &puLenFileInfo))
	{
		printf("\nError in VerQueryValue: %d\n", GetLastError());
		delete[] pbVersionInfo;
		return 1;
	}

	// pFileInfo->dwFileVersionMS is usually zero. However, you should check
	// this if your version numbers seem to be wrong

	/*
	swprintf_s(pszFileVersion, 1024, L"%d.%d.%d.%d",
		(pFileInfo->dwFileVersionLS >> 24) & 0xff,
		(pFileInfo->dwFileVersionLS >> 16) & 0xff,
		(pFileInfo->dwFileVersionLS >> 8) & 0xff,
		(pFileInfo->dwFileVersionLS >> 0) & 0xff
		);
	*/

	swprintf_s(pszFileVersion, 1024, L"%d.%d.%d.%d",
		(pFileInfo->dwFileVersionMS >> 16) & 0xffff,
		(pFileInfo->dwFileVersionMS >> 0 ) & 0xffff,
		(pFileInfo->dwFileVersionLS >> 16) & 0xffff,
		(pFileInfo->dwFileVersionLS >> 0 ) & 0xffff
		);


	// pFileInfo->dwProductVersionMS is usually zero. However, you should check
	// this if your version numbers seem to be wrong

	swprintf_s(pszProductVersion, 1024, L"%d.%d.%d.%d",
		(pFileInfo->dwProductVersionMS >> 16) & 0xffff,
		(pFileInfo->dwProductVersionMS >> 0 ) & 0xffff,
		(pFileInfo->dwProductVersionLS >> 16) & 0xffff,
		(pFileInfo->dwProductVersionLS >> 0 ) & 0xffff
		);


	if (IsWow64())
	{
		// 64 bit build
		DWORD major = (pFileInfo->dwProductVersionMS >> 16) & 0xff;
		DWORD minor = (pFileInfo->dwProductVersionMS >> 0) & 0xff;
		DWORD revision = (pFileInfo->dwProductVersionLS >> 16) & 0xff;
		DWORD build = (pFileInfo->dwProductVersionLS >> 0) & 0xff;
		//printf("Version 64-bit build: %d.%d.%d.%d\n", major, minor, revision, build);
	}
	else
	{
		// 32 bit build
		DWORD major = HIWORD(pFileInfo->dwProductVersionMS);
		DWORD minor = LOWORD(pFileInfo->dwProductVersionMS);
		DWORD revision = HIWORD(pFileInfo->dwProductVersionLS);
		DWORD build = LOWORD(pFileInfo->dwProductVersionLS);
		//printf("Version 64-bit build: %d.%d.%d.%d\n", major, minor, revision, build);
	}
	return 0;
}


BOOL IasVersion::IsWow64()
{
	BOOL bIsWow64 = FALSE;

	//IsWow64Process is not available on all supported versions of Windows.
	//Use GetModuleHandle to get a handle to the DLL that contains the function
	//and GetProcAddress to get a pointer to the function if available.

	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
		GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
		{
			// Handle error...
		}
	}
	return bIsWow64;
}

// http://stackoverflow.com/questions/940707/how-do-i-programatically-get-the-version-of-a-dll-or-exe-file
//