#include "pch.h"
#include <boost/json.hpp>
#include "QuakeCommand.h"
#include "../GameManager/GameManager.h"

QuakeCommand::QuakeCommand(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool QuakeCommand::Run(std::shared_ptr<GameManager> gameManager) const
{
  LOG_DEBUG("Running quake command");

  *gameManager->quakeNext = QuakeNext(this->GameClock, this->Severity, this->Enabled);

  gameManager->quakeUnsetLastIndex();

  *gameManager->quakeNextClock = 1;

  while (*gameManager->quakeStage == 0) { std::this_thread::sleep_for(std::chrono::seconds(1)); }

  return true;
}