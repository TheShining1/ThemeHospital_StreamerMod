#pragma once

class Emergency
{
private:
  DWORD _lpModuleBaseAddress;

	DWORD _indexUsedOffset = 0xe11eb;
	DWORD _nextOffset = 0xe11ad;
	DWORD _emergencyCountOffset = 0xe11ce;
	DWORD _skippedOffset = 0x0e118d;

	short _bonus;
	BYTE _illnes;
	BYTE _amount;
	BYTE _percWin;

public:
	Emergency(DWORD lpModuleBaseAddress, short bonus, BYTE illnes, BYTE amount, BYTE percWin);
};