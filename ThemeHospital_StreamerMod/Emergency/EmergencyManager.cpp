#include "pch.h"
#include <chrono>
#include <thread>
#include "EmergencyManager.h"

std::shared_ptr<EmergencyManager> EmergencyManager::instance = nullptr;

std::shared_ptr<EmergencyManager> EmergencyManager::Get(DWORD LpModuleBaseAddress, DWORD PtHospitalDataOffset)
{
	if (instance == nullptr)
		instance.reset(new EmergencyManager(LpModuleBaseAddress, PtHospitalDataOffset));
	return instance;
}

EmergencyManager::EmergencyManager(DWORD LpModuleBaseAddress, DWORD PtHospitalDataOffset)
{
	this->lpModuleBaseAddress = LpModuleBaseAddress;
	this->ptHospitalDataOffset = PtHospitalDataOffset;

	this->emergencyIndexUsed = this->setIndexUsed();
	this->emergencyNext = this->setEmergencyNext();
}

std::array<bool, 16>* EmergencyManager::setIndexUsed()
{
	return (std::array<bool, 16>*)(this->lpModuleBaseAddress + this->emergencyIndexUsedOffset);
}

BYTE* EmergencyManager::setEmergencySkippedCount()
{
	return (BYTE*)(this->lpModuleBaseAddress + this->emergencySkippedCountOffset);
}

EmergencyNext* EmergencyManager::setEmergencyNext()
{
	return (EmergencyNext*)(this->lpModuleBaseAddress + this->emergencyNextOffset);
}

void EmergencyManager::UnsetLastIndex()
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

void EmergencyManager::DecrementSkippedCount()
{
	this->emergencySkippedCount--;
};

void EmergencyManager::ReplaceEmergencyNext(EmergencyNext emergency)
{
	this->emergencyStage = this->setEmergencyStage();
	*this->emergencyNext = emergency;
};

BYTE* EmergencyManager::setEmergencyStage()
{
	return (BYTE*)(*(BYTE**)(this->lpModuleBaseAddress + this->ptHospitalDataOffset) + this->hospitalEmergencyStageOffset);
}

bool EmergencyManager::WaitDone()
{
	const auto start = std::chrono::steady_clock::now();
	auto now = std::chrono::steady_clock::now();

	do
	{
		LOG_DEBUG("EmergencyManager::WaitDone");
		now = std::chrono::steady_clock::now();
		if ((now - start) > waitDuration) return false;

		std::this_thread::sleep_for(std::chrono::seconds(1));
	} while (*this->emergencyStage == 0);

	return true;
}