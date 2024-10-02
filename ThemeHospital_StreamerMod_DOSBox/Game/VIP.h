#pragma once

enum VIPStages : uint8_t
{
  NoVIP,
  Invitation,
  Arriving,
  Touring,
  Departed,
};

struct VIP {
  uint32_t GameClock;
  uint16_t ObjectIndex;
  uint8_t NameIndex;
  VIPStages Stage;
  uint16_t Score;
  int16_t vipUnk;
  uint16_t DaysFromLast;
};