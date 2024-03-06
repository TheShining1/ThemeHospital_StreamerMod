#pragma once
#include <string>

class VIP
{
private:

	DWORD _lpModuleBaseAddress;

	DWORD _gbvMayorLaunchOffset = 0xc4828;

	DWORD _hospitalFileAddrOffset = 0xDD124;

	DWORD _vipDaysOffset = 0x1ff;
	DWORD _vipScoreOffset = 0x1fb;

	std::string _username;
	BYTE _score;

public:
	VIP(DWORD lpModuleBaseAddress, std::string Username, BYTE score);
};