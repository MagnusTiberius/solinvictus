#include "SharedFile.h"


SharedFile::SharedFile()
{
}

SharedFile::~SharedFile()
{
	::CloseHandle(hFile);
}

BOOL SharedFile::Init(const wchar_t* szFileName, char* buffer, size_t siz)
{
	m_szFileName = szFileName;
	memset(buffer, '\0', siz);
	m_buffer = buffer;
	m_siz = siz;
	hFile = ::CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	return true;
}

BOOL SharedFile::Read(char* buffer, size_t siz)
{
	memset(buffer, '\0', siz);
	DWORD dwXfer = 0;
	::SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
	BOOL res = ::ReadFile(hFile, (LPVOID)buffer, siz, &dwXfer, NULL);
	return res;
}

BOOL SharedFile::Write(const char* buffer, size_t siz)
{
	DWORD dwXfer = 0;
	::SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
	BOOL res = ::WriteFile(hFile, (LPCVOID)buffer, siz, &dwXfer, NULL);
	return res;
}
