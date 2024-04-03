#pragma once

class Emergency
{
private:
  DWORD lpModuleBaseAddress;

	DWORD indexUsedOffset = 0xe11eb;
	DWORD nextOffset = 0xe11ad;
	DWORD emergencyCountOffset = 0xe11ce;
	DWORD skippedOffset = 0x0e118d;

	short bonus;
	BYTE illnes;
	BYTE amount;
	BYTE percWin;

public:
	Emergency(DWORD lpModuleBaseAddress, short bonus, BYTE illnes, BYTE amount, BYTE percWin);
};