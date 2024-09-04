#include "pch.h"
#include <boost/json.hpp>
#include "EmergencyCommand.h"
#include "../GameManager/GameManager.h"

EmergencyCommand::EmergencyCommand(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool EmergencyCommand::Run(std::shared_ptr<GameManager> gameManager) const
{
  LOG_DEBUG("Running emergency command");

  EmergencyNext emergencyNext = EmergencyNext{
    .Gametick = 0,
    .Bonus = this->Bonus,
    .Enabled = true,
    .Illness = this->Illness,
    .Amount = this->Amount,
    .PercWin = this->PercWin
  };

  gameManager->emergencyUnsetLastIndex();

  gameManager->emergencySkippedCount--;
  *gameManager->emergencyNext = emergencyNext;

  //return em->WaitDone();
  return false;
}