#pragma once
#include "UIAuto.h"
#include "SetupRepo.h"
#include "CommandMsiExec.h"

class UiAutoConfig
{
public:
	UiAutoConfig();
	UiAutoConfig(wchar_t* jsonfile);
	~UiAutoConfig();

public:
	DWORD execute(std::string cmdkey);
	DWORD validateFiles(std::string str);

private:
	Json::Value root;
	UIAuto uiauto;
	SetupRepo setuprepo;
	JsonConfig jsonconfig;
	std::string json_config;

	//const std::string jcfg;
};

