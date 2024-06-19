#include "pch.h"
#include "DisasterManager.h"

std::shared_ptr<DisasterManager> DisasterManager::instance = nullptr;

std::shared_ptr<DisasterManager> DisasterManager::Get(DWORD LpModuleBaseAddress, DWORD PtHospitalDataOffset)
{
	if (instance == nullptr)
		instance.reset(new DisasterManager(LpModuleBaseAddress, PtHospitalDataOffset));
	return instance;
}

DisasterManager::DisasterManager(DWORD LpModuleBaseAddress, DWORD PtHospitalDataOffset)
{
	this->lpModuleBaseAddress = LpModuleBaseAddress;
	this->ptHospitalDataOffset = PtHospitalDataOffset;
}

void DisasterManager::BreakBoiler(BYTE type)
{
	bool* heatLevelLock = (bool*)(*(bool**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospHeatLevelLockOffset);
	*heatLevelLock = 1;
	
	BYTE* heatLevel = (BYTE*)(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospHeatLevelOffset);
	BYTE* heatLevelPrev = (BYTE*)(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospHeatLevelPrevOffset);
	*heatLevelPrev = *heatLevel;

	if (type == 1)
	{
		*heatLevel = this->heatMin;
	} else {
		*heatLevel = this->heatMax;
	}
}

short DisasterManager::SwapVomitLimit(short limit)
{
	short* gbvVomitLimit = (short*)(this->lpModuleBaseAddress + this->gbvVomitLimitOffset);
	short oldLimit = *gbvVomitLimit;
	*gbvVomitLimit = limit;

	return oldLimit;
}
void DisasterManager::SetPopup(BYTE type)
{
	short* gbvDoctorPopupText = (short*)(this->lpModuleBaseAddress + this->gbvDoctorPopupTextOffset);
	*gbvDoctorPopupText = this->doctorPopupText[type - 1];
}

void DisasterManager::SetLength()
{
	BYTE length = rand() % 30 + 10;
	BYTE* disasterLength = (BYTE*)(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospDisasterLengthOffset);
	*disasterLength = length;
}

void DisasterManager::SetType(BYTE type)
{
	BYTE* disasterType = (BYTE*)(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospDisasterTypeOffset);
	*disasterType = type;
}

BYTE DisasterManager::GetType()
{
	return *(BYTE*)(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospDisasterTypeOffset);
}

void DisasterManager::ResetDays()
{
	short* daysFromDisaster = (short*)(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospDaysFromLastDisasterOffset);
	*daysFromDisaster = 0;
}

bool DisasterManager::WaitDone()
{
	return true;
}