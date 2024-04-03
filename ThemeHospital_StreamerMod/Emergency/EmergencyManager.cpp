#include "pch.h"
#include "EmergencyManager.h"

std::shared_ptr<EmergencyManager> EmergencyManager::instance = nullptr;

std::shared_ptr<EmergencyManager> EmergencyManager::Get(DWORD LpModuleBaseAddress)
{
	if (instance == nullptr)
		instance.reset(new EmergencyManager(LpModuleBaseAddress));
	return instance;
}

EmergencyManager::EmergencyManager(DWORD LpModuleBaseAddress)
{
	this->lpModuleBaseAddress = LpModuleBaseAddress;

	this->emergencyNext = this->setEmergencyNext();
}

EmergencyNext* EmergencyManager::setEmergencyNext()
{
	return (EmergencyNext*)(this->lpModuleBaseAddress + this->emergencyNextOffset);
}

void EmergencyManager::ReplaceEmergencyNext(EmergencyNext emergency)
{
	*this->emergencyNext = emergency;
};