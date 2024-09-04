#pragma once
#include "GameObject.h"

typedef GameObject* (__cdecl* createPatientFunc)(uint16_t, uint8_t, uint8_t);
typedef void(__cdecl* spawnObjectFunc)(GameObject*);

struct EpidemicOffsets {
  uint32_t createPatientObjFunc;  // 0x36bf0
  uint32_t spawnObjectFunc;       // 0x6c120;
};

struct Epidemic {
  uint16_t InspectorObjectIndex;
  uint16_t Fine;
  uint16_t PatientsCount;
  uint16_t TimeLeft;
  uint8_t Outcome;                 /* 0 == covered up, 1-2 == lost, 3 == evacuation */
  uint8_t InspectorStage;
  uint8_t Disease;
  uint8_t DiseasePrev;
  uint8_t Stage;
  uint8_t Timer;
};