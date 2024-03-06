#pragma once

class Quake
{
private:
  DWORD _lpModuleBaseAddress;

  DWORD _indexUsedOffset = 0xe11db;
  DWORD _nextOffset = 0xe11b7;

  BYTE _severity;

public:
  Quake(DWORD lpModuleBaseAddress, BYTE severity);
};