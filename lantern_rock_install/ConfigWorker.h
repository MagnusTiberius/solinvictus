#pragma once
#include "stdafx.h"
#include "MsiConfig.h"
#include <assert.h>
#include "DirChange.h"

#if defined(_WIN64)
const int PLATFORM = 64;
#else
const int PLATFORM = 86;
#endif

#if defined(_DEBUG)
const int CONFIGURATIONDEBUG = 1;
const int CONFIGURATIONRELEASE = 0;
#else
const int CONFIGURATIONDEBUG = 0;
const int CONFIGURATIONRELEASE = 1;
#endif

class ConfigWorker
{
public:
	ConfigWorker();
	~ConfigWorker();

	void Install();

private:
	int do_it(ConfigSetting *config_2_0_48, ConfigSetting *config_2_0_52, ConfigSetting *config_2_0_54);
	SharedFile m_sharedFile;
	const wchar_t* m_fileName = L"SharedFile001.txt";
	const size_t bufsiz = 1024;
	char buffer[1024];

	void VerifyJsonFile(MsiConfig* pconfig);

};

