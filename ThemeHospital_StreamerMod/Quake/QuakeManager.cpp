#include "pch.h"
#include "QuakeManager.h"
#include <iostream>
#include <chrono>
#include <thread>

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
	this->_quakeStage = this->setQuakeStage();
}

std::array<bool, 16>* QuakeManager::setIndexUsed()
{
	return (std::array<bool, 16>*)(this->_lpModuleBaseAddress + this->_indexUsedOffset);
}

QuakeNext* QuakeManager::setQuakeNext()
{
	return (QuakeNext*)(this->_lpModuleBaseAddress + this->_quakeNextOffset);
}

BYTE* QuakeManager::setQuakeStage()
{
	return (BYTE*)(this->_lpModuleBaseAddress + this->_quakeStageOffset);
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
	*this->_quakeNext = quake;
};

void QuakeManager::DropWaitTime()
{
	int* quakeClock = (int*)(this->_lpModuleBaseAddress + this->_quakeNextClockOffset);
	*quakeClock = 0;
}

bool QuakeManager::WaitDone()
{
	const auto start = std::chrono::steady_clock::now();
	auto now = std::chrono::steady_clock::now();

	do
	{
		LOG_DEBUG("QuakeManager::WaitDone");
		now = std::chrono::steady_clock::now();
		if ((now - start) > _waitDuration) return false;
		
		std::this_thread::sleep_for(std::chrono::seconds(1));
	} while (*this->_quakeStage != 4);

	return true;
}