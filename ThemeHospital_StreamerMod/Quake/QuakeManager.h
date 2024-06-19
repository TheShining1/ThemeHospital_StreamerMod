#pragma once
#include <array>
#include <chrono>
#include "../Logger.h"
#include "QuakeNext.h"
#include "QuakeCommand.h"

class QuakeManager
{
private:
  static std::shared_ptr <QuakeManager> instance;
  QuakeManager(DWORD lpModuleBaseAddress);

  DWORD _lpModuleBaseAddress;

  DWORD _indexUsedOffset = 0xe11db;
  DWORD _quakeNextOffset = 0xe11b7;
  DWORD _quakeStageOffset = 0xe117f;
  DWORD _quakeNextClockOffset = 0xe117b;

  std::chrono::duration<int> _waitDuration = std::chrono::minutes(5);

  std::array<bool,16>* _indexUsed;
  QuakeNext* _quakeNext;
  BYTE* _quakeStage;

  std::array<bool, 16>* setIndexUsed();
  QuakeNext* setQuakeNext();
  BYTE* setQuakeStage();
public:
  static std::shared_ptr<QuakeManager> Get(DWORD lpModuleBaseAddress);
  void UnsetLastIndex();
  void ReplaceQuakeNext(QuakeNext quake);
  void DropWaitTime();
  bool WaitDone();
};
