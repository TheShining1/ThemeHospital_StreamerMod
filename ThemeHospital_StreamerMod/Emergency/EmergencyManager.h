#pragma once
#include "../Logger.h"
#include "./EmergencyNext.h"

class EmergencyManager
{
private:
  static std::shared_ptr<EmergencyManager> instance;
  EmergencyManager(DWORD LpModuleBaseAddress);

  DWORD lpModuleBaseAddress;

  DWORD emergencyNextOffset = 0xe11ad;

  EmergencyNext* emergencyNext;

  EmergencyNext* setEmergencyNext();
public:
  static std::shared_ptr<EmergencyManager> Get(DWORD LpModuleBaseAddress);

  void ReplaceEmergencyNext(EmergencyNext emergency);
};