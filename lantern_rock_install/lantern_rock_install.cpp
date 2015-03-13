// lantern_rock_install.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UIAuto.h"
#include "SetupRepo.h"
#include "CommandMsiExec.h"
#include "UiAutoConfig.h"
#include "WinReg.h"
#include "IasVersion.h"

UIAuto uiauto;

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
		//std::cout << "Window not found, window text has changed, please update text." << std::endl;
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

void installValidate(UiAutoConfig uiautoconfig, const char* cmdparam)
{
	uiautoconfig.execute(cmdparam);
	UiAutoInstallValidate();
}

void uninstallValidate(UiAutoConfig uiautoconfig, const char* cmdparam)
{
	uiautoconfig.execute(cmdparam);
	UiAutoUninstallValidate();
}

void verifyFile(IasVersion iasversion, const wchar_t *strname)
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

void verifyFiles(UiAutoConfig uiautoconfig, IasVersion iasversion, std::string name)
{
	std::string arr1[1024];
	int cnt = uiautoconfig.GetJsonValue(name, arr1);
	for (int i = 0; i < cnt; i++) {
		std::string itm = arr1[i];
		std::wstring widestr = std::wstring(itm.begin(), itm.end());
		verifyFile(iasversion, widestr.c_str());
	}
}

void verifyRegistry(UiAutoConfig uiautoconfig, std::string name, const wchar_t* searchfor)
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
			size_t diff=0;
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

int _tmain(int argc, _TCHAR* argv[])
{
	UiAutoConfig uiautoconfig(L"LanternRockInstallConfig.json");
	IasVersion iasversion;

	std::wstring prdid;
	int cnt = uiautoconfig.GetJsonOneValue("PRODUCT_ID", &prdid);


	if (true) {
		std::wcout << "\n\n==================== WIN32_DEBUG ======================" << std::endl;
		installValidate(uiautoconfig, "MSIEXEC_INSTALL_WIN32_DEBUG");
		std::wcout << "Install done." << std::endl;
		std::wcout << "Verifying dll file and executables:" << std::endl;
		uiautoconfig.validateFiles("FILES_INSTALL");
		uiautoconfig.validateFiles("FILES_INSTALL_X86");
		verifyRegistry(uiautoconfig, "REGISTRY_COMPANY", prdid.c_str());

		verifyFiles(uiautoconfig, iasversion, "FILES_INSTALL");
		verifyFiles(uiautoconfig, iasversion, "FILES_INSTALL_X86");

		std::wcout << "Verifying dll file using loadlibrary and getprocaddress:" << std::endl;
		uiautoconfig.VerifyAddressName("FILES_INSTALL_X86", "DLL_PROC_ADDRESS_NAMES");

		std::wcout << "Starting uninstall." << std::endl;
		uninstallValidate(uiautoconfig, "MSIEXEC_UNINSTALL_WIN32_DEBUG");
		std::wcout << "Uninstall done." << std::endl;
		std::wcout << "Verifying dll file and executables:" << std::endl;
		uiautoconfig.validateFiles("FILES_INSTALL");
		uiautoconfig.validateFiles("FILES_INSTALL_X86");
		verifyRegistry(uiautoconfig, "REGISTRY_COMPANY", prdid.c_str());
	}

	if (true) {
		std::wcout << "\n\n==================== WIN32_RELEASE ======================" << std::endl;
		installValidate(uiautoconfig, "MSIEXEC_INSTALL_WIN32_RELEASE");
		std::wcout << "Install done." << std::endl;
		std::wcout << "Verifying dll file and executables:" << std::endl;
		uiautoconfig.validateFiles("FILES_INSTALL");
		uiautoconfig.validateFiles("FILES_INSTALL_X86");
		verifyRegistry(uiautoconfig, "REGISTRY_COMPANY", prdid.c_str());

		verifyFiles(uiautoconfig, iasversion, "FILES_INSTALL");
		verifyFiles(uiautoconfig, iasversion, "FILES_INSTALL_X86");

		std::wcout << "Verifying dll file using loadlibrary and getprocaddress:" << std::endl;
		uiautoconfig.VerifyAddressName("FILES_INSTALL_X86", "DLL_PROC_ADDRESS_NAMES");

		std::wcout << "Starting uninstall." << std::endl;
		uninstallValidate(uiautoconfig, "MSIEXEC_UNINSTALL_WIN32_RELEASE");
		std::wcout << "Uninstall done." << std::endl;
		std::wcout << "Verifying dll file and executables:" << std::endl;
		uiautoconfig.validateFiles("FILES_INSTALL");
		uiautoconfig.validateFiles("FILES_INSTALL_X86");
		verifyRegistry(uiautoconfig, "REGISTRY_COMPANY", prdid.c_str());
	}

	if (false) {

		installValidate(uiautoconfig, "MSIEXEC_INSTALL_WIN32_DEBUG");
		installValidate(uiautoconfig, "MSIEXEC_INSTALL_WIN32_RELEASE");
		installValidate(uiautoconfig, "MSIEXEC_INSTALL_X64_DEBUG");
		installValidate(uiautoconfig, "MSIEXEC_INSTALL_X64_RELEASE");


		uiautoconfig.validateFiles("FILES_INSTALL_X86");
		uiautoconfig.validateFiles("FILES_INSTALL_X64");

		uiautoconfig.validateFiles("FILES_INSTALL");


		WinReg winreg;
		HKEY hkey3;
		wchar_t buf[4096];
		DWORD dlen = 4096;
		memset(buf, '\0', 4096);
		long res3 = winreg.GetRegValue(&hkey3, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"SystemRoot", L"", buf, &dlen);

		uninstallValidate(uiautoconfig, "MSIEXEC_UNINSTALL_WIN32_DEBUG");
		uninstallValidate(uiautoconfig, "MSIEXEC_UNINSTALL_WIN32_RELEASE");
		uninstallValidate(uiautoconfig, "MSIEXEC_UNINSTALL_X64_DEBUG");
		uninstallValidate(uiautoconfig, "MSIEXEC_UNINSTALL_X64_RELEASE");

		uiautoconfig.validateFiles("FILES_INSTALL_X86");
		uiautoconfig.validateFiles("FILES_INSTALL_X64");

		uiautoconfig.validateFiles("FILES_INSTALL");


	}

	std::cout << "Done" << std::endl;
	Sleep(3000);

	return 0;
}

