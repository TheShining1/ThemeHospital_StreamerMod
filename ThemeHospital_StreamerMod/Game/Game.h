#pragma once
#include "Hospital.h"

const uint16_t CameraPosMinValue = 0x0;
const uint16_t CameraPosMaxValue = 0xFFFF;
const uint32_t TicksPerDay = 50;

struct CameraPosition
{
  uint16_t min;
  uint16_t max;
};

struct GlobalsOffset
{
  int32_t howContagious;        // 0xc47ce
  int32_t leaveMax;             // 0xc4808
  int32_t bowelOverflows;       // 00c4818
  int32_t mayorLaunch;          // 0xc4828
  int32_t langTextSections;     // 0xdaf60
  int32_t isFaxOpen;            // 0xdefb0
  int32_t hospital;             // 0xdd124
  int32_t isPaused;             // 0xe10b1
  int32_t cameraPositionLimit;  // 0xe11c2
  uint32_t gameClock;           // 0xe48a8
  int32_t rooms;                // 0xe5208  
};

struct GameOffsets
{
  GlobalsOffset globalsOffset;
  DisastersOffsets disastersOffsets;
  EmergencyOffsets emergencyOffsets;
  QuakeOffsets quakeOffsets;
  EpidemicOffsets epidemicOffsets;
};