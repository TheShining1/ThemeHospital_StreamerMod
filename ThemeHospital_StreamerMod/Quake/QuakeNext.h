#pragma once

class QuakeNext
{
private:

public:
  DWORD _gametick;
  BYTE _severity;
  bool _enabled;

  QuakeNext(DWORD gametick, BYTE severity, bool enabled);
};