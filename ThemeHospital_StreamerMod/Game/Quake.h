#pragma once
#include <minwindef.h>

struct QuakeOffsets
{
  DWORD NextClock;  // 0xe117b
  DWORD Stage;      // 0xe117f
  DWORD Next;       // 0xe11b7
  DWORD IndexUsed;  // 0xe11db
};

struct QuakeNext
{
  int GameClock;
  BYTE Severity;
  bool Enabled;
};