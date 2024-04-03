#pragma once

class EmergencyNext
{
private:
  DWORD gametick;
  WORD bonus;
  BYTE enabled;
public:
  EmergencyNext(DWORD gametick, WORD bonus, BYTE enabled);
};