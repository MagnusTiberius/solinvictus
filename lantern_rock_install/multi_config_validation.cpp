#pragma once
#include "stdafx.h"
#include "MsiConfig.h"


#if defined(_WIN64)
const int PLATFORM = 64;
#else
const int PLATFORM = 86;
#endif

int _tmain(int argc, _TCHAR* argv[])
{

	ConfigSetting config_2_0_52;
	config_2_0_52.configFilename = L"LanternRockInstallConfig-2.0.52.201493.json";
	config_2_0_52.installName = "MSIEXEC_INSTALL_WIN32_DEBUG";
	config_2_0_52.filesInstall = "FILES_INSTALL_X86";
	config_2_0_52.filesInstallExe = "FILES_INSTALL_EXE_X86";
	config_2_0_52.uninstallName = "MSIEXEC_UNINSTALL_WIN32_DEBUG";
	config_2_0_52.registryCompany = "REGISTRY_COMPANY";
	config_2_0_52.addressNames = "DLL_PROC_ADDRESS_NAMES";
	config_2_0_52.productId = "PRODUCT_ID";

	ConfigSetting config_2_0_48;
	config_2_0_48.configFilename = L"LanternRockInstallConfig-2.0.48.199814.json";
	config_2_0_48.installName = "MSIEXEC_INSTALL_WIN32_DEBUG";
	config_2_0_48.filesInstall = "FILES_INSTALL_X86";
	config_2_0_48.filesInstallExe = "FILES_INSTALL_EXE_X86";
	config_2_0_48.uninstallName = "MSIEXEC_UNINSTALL_WIN32_DEBUG";
	config_2_0_48.registryCompany = "REGISTRY_COMPANY";
	config_2_0_48.addressNames = "DLL_PROC_ADDRESS_NAMES";
	config_2_0_48.productId = "PRODUCT_ID";


	MsiConfig config1;

	//DirMgr dirMgr;
	//dirMgr.GetDirChange(L"C:\\Users\\bbgonzaX\\AppData\\Local\\Intel Telemetry\\deadbeef\\deadbeef-dead-beef-dead-beefdeadbeef\\");


	config1.Uninstall(&config_2_0_48);
	config1.Uninstall(&config_2_0_52);

	if (true) {
		printf("\n\n===============================================================\n");
		printf("Verify version 2.0.48 will install and uninstall.\n");
		printf("++INSTALL Config-2.0.48.199814.json \n");
		printf("++UNINSTALL Config-2.0.48.199814.json \n");
		config1.Install(&config_2_0_48);
		config1.Uninstall(&config_2_0_48);
		printf("................................................................\n");
		printf("\n\n\n\n");
	}

	if (true) {
		printf("\n\n===============================================================\n");
		printf("Verify version 2.0.52 followed immediately by installing version 2.0.48.\n");
		printf("++INSTALL Config-2.0.52.201493.json \n");
		printf("++INSTALL Config-2.0.48.199814.json \n");
		printf("++UNINSTALL Config-2.0.48.199814.json \n");
		config1.Install(&config_2_0_52);
		config1.Install(&config_2_0_48);
		config1.Uninstall(&config_2_0_52);
		printf("................................................................\n");
		printf("\n\n\n\n");
	}

	config1.Uninstall(&config_2_0_48);


	if (true) {
		printf("\n\n===============================================================\n");
		printf("Verify version 2.0.48 followed immediately by installing version 2.0.52.\n");
		printf("++INSTALL Config-2.0.48.199814.json \n");
		printf("++INSTALL Config-2.0.52.201493.json \n");
		printf("++UNINSTALL Config-2.0.48.199814.json \n");
		config1.Install(&config_2_0_48);
		config1.Install(&config_2_0_52);
		config1.Uninstall(&config_2_0_48);
		printf("................................................................\n");
		printf("\n\n\n\n");
	}
	config1.Uninstall(&config_2_0_52);

	if (false) {
		config1.Install(L"LanternRockInstallConfig.json", "MSIEXEC_INSTALL_WIN32_DEBUG", 
			"FILES_INSTALL_X86", "FILES_INSTALL_EXE_X86", "MSIEXEC_UNINSTALL_WIN32_DEBUG",
			"REGISTRY_COMPANY", "DLL_PROC_ADDRESS_NAMES", "PRODUCT_ID");

		config1.Uninstall(L"LanternRockInstallConfig.json", "MSIEXEC_INSTALL_WIN32_DEBUG", 
			"FILES_INSTALL_X86", "FILES_INSTALL_EXE_X86", "MSIEXEC_UNINSTALL_WIN32_DEBUG",
			"REGISTRY_COMPANY", "DLL_PROC_ADDRESS_NAMES", "PRODUCT_ID");
	}

	std::cout << "Done" << std::endl;
	Sleep(1000);

	return 0;
}

