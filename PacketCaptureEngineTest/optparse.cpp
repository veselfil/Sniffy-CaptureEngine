#include "stdafx.h"
#include "optparse.h"

bool ParseParams(int argc, char** argv, Parameters* params) 
{
	if (argc != 5) return false;

	for (int i = 1; i < argc; i += 2) {
		if (strcmp(argv[i], "-a") == 0)
			params->IpAddress = argv[i + 1];
		else if (strcmp(argv[i], "-p") == 0)
			params->Port = std::atoi(argv[i + 1]);
	}

	return true;
}