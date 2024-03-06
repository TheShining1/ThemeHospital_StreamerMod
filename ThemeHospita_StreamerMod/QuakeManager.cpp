#include "pch.h"
#include "QuakeManager.h"

QuakeManager::QuakeManager(DWORD lpModuleBaseAddress)
{
	this->_lpModuleBaseAddress = lpModuleBaseAddress;
}