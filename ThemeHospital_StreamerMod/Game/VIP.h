#pragma once
#include <minwindef.h>

struct VIP {
  DWORD GameClock;
  unsigned short ObjectIndex;
  BYTE NameIndex;
  BYTE Stage;
  unsigned short Score;
  WORD vipUnk;
  unsigned short DaysFromLast;
};