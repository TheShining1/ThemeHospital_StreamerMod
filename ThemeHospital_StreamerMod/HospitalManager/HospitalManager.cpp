#include "pch.h"

#include "./HospitalManager.h"
#include "../Game/Hospital.h"

std::shared_ptr<HospitalManager> HospitalManager::instance = nullptr;

std::shared_ptr<HospitalManager> HospitalManager::Get(DWORD LpModuleBaseAddress, DWORD PtHospitalOffset)
{
	if (instance == nullptr)
		instance.reset(new HospitalManager(LpModuleBaseAddress, PtHospitalOffset));
	return instance;
}

HospitalManager::HospitalManager(DWORD LpModuleBaseAddress, DWORD PtHospitalOffset)
{
	this->hospital = *(Hospital**)(LpModuleBaseAddress + PtHospitalOffset);
}

bool HospitalManager::IsHospitalReady()
{
	return this->hospital->IsOpen == false && this->hospital->ReceptionistsCount > 0;
}