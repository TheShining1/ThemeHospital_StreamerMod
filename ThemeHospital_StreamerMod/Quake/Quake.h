#pragma once

class Quake
{
private:
  WORD _startMonth;
  WORD _endMonth;
  WORD _severity;

public:
  Quake(WORD _startMonth, WORD _endMonth, WORD severity);
};