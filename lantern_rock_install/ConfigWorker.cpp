#include "ConfigWorker.h"


ConfigWorker::ConfigWorker()
{
	m_sharedFile.Init(m_fileName, buffer, bufsiz);
}


ConfigWorker::~ConfigWorker()
{
}

void ConfigWorker::VerifyJsonFile(MsiConfig* pconfig)
{
	printf("Verifying content of json file.\n");
	m_sharedFile.Read(buffer, bufsiz);
	bool isOk = pconfig->ValidateFileContent(buffer, bufsiz);
	if (!isOk) {
		printf("Error: Content of json file did not parse correctly.\n");
		printf("Filename: %s \n", buffer);
	}
	else {
		printf("OK: Content of json file parsed correctly.\n");
		printf("Filename: %s \n", buffer);
	}
}

int ConfigWorker::do_it(ConfigSetting *config_2_0_48, ConfigSetting *config_2_0_52, ConfigSetting *config_2_0_54)
{
	MsiConfig config1;

	//config1.Uninstall(config_2_0_48);
	//config1.Uninstall(config_2_0_52);
	//config1.Uninstall(config_2_0_54);

	if (true) {
		printf("\n\n===============================================================\n");
		printf("Verify version 2.0.54 will install and uninstall.\n");
		printf("++INSTALL config_2_0_54 \n");
		printf("++UNINSTALL config_2_0_54 \n");
		config1.Install(config_2_0_54);
		VerifyJsonFile(&config1);
		config1.Uninstall(config_2_0_54);
		printf("................................................................\n");
		printf("\n\n\n\n");
	}



	if (false) {
		printf("\n\n===============================================================\n");
		printf("Verify version 2.0.52 will install and uninstall.\n");
		printf("++INSTALL config_2_0_52 \n");
		printf("++UNINSTALL config_2_0_52 \n");
		config1.Install(config_2_0_52);
		VerifyJsonFile(&config1);
		config1.Uninstall(config_2_0_52);
		printf("................................................................\n");
		printf("\n\n\n\n");
	}

	if (false) {
		printf("\n\n===============================================================\n");
		printf("Verify version 2.0.48 will install and uninstall.\n");
		printf("++INSTALL config_2_0_48 \n");
		printf("++UNINSTALL config_2_0_48 \n");
		config1.Install(config_2_0_48);
		VerifyJsonFile(&config1);
		config1.Uninstall(config_2_0_48);
		printf("................................................................\n");
		printf("\n\n\n\n");
	}

	if (false) {
		printf("\n\n===============================================================\n");
		printf("Verify version 2.0.54 install then donwgrade it to 2.0.52 and 2.0.48.\n");
		printf("++INSTALL config_2_0_54 \n");
		printf("++INSTALL config_2_0_52 \n");
		printf("++INSTALL config_2_0_48 \n");
		config1.Install(config_2_0_54);
		VerifyJsonFile(&config1);
		config1.Install(config_2_0_52);
		VerifyJsonFile(&config1);
		config1.Install(config_2_0_48);
		VerifyJsonFile(&config1);
		config1.Uninstall(config_2_0_54);
		printf("................................................................\n");
		printf("\n\n\n\n");
	}

	//config1.Uninstall(config_2_0_48);
	//config1.Uninstall(config_2_0_52);
	//config1.Uninstall(config_2_0_54);


	if (false) {
		printf("\n\n===============================================================\n");
		printf("Verify version 2.0.54 by performing an upgrade from 2.0.48 and 2.0.52.\n");
		printf("++INSTALL config_2_0_48 \n");
		printf("++INSTALL config_2_0_52 \n");
		printf("++INSTALL config_2_0_54 \n");
		config1.Install(config_2_0_48);
		VerifyJsonFile(&config1);
		config1.Install(config_2_0_52);
		VerifyJsonFile(&config1);
		config1.Install(config_2_0_54);
		VerifyJsonFile(&config1);
		config1.Uninstall(config_2_0_54);
		printf("................................................................\n");
		printf("\n\n\n\n");
	}
	//config1.Uninstall(config_2_0_48);
	//config1.Uninstall(config_2_0_52);
	//config1.Uninstall(config_2_0_54);

	if (false) {
		config1.Install(L"LanternRockInstallConfig.json", "MSIEXEC_INSTALL_WIN32_DEBUG",
			"FILES_INSTALL_X86", "FILES_INSTALL_EXE_X86", "MSIEXEC_UNINSTALL_WIN32_DEBUG",
			"REGISTRY_COMPANY", "DLL_PROC_ADDRESS_NAMES", "PRODUCT_ID");

		config1.Uninstall(L"LanternRockInstallConfig.json", "MSIEXEC_INSTALL_WIN32_DEBUG",
			"FILES_INSTALL_X86", "FILES_INSTALL_EXE_X86", "MSIEXEC_UNINSTALL_WIN32_DEBUG",
			"REGISTRY_COMPANY", "DLL_PROC_ADDRESS_NAMES", "PRODUCT_ID");
	}

	return 0;

}

void ConfigWorker::Install()
{
	ConfigSetting config_2_0_54;
	config_2_0_54.configFilename = L"LanternRockInstallConfig-2.0.54.205305.json";
	config_2_0_54.installName = "MSIEXEC_INSTALL_WIN32_DEBUG";
	config_2_0_54.filesInstall = "FILES_INSTALL_X86";
	config_2_0_54.filesInstallExe = "FILES_INSTALL_EXE_X86";
	config_2_0_54.uninstallName = "MSIEXEC_UNINSTALL_WIN32_DEBUG";
	config_2_0_54.registryCompany = "REGISTRY_COMPANY";
	config_2_0_54.addressNames = "DLL_PROC_ADDRESS_NAMES";
	config_2_0_54.productId = "PRODUCT_ID";

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

	if (PLATFORM == 86) {

		config_2_0_54.installName = "MSIEXEC_INSTALL_WIN32_DEBUG";
		config_2_0_54.uninstallName = "MSIEXEC_UNINSTALL_WIN32_DEBUG";

		config_2_0_52.installName = "MSIEXEC_INSTALL_WIN32_DEBUG";
		config_2_0_52.uninstallName = "MSIEXEC_UNINSTALL_WIN32_DEBUG";

		config_2_0_48.installName = "MSIEXEC_INSTALL_WIN32_DEBUG";
		config_2_0_48.uninstallName = "MSIEXEC_UNINSTALL_WIN32_DEBUG";

		if (CONFIGURATIONDEBUG == 1) {
			do_it(&config_2_0_48, &config_2_0_52, &config_2_0_54);
		}

		config_2_0_48.installName = "MSIEXEC_INSTALL_WIN32_RELEASE";
		config_2_0_48.uninstallName = "MSIEXEC_UNINSTALL_WIN32_RELEASE";

		config_2_0_52.installName = "MSIEXEC_INSTALL_WIN32_RELEASE";
		config_2_0_52.uninstallName = "MSIEXEC_UNINSTALL_WIN32_RELEASE";

		config_2_0_54.installName = "MSIEXEC_INSTALL_WIN32_RELEASE";
		config_2_0_54.uninstallName = "MSIEXEC_UNINSTALL_WIN32_RELEASE";

		if (CONFIGURATIONRELEASE == 1) {
			do_it(&config_2_0_48, &config_2_0_52, &config_2_0_54);
		}

	}

	if (PLATFORM == 64) {
		printf("Platform: x64\n");
		config_2_0_54.installName = "MSIEXEC_INSTALL_X64_DEBUG";
		config_2_0_54.uninstallName = "MSIEXEC_UNINSTALL_X64_DEBUG";
		config_2_0_54.filesInstall = "FILES_INSTALL_X64";
		config_2_0_54.filesInstallExe = "FILES_INSTALL_EXE_X64";

		config_2_0_52.installName = "MSIEXEC_INSTALL_X64_DEBUG";
		config_2_0_52.uninstallName = "MSIEXEC_UNINSTALL_X64_DEBUG";
		config_2_0_52.filesInstall = "FILES_INSTALL_X64";
		config_2_0_52.filesInstallExe = "FILES_INSTALL_EXE_X64";

		config_2_0_48.installName = "MSIEXEC_INSTALL_X64_DEBUG";
		config_2_0_48.uninstallName = "MSIEXEC_UNINSTALL_X64_DEBUG";
		config_2_0_48.filesInstall = "FILES_INSTALL_X64";
		config_2_0_48.filesInstallExe = "FILES_INSTALL_EXE_X64";

		if (CONFIGURATIONDEBUG == 1) {
			printf("Configuration: debug\n");
			do_it(&config_2_0_48, &config_2_0_52, &config_2_0_54);
		}

		config_2_0_48.installName = "MSIEXEC_INSTALL_X64_RELEASE";
		config_2_0_48.uninstallName = "MSIEXEC_UNINSTALL_X64_RELEASE";
		config_2_0_54.filesInstall = "FILES_INSTALL_X64";
		config_2_0_54.filesInstallExe = "FILES_INSTALL_EXE_X64";

		config_2_0_52.installName = "MSIEXEC_INSTALL_X64_RELEASE";
		config_2_0_52.uninstallName = "MSIEXEC_UNINSTALL_X64_RELEASE";
		config_2_0_52.filesInstall = "FILES_INSTALL_X64";
		config_2_0_52.filesInstallExe = "FILES_INSTALL_EXE_X64";

		config_2_0_54.installName = "MSIEXEC_INSTALL_X64_RELEASE";
		config_2_0_54.uninstallName = "MSIEXEC_UNINSTALL_X64_RELEASE";
		config_2_0_54.filesInstall = "FILES_INSTALL_X64";
		config_2_0_54.filesInstallExe = "FILES_INSTALL_EXE_X64";

		if (CONFIGURATIONRELEASE == 1) {
			printf("Configuration: release\n");
			do_it(&config_2_0_48, &config_2_0_52, &config_2_0_54);
		}

	}

	return;
}
