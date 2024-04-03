#include "pch.h"
#include "EmergencyNext.h"

EmergencyNext::EmergencyNext(DWORD gametick, WORD bonus, BYTE enabled, BYTE illness, BYTE amount, BYTE percWin)
{
  this->gametick = gametick;
  this->bonus = bonus;
  this->enabled = enabled;
  this->illness = illness;
  this->amount = amount;
  this->percWin = percWin;
}