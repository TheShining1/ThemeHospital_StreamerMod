#pragma once
#include <string>

class VIP
{
private:
	DWORD _vipScoreOffset = 0x1fb;

	std::string _username;
	BYTE _score;

public:
	VIP(DWORD lpModuleBaseAddress, std::string Username, BYTE score);
};