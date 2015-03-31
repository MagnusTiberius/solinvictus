// TestHttpSslClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "Winhttp.h"
#include "Sspi.h"
//#include "Wininet.h"

BOOL bResults = FALSE;
HINTERNET	hSession = NULL,
hConnect = NULL,
hRequest = NULL;

int _tmain(int argc, _TCHAR* argv[])
{

	ULONG pcPackages;
	PSecPkgInfo ppPackageInfo[1024];
	SECURITY_STATUS sstat;

	sstat = EnumerateSecurityPackages(&pcPackages, ppPackageInfo);

	if (SEC_E_OK == sstat) {
		printf("EnumerateSecurityPackages = SEC_E_OK\n");
		printf("#packages:%d\n", pcPackages);
		//for (int i = 0; i < pcPackages; i++) {
		//	if (ppPackageInfo[i]) {
		//		if (ppPackageInfo[i]->Name) {
		//			wchar_t* name = ppPackageInfo[i]->Name;
		//			wprintf(L"Name: %s \n", name);
		//		}
		//	}
		//}
	}
	if (SEC_E_INSUFFICIENT_MEMORY == sstat) {
		printf("SEC_E_INSUFFICIENT_MEMORY\n");
	}
	if (SEC_E_INVALID_HANDLE == sstat) {
		printf("SEC_E_INVALID_HANDLE\n");
	}
	if (SEC_E_SECPKG_NOT_FOUND == sstat) {
		printf("SEC_E_SECPKG_NOT_FOUND\n");
	}


	wchar_t pszPrincipal[1024] = L"My";
	ZeroMemory(pszPrincipal, 1024);
	wchar_t pszPackage[1024];

	CredHandle pCredHandle;
	TimeStamp ptsExpiry;
	
	SECURITY_STATUS  stat1 = AcquireCredentialsHandle(pszPrincipal, ppPackageInfo[0]->Name, SECPKG_CRED_INBOUND | SECPKG_CRED_OUTBOUND, NULL, NULL, NULL, NULL, &pCredHandle, &ptsExpiry);
	//SECURITY_STATUS  stat1 = AcquireCredentialsHandle(pszPrincipal, NULL, SECPKG_CRED_INBOUND | SECPKG_CRED_OUTBOUND, NULL, NULL, NULL, NULL, &pCredHandle, &ptsExpiry);

	if (SEC_E_OK == stat1) {
		printf("AcquireCredentialsHandle = SEC_E_OK\n");
	}
	if (SEC_E_INSUFFICIENT_MEMORY == stat1) {
		printf("SEC_E_INSUFFICIENT_MEMORY\n");
	}
	if (SEC_E_INTERNAL_ERROR == stat1) {
		printf("SEC_E_INTERNAL_ERROR\n");
	}
	if (SEC_E_NO_CREDENTIALS == stat1) {
		printf("SEC_E_NO_CREDENTIALS\n");
	}
	if (SEC_E_NOT_OWNER == stat1) {
		printf("SEC_E_NOT_OWNER\n");
	}
	if (SEC_E_SECPKG_NOT_FOUND == stat1) {
		printf("SEC_E_SECPKG_NOT_FOUND\n");
	}
	if (SEC_E_UNKNOWN_CREDENTIALS == stat1) {
		printf("SEC_E_UNKNOWN_CREDENTIALS\n");
	}


	CtxtHandle ctxtHandle;
	wchar_t pszTargetName[1024] = L"127.0.0.1:8080";
	ULONG fContextReq  = ISC_REQ_SEQUENCE_DETECT |
		ISC_REQ_REPLAY_DETECT |
		ISC_REQ_CONFIDENTIALITY |
		ISC_RET_EXTENDED_ERROR |
		ISC_REQ_STREAM |
		ISC_REQ_MANUAL_CRED_VALIDATION;
	SecBufferDesc pInput;
	SecBuffer  BuffersInp[3];
	pInput.ulVersion = SECBUFFER_VERSION;
	pInput.cBuffers = 3;
	pInput.pBuffers = BuffersInp;

	CredHandle phNewContext;
	SecBufferDesc pOutput;
	DWORD pfContextAttr;

	SECURITY_STATUS stat2 = InitializeSecurityContext(&pCredHandle, &ctxtHandle, pszTargetName, fContextReq, 0, 0, &pInput,
		0, &phNewContext, &pOutput, &pfContextAttr, 0);
	if (SEC_I_COMPLETE_AND_CONTINUE == stat2) {
		printf("SEC_I_COMPLETE_AND_CONTINUE\n");
	}
	if (SEC_I_COMPLETE_NEEDED == stat2) {
		printf("SEC_I_COMPLETE_NEEDED\n");
	}
	if (SEC_I_CONTINUE_NEEDED == stat2) {
		printf("SEC_I_CONTINUE_NEEDED\n");
	}
	if (SEC_I_INCOMPLETE_CREDENTIALS == stat2) {
		printf("SEC_I_INCOMPLETE_CREDENTIALS\n");
	}
	if (SEC_E_INCOMPLETE_MESSAGE == stat2) {
		printf("SEC_E_INCOMPLETE_MESSAGE\n");
	}
	if (SEC_E_OK == stat2) {
		printf("SEC_E_OK\n");
	}


	if (SEC_E_INSUFFICIENT_MEMORY == stat2) {
		printf("InitializeSecurityContext = SEC_E_INSUFFICIENT_MEMORY\n");
	}
	if (SEC_E_INTERNAL_ERROR == stat2) {
		printf("InitializeSecurityContext = SEC_E_INTERNAL_ERROR\n");
	}
	if (SEC_E_INVALID_HANDLE == stat2) {
		printf("InitializeSecurityContext = SEC_E_INVALID_HANDLE\n");
	}
	if (SEC_E_INVALID_TOKEN == stat2) {
		printf("InitializeSecurityContext = SEC_E_INVALID_TOKEN\n");
	}
	if (SEC_E_LOGON_DENIED == stat2) {
		printf("InitializeSecurityContext = SEC_E_LOGON_DENIED\n");
	}
	if (SEC_E_NO_AUTHENTICATING_AUTHORITY == stat2) {
		printf("InitializeSecurityContext = SEC_E_NO_AUTHENTICATING_AUTHORITY\n");
	}
	if (SEC_E_NO_CREDENTIALS == stat2) {
		printf("InitializeSecurityContext = SEC_E_NO_CREDENTIALS\n");
	}
	if (SEC_E_TARGET_UNKNOWN == stat2) {
		printf("InitializeSecurityContext = SEC_E_TARGET_UNKNOWN\n");
	}
	if (SEC_E_UNSUPPORTED_FUNCTION == stat2) {
		printf("InitializeSecurityContext = SEC_E_UNSUPPORTED_FUNCTION\n");
	}
	if (SEC_E_WRONG_PRINCIPAL == stat2) {
		printf("InitializeSecurityContext = SEC_E_WRONG_PRINCIPAL\n");
	}
	if (SEC_E_APPLICATION_PROTOCOL_MISMATCH == stat2) {
		printf("InitializeSecurityContext = SEC_E_APPLICATION_PROTOCOL_MISMATCH\n");
	}


	hSession = WinHttpOpen(L"my app",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);


	if (hSession)
		hConnect = WinHttpConnect(hSession, L"127.0.0.1", 8080, 0);


	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, L"GET",
			NULL,
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_SECURE);

	if (hRequest)
		bResults = WinHttpSendRequest(hRequest,
			WINHTTP_NO_ADDITIONAL_HEADERS, 0,
			WINHTTP_NO_REQUEST_DATA, 0,
			0, 0);

	WINHTTP_CERTIFICATE_INFO certInfo;

	DWORD certInfoLen = sizeof(certInfo);
	if (bResults) {
		bool res = WinHttpQueryOption(hRequest,
			WINHTTP_OPTION_SECURITY_CERTIFICATE_STRUCT,
			&certInfo,
			&certInfoLen);
	}

	return 0;
}

