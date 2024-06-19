#include "pch.h"
#include "EpidemyManager.h"
#include <thread>

std::shared_ptr<EpidemyManager> EpidemyManager::instance = nullptr;

std::shared_ptr<EpidemyManager> EpidemyManager::Get(DWORD LpModuleBaseAddress)
{
  if (instance == nullptr)
    instance.reset(new EpidemyManager(LpModuleBaseAddress));
  return instance;
}

EpidemyManager::EpidemyManager(DWORD lpModuleBaseAddress)
{
  this->lpModuleBaseAddress = lpModuleBaseAddress;
  this->contagious = setContagious();
  this->ptRooms = setRooms();
  this->createPatient = (createPatientFunc)setCreatePatient();
  this->spawnObject = (spawnObjectFunc)setSpawnObjectPatient();
}

unsigned short EpidemyManager::setContagious()
{
  return *(unsigned short*)(this->lpModuleBaseAddress + this->gbvHowContagiousOffset);
}

DWORD* EpidemyManager::setRooms()
{
  return (DWORD*)(this->lpModuleBaseAddress + this->ptRoomsOffset);
}

DWORD EpidemyManager::setCreatePatient()
{
  return (this->lpModuleBaseAddress + this->createPatientObjFuncOffset);
}

DWORD EpidemyManager::setSpawnObjectPatient()
{
  return (this->lpModuleBaseAddress + this->spawnObjectFuncOffset);
}

void EpidemyManager::CreatePatients(BYTE disease, BYTE amount)
{
  WORD* ptStartPoint = (WORD*)(*ptRooms + 0x23 + 4);

  while (amount > 0)
  {
    amount--;

    DWORD ptPatient = createPatient(*ptStartPoint, disease, 0);
    BYTE* contagious = (BYTE*)(ptPatient + 0xAE);
    *contagious = (BYTE)this->contagious;
    spawnObject(ptPatient);

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

bool EpidemyManager::WaitDone()
{
  return true;
}