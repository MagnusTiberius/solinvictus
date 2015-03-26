#pragma once

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <Windows.h>
#include <direct.h>
#include "..\jsoncpp\include\json\json.h"

class JsonConfig
{
public:
	JsonConfig();
	~JsonConfig();

	JsonConfig(const std::wstring& filepath);

	std::wstring ReadFileIntoStringW(const std::wstring& filepath);
	std::string ReadFileIntoStringA(const std::wstring& filepath);
	BOOL FileExist(const wchar_t* filename);
	std::string CreateDefaultConfig(const wchar_t* filename);
	std::wstring s2ws(const std::string& str);
	std::string ws2s(const std::wstring& wstr);
	const wchar_t *GetWC(const char *c);
	BOOL ParseFile(const std::wstring& filepath, Json::Value *root);
	BOOL Parse(Json::Value *root);
	BOOL Parse();

private:
	std::wstring wszFileName;
	Json::Value m_root;
};

