#pragma once

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#include "stdafx.h"
#include "SChannelServer.hpp"

#define PORT 5150
#define DATA_BUFSIZE 8192
#define SOCKET_ARRAY_SZ (1024 * 8)

class SocketSelectServer
{
public:
	SocketSelectServer();
	~SocketSelectServer();

protected:
	typedef struct _SOCKET_INFORMATION {
		CHAR Buffer[DATA_BUFSIZE];
		CHAR BufferOut[DATA_BUFSIZE];
		WSABUF DataBuf;
		WSABUF DataBufOut;
		SOCKET Socket;
		OVERLAPPED Overlapped;
		DWORD BytesSEND;
		DWORD BytesRECV;
	} SOCKET_INFORMATION, *LPSOCKET_INFORMATION;

	// Global var
	DWORD TotalSockets = 0;
	LPSOCKET_INFORMATION SocketArray[SOCKET_ARRAY_SZ];   //FD_SETSIZE


	typedef struct _CONNECTED_ENTITY_INFORMATION {
		CHAR	UserName[512];
		DWORD	Location;
	} CONNECTED_ENTITY_INFORMATION, *LPCONNECTED_ENTITY_INFORMATION;
	LPCONNECTED_ENTITY_INFORMATION ConnectedEntityArray[SOCKET_ARRAY_SZ];   //FD_SETSIZE

	

public:
	int Init(u_short portnum);
	virtual void Request(LPSOCKET_INFORMATION pSocketInfo);

private:
	BOOL CreateSocketInformation(SOCKET s);
	void FreeSocketInformation(DWORD Index);
};

