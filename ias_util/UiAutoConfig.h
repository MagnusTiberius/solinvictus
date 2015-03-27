#pragma once
#include "UIAuto.h"
#include "SetupRepo.h"
#include "CommandMsiExec.h"
#include "Dll.h"

#include "stdafx.h"

class UiAutoConfig
{
public:
	UiAutoConfig();
	UiAutoConfig(wchar_t* jsonfile);
	~UiAutoConfig();

public:
	DWORD execute(std::string cmdkey);
	DWORD validateFiles(std::string str);
	DWORD GetJsonValue(std::string cmdkey, std::string arr[]);
	DWORD VerifyAddressName(char* dllfile, char* procnames);
	DWORD GetJsonOneValue(std::string cmdkey, std::wstring *ws);
	DWORD UiAutoConfig::VerifyFunctionDefinition(char* dllfile, int actiontotake);
	DWORD LoadConfig(wchar_t* jsonfile);

private:
	Json::Value root;
	UIAuto uiauto;
	SetupRepo setuprepo;
	JsonConfig jsonconfig;
	std::string json_config;
	Dll dll;

	//const std::string jcfg;
};

