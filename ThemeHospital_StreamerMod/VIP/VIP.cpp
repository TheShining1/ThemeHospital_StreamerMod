#include "pch.h"
#include "VIP.h"

VIP::VIP(DWORD lpModuleBaseAddress, std::string username, BYTE score)
{
  this->_username = username;
  this->_score = score;
};