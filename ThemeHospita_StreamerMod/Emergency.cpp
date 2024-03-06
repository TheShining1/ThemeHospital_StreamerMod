#include "pch.h"
#include "Emergency.h"

Emergency::Emergency(DWORD lpModuleBaseAddress, short bonus, BYTE illnes, BYTE amount, BYTE percWin)
{
  this->_lpModuleBaseAddress = lpModuleBaseAddress;
  this->_bonus = bonus;
  this->_illnes = illnes;
  this->_amount = amount;
  this->_percWin = percWin;
}