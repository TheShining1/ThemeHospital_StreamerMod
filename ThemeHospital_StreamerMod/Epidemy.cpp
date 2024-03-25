#include "pch.h"
#include "Epidemy.h"

Epidemy::Epidemy(DWORD lpModuleBaseAddress, BYTE disease, DWORD count)
{
  this->_lpModuleBaseAddress = lpModuleBaseAddress;
  this->_disease = disease;
  this->_count = count;
}