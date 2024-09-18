#pragma once
#include <boost/describe.hpp>
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
  uint32_t howContagious;       // 0xc47ce
  uint32_t leaveMax;            // 0xc4808
  uint32_t bowelOverflows;      // 00c4818
  uint32_t mayorLaunch;         // 0xc4828
  uint32_t langTextSections;    // 0xdaf60
  uint32_t isFaxOpen;           // 0xdefb0
  uint32_t hospital;            // 0xdd124
  uint32_t isPaused;            // 0xe10b1
  uint32_t cameraPositionLimit; // 0xe11c2
  uint32_t gameClock;           // 0xe48a8
  uint32_t rooms;               // 0xe5208
};
BOOST_DESCRIBE_STRUCT(GlobalsOffset, (), (howContagious, leaveMax, bowelOverflows, mayorLaunch, langTextSections, isFaxOpen, hospital, isPaused, cameraPositionLimit, gameClock, rooms));

struct GameOffsets
{
  uint32_t lpModuleBaseAddress;
  GlobalsOffset globalsOffset;
  DisastersOffsets disastersOffsets;
  EmergencyOffsets emergencyOffsets;
  QuakeOffsets quakeOffsets;
  EpidemicOffsets epidemicOffsets;
};
BOOST_DESCRIBE_STRUCT(GameOffsets, (), (lpModuleBaseAddress, globalsOffset, disastersOffsets, emergencyOffsets, quakeOffsets, epidemicOffsets));
