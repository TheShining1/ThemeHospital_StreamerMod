#include "pch.h"
#include <thread>

#include "./GameManager.h"

#pragma region GameManager
std::shared_ptr<GameManager> GameManager::instance = nullptr;

std::shared_ptr<GameManager> GameManager::Get()
{
	if (instance == nullptr)
		throw("GameManager is not initialized");
	return instance;
}

std::shared_ptr<GameManager> GameManager::Get(uint32_t LpModuleBaseAddress, GameOffsets gameOffsets)
{
	if (instance == nullptr)
		instance.reset(new GameManager(LpModuleBaseAddress, gameOffsets));
	return instance;
}

GameManager::GameManager(uint32_t LpModuleBaseAddress, GameOffsets gameOffsets)
{
	setGlobals(LpModuleBaseAddress, gameOffsets.globalsOffset);
	setDisastersMembers(LpModuleBaseAddress, gameOffsets.disastersOffsets);
	setEmergencyMembers(LpModuleBaseAddress, gameOffsets.emergencyOffsets);
	setEpidemicMembers(LpModuleBaseAddress, gameOffsets.epidemicOffsets);

	setQuakeMembers(LpModuleBaseAddress, gameOffsets.quakeOffsets);
}
#pragma endregion
#pragma region Globals
void GameManager::setGlobals(uint32_t LpModuleBaseAddress, GlobalsOffset globalsOffset)
{
	this->howContagious = (uint8_t*)(LpModuleBaseAddress + globalsOffset.howContagious);
	this->mayorLaunch = (uint16_t*)(LpModuleBaseAddress + globalsOffset.mayorLaunch);
	this->isFaxOpen = (bool*)(LpModuleBaseAddress + globalsOffset.isFaxOpen);
	this->hospital = *(Hospital**)(LpModuleBaseAddress + globalsOffset.hospital);
	this->cameraPositionLimit = (CameraPosition*)(LpModuleBaseAddress + globalsOffset.cameraPositionLimit);
	this->rooms = *(std::array<Room,25>**)(LpModuleBaseAddress + globalsOffset.rooms);
	this->langTextSections = (LangTextSections*)(LpModuleBaseAddress + globalsOffset.langTextSections);
}
#pragma endregion

#pragma region Disasters
void GameManager::setDisastersMembers(uint32_t LpModuleBaseAddress, DisastersOffsets offsets)
{
	this->vomitLimit = (uint16_t*)(LpModuleBaseAddress + offsets.VomitLimit);
	this->doctorPopupText = (uint16_t*)(LpModuleBaseAddress + offsets.DoctorPopupText);
}

void GameManager::BoilerBreak(uint8_t type)
{
	this->hospital->heatLevelLock = true;
	this->hospital->heatLevelPrev = this->hospital->heatLevel;

	switch (type)
	{
	case BoilerDown:
		this->hospital->heatLevel = HEATMIN;
		break;
	case BoilerUp:
		this->hospital->heatLevel = HEATMAX;
	}
}

void GameManager::VomitWave()
{
	this->vomitLimit = 0;
}

void GameManager::SetPopup(uint16_t index)
{
	*this->doctorPopupText = doctorPopupTextIndexes[index - 1];
}

void GameManager::SetDisasterDuration()
{
	uint8_t duration = rand() % 30 + 10;
	this->hospital->disasterDuration = duration;
};

void GameManager::SetDisasterType(uint8_t type)
{
	this->hospital->disasterType = type;
};

void GameManager::ResetDisasterDays()
{
	this->hospital->daysFromLastDisaster = 0;
};
#pragma endregion
#pragma region Quake
void GameManager::setQuakeMembers(uint32_t LpModuleBaseAddress, QuakeOffsets offsets)
{
	this->quakeIndexUsed = (std::array<bool, 16>*)(LpModuleBaseAddress + offsets.IndexUsed);
	this->quakeNext = (QuakeNext*)(LpModuleBaseAddress + offsets.Next);
	this->quakeNextClock = (int*)(LpModuleBaseAddress + offsets.NextClock);
	this->quakeStage = (BYTE*)(LpModuleBaseAddress + offsets.Stage);
}

void GameManager::quakeUnsetLastIndex()
{
	for (int i = this->quakeIndexUsed->size() - 1; i >= 0; i--)
	{
		if (this->quakeIndexUsed->at(i) == true)
		{
			this->quakeIndexUsed->at(i) = false;
			return;
		}
	}
};
#pragma endregion
#pragma region Emergency
void GameManager::setEmergencyMembers(uint32_t LpModuleBaseAddress, EmergencyOffsets offsets)
{
	this->emergencyNext = (EmergencyNext*)(LpModuleBaseAddress + offsets.Next);
	this->emergencyIndexUsed = (std::array<bool, 16>*)(LpModuleBaseAddress + offsets.IndexUsed);
	this->emergencySkippedCount = (BYTE*)(LpModuleBaseAddress + offsets.SkippedCount);
}

void GameManager::emergencyUnsetLastIndex()
{
	for (int i = this->emergencyIndexUsed->size() - 1; i >= 0; i--)
	{
		if (this->emergencyIndexUsed->at(i) == true)
		{
			this->emergencyIndexUsed->at(i) = false;
			return;
		}
	}
};
#pragma endregion

#pragma  region Epidemic
void GameManager::setEpidemicMembers(uint32_t LpModuleBaseAddress, EpidemicOffsets offsets)
{
	createPatient = (createPatientFunc)(LpModuleBaseAddress + offsets.createPatientObjFunc);
	spawnObject = (spawnObjectFunc)(LpModuleBaseAddress + offsets.spawnObjectFunc);
};

void GameManager::CreatePatients(uint8_t disease, uint8_t amount)
{
	Room room = this->rooms->at(1);

	uint16_t ptStartPoint = room.SpawnPoint;

	while (amount > 0)
	{
		amount--;

		GameObject* patient = this->createPatient(ptStartPoint, disease, 0);
		patient->Contagious = *this->howContagious;
		this->spawnObject(patient);

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
};
#pragma endregion

#pragma region VIP
void GameManager::vipSetDays()
{
	this->hospital->VIP.DaysFromLast = *this->mayorLaunch - 1;
}

VIPStages GameManager::GetVIPStage()
{
	return this->hospital->VIP.Stage;
}
const char* GameManager::VIPSwapName(const char* newName)
{
	uint8_t nameIndex = this->hospital->VIP.NameIndex;
	const char* oldName = this->langTextSections->VIPNames->at(nameIndex);
	this->langTextSections->VIPNames->at(nameIndex) = newName;

	return oldName;
}

void GameManager::VIPDropWaitTime()
{
	this->hospital->VIP.GameClock = 0;
}

void GameManager::VIPSetScore(uint16_t score)
{
	this->hospital->VIP.Score = score;
}
#pragma endregion

bool GameManager::IsHospitalReady()
{
	return this->hospital->IsOpen && this->hospital->ReceptionistsCount > 0;
}

void GameManager::UnlockCamera()
{
	this->cameraPositionLimit->min = CameraPosMinValue;
	this->cameraPositionLimit->max = CameraPosMaxValue;
}