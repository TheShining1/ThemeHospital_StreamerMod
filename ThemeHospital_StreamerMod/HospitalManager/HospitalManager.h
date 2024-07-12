#pragma once
#include <memory>
#include "../Game/Hospital.h"

class HospitalManager
{
private:
  static std::shared_ptr<HospitalManager> instance;
  HospitalManager(DWORD LpModuleBaseAddress, DWORD PtHospitalOffset);

public:
  static std::shared_ptr<HospitalManager> Get(DWORD LpModuleBaseAddress, DWORD PtHospitalOffset);
  Hospital* hospital;

  bool IsHospitalReady();
};