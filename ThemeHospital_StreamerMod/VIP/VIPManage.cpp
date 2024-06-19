#include "pch.h"
#include "VIPManager.h"
#include <thread>

std::shared_ptr<VIPManager> VIPManager::instance = nullptr;

std::shared_ptr<VIPManager> VIPManager::Get(DWORD LpModuleBaseAddress, DWORD PtHospitalDataOffset)
{
	if (instance == nullptr)
		instance.reset(new VIPManager(LpModuleBaseAddress, PtHospitalDataOffset));
	return instance;
}

VIPManager::VIPManager(DWORD LpModuleBaseAddress, DWORD PtHospitalDataOffset)
{
	this->lpModuleBaseAddress = LpModuleBaseAddress;
	this->ptHospitalDataOffset = PtHospitalDataOffset;
}

const char* VIPManager::SwapName(const char* Username)
{
	const char*** langTextSections = (const char***)(this->lpModuleBaseAddress + this->langTextSectionsOffset);
	const char** vipNamesSection = langTextSections[0];

	BYTE* vipNameIndex = (BYTE*)(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospitalVIPNameIndexOffset);

	const char* vipNameOld = vipNamesSection[*vipNameIndex];

	vipNamesSection[*vipNameIndex] = Username;

	return vipNameOld;
}

void VIPManager::SetDays()
{
	//short* vipDays = (short*)(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospitalVIPDaysOffset);
	short* vipDays = (short*)(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospitalVIPDaysOffset);
	short vipDaysMax = *(short*)(this->lpModuleBaseAddress + this->gbvMayorLaunchOffset);
	*vipDays = vipDaysMax - 1;
}

BYTE VIPManager::GetStage()
{
	return *(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospitalVIPStageOffset);
}

void VIPManager::DropWaitTime()
{
	int* vipClock = (int*)(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospitalVIPClockOffset);
	*vipClock = 0;
}

void VIPManager::SetScore(int score)
{
	int* vipScore = (int*)(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospitalVIPScoreOffset);
	*vipScore = score;
}

bool VIPManager::IsFaxOpen()
{
	return *(bool*)(this->lpModuleBaseAddress + this->isFaxOpenOffset);
}

bool VIPManager::WaitDone()
{
	return true;
}