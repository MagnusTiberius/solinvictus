#include "MsiConfig.h"


MsiConfig::MsiConfig()
{
}


MsiConfig::~MsiConfig()
{
}


void MsiConfig::UiAutoInstallValidate()
{
	HWND installDialog = uiauto.findWindow((LPARAM)TEXT("User Account Control"));
	if (installDialog != NULL)
	{
		std::cout << "Window found, closing it now." << std::endl;
		EnumChildWindows(installDialog, uiauto.ClickButton, (LPARAM)TEXT("Yes"));
	}
	HWND errorDialog = uiauto.findWindow((LPARAM)TEXT("Telemetry Stand-Alone 2.0"));
	if (errorDialog != NULL)
	{
		std::cout << "Window found, closing it now." << std::endl;
		EnumChildWindows(errorDialog, uiauto.ClickButton, (LPARAM)TEXT("OK"));
	}
	else {
		//std::cout << "Window not found, window text has changed, please update text." << std::endl;
	}

}

void MsiConfig::UiAutoUninstallValidate()
{
	HWND installItDialog = uiauto.findWindow((LPARAM)TEXT("Windows Installer"));
	if (installItDialog != NULL)
	{
		std::cout << "Window found, closing it now." << std::endl;
		EnumChildWindows(installItDialog, uiauto.ClickButton, (LPARAM)TEXT("Yes"));
	}
	Sleep(3000);
	HWND askDialog = uiauto.findWindow((LPARAM)TEXT("Telemetry Stand-Alone 2.0"));
	if (askDialog != NULL)
	{
		//EnumChildWindows(askDialog, uiauto.SetCheckButton, (LPARAM)TEXT("Do not close applications. (A Reboot may be required.)"));
		//uiauto.typeKey(VK_MENU);
		uiauto.typeKeys((LPARAM)TEXT("%n"));
		Sleep(2000);
		std::cout << "Window found, closing it now." << std::endl;
		EnumChildWindows(askDialog, uiauto.ClickButton, (LPARAM)TEXT("OK"));
	}
	Sleep(1000);
	HWND errDialog = uiauto.findWindow((LPARAM)TEXT("Windows Installer"));
	if (errDialog != NULL)
	{
		std::cout << "Window found, closing it now." << std::endl;
		EnumChildWindows(errDialog, uiauto.ClickButton, (LPARAM)TEXT("OK"));
	}
	Sleep(1000);
	errDialog = uiauto.findWindow((LPARAM)TEXT("Windows Installer"));
	if (errDialog != NULL)
	{
		std::cout << "Window found, closing it now." << std::endl;
		EnumChildWindows(errDialog, uiauto.ClickButton, (LPARAM)TEXT("OK"));
	}
}

void MsiConfig::installValidate(UiAutoConfig uiautoconfig, const char* cmdparam)
{
	uiautoconfig.execute(cmdparam);
	UiAutoInstallValidate();
}

void MsiConfig::uninstallValidate(UiAutoConfig uiautoconfig, const char* cmdparam)
{
	uiautoconfig.execute(cmdparam);
	UiAutoUninstallValidate();
}

void MsiConfig::verifyFile(IasVersion iasversion, const wchar_t *strname)
{
	wchar_t fileVersion[1024];
	wchar_t productVersion[1024];
	memset(fileVersion, '\0', 1024);
	memset(productVersion, '\0', 1024);
	DWORD res = iasversion.PrintFileVersion(strname, fileVersion, productVersion);
	if (res == 0) {
		std::wcout << "file: " << strname << std::endl;
		std::wcout << "\tproduct version:" << productVersion << std::endl;
		std::wcout << "\tfile version:" << fileVersion << std::endl;
	}
	else
	{
		std::wcout << "file not found: " << strname << std::endl;
	}

}

void MsiConfig::verifyFiles(UiAutoConfig uiautoconfig, IasVersion iasversion, std::string name)
{
	std::string arr1[1024];
	int cnt = uiautoconfig.GetJsonValue(name, arr1);
	for (int i = 0; i < cnt; i++) {
		std::string itm = arr1[i];
		std::wstring widestr = std::wstring(itm.begin(), itm.end());
		verifyFile(iasversion, widestr.c_str());
	}
}

void MsiConfig::verifyRegistry(UiAutoConfig uiautoconfig, std::string name, const wchar_t* searchfor)
{
	std::string arr1[1024];
	int cnt = uiautoconfig.GetJsonValue(name, arr1);
	std::cout << "Printing elements of " << name << std::endl;
	for (int i = 0; i < cnt; i++) {
		std::string itm = arr1[i];
		std::wstring widestr = std::wstring(itm.begin(), itm.end());
		std::wstring elements[1024];
		WinReg winreg;
		HKEY hkey;
		int sz;
		long res = winreg.LocalMachineKey(&hkey, widestr.c_str(), elements, &sz);
		int foundcnt = 0;
		for (int i = 0; i < sz; i++) {
			std::wstring s = elements[i];
			size_t diff = 0;
			diff = wcscmp(s.c_str(), searchfor);
			if (diff == 0) {
				foundcnt++;
			}
		}
		if (foundcnt > 0) {
			std::wcout << "Found product key in registry: " << searchfor << std::endl;
		}
		else {
			std::wcout << "No product key in registry: " << searchfor << std::endl;
		}
	}

}


int MsiConfig::RunCurrentAgainstPrevious(wchar_t* current, wchar_t* previous)
{
	return 0;
}

BOOL MsiConfig::ValidateFileContent(char* szFileName, size_t siz)
{
	JsonConfig jsonconfig;
	std::wstring wstr = std::wstring(szFileName, szFileName + strlen(szFileName));
	std::string json_config = jsonconfig.ReadFileIntoStringA(wstr.c_str());
	Json::Value root;
	Json::Reader reader;
	bool res = reader.parse(json_config.c_str(), root, false);
	return res;
}



int MsiConfig::Install(lpConfigSetting cs)
{
	uiautoconfig.LoadConfig(cs->configFilename);
	cnt = uiautoconfig.GetJsonOneValue(cs->productId, &prdid);

	installValidate(uiautoconfig, cs->installName);
	std::wcout << "Install done." << std::endl;
	std::wcout << "Verifying dll file and executables:" << std::endl;
	uiautoconfig.validateFiles(cs->filesInstallExe);
	uiautoconfig.validateFiles(cs->filesInstall);
	verifyRegistry(uiautoconfig, cs->registryCompany, prdid.c_str());


	std::wcout << "Verifying dll file using loadlibrary and getprocaddress:" << std::endl;
	uiautoconfig.VerifyAddressName(cs->filesInstall, cs->addressNames);

	uiautoconfig.VerifyFunctionDefinition(cs->filesInstall, 1);
	uiautoconfig.VerifyFunctionDefinition(cs->filesInstall, 2);
	uiautoconfig.VerifyFunctionDefinition(cs->filesInstall, 3);
	uiautoconfig.VerifyFunctionDefinition(cs->filesInstall, 4);

	verifyFiles(uiautoconfig, iasversion, cs->filesInstallExe);
	verifyFiles(uiautoconfig, iasversion, cs->filesInstall);


	return 0;
}

int MsiConfig::Uninstall(lpConfigSetting cs)
{
	uiautoconfig.LoadConfig(cs->configFilename);
	cnt = uiautoconfig.GetJsonOneValue(cs->productId, &prdid);

	std::wcout << "Starting uninstall." << std::endl;
	uninstallValidate(uiautoconfig, cs->uninstallName);
	std::wcout << "Uninstall done." << std::endl;
	std::wcout << "Verifying dll file and executables:" << std::endl;
	uiautoconfig.validateFiles(cs->filesInstallExe);
	uiautoconfig.validateFiles(cs->filesInstall);
	verifyRegistry(uiautoconfig, cs->registryCompany, prdid.c_str());

	return 0;
}


