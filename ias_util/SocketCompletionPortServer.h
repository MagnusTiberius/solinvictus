#pragma once
// Link to ws2_32.lib
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#include "stdafx.h"

#include "HttpRequest.h"
#include "HttpResponse.h"

#define PORT 5150
#define DATA_BUFSIZE 8192

class SocketCompletionPortServer
{
public:
	SocketCompletionPortServer();
	~SocketCompletionPortServer();

	typedef struct
	{
		OVERLAPPED Overlapped;
		WSABUF DataBuf;
		CHAR Buffer[DATA_BUFSIZE];
		DWORD BytesSEND;
		DWORD BytesRECV;
	} PER_IO_OPERATION_DATA, *LPPER_IO_OPERATION_DATA;

	typedef struct
	{
		SOCKET Socket;
	} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;


	int Start();

	HANDLE GetCompletionPort();

private:
	static DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID);

	HANDLE CompletionPort;

};

