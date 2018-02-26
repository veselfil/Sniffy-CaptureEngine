#include "stdafx.h"
#include "comm.h"

static int PortNumber;
static char* IPAddress;
static SOCKADDR_IN Target;

bool CreateSocket(int portNo, char* ip)
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

	Target.sin_family = AF_INET;
	Target.sin_port = htons(portNo);
	Target.sin_addr.s_addr = inet_addr(ip);

	_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (_sock == INVALID_SOCKET)
	{
		return false;
	}

	PortNumber = portNo;
	IPAddress = ip;
}

void CloseConnection()
{
	if (_sock)
		closesocket(_sock);

	WSACleanup(); // retarded windows bullshit
}

void SendData(u_char* data, u_int dataLength)
{
	sendto(_sock, (const char*)data, dataLength, 0, (SOCKADDR *) &Target, sizeof(Target));
}
