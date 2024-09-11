#include "pch.h"
#include <boost/json.hpp>
#include "PissCommand.h"
#include "../GameManager/GameManager.h"

PissCommand::PissCommand(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool PissCommand::Run(std::shared_ptr<GameManager> gameManager) const
{
  LOG_DEBUG("Running Piss command");

  uint16_t oldValue = *gameManager->bowelOverflows;

  *gameManager->bowelOverflows = 1;

  uint32_t endGameClock = *gameManager->gameClock + this->Duration * TicksPerDay;
  while (endGameClock > *gameManager->gameClock) { std::this_thread::sleep_for(std::chrono::seconds(1)); }

  *gameManager->bowelOverflows = oldValue;

  return true;
}