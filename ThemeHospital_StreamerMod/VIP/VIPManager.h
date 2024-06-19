#pragma once
#include "../Logger.h"
#include <chrono>
#include "VIPCommand.h"

class VIPManager
{
private:
  static std::shared_ptr<VIPManager> instance;
  VIPManager(DWORD LpModuleBaseAddress, DWORD PtHospitalDataOffset);

  DWORD lpModuleBaseAddress;
  DWORD ptHospitalDataOffset;

  DWORD langTextSectionsOffset = 0xdaf60;
  DWORD isFaxOpenOffset = 0xdefb0;

  DWORD gbvMayorLaunchOffset = 0xc4828;

  DWORD hospitalVIPNameIndexOffset = 0x1f9;
  DWORD hospitalVIPStageOffset = 0x1fa;
  DWORD hospitalVIPScoreOffset = 0x1fb;
  DWORD hospitalVIPDaysOffset = 0x1ff;
  DWORD hospitalVIPClockOffset = 0x1f3;

public:
  static std::shared_ptr<VIPManager> Get(DWORD LpModuleBaseAddress, DWORD PtHospitalDataOffset);
  const char* SwapName(const char* Username);
  void RevertName();
  void SetDays();
  BYTE GetStage();
  void DropWaitTime();
  void SetScore(int score);
  bool IsFaxOpen();

  bool WaitDone();
};