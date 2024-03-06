#pragma once

class QuakeNext
{
private:
  DWORD _gametick;
  BYTE _severity;
  bool _enabled;

public:
  QuakeNext(DWORD gametick, BYTE severity, bool enabled);
};