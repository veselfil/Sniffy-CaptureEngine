#pragma once

#include <vector>
#include <iostream>

#define WIN32
#define WINPCAP
#define HAVE_REMOTE

#include <pcap/pcap.h>

typedef struct CaptureDevice {
	int DeviceID;
	std::string DeviceName;
	std::string DeviceDescription;

	void PrintDevice();

} CaptureDevice;

void RegisterCaptureCallback(unsigned int inum, pcap_handler handler);
std::vector<CaptureDevice> ListAllDevices();
void PacketReady(u_char* s, const struct pcap_pkthdr* header, const u_char* data);
