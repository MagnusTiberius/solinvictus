#pragma once
#include "stdafx.h"
#include "UIAuto.h"
#include "SetupRepo.h"
#include "CommandMsiExec.h"
#include "UiAutoConfig.h"
#include "WinReg.h"
#include "IasVersion.h"


typedef struct configSetting{
	wchar_t* configFilename;
	char* installName;
	char* filesInstall;
	char* filesInstallExe;
	char* uninstallName;
	char* registryCompany;
	char* addressNames;
	char* productId;
} ConfigSetting, *lpConfigSetting;


class MsiConfig
{
public:
	MsiConfig();
	~MsiConfig();

	int Install(lpConfigSetting configSetting);
	int Uninstall(lpConfigSetting cs);
	BOOL ValidateFileContent(char* szFileName, size_t siz);

private:
	void UiAutoInstallValidate();
	void UiAutoUninstallValidate();
	void installValidate(UiAutoConfig uiautoconfig, const char* cmdparam);
	void uninstallValidate(UiAutoConfig uiautoconfig, const char* cmdparam);
	void verifyFile(IasVersion iasversion, const wchar_t *strname);
	void verifyFiles(UiAutoConfig uiautoconfig, IasVersion iasversion, std::string name);
	void verifyRegistry(UiAutoConfig uiautoconfig, std::string name, const wchar_t* searchfor);
	int RunCurrentAgainstPrevious(wchar_t* current, wchar_t* previous);


private:
	UIAuto uiauto;
	std::wstring prdid;
	UiAutoConfig uiautoconfig;
	IasVersion iasversion;
	wchar_t* configFileCurrentVer;
	int cnt;

#if defined(_WIN64)
	const int PLATFORM = 64;
#else
	const int PLATFORM = 86;
#endif


};

