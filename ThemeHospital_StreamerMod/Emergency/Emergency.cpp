#include "pch.h"
#include "Emergency.h"

Emergency::Emergency(DWORD lpModuleBaseAddress, short bonus, BYTE illness, BYTE amount, BYTE percWin)
{
  this->lpModuleBaseAddress = lpModuleBaseAddress;

  this->bonus = bonus;
  this->illness = illness;
  this->amount = amount;
  this->percWin = percWin;
}