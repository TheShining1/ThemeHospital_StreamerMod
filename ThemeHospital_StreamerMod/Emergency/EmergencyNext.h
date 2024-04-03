#pragma once

class EmergencyNext
{
private:
  DWORD gametick;
  WORD bonus;
  BYTE enabled;
  BYTE illness;
  BYTE amount;
  BYTE percWin;
public:
  EmergencyNext(DWORD gametick, WORD bonus, BYTE enabled, BYTE illness, BYTE amount, BYTE percWin);
};