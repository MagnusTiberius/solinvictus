#pragma once
// Link to ws2_32.lib
#include <winsock2.h>
// Link to mswsock.lib
#include <mswsock.h>
#include <windows.h>
#include <stdio.h>

#include "stdafx.h"

#define PORT 5150
#define DATA_BUFSIZE 8192

class SocketOverlapServer
{
public:
	SocketOverlapServer();
	~SocketOverlapServer();

	typedef struct _SOCKET_INFORMATION {
		OVERLAPPED Overlapped;
		SOCKET Socket;
		CHAR Buffer[DATA_BUFSIZE];
		WSABUF DataBuf;
		DWORD BytesSEND;
		DWORD BytesRECV;
	} SOCKET_INFORMATION, *LPSOCKET_INFORMATION;

	int Start();
	static void CALLBACK WorkerRoutine(DWORD Error, DWORD BytesTransferred, LPWSAOVERLAPPED Overlapped, DWORD InFlags);
};

