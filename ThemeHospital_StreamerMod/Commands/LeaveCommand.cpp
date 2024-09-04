#include "pch.h"
#include <boost/json.hpp>
#include "LeaveCommand.h"
#include "../GameManager/GameManager.h"

LeaveCommand::LeaveCommand(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool LeaveCommand::Run(std::shared_ptr<GameManager> gameManager) const
{
  LOG_DEBUG("Running Leave command");

  uint16_t oldValue = *gameManager->leaveMax;

  *gameManager->leaveMax = 0;

  std::this_thread::sleep_for(std::chrono::seconds(this->Duration)); // TODO change to game_clock check

  *gameManager->leaveMax = oldValue;

  return true;
}