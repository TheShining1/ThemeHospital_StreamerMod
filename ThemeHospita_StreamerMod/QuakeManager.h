#pragma once

class QuakeManager
{
private:
  DWORD _lpModuleBaseAddress;

  DWORD _indexUsedOffset = 0xe11db;
  DWORD _nextOffset = 0xe11b7;

public:
  QuakeManager(DWORD lpModuleBaseAddress);
};