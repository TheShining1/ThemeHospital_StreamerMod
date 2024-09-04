#pragma once
#include <minwindef.h>

struct EmergencyOffsets
{
  uint32_t Next;          // 0xe11ad;
  uint32_t SkippedCount;  // 0xe11ce;
  uint32_t IndexUsed;     // 0xe11eb;
};

struct Emergency {
  uint16_t TimeLeft;
  int8_t Unk_2;
  int8_t Unk_3;
  uint16_t Bonus;
  uint16_t HelicopterIndex;
  uint8_t HelicopterUnload;
  uint8_t Stage;
  uint8_t HelicopterPatientsLeft;
  uint8_t Disease;
  uint8_t CuredCount;
  uint8_t TotalCount;
  uint8_t PatientsInHospital;
  uint8_t PercWin;
};

struct EmergencyNext {
  uint32_t Gametick;
  uint16_t Bonus;
  bool Enabled;
  uint8_t Illness;
  uint8_t Amount;
  uint8_t PercWin;
};