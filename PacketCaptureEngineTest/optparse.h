#pragma once

#include <iostream>

#define INVALID_ARGS nullptr

typedef struct Parameters {
	const char* IpAddress;
	unsigned short Port;
} Parameters;

bool ParseParams(int argc, char** argv, Parameters* params);