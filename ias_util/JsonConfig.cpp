#include "JsonConfig.h"


JsonConfig::JsonConfig()
{
}


JsonConfig::~JsonConfig()
{
}

JsonConfig::JsonConfig(const std::wstring& filepath)
{
	wszFileName = std::wstring(filepath.begin(), filepath.end());
}

std::wstring JsonConfig::ReadFileIntoStringW(const std::wstring& filepath)
{
	wszFileName = std::wstring(filepath.begin(), filepath.end());

	std::wstring wstr;
	std::ifstream file(filepath.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	size_t size = (size_t)file.tellg();
	file.seekg(0, std::ios::beg);
	char* buffer = new char[size];
	file.read(buffer, size);
	wstr = (wchar_t*)buffer;
	file.close();
	delete[] buffer;
	return wstr;
}

std::string JsonConfig::ReadFileIntoStringA(const std::wstring& filepath)
{
	wszFileName = std::wstring(filepath.begin(), filepath.end());
	Sleep(500);
	std::string str;
	std::ifstream file(filepath.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	Sleep(500);
	size_t size = (size_t)file.tellg();
	file.seekg(0, std::ios::beg);
	char* buffer = new char[size];
	file.read(buffer, size);
	str = buffer;
	file.close();
	delete[] buffer;
	return str;
}


BOOL JsonConfig::FileExist(const wchar_t* filename)
{
	DWORD attribs = ::GetFileAttributesW(filename);
	if (attribs == INVALID_FILE_ATTRIBUTES) {
		return false;
	}
	return (attribs & (FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE));
}

// multi byte to wide char:
std::wstring JsonConfig::s2ws(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

// wide char to multi byte:
std::string JsonConfig::ws2s(const std::wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), 0, 0, 0, 0);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), &strTo[0], size_needed, 0, 0);
	return strTo;
}

std::string JsonConfig::CreateDefaultConfig(const wchar_t* filename)
{
	return NULL;

	Json::Value fromScratch;
	Json::Value array;

	fromScratch["LOCALREPO"] = "C:\\tmp\\";  // edit: should be the path to the project main directory
	fromScratch["WLOCALREPO"] = "C:\\tmp\\"; // edit: should be the path to the project main directory


	Json::StyledWriter styledWriter;
	std::cout << styledWriter.write(fromScratch);
	std::string sout = styledWriter.write(fromScratch);

	std::ofstream file(filename);
	file << sout;
	file.close();

	return sout;
}

const wchar_t *JsonConfig::GetWC(const char *c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t wc[4096];
	memset(wc, '\0', 4096);
	size_t res;
	mbstowcs_s(&res, wc, c, cSize);

	return wc;
}

BOOL JsonConfig::ParseFile(const std::wstring& filepath, Json::Value *root)
{
	wszFileName = std::wstring(filepath.begin(), filepath.end());

	std::string str = ReadFileIntoStringA(filepath);
	Json::Reader reader;
	bool res = reader.parse(str.c_str(), *root, false);
	return res;
}

BOOL JsonConfig::Parse(Json::Value *root)
{
	std::string str = ReadFileIntoStringA(wszFileName);
	Json::Reader reader;
	bool res = reader.parse(str.c_str(), *root, false);
	m_root = *root;
	return res;
}

BOOL JsonConfig::Parse()
{
	std::string str = ReadFileIntoStringA(wszFileName);
	Json::Reader reader;
	bool res = reader.parse(str.c_str(), m_root, false);
	return res;
}