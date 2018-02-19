#include "stdafx.h"
#include "comm.h"

bool ConnectToHost(int PortNo, char* IPAddress)
{
	WSADATA wsadata; // retarded windows bullshit

	int error = WSAStartup(0x0202, &wsadata); // retarded windows bullshit

	if (error)
		return false;

	if (wsadata.wVersion != 0x0202) // retarded windows bullshit
	{
		WSACleanup(); // retarded windows bullshit 
		return false;
	}

	SOCKADDR_IN target;

	target.sin_family = AF_INET;
	target.sin_port = htons(PortNo);
	target.sin_addr.s_addr = inet_addr(IPAddress);

	_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_sock == INVALID_SOCKET)
	{
		return false;
	}

	if (connect(_sock, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CloseConnection()
{
	if (_sock)
		closesocket(_sock);

	WSACleanup(); // retarded windows bullshit
}

void SendData(u_char* data, u_int dataLength)
{
	send(_sock, (const char*)data, dataLength, 0);
}
