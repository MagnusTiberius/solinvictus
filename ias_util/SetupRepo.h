#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <Windows.h>
#include <direct.h>
#include "..\jsoncpp\include\json\json.h"
#include "JsonConfig.h"

#define IASQA			 "Intel IAS QA"
#define WIASQA			L"Intel IAS QA"
#define LOCALAPPDATA	 "LOCALAPPDATA"
#define WLOCALAPPDATA	L"LOCALAPPDATA"

class SetupRepo
{
public:
	SetupRepo();
	~SetupRepo();

	BOOL SetupRepo::directory_exists(const wchar_t* dirName);
	std::wstring SetupRepo::s2ws(const std::string& str);
	std::string SetupRepo::ws2s(const std::wstring& wstr);
	char* SetupRepo::get_ias_app_data_path();
	int SetupRepo::get_ias_app_data_pathw(wchar_t* iaspath, Json::Value root);
	void SetupRepo::wappend(const wchar_t* s1, wchar_t* s2, wchar_t* res, size_t count);
	void SetupRepo::CopyContent(wchar_t* source, wchar_t* dest);
	int SetupRepo::create_dir(wchar_t* dirname);
	void SetupRepo::create_dir_fragment(wchar_t* dirname, wchar_t* fragment);
	int SetupRepo::Run(int argc, _TCHAR* argv[]);

private:
	JsonConfig jsonconfig;
};

