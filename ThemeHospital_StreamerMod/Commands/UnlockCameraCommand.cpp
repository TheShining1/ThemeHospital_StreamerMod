#include "pch.h"
#include <boost/json.hpp>
#include "UnlockCameraCommand.h"
#include "../GameManager/GameManager.h"

UnlockCameraCommand::UnlockCameraCommand(std::string body)
{
  //boost::json::parse_into(*this, body);
}

bool UnlockCameraCommand::Run(std::shared_ptr<GameManager> gameManager) const
{
  LOG_DEBUG("Running UnlockCamera command");

  gameManager->UnlockCamera();

  return true;
}
