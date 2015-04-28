#include "VersionValidate.h"



VersionValidate::VersionValidate()
{
}


VersionValidate::~VersionValidate()
{
}


void VersionValidate::Validate()
{
	std::vector<std::wstring> dirlist;
	dirlist.push_back(L"C:\\src\\lib\\");
	dirlist.push_back(L"C:\\src\\exe\\");
	dirlist.push_back(L"C:\\src\\installer\\");

	std::vector<std::wstring> dirlist2;
	dirlist2.push_back(L"C:\\Users\\");


	std::vector<std::wstring>::iterator itr_dirlist;

	auto handler1 = [](std::wstring wfile, bool *bStatus, void* lpObj) {
		VersionValidate *obj = (VersionValidate*)lpObj;
		char *body = obj->GetContent(wfile);

		std::string str;
		str.assign(body);

		std::regex pattern1("");
		std::regex pattern2("");
		std::smatch vmatch;
		//bool match = regex_search(str, vmatch, pattern1);
		bool match = regex_search(str.begin(), str.end(), pattern2);
		if (match)
		{
			//printf("\n\n==========================================  PASSED =================================\n\n");
			//wprintf(L"\nFILE: %s\n\n", wfile.c_str());
			//printf("%s\n", body);
			printf(".");
		}
		else
		{
			//printf("\n\n------------------------------------------  FAILED ---------------------------------\n");
			wprintf(L"\nFILE: %s", wfile.c_str());
			//printf("%s\n", body);
		}
		free(body);
	};

	auto handler2 = [](std::wstring wfile, bool *bStatus, void* lpObj) {
		VersionValidate *obj = (VersionValidate*)lpObj;
		char *body = obj->GetContent(wfile);

		IasVersion iasVersion;
		wchar_t fileVersion[1024];
		wchar_t productVersion[1024];
		memset(fileVersion, '\0', 1024);
		memset(productVersion, '\0', 1024);

		std::vector<std::pair<std::wstring, std::wstring>>::iterator it;
		std::vector<std::pair<std::wstring, std::wstring>> list;
		DWORD res2 = iasVersion.PrintFileVersion2(wfile.c_str(), &list);

		for (it = list.begin(); it != list.end(); it++)
		{
			auto item = *it;
			std::wstring name = item.first;
			std::wstring value = item.second;
			if (name.compare(L"InternalName") == 0)
			{

			}
			if (name.compare(L"OriginalFilename") == 0)
			{

			}
			if (name.compare(L"CompanyName") == 0)
			{
				if (value.compare(L"Intel Corporation") == 0)
				{

				}
				else
				{
					*bStatus = true;
				}
			}
			if (name.compare(L"FileVersion") == 0 || name.compare(L"ProductVersion") == 0)
			{
				std::smatch match;
				std::string sval(value.begin(), value.end());
				std::regex pattern1("[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+");
				bool ismatch = regex_search(sval.begin(), sval.end(), pattern1);
				if (ismatch)
				{

				}
				else
				{
					*bStatus = true;
				}
			}
			if (name.compare(L"ProductName") == 0)
			{
				if (value.compare(L"Product Item") == 0)
				{

				}
				else
				{
					*bStatus = true;
				}
			}
			if (name.compare(L"LegalCopyright") == 0)
			{
				if (value.compare(L"Copyright 2013-2015 Corporation. All Rights Reserved.") == 0)
				{

				}
				else
				{
					*bStatus = true;
				}
			}
		}

		//DWORD res = iasVersion.PrintFileVersion(wfile.c_str(), fileVersion, productVersion);
		//if (res == 0) {
		//	//std::wcout << "file: " << wfile << std::endl;
		//	//std::wcout << "\tproduct version:" << productVersion << std::endl;
		//	//std::wcout << "\tfile version:" << fileVersion << std::endl;
		//}
		//else
		//{
		//	std::wcout << "file not found: " << wfile << std::endl;
		//}
	};

	/*
	for (itr_dirlist = dirlist.begin(); itr_dirlist != dirlist.end(); itr_dirlist++)
	{
	auto d = *itr_dirlist;
	bool bErr = false;
	VisitDirectory(d, L".h", handler1, &bErr);
	VisitDirectory(d, L".cpp", handler1, &bErr);
	}
	*/

	for (itr_dirlist = dirlist2.begin(); itr_dirlist != dirlist2.end(); itr_dirlist++)
	{
		auto d2 = *itr_dirlist;
		bool bHasError = false;
		VisitDirectory(d2, L".exe", handler2, &bHasError);
		VisitDirectory(d2, L".dll", handler2, &bHasError);
	}
}

//
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa365200%28v=vs.85%29.aspx
//
std::vector<std::wstring> VersionValidate::EnumFiles(const std::wstring& path, const wchar_t* prefix, const wchar_t* postfix, bool fullpath)
{
	std::vector<std::wstring> list;

	WIN32_FIND_DATA ffd;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	hFind = FindFirstFile(path.c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		return list;
	}

	do
	{
		bool bres1 = true;
		bool bres2 = true;
		auto fname = ffd.cFileName;
		std::wstring wname(fname);
		if (fullpath)
		{
			memset(buffer, 0, BUFSIZE);
			lppPart = { NULL };
			DWORD rv = GetFullPathName(fname, BUFSIZE, buffer, lppPart);
			wname.assign(buffer);
		}
		std::wstring wpostfix(postfix);
		if (wpostfix.size() > 0)
		{
			std::wregex rx(postfix);
			std::wsmatch match;
			bres1 = std::regex_search(wname, match, rx);
		}
		std::wstring wprefix(prefix);
		if (wprefix.size() > 0)
		{
			std::wregex rx(prefix);
			std::wsmatch match;
			bres2 = std::regex_search(wname, match, rx);
		}
		if (bres1 && bres2)
		{
			if (std::tr2::sys::is_regular_file(ffd))
			{
				list.push_back(ffd.cFileName);
			}
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	return list;
}

std::vector<std::wstring> VersionValidate::EnumFolders(const std::wstring& path, const wchar_t* prefix, const wchar_t* postfix, bool fullpath)
{
	std::vector<std::wstring> list;

	WIN32_FIND_DATA ffd;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	hFind = FindFirstFile(path.c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		return list;
	}

	do
	{
		if (std::tr2::sys::is_directory(ffd))
		{
			list.push_back(ffd.cFileName);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	return list;
}


void VersionValidate::VisitDirectory(std::wstring dir, std::wstring filter, LPFunc anonf, bool *bStatus)
{
	auto header_files = EnumFiles(dir, nullptr, filter.c_str(), true);
	if (header_files.size() > 0)
	{
		std::vector<std::wstring>::iterator itr_file;
		for (itr_file = header_files.begin(); itr_file != header_files.end(); itr_file++)
		{
			std::wstring wfile = *itr_file;
			anonf(wfile, bStatus, this);
		}
	}

	auto folder_names = EnumFolders(dir, nullptr, nullptr, true);
	if (folder_names.size() > 0)
	{
		std::vector<std::wstring>::iterator itr_folder;
		for (itr_folder = folder_names.begin(); itr_folder != folder_names.end(); itr_folder++)
		{
			std::wstring wdir = *itr_folder;
			VisitDirectory(wdir, filter, anonf, bStatus);
		}
	}

}

char* VersionValidate::GetContent(std::wstring wfile_name)
{
	FILE *fp;
	char *buf = NULL;

	std::string file_name;
	file_name.assign(wfile_name.begin(), wfile_name.end());

	fopen_s(&fp, file_name.c_str(), "rb");
	if (fp == NULL)
	{
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);

	buf = (char*)malloc(size + 1);
	memset(buf, 0, size);

	int i = 0;
	int ch;
	while ((ch = fgetc(fp)) != EOF)
	{
		buf[i++] = ch;
	}

	fclose(fp);

	return buf;
}
