#pragma once
#include <boost/describe.hpp>
#include <minwindef.h>

struct QuakeOffsets
{
  uint32_t NextClock;  // 0xe117b
  uint32_t Stage;      // 0xe117f
  uint32_t Next;       // 0xe11b7
  uint32_t IndexUsed;  // 0xe11db
};
BOOST_DESCRIBE_STRUCT(QuakeOffsets, (), (NextClock, Stage, Next, IndexUsed));

struct QuakeNext
{
  int GameClock;
  BYTE Severity;
  bool Enabled;
};