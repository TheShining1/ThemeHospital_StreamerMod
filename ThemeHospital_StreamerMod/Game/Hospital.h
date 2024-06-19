#pragma once

struct Hospital
{
  char    Name[41];             // 0x0
  BYTE    Level;                // 0x29
  BYTE    PlayerType;           // 0x2A 1 for local player, 2 for AI
  BYTE    Unk1;                 // 0x2B
  BYTE    Unk2;                 // 0x2C
  int     Salary;               // 0x2D
  DWORD   PrevSalary;           // 0x31
  DWORD   Money;                // 0x35
  BYTE    Unk3_6[4];            // 0x36
  int     Loan;                 // 0x3D
  int     LoanMax;              // 0x41
  DWORD   Unk7;                 // 0x45
  BYTE    Unk8;                 // 0x49
  BYTE    Unk9;                 // 0x4A
  BYTE    Unk10;                // 0x4B

  DWORD   VIPGameClock;         // 0x1F3
  ushort  VIPObjectIndex;       // 0x1F7
  BYTE    VIPNameIndex;         // 0x1F9
  BYTE    VIPStage;             // 0x1FA
  BYTE    VIPScore;             // 0x1FB

  BYTE    VIPDaysFromLast;      // 0x1FF

  BYTE    DaysFromLastDisaster; // 0x20F

  BYTE    IsOpen ? ;              // 0x1256
}