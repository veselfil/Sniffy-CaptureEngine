// PacketCaptureEngineTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

#include "capture.h"
#include "comm.h"
#include "optparse.h"

#define PAUSE system("PAUSE")

int main(int argc, char** argv)
{
	std::cout << argc << std::endl;

	Parameters p;
	if (!ParseParams(argc, argv, &p)) 
	{
		std::cout << "Invalid arguments, usage: PacketCaptureEngine.exe -a <ip_address> -p <port>." << std::endl;
		return 1;
	}

	std::cout << "Address: " << p.IpAddress << std::endl;
	std::cout << "Port: " << p.Port << std::endl;

	std::vector<CaptureDevice> devices = ListAllDevices();
	for (auto &device : devices)
	{
		device.PrintDevice();
	}

	bool connectionSuccessful = ConnectToHost(5005, (char*) "127.0.0.1");

	if (!connectionSuccessful) 
	{
		std::cerr << "Could not connect to display component!" << std::endl;
		PAUSE;
		return 1;
	}

	RegisterCaptureCallback(1, PacketReady);
	CloseConnection();

	PAUSE;
	return 0;
}

void PacketReady(u_char* s, const struct pcap_pkthdr* header, const u_char* data)
{
	std::cout << "Captured a packet of length: " << header->caplen << std::endl;
	SendData((u_char*) data, header->caplen);
}