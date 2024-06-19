#include "pch.h"
#include <boost/json.hpp>
#include "EpidemyCommand.h"
#include "EpidemyManager.h"

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