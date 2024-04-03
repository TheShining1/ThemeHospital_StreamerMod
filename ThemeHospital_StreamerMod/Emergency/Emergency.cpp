#include "pch.h"
#include "Emergency.h"

Emergency::Emergency(DWORD lpModuleBaseAddress, short bonus, BYTE illnes, BYTE amount, BYTE percWin)
{
  this->lpModuleBaseAddress = lpModuleBaseAddress;

  this->bonus = bonus;
  this->illnes = illnes;
  this->amount = amount;
  this->percWin = percWin;
}