#include "pch.h"
#include "QuakeManager.h"
#include <iostream>

std::shared_ptr<QuakeManager> QuakeManager::instance = nullptr;

std::shared_ptr<QuakeManager> QuakeManager::Get(DWORD lpModuleBaseAddress)
{
	if (instance == nullptr)
		instance.reset(new QuakeManager(lpModuleBaseAddress));
	return instance;
}

QuakeManager::QuakeManager(DWORD lpModuleBaseAddress)
{
	this->_lpModuleBaseAddress = lpModuleBaseAddress;

	this->_indexUsed = this->setIndexUsed();
	this->_quakeNext = this->setQuakeNext();
}

std::array<bool, 16>* QuakeManager::setIndexUsed()
{
	return (std::array<bool, 16>*)(this->_lpModuleBaseAddress + this->_indexUsedOffset);
}

QuakeNext* QuakeManager::setQuakeNext()
{
	return (QuakeNext*)(this->_lpModuleBaseAddress + this->_quakeNextOffset);
}

void QuakeManager::UnsetLastIndex()
{
	for (int i = this->_indexUsed->size() - 1; i >= 0; i--)
	{
		if (this->_indexUsed->at(i) == true)
		{
			this->_indexUsed->at(i) = false;
			return;
		}
	}
};

void QuakeManager::ReplaceQuakeNext(QuakeNext quake)
{
	this->_quakeNext->_gametick = quake._gametick;
	this->_quakeNext->_severity = quake._severity;
	this->_quakeNext->_enabled = quake._enabled;
};