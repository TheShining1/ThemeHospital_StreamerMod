#pragma once
#include <minwindef.h>

struct Epidemic {
  WORD InspectorObjectIndex;
  short Fine;
  unsigned short PatientsCount;
  unsigned short TimeLeft;
  BYTE Outcome;                 /* 0 == covered up, 1-2 == lost, 3 == evacuation */
  BYTE InspectorStage;
  BYTE Disease;
  BYTE DiseasePrev;
  BYTE Stage;
  BYTE Timer;
};