#include "pch.h"
#include <boost/json.hpp>
#include "DisasterCommand.h"
#include "../GameManager/GameManager.h"

DisasterCommand::DisasterCommand(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool DisasterCommand::Run(std::shared_ptr<GameManager> gameManager) const
{
  LOG_DEBUG("Running Disaster command");

  uint16_t oldVomitLimit;

  switch (this->Type)
  {
  case DisasterType::BoilerDown:
  case DisasterType::BoilerUp:
    gameManager->BoilerBreak(this->Type);
    break;
  case DisasterType::VomitWave:
    oldVomitLimit = gameManager->SwapVomitLimit(1);
  }

  gameManager->SetPopup(this->Type);
  gameManager->SetDisasterDuration();
  gameManager->SetDisasterType(this->Type);
  gameManager->ResetDisasterDays();

  while (gameManager->GetDisasterType() != DisasterType::NoDisaster) { std::this_thread::sleep_for(std::chrono::seconds(1)); }
  
  if (this->Type == DisasterType::VomitWave) {
    gameManager->SwapVomitLimit(oldVomitLimit);
  }

  return true;
}