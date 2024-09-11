#include "pch.h"
#include <boost/json.hpp>
#include "EpidemicCommand.h"
#include "../GameManager/GameManager.h"

EpidemicCommand::EpidemicCommand(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool EpidemicCommand::Run(std::shared_ptr<GameManager> gameManager) const
{
  LOG_DEBUG("Running Epidemy command");

  gameManager->CreatePatients(this->Disease, this->Amount);

  while (gameManager->hospital->Epidemic.TimeLeft == 0) { std::this_thread::sleep_for(std::chrono::seconds(1)); }
  while (gameManager->hospital->Epidemic.TimeLeft != 0 && gameManager->hospital->Epidemic.Stage != 0) { std::this_thread::sleep_for(std::chrono::seconds(1)); }

  return true;
}