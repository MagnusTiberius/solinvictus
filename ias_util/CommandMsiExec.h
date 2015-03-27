#pragma once
#include "stdafx.h"

#include "UIAuto.h"
#include "SetupRepo.h"

class CommandMsiExec
{
public:
	CommandMsiExec(UIAuto *puiauto, JsonConfig *pjsonconfig);
	~CommandMsiExec();

	DWORD execute(std::string strcmd);

private:
	UIAuto *uiauto;
	std::string str;
	JsonConfig *jsonconfig;
};

