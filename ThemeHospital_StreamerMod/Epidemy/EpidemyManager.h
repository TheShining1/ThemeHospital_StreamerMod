#pragma once
#include <chrono>
#include <functional>

typedef DWORD(__cdecl* createPatientFunc)(WORD, BYTE, BYTE);
typedef void(__cdecl* spawnObjectFunc)(DWORD);

class EpidemyManager
{
private:
  static std::shared_ptr<EpidemyManager> instance;
  EpidemyManager(DWORD lpModuleBaseAddress);

  DWORD lpModuleBaseAddress;

  //DWORD _randomSeedFuncOffset = 0x66010;

  DWORD ptRoomsOffset = 0xe5208;
  DWORD* ptRooms;

  DWORD createPatientObjFuncOffset = 0x36bf0;
  createPatientFunc createPatient;

  DWORD spawnObjectFuncOffset = 0x6c120;
  spawnObjectFunc spawnObject;

  DWORD gbvHowContagiousOffset = 0xc47ce;

  unsigned short contagious;

  unsigned short setContagious();
  DWORD* setRooms();
  DWORD setCreatePatient();
  DWORD setSpawnObjectPatient();

public:
  static std::shared_ptr<EpidemyManager> Get(DWORD LpModuleBaseAddress);
  void CreatePatients(BYTE disease, BYTE amount);

  bool WaitDone();
};