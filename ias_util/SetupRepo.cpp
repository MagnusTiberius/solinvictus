#include "SetupRepo.h"


SetupRepo::SetupRepo()
{
}


SetupRepo::~SetupRepo()
{
}


BOOL SetupRepo::directory_exists(const wchar_t* dirName) 
{
	DWORD attribs = ::GetFileAttributesW(dirName);
	if (attribs == INVALID_FILE_ATTRIBUTES) {
		return false;
	}
	return (attribs & FILE_ATTRIBUTE_DIRECTORY);
}

// multi byte to wide char:
std::wstring SetupRepo::s2ws(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

// wide char to multi byte:
std::string SetupRepo::ws2s(const std::wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), 0, 0, 0, 0);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), &strTo[0], size_needed, 0, 0);
	return strTo;
}

char* SetupRepo::get_ias_app_data_path()
{
	char *pValue;
	size_t len;
	errno_t err = _dupenv_s(&pValue, &len, LOCALAPPDATA);
	printf(pValue);
	char *iaspath = new char[1024];
	memset(iaspath, '\0', 1024);
	sprintf_s(iaspath, 1024, "%s\\%s\\", pValue, IASQA);
	return iaspath;
}

int SetupRepo::get_ias_app_data_pathw(wchar_t* iaspath, Json::Value root)
{
	wchar_t *pValue;
	size_t len;
	errno_t err = _wdupenv_s(&pValue, &len, WLOCALAPPDATA);
	wprintf(pValue);
	memset(iaspath, '\0', 1024);
	swprintf_s(iaspath, 1024, L"%s\\%s\\", pValue, WIASQA);

	std::string localapp = root.get("LOCALAPPDATA", "").asString();
	if (strlen(localapp.c_str()) > 0) {
		const wchar_t* localappw = jsonconfig.GetWC(localapp.c_str());
		swprintf_s(iaspath, 1024, L"%s\\%s\\", localappw, WIASQA);
	}
	return 0;
}

void SetupRepo::wappend(const wchar_t* s1, wchar_t* s2, wchar_t* res, size_t count)
{
	swprintf_s(res, count, L"%s%s", s1, s2);
}

void SetupRepo::CopyContent(wchar_t* source, wchar_t* dest)
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	LARGE_INTEGER filesize;
	WIN32_FIND_DATA ffd;

	if (!directory_exists(dest)) {
		int r = _wmkdir(dest);
		printf("mkdir result=%d", r);
	}

	wchar_t src_all[4096];
	wchar_t child_src_all[4096];
	wchar_t child_dst_all[4096];
	wappend(source, L"*.*", src_all, 4096);

	hFind = FindFirstFile(src_all, &ffd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		exit(1);
	}

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
			if (wcscmp(ffd.cFileName, L".") == 0) {

			}
			else if (wcscmp(ffd.cFileName, L"..") == 0) {

			}
			else {
				swprintf_s(child_src_all, 4096, L"%s%s\\", source, ffd.cFileName);
				swprintf_s(child_dst_all, 4096, L"%s%s\\", dest, ffd.cFileName);
				CopyContent(child_src_all, child_dst_all);
			}
		}
		else
		{
			wchar_t src_file[4096];
			wchar_t dst_file[4096];
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			swprintf_s(src_file, 4096, L"%s%s", source, ffd.cFileName);
			swprintf_s(dst_file, 4096, L"%s%s", dest, ffd.cFileName);
			_tprintf(TEXT("copy  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
			BOOL b = CopyFile(src_file, dst_file, 0);
		}
	} while (FindNextFile(hFind, &ffd) != 0);
}

int SetupRepo::create_dir(wchar_t* dirname)
{
	if (!directory_exists(dirname)) {
		int r = _wmkdir(dirname);
		return r;
	}
	return -1;
}

void SetupRepo::create_dir_fragment(wchar_t* dirname, wchar_t* fragment)
{
	wchar_t full[4096];
	wappend(dirname, fragment, full, 4096);
	create_dir(full);
}


int SetupRepo::Run(int argc, _TCHAR* argv[])
{
	HANDLE hFind = INVALID_HANDLE_VALUE;

	if (argc < 2)
	{
		std::wcout << "usage: [thisprogram] -rev <number>" << std::endl;
	}

	if (!jsonconfig.FileExist(L"setuprepo.json"))
	{
		//jsonconfig.CreateDefaultConfig(L"setuprepo.json");
	}
	std::string json_config = jsonconfig.ReadFileIntoStringA(L"setuprepo.json");
	const std::string jcfg = std::string(json_config);
	Json::Value root;
	Json::Reader reader;
	std::ifstream test("setuprepo.json", std::ifstream::binary);
	reader.parse(test, root, false);

	std::string localrepo = root.get("LOCALREPO", "").asString();

	const wchar_t* localrepow = jsonconfig.GetWC(localrepo.c_str());

	wchar_t *rn = argv[2];
	wchar_t dp[4096];
	int sz = get_ias_app_data_pathw(dp, root);
	wchar_t fp[4096];
	swprintf_s(fp, 4096, L"%sdev@%s\\", dp, rn);
	if (!directory_exists(fp)) {
		int r = _wmkdir(fp);
	}

	wchar_t repo_win32[4096];
	wappend(localrepow, L"bin\\Win32\\", repo_win32, 4096);
	wchar_t repo_x64[4096];
	wappend(localrepow, L"bin\\x64\\", repo_x64, 4096);

	create_dir_fragment(fp, L"bin");
	create_dir_fragment(fp, L"bin\\Win32");
	wchar_t test_win32[4096];
	wappend(fp, L"bin\\Win32\\", test_win32, 4096);
	wchar_t test_x64[4096];
	wappend(fp, L"bin\\x64\\", test_x64, 4096);
	CopyContent(repo_win32, test_win32);
	CopyContent(repo_x64, test_x64);


	create_dir_fragment(fp, L"src");
	create_dir_fragment(fp, L"src\\include");
	wappend(fp, L"src\\include\\", test_win32, 4096);
	wappend(localrepow, L"src\\include\\", repo_win32, 4096);
	CopyContent(repo_win32, test_win32);
	CopyContent(repo_x64, test_x64);


	return 0;
}