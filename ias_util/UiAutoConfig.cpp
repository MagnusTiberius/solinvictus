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


DWORD UiAutoConfig::validateFiles(std::string str)
{
	DWORD ret = 0;
	Json::Value arr = root.get(str, "");
	if (arr.isArray()) {
		std::cout << "ARRAY" << std::endl;
		Json::Value::ArrayIndex i = arr.size();
		for (int j=0; j < i; j++)
		{
			auto itm = arr[j];
			auto v = itm.asString();
			std::wstring ws = jsonconfig.s2ws(v);
			const wchar_t* cwc = ws.c_str();
			if (!jsonconfig.FileExist(cwc)) 
			{
				std::cout << "FILE NOT FOUND " << v << std::endl;
				return 1;
			}
			else
			{
				std::cout << "FILE FOUND " << v << std::endl;
			}
		}
	}
	return ret;
}