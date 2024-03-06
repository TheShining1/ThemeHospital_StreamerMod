#pragma once
#include <array>

class QuakeManager
{
private:
  DWORD _lpModuleBaseAddress;

  DWORD _indexUsedOffset = 0xe11db;
  DWORD _nextOffset = 0xe11b7;

  std::array<bool,16>* _indexUsed;

public:
  QuakeManager(DWORD lpModuleBaseAddress);
  std::array<bool, 16>* SetIndexUsed();
};