#pragma once
#define usPort 2000
#define SECURITY_WIN32
#define SEC_SUCCESS(Status) ((Status) >= 0)

#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include "Sspiexample.h"

class SspiServer
{
public:
	SspiServer();
	~SspiServer();

	void SspiServer::Run();
	void SspiServer::cleanup();
	BOOL SspiServer::ReceiveBytes(SOCKET s, PBYTE pBuf, DWORD cbBuf, DWORD *pcbRead);
	BOOL SspiServer::SendBytes(SOCKET s, PBYTE pBuf, DWORD cbBuf);
	BOOL SspiServer::ReceiveMsg(SOCKET s, PBYTE pBuf, DWORD cbBuf, DWORD *pcbRead);
	BOOL SspiServer::SendMsg(SOCKET s, PBYTE pBuf, DWORD cbBuf);
	void SspiServer::PrintHexDump(DWORD length, PBYTE buffer);
	BOOL SspiServer::EncryptThis(PBYTE pMessage, ULONG cbMessage, BYTE ** ppOutput, ULONG * pcbOutput, ULONG cbSecurityTrailer);
	BOOL SspiServer::GenServerContext(BYTE *pIn, DWORD cbIn, BYTE *pOut, DWORD *pcbOut, BOOL *pfDone, BOOL fNewConversation);
	BOOL SspiServer::DoAuthentication(SOCKET AuthSocket);
	BOOL SspiServer::AcceptAuthSocket(SOCKET *ServerSocket);

	CredHandle hcred;
	struct _SecHandle  hctxt;

	PBYTE g_pInBuf;
	PBYTE g_pOutBuf;
	DWORD g_cbMaxMessage;
	wchar_t g_lpPackageName[1024];

	CHAR pMessage[200];
	DWORD cbMessage;
	PBYTE pDataToClient = NULL;
	DWORD cbDataToClient = 0;
	wchar_t *pUserName = NULL;
	DWORD cbUserName = 0;
	SOCKET Server_Socket;
	WSADATA wsaData;
	SECURITY_STATUS ss;
	PSecPkgInfo pkgInfo;
	SecPkgContext_Sizes SecPkgContextSizes;
	SecPkgContext_NegotiationInfo SecPkgNegInfo;
	ULONG cbMaxSignature;
	ULONG cbSecurityTrailer;


};

