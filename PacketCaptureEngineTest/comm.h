#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock.h>

static SOCKET _sock;

bool ConnectToHost(int PortNo, char* IPAddress);
void CloseConnection();
void SendData(u_char* data, u_int dataLength);
