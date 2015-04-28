#pragma once
#include "stdafx.h"

#include <windows.h>


#include "IasVersion.h"
#include <regex>

#include <filesystem>

#define BUFSIZE 4096

class VersionValidate
{
public:
	VersionValidate();
	~VersionValidate();

	typedef void(*LPFunc)(std::wstring, bool *bStatus, void* LPF);

	void VisitDirectory(std::wstring dir, std::wstring filter, LPFunc anonf, bool *bStatus);

	void Validate();

	std::vector<std::wstring> EnumFiles(const std::wstring& path, const wchar_t* prefix, const wchar_t* postfix, bool fullpath);
	std::vector<std::wstring> EnumFolders(const std::wstring& path, const wchar_t* prefix, const wchar_t* postfix, bool fullpath);


private:
	char* GetContent(std::wstring wfile_name);
	WCHAR  buffer[BUFSIZE];
	WCHAR** lppPart;

};

