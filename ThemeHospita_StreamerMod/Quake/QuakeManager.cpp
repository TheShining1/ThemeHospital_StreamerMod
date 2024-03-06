#include "pch.h"
#include "QuakeManager.h"
#include <iostream>

QuakeManager::QuakeManager(DWORD lpModuleBaseAddress)
{
	this->_lpModuleBaseAddress = lpModuleBaseAddress;

	this->_indexUsed = this->SetIndexUsed();
}

std::array<bool, 16>* QuakeManager::SetIndexUsed()
{
	return (std::array<bool, 16>*)(this->_lpModuleBaseAddress + this->_indexUsedOffset);;
}