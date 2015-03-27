#pragma once
#include "stdafx.h"

class SharedFile
{
public:
	SharedFile();
	~SharedFile();

	BOOL Init(const wchar_t* szFileName, char* buffer, size_t siz);
	BOOL Read(char* buffer, size_t siz);
	BOOL Write(const char* buffer, size_t siz);

private:
	HANDLE hFile;
	char* m_buffer; 
	size_t m_siz;
	const wchar_t* m_szFileName;
};

