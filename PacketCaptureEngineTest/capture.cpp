#include "stdafx.h"
#include "capture.h"

void CaptureDevice::PrintDevice() 
{
	std::cout << "ID: " << DeviceID << ", Name: " << DeviceName.c_str() << std::endl;
	std::cout << "Description: " << &DeviceDescription[0] << std::endl;
	std::cout << std::endl;
}

void RegisterCaptureCallback(unsigned int inum, pcap_handler handler)
{
	pcap_t *pcaphandle;
	pcap_if_t *allDevices;
	pcap_if_t *captureDevice;
	unsigned short i;

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_findalldevs(&allDevices, errbuf);

	for (captureDevice = allDevices, i = 0; i < inum - 1; captureDevice = captureDevice->next, i++);

	pcap_t* pcapHandle = pcap_open(captureDevice->name, 100, PCAP_OPENFLAG_PROMISCUOUS, 20, NULL, errbuf);
	pcap_loop(pcapHandle, 0, handler, NULL);
}

std::vector<CaptureDevice> ListAllDevices()
{
	std::vector<CaptureDevice> devices;
	pcap_if_t *allDevices, *device;

	unsigned short i = 0;
	char errbuf[PCAP_ERRBUF_SIZE];

	pcap_findalldevs(&allDevices, (char*)errbuf);

	for (device = allDevices; device; device = device->next)
	{
		CaptureDevice capDev;

		capDev.DeviceID = ++i;
		if (device->description)
			capDev.DeviceDescription = std::string(device->description);
		else
			capDev.DeviceDescription = std::string("(No description available)");

		capDev.DeviceName = std::string(device->name);

		devices.push_back(capDev);
	}

	return devices;
}
