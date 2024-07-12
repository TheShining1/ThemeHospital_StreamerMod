#pragma once
#include <minwindef.h>

struct Emergency {
  WORD TimeLeft;
  BYTE Unk_2;
  BYTE Unk_3;
  WORD Bonus;
  WORD HelicopterIndex;
  BYTE HelicopterUnload;
  BYTE Stage;
  BYTE HelicopterPatientsLeft;
  BYTE Disease;
  BYTE CuredCount;
  BYTE TotalCount;
  BYTE PatientsInHospital;
  BYTE PercWin;
};