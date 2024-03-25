#pragma once
#include <array>
#include "../Logger.h"
#include "QuakeNext.h"

class QuakeManager
{
private:
  static std::shared_ptr <QuakeManager> instance;
  QuakeManager(DWORD lpModuleBaseAddress);

  DWORD _lpModuleBaseAddress;

  DWORD _indexUsedOffset = 0xe11db;
  DWORD _quakeNextOffset = 0xe11b7;

  std::array<bool,16>* _indexUsed;
  QuakeNext* _quakeNext;

  std::array<bool, 16>* setIndexUsed();
  QuakeNext* setQuakeNext();
public:
  static std::shared_ptr<QuakeManager> Get(DWORD lpModuleBaseAddress);
  void UnsetLastIndex();
  void ReplaceQuakeNext(QuakeNext quake);
};
