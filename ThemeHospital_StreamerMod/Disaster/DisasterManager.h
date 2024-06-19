#pragma once
#include "../Logger.h"

class DisasterManager
{
private:
  static std::shared_ptr<DisasterManager> instance;
  DisasterManager(DWORD LpModuleBaseAddress, DWORD PtHospitalDataOffset);

  DWORD lpModuleBaseAddress;
  DWORD ptHospitalDataOffset;

  DWORD gbvVomitLimitOffset = 0xc481a;

  DWORD gbvDoctorPopupTextOffset = 0xdcb92;

  int doctorPopupText[3] = { 11,10,13 };

  //int doctorPopupTextHeatDownIndex = 11;
  //int doctorPopupTextHeatUpIndex = 10;
  //int doctorPopupTextVomitWaveIndex = 13;

  DWORD hospDaysFromLastDisasterOffset = 0x20f;
  DWORD hospHeatLevelPrevOffset = 0x211;
  DWORD hospDisasterTypeOffset = 0x213;
  DWORD hospDisasterLengthOffset = 0x214;

  DWORD hospHeatLevelOffset = 0xc94;
  DWORD hospHeatLevelLockOffset = 0xc95;

  int heatMin = 0;
  int heatMax = 10;

public:
  static std::shared_ptr<DisasterManager> Get(DWORD LpModuleBaseAddress, DWORD PtHospitalDataOffset);

  void BreakBoiler(BYTE type);
  short SwapVomitLimit(short limit);
  void SetLength();
  void SetPopup(BYTE type);
  void SetType(BYTE type);
  BYTE GetType();
  void ResetDays();

  bool WaitDone();
};