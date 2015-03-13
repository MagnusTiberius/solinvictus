#include "Dll.h"


Dll::Dll()
{
	dll_inst = NULL;
}


Dll::~Dll()
{
	UnloadDll();
}

void Dll::UnloadDll()
{
	if (dll_inst != NULL) {
		FreeLibrary(dll_inst);
		dll_inst = NULL;
	}
}

HINSTANCE Dll::LoadDll(const wchar_t* pfilepath)
{
	filepath = pfilepath;
	dll_inst = LoadLibrary(pfilepath);
	return dll_inst;
}

f_funci Dll::GetDllProcAddress(const char* pszProcName)
{
	f_funci funci = NULL;
	if (dll_inst != NULL) {
		funci = (f_funci)::GetProcAddress(dll_inst, pszProcName);
	}
	return funci;
}

