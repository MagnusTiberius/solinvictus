#pragma once
#define SECURITY_WIN32
#define BIG_BUFF   2048
#define SEC_SUCCESS(Status) ((Status) >= 0)
#define g_usPort 2000

#define cbMaxMessage 12000
#define MessageAttribute ISC_REQ_CONFIDENTIALITY 

#include <winsock.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "SspiExample.h"


//  The following #define statement must be changed. ServerName must
//  be defined as the name of the computer running the server sample.
//  TargetName must be defined as the logon name of the user running 
//  the server program.
#define ServerName  "127.0.0.1"
#define TargetName  "localhost"

class SspiClient
{
public:
	SspiClient();
	~SspiClient();

	CredHandle hCred;
	struct _SecHandle  hCtxt;

	SOCKET            Client_Socket;
	BYTE              Data[BIG_BUFF];
	PCHAR             pMessage;
	WSADATA           wsaData;
	//CredHandle        hCred;
	struct _SecHandle hcText2;
	SECURITY_STATUS   ss;
	DWORD             cbRead;
	ULONG             cbMaxSignature;
	ULONG             cbSecurityTrailer;
	SecPkgContext_Sizes            SecPkgContextSizes;
	SecPkgContext_NegotiationInfo  SecPkgNegInfo;
	BOOL DoAuthentication(SOCKET s);


	void Run();
	BOOL SspiClient::ConnectAuthSocket(SOCKET *s, CredHandle        *hCred, struct _SecHandle *hcText);
	BOOL SspiClient::GenClientContext(BYTE *pIn, DWORD cbIn, BYTE *pOut, DWORD *pcbOut, BOOL *pfDone, CHAR *pszTarget, CredHandle *hCred, struct _SecHandle *hcText);
	PBYTE SspiClient::DecryptThis(
		PBYTE              pBuffer,
		LPDWORD            pcbMessage,
		struct _SecHandle *hCtxt,
		ULONG              cbSecurityTrailer);
	PBYTE SspiClient::SspiClientSspiClientVerifyThis(
		PBYTE   pBuffer,
		LPDWORD pcbMessage,
		struct _SecHandle *hCtxt,
		ULONG   cbMaxSignature);

	void SspiClient::PrintHexDump(
		DWORD length,
		PBYTE buffer);

	BOOL SspiClient::SendMsg(
		SOCKET  s,
		PBYTE   pBuf,
		DWORD   cbBuf);

	BOOL SspiClient::ReceiveMsg(
		SOCKET  s,
		PBYTE   pBuf,
		DWORD   cbBuf,
		DWORD  *pcbRead);

	BOOL SspiClient::SendBytes(
		SOCKET  s,
		PBYTE   pBuf,
		DWORD   cbBuf);

	BOOL SspiClient::ReceiveBytes(
		SOCKET  s,
		PBYTE   pBuf,
		DWORD   cbBuf,
		DWORD  *pcbRead);

	void SspiClient::MyHandleError(char *s);
};

