#include "pch.h"
#include "QuakeNext.h"

QuakeNext::QuakeNext(DWORD gametick, BYTE severity, bool enabled)
{
  this->_gametick = gametick;
  this->_severity = severity;
  this->_enabled = enabled;
}