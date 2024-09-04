#pragma once
#include <array>
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include <thread>
#include "../Game/Game.h"

class GameManager
{
private:
  static std::shared_ptr<GameManager> instance;
  GameManager(uint32_t LpModuleBaseAddress, GameOffsets gameOffsets);

  void setGlobals(uint32_t LpModuleBaseAddress, GlobalsOffset globalsOffset);

  void setDisastersMembers(uint32_t LpModuleBaseAddress, DisastersOffsets offsets);
  void setEmergencyMembers(uint32_t LpModuleBaseAddress, EmergencyOffsets offsets);
  void setEpidemicMembers(uint32_t LpModuleBaseAddress, EpidemicOffsets offsets);
  void setQuakeMembers(uint32_t LpModuleBaseAddress, QuakeOffsets offsets);

public:
  static std::shared_ptr<GameManager> Get();
  static std::shared_ptr<GameManager> Get(uint32_t LpModuleBaseAddress, GameOffsets gameOffsets);

  LangTextSections* langTextSections;
  Hospital* hospital;
  std::array<Room, 25>* rooms;
  CameraPosition* cameraPositionLimit;
  uint8_t* howContagious;
  bool* isFaxOpen;

  bool IsHospitalReady();
  void UnlockCamera();
#pragma region Disasters
  uint16_t* doctorPopupText;
  uint16_t* vomitLimit;
  void BoilerBreak(uint8_t type);
  void VomitWave();
  void SetPopup(uint16_t index);
  void SetDisasterDuration();
  void SetDisasterType(uint8_t type);
  void ResetDisasterDays();
#pragma endregion
#pragma region Quake
  std::array<bool, 16>* quakeIndexUsed;
  QuakeNext* quakeNext;
  int* quakeNextClock;
  BYTE* quakeStage;
  void quakeUnsetLastIndex();
#pragma endregion
#pragma region Emergency
  std::array<bool, 16>* emergencyIndexUsed;
  EmergencyNext* emergencyNext;
  uint8_t* emergencySkippedCount;
  void emergencyUnsetLastIndex();
#pragma endregion

#pragma region Epidemic
  createPatientFunc createPatient;
  spawnObjectFunc spawnObject;
  void CreatePatients(uint8_t disease, uint8_t amount);
#pragma endregion

#pragma region VIP
  uint16_t* mayorLaunch;
  void vipSetDays();
  VIPStages GetVIPStage();
  const char* VIPSwapName(const char* newName);
  void VIPDropWaitTime();
  void VIPSetScore(uint16_t score);
#pragma endregion
};