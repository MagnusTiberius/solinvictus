// lantern_rock_install.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UIAuto.h"
#include "SetupRepo.h"
#include "CommandMsiExec.h"
#include "UiAutoConfig.h"
#include "WinReg.h"

//Json::Value root;
UIAuto uiauto;
//SetupRepo setuprepo;
//JsonConfig jsonconfig;

void UiAutoInstallValidate()
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
		std::cout << "Window not found, window text has changed, please update text." << std::endl;
	}

}

void UiAutoUninstallValidate()
{
	HWND installItDialog = uiauto.findWindow((LPARAM)TEXT("Windows Installer"));
	if (installItDialog != NULL)
	{
		std::cout << "Window found, closing it now." << std::endl;
		EnumChildWindows(installItDialog, uiauto.ClickButton, (LPARAM)TEXT("Yes"));
	}
	Sleep(2000);
	HWND errDialog = uiauto.findWindow((LPARAM)TEXT("Windows Installer"));
	if (errDialog != NULL)
	{
		std::cout << "Window found, closing it now." << std::endl;
		EnumChildWindows(errDialog, uiauto.ClickButton, (LPARAM)TEXT("OK"));
	}
	Sleep(2000);
	errDialog = uiauto.findWindow((LPARAM)TEXT("Windows Installer"));
	if (errDialog != NULL)
	{
		std::cout << "Window found, closing it now." << std::endl;
		EnumChildWindows(errDialog, uiauto.ClickButton, (LPARAM)TEXT("OK"));
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	UiAutoConfig uiautoconfig(L"LanternRockInstallConfig.json");
	uiautoconfig.execute("MSIEXEC_INSTALL_WIN32_DEBUG");
	UiAutoInstallValidate();

	uiautoconfig.execute("MSIEXEC_INSTALL_WIN32_RELEASE");
	UiAutoInstallValidate();

	uiautoconfig.execute("MSIEXEC_INSTALL_X64_DEBUG");
	UiAutoInstallValidate();

	uiautoconfig.execute("MSIEXEC_INSTALL_X64_RELEASE");
	UiAutoInstallValidate();


	uiautoconfig.validateFiles("FILES_INSTALL_X86");
	uiautoconfig.validateFiles("FILES_INSTALL_X64");

	uiautoconfig.validateFiles("FILES_INSTALL");

	return 0;

	std::wstring elements[1024];
	WinReg winreg;
	HKEY hkey;
	long res = winreg.LocalMachineKey(&hkey, L"SOFTWARE\\www\\ggg 2.0", elements);
	HKEY hkey2;
	long res2 = winreg.LocalMachineKey(&hkey2, L"SOFTWARE\\www\\", elements);

	HKEY hkey3;
	wchar_t buf[4096];
	DWORD dlen = 4096;
	memset(buf, '\0', 4096);
	//long res3 = winreg.GetRegValue(&hkey3, L"SOFTWARE\\www\\ggg 2.0", L"Location64", L"", buf, &dlen);
	long res3 = winreg.GetRegValue(&hkey3, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"SystemRoot", L"", buf, &dlen);
	//long res3 = winreg.GetRegValue(&hkey3, L"SOFTWARE\\www\\IAS", L"test", L"", buf, &dlen);
	//long res3 = winreg.GetRegValue(&hkey3, L"SOFTWARE\\www\\Display\\igfxcui", L"Inst", L"", buf, &dlen);

	uiautoconfig.execute("MSIEXEC_UNINSTALL_WIN32_DEBUG");
	UiAutoUninstallValidate();
	uiautoconfig.execute("MSIEXEC_UNINSTALL_WIN32_RELEASE");
	UiAutoUninstallValidate();
	uiautoconfig.execute("MSIEXEC_UNINSTALL_X64_DEBUG");
	UiAutoUninstallValidate();
	uiautoconfig.execute("MSIEXEC_UNINSTALL_X64_RELEASE");
	UiAutoUninstallValidate();

	uiautoconfig.validateFiles("FILES_INSTALL_X86");
	uiautoconfig.validateFiles("FILES_INSTALL_X64");

	uiautoconfig.validateFiles("FILES_INSTALL");

	long res4 = winreg.LocalMachineKey(&hkey2, L"SOFTWARE\\www\\", elements);


	std::cout << "Done" << std::endl;
	Sleep(3000);

	return 0;
}

