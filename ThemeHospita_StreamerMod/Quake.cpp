#include "pch.h"
#include "Quake.h"

Quake::Quake(DWORD lpModuleBaseAddress, BYTE severity)
{
	this->_lpModuleBaseAddress = lpModuleBaseAddress;
	this->_severity = severity;
}