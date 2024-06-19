#pragma once
#include <array>
#include "../Logger.h"
#include "./EmergencyNext.h"

class EmergencyManager
{
private:
  static std::shared_ptr<EmergencyManager> instance;
  EmergencyManager(DWORD LpModuleBaseAddress, DWORD PtHospitalDataOffset);

  DWORD lpModuleBaseAddress;
  DWORD ptHospitalDataOffset;

  DWORD emergencyIndexUsedOffset = 0xe11eb;
  DWORD emergencySkippedCountOffset = 0xe11ce;
  DWORD emergencyNextOffset = 0xe11ad;

  DWORD hospitalEmergencyStageOffset = 0x1e2;

  std::chrono::duration<int> waitDuration = std::chrono::minutes(5);

  BYTE* emergencySkippedCount;
  std::array<bool,16>* emergencyIndexUsed;
  EmergencyNext* emergencyNext;
  BYTE* emergencyStage;

  BYTE* setEmergencySkippedCount();
  std::array<bool, 16>* setIndexUsed();
  EmergencyNext* setEmergencyNext();
  BYTE* setEmergencyStage();
public:
  static std::shared_ptr<EmergencyManager> Get(DWORD LpModuleBaseAddress, DWORD PtHospitalDataOffset);

  void UnsetLastIndex();
  void DecrementSkippedCount();
  void ReplaceEmergencyNext(EmergencyNext emergency);
  bool WaitDone();
};