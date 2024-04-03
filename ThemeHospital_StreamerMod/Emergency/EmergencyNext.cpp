#include "pch.h"
#include "EmergencyNext.h"

EmergencyNext::EmergencyNext(DWORD gametick, WORD bonus, BYTE enabled)
{
  this->gametick = gametick;
  this->bonus = bonus;
  this->enabled = enabled;
}