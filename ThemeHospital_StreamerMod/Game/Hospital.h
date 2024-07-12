#pragma once
#include <minwindef.h>

#pragma pack(1)

#include "./Emergency.h"
#include "./VIP.h"
#include "./Epidemic.h"
#include "./HospitalPolicy.h"
#include "./RatHole.h"

#include "./UnkStuff.h"

struct Hospital {
  char Name[41];
  BYTE Level;
  BYTE PlayerType;                                /* 1 for local player, 2 for AI */
  BYTE Unk_2b;
  BYTE Unk_2c;
  int Salary;
  int PrevSalary;
  int Money;
  BYTE Unk_39;                                    /* unused? */
  BYTE Unk_3a;                                    /* unused? */
  BYTE Unk_3b;                                    /* unused? */
  BYTE Unk_3c;                                    /* unused? */
  int Loan;
  int LoanMax;
  DWORD UnkArr_45[12];
  DWORD UnkArr_75[12];                            /* only accessed via 0x45 */
  DWORD UnkArr_a5[12];                            /* also accessed via 0x45 */
  DWORD Unk_d5;
  BYTE Unk_d9;
  BYTE Unk_da;                                    /* unused? */
  BYTE Unk_db;                                    /* unused? */
  BYTE Unk_dc;
  DWORD ResearchPointsLeft;
  DWORD ExpertiseResearchLevels[47];
  DWORD UnkArr_19d[5];                            /* Research? */
  WORD UnkArr_1b1[5];
  int HospitalValue;
  DWORD Unk_1bf;
  DWORD EndYearMoney;
  DWORD Unk_1c7;
  WORD PopulationPercent;
  WORD Unk_1cd;
  WORD CanPlaceStuff;                             /* something with building */
  WORD Unk_1d1;
  WORD VipSpawn_1D3;
  WORD Unk_1d5;
  WORD Unk_1d7;
  struct Emergency Emergency;
  WORD CuredCount;
  WORD DiedCount;
  WORD VisitorsCount;
  WORD Unk_1ef;
  WORD HospitalTileCount;
  struct VIP VIP;
  struct Epidemic Epidemic;
  unsigned short daysFromLastDisaster;
  short heatLevelPrev;
  BYTE disasterType;
  BYTE disasterLength;
  BYTE Unk_215;
  BYTE Unk_216;
  struct HospitalPolicy HospitalPolicy;
  BYTE Unk_220;
  BYTE Unk_221;
  BYTE Unk_222;
  BYTE Unk_223;
  struct HospUnkStruct_0x26 UnkArr_224[47];
  struct HospUnkStruct_0xe UnkArr_91e[61];
  BYTE Unk_c74;
  BYTE Unk_c75;
  BYTE Unk_c76;
  BYTE Unk_c77;
  BYTE Unk_c78;
  BYTE Unk_c79;
  BYTE Unk_c7a;
  BYTE Unk_c7b;
  BYTE Unk_c7c;
  BYTE Unk_c7d;
  DWORD Reputation;
  DWORD ReputationPositiveFactor;
  DWORD ReputationNegativeFactor;
  WORD Unk_c8a;
  WORD Unk_c8c;
  WORD Unk_c8e;
  WORD Unk_c90;
  short radiatorsCount;
  BYTE heatLevel;
  BYTE heatLevelLock;
  BYTE Unk_c96;
  BYTE Unk_c97;
  WORD Unk_c98;
  WORD Unk_c9a;
  short StuffTotalCount;
  short NursesCount;
  short DoctorsCount;
  short HandymansCount;
  short ReceptionistsCount;
  WORD Unk_ca6;
  WORD Unk_ca8;
  short LitterCount;
  WORD LitterLastCoords;
  BYTE RatHolesCount;                             /* Max: 40 */
  struct RatHole RatHoles[40];
  WORD RatsKilledCount;
  WORD RatsShotsFired;
  struct UnkStruct_d2b_0x9 UnkStruct_d2b_0x9[64];
  BYTE Unk_f6b;
  BYTE Unk_f6c;
  struct UnkStruct_d2b_0x9 UnkStruct_f69_0x9[64];
  BYTE Unk_11ad;
  BYTE Unk_11ae;
  BYTE Unk_11af[60];
  BYTE Unk_11eb;
  WORD Unk_11ec;
  WORD Unk_11ee;
  WORD Unk_11f0;
  WORD Unk_11f2;
  WORD PickedStuffObjIndex;
  WORD PickedStuffCoords;
  DWORD AINextTick;
  WORD AI_unk_11fc;
  WORD Unk_11fe;
  WORD Unk_1200;
  WORD Unk_1202;
  struct UnkStruct_0x6 UnkArr_1204[8];
  DWORD Unk_1234;
  DWORD Unk_1238;
  DWORD Unk_123c;
  WORD Unk_1240;
  WORD Unk_1242;
  BYTE Unk_1244;
  BYTE Unk_1245;
  WORD Unk_1246;
  BYTE Unk_1248;
  BYTE Unk_1249;
  BYTE Unk_124a;
  BYTE Unk_124b;
  BYTE Unk_124c;
  BYTE Unk_124d;
  BYTE Unk_124e;
  BYTE Unk_124f;
  BYTE Unk_1250;
  BYTE Unk_1251;
  BYTE Unk_1252;
  BYTE Unk_1253;
  BYTE Unk_1254;
  BYTE Unk_1255;
  BYTE IsOpen;
  WORD OpenTimer;
};