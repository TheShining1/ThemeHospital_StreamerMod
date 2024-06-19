#include "pch.h"
#include <boost/json.hpp>
#include "EmergencyCommand.h"
#include "EmergencyManager.h"

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