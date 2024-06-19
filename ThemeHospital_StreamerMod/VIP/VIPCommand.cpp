#include "pch.h"
#include <boost/json.hpp>
#include "VIPCommand.h"
#include "VIPManager.h"

CommandVIP::CommandVIP(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool CommandVIP::Run() const
{
  LOG_DEBUG("Running VIP command");

  std::shared_ptr<VIPManager> vm = VIPManager::Get(0x00400000, 0xdd124);
  vm->SetDays();
  while (vm->GetStage() != 1) {};
  const char* nameOld = vm->SwapName(Username.c_str());
  while (vm->GetStage() != 2) {};
  vm->DropWaitTime();
  while (vm->GetStage() != 4) {};
  vm->SetScore(Score);
  while (vm->GetStage() != 0) {}
  while (!vm->IsFaxOpen()) {}
  while (vm->IsFaxOpen()) {}
  vm->SwapName(nameOld);

  return vm->WaitDone();
}