#include "pch.h"
#include "Commands.h"
#include <boost/json.hpp>
#include "../Logger.h"
#include "../Quake/QuakeManager.h"
#include "../Emergency/EmergencyManager.h"
#include "../VIP/VIPManager.h"
#include "../Disaster/DisasterManager.h"
#include "../Epidemy/EpidemyManager.h"

ICommand* CommandsFactory::Generate(Commands name, std::string body)
{
  switch (name)
  {
  case Commands::Close:
    return new CommandClose(body);
    break;
  case Commands::Quake:
    return new CommandQuake(body);
    break;
  case Commands::Emergency:
    return new CommandEmergency(body);
    break;
  case Commands::VIP:
    return new CommandVIP(body);
    break;
  case Commands::Disaster:
    return new CommandDisaster(body);
    break;
  case Commands::Epidemy:
    return new CommandEpidemy(body);
    break;
  default:
    return new CommandUnknown();
    break;
  }
}

CommandClose::CommandClose(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool CommandClose::Run() const
{
  LOG_DEBUG("Running close command");
  return false;
}

CommandQuake::CommandQuake(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool CommandQuake::Run() const
{
  LOG_DEBUG("Running quake command");

  std::shared_ptr<QuakeManager> qm = QuakeManager::Get(0x00400000);
  qm->UnsetLastIndex();

  QuakeNext qn = QuakeNext(0, this->Severity, true);
  qm->ReplaceQuakeNext(qn);
  qm->DropWaitTime();

  return qm->WaitDone();
}

CommandEmergency::CommandEmergency(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool CommandEmergency::Run() const
{
  LOG_DEBUG("Running emergency command");

  std::shared_ptr<EmergencyManager> em = EmergencyManager::Get(0x00400000, 0xdd124);
  em->UnsetLastIndex();
  em->DecrementSkippedCount();

  EmergencyNext en = EmergencyNext(0, this->Bonus, true, this->Illness, this->Amount, this->PercWin);
  em->ReplaceEmergencyNext(en);

  return em->WaitDone();
}

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
  while(vm->GetStage() != 0){}
  while(!vm->IsFaxOpen()) {}
  while(vm->IsFaxOpen()) {}
  vm->SwapName(nameOld);

  return vm->WaitDone();
}

CommandDisaster::CommandDisaster(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool CommandDisaster::Run() const
{
  LOG_DEBUG("Running Disaster command");

  std::shared_ptr<DisasterManager> dm = DisasterManager::Get(0x00400000, 0xdd124);

  short oldLimit = 0;
  if (this->Type == 1 || this->Type == 2)
  {
    dm->BreakBoiler(this->Type);
  }
  else {
    oldLimit = dm->SwapVomitLimit(0);
  }

  dm->SetPopup(this->Type);
  dm->SetLength();
  dm->SetType(this->Type);

  dm->ResetDays();

  if (this->Type == 3)
  {
    while(dm->GetType() != 0){}
    dm->SwapVomitLimit(oldLimit);
  }

  return dm->WaitDone();
}

CommandEpidemy::CommandEpidemy(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool CommandEpidemy::Run() const
{
  LOG_DEBUG("Running Epidemy command");

  std::shared_ptr<EpidemyManager> em = EpidemyManager::Get(0x00400000);

  em->CreatePatients(this->Disease, this->Amount);

  return em->WaitDone();
}
bool CommandUnknown::Run() const {
  return false;
}