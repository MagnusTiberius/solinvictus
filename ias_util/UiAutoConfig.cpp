#include "UiAutoConfig.h"


UiAutoConfig::UiAutoConfig()
{
}

UiAutoConfig::UiAutoConfig(wchar_t* jsonfile)
{
	json_config = jsonconfig.ReadFileIntoStringA(jsonfile);
	const std::string jcfg = std::string(json_config);

	Json::Reader reader;
	std::ifstream test(jsonfile, std::ifstream::binary);
	reader.parse(test, root, false);

}

UiAutoConfig::~UiAutoConfig()
{
}


DWORD UiAutoConfig::execute(std::string cmdkey)
{
	CommandMsiExec cmdIsntallX86Debug(&uiauto, &jsonconfig);
	DWORD ret = cmdIsntallX86Debug.execute(root.get(cmdkey, "").asString());
	return ret;
}

DWORD UiAutoConfig::GetJsonValue(std::string cmdkey, std::string arr[])
{
	Json::Value v = root.get(cmdkey, "");
	Json::Value::ArrayIndex i = v.size();
	for (Json::Value::ArrayIndex j = 0; j < i; j++) {
		auto itm = v[j];
		std::string s = itm.asString();
		arr[j] = s;
	}
	return i;
}

DWORD UiAutoConfig::GetJsonOneValue(std::string cmdkey, std::wstring *ws)
{
	Json::Value v = root.get(cmdkey, "");
	std::string s = v.asString();
	*ws = jsonconfig.s2ws(s);
	return 0;
}

DWORD UiAutoConfig::validateFiles(std::string str)
{
	DWORD ret = 0;
	Json::Value arr = root.get(str, "");
	if (arr.isArray()) {
		Json::Value::ArrayIndex i = arr.size();
		for (Json::Value::ArrayIndex j = 0; j < i; j++)
		{
			auto itm = arr[j];
			auto v = itm.asString();
			std::wstring ws = jsonconfig.s2ws(v);
			const wchar_t* cwc = ws.c_str();
			if (!jsonconfig.FileExist(cwc)) 
			{
				std::cout << "File not found: " << v << std::endl;
				ret = 1;
			}
			else
			{
				std::cout << "File found: " << v << std::endl;
			}
		}
	}
	return ret;
}

DWORD UiAutoConfig::VerifyFunctionDefinition(char* dllfile, int actiontotake)
{
	DWORD ret = 0;
	Json::Value arr = root.get(dllfile, "");
	if (arr.isArray()) {
		Json::Value::ArrayIndex i = arr.size();
		for (Json::Value::ArrayIndex j = 0; j < i; j++)
		{
			auto itm = arr[j];
			auto v = itm.asString();
			std::wstring ws = jsonconfig.s2ws(v);
			const wchar_t* cwc = ws.c_str();
			std::wcout << "Loading DLL to memory : " << cwc << std::endl;
			HINSTANCE inst = dll.LoadDll(cwc);
			if (inst != NULL) {
				std::wcout << "Loaded into memory - valid state : " << cwc << std::endl;
				if (actiontotake == 1) {
					dll.CommandApiVersion();
				}
				if (actiontotake == 2) {
					dll.CommandHasSystemConsentFeature();
				}
				if (actiontotake == 3) {
					dll.CommandInitialize();
					dll.CommandRecordEvent();
					dll.CommandDeinitialize();
				}
				dll.UnloadDll();
				std::wcout << "Unloading DLL : " << cwc << std::endl;
			}
			else
			{
				std::wcout << "Not loaded into memory - invalid state : " << cwc << std::endl;
			}
		}
	}
	return ret;
}

DWORD UiAutoConfig::VerifyAddressName(char* dllfile, char* procnames)
{
	typedef int(__stdcall *f_funci)();
	DWORD ret = 0;
	Json::Value arr = root.get(dllfile, "");
	if (arr.isArray()) {
		Json::Value::ArrayIndex i = arr.size();
		for (Json::Value::ArrayIndex j = 0; j < i; j++)
		{
			auto itm = arr[j];
			auto v = itm.asString();
			std::wstring ws = jsonconfig.s2ws(v);
			const wchar_t* cwc = ws.c_str();
			std::wcout << "Loading DLL to memory : " << cwc << std::endl;
			HINSTANCE inst = dll.LoadDll(cwc);
			if (inst != NULL) {
				std::wcout << "Loaded into memory - valid state : " << cwc << std::endl;
				Json::Value arrnames = root.get(procnames, "");
				if (arrnames.isArray()) {
					Json::Value::ArrayIndex b = arrnames.size();
					for (Json::Value::ArrayIndex k = 0; k < b; k++)
					{
						auto itmname = arrnames[k];
						auto vname = itmname.asString();
						const char* cc = vname.c_str();
						f_funci funci = (f_funci)dll.GetDllProcAddress(cc);
						if (funci == NULL) 
						{
							ret = 1;
							std::wcout << "Invalid state - Function not found : " << cc << "()" << std::endl;
						}
						else 
						{
							std::wcout << "Function is present - valid state : " << cc << "()" << std::endl;

						}
					}
					dll.UnloadDll();
					inst = NULL;
				}
			}
			else 
			{
				std::wcout << "Not loaded into memory - invalid state : " << cwc << std::endl;
			}
		}
	}
	std::wcout << "Verification of library and proc addresses completed. " << std::endl;
	return ret;

}