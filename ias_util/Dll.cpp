#include "Dll.h"


Dll::Dll()
{
	dll_inst = NULL;
}


Dll::~Dll()
{
	UnloadDll();
}

BOOL Dll::UnloadDll()
{
	BOOL res = false;
	if (dll_inst != NULL) {
		res = FreeLibrary(dll_inst);
		dll_inst = NULL;
	}
	return res;
}

HINSTANCE Dll::LoadDll(const wchar_t* pfilepath)
{
	filepath = pfilepath;
	dll_inst = LoadLibrary(pfilepath);
	if (dll_inst == NULL) {
		DWORD err = GetLastError();
		printf("get last error code: %d\n", err);
	}
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

void Dll::CommandApiVersion()
{
	printf("Calling GetApiVersion()\n");
	typedef HRESULT(*LPGETAPIVERSION)(unsigned int *major, unsigned int *minor);
	LPGETAPIVERSION lpGetApiVersion;
	if (dll_inst != NULL) {
		lpGetApiVersion = (LPGETAPIVERSION)::GetProcAddress(dll_inst, "GetApiVersion");
		if (lpGetApiVersion != NULL) {
			unsigned int major;
			unsigned int minor;
			HRESULT hres = lpGetApiVersion(&major, &minor);
			if (SUCCEEDED(hres)) {
				printf("version: %d.%d\n", major, minor);
			}
		}
	}
}

void Dll::CommandHasSystemConsentFeature()
{
	printf("Calling HasSystemConsentFeature()\n");
	typedef HRESULT(*LPHASSYSTEMCONSENTFEATURE)(unsigned int *consent_feature);
	LPHASSYSTEMCONSENTFEATURE lpHasSystemConsentFeature;
	if (dll_inst != NULL) {
		lpHasSystemConsentFeature = (LPHASSYSTEMCONSENTFEATURE)::GetProcAddress(dll_inst, "HasSystemConsentFeature");
		if (lpHasSystemConsentFeature != NULL) {
			unsigned int consent_feature;
			HRESULT hres = lpHasSystemConsentFeature(&consent_feature);
			if (SUCCEEDED(hres)) {
				printf("HasSystemConsentFeature() return value: %d\n", consent_feature);
			}
		}
	}
}

void Dll::CommandInitialize()
{
	typedef struct{} handle_t, *lphandle_t;
	printf("Calling HasSystemConsentFeature()\n");
	typedef HRESULT(*LPINITIALIZE)(lphandle_t handle, const wchar_t* app_name, const wchar_t* app_version, const wchar_t* telemetry_id, const wchar_t* options, const wchar_t* store_folder);
	LPINITIALIZE lpInitialize;
	if (dll_inst != NULL) {
		lpInitialize = (LPINITIALIZE)::GetProcAddress(dll_inst, "Initialize");
		if (lpInitialize != NULL) {
			const wchar_t app_name[1024] = L"deadbeef";
			const wchar_t app_version[1024] = L"appversion";
			const wchar_t telemetry_id[1024] = L"deadbeef-dead-beef-dead-beefdeadbeef";
			const wchar_t options[1024] = L"";
			const wchar_t store_folder[1024] = L"";
			HRESULT hres = lpInitialize(NULL, app_name, app_version, telemetry_id, NULL, NULL);
			if (SUCCEEDED(hres)) {
				printf("Initialize() return OK\n");
			}
		}
	}
}

void Dll::CommandDeinitialize()
{
	typedef struct{} handle_t, *lphandle_t;
	printf("Calling Deinitialize()\n");
	typedef HRESULT(*LPDEINITIALIZE)(lphandle_t handle);
	LPDEINITIALIZE lpDeinitialize;
	if (dll_inst != NULL) {
		lpDeinitialize = (LPDEINITIALIZE)::GetProcAddress(dll_inst, "Deinitialize");
		if (lpDeinitialize != NULL) {
			HRESULT hres = lpDeinitialize(NULL);
			if (SUCCEEDED(hres)) {
				printf("Deinitialize() return OK\n");
			}
		}
	}
}

void Dll::CommandRecordEvent()
{
	typedef struct{} handle_t, *lphandle_t;
	typedef struct{} session_t, *lpsession_t;
	printf("Calling RecordEvent()\n");
	typedef HRESULT(*LPRECORDEVENT)(lphandle_t handle, lpsession_t session, const wchar_t* const name, unsigned int count, double sum);
	LPRECORDEVENT lpRecordEvent;
	if (dll_inst != NULL) {
		lpRecordEvent = (LPRECORDEVENT)::GetProcAddress(dll_inst, "RecordEvent");
		if (lpRecordEvent != NULL) {
			HRESULT hres = lpRecordEvent(NULL, NULL, L"AnEvent", 1, 0);
			if (SUCCEEDED(hres)) {
				printf("RecordEvent() return OK\n");
			}
		}
	}
}
