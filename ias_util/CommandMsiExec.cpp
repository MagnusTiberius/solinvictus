#include "CommandMsiExec.h"


CommandMsiExec::CommandMsiExec(UIAuto *puiauto, JsonConfig *pjsonconfig)
{
	uiauto = puiauto;
	jsonconfig = pjsonconfig;
}


CommandMsiExec::~CommandMsiExec()
{
}


DWORD CommandMsiExec::execute(std::string strcmd)
{
	if (strlen(strcmd.c_str()) == 0)
	{
		std::cout << "No command found." << std::endl;
		return 0;
	}
	else
	{
		std::cout << "command: " << strcmd << std::endl;
	}

	const wchar_t* cmd = jsonconfig->GetWC(strcmd.c_str());
	DWORD ret = uiauto->startProcess((wchar_t*)cmd);
	std::cout << "CommandMsiExec " << ret << std::endl;
	Sleep(2000);
	return ret;
}