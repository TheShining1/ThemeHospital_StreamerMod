#include "pch.h"
#include <boost/json.hpp>
#include "VIPCommand.h"
#include "../GameManager/GameManager.h"

VIPCommand::VIPCommand(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool VIPCommand::Run(std::shared_ptr<GameManager> gameManager) const
{
  LOG_DEBUG("Running VIP command");

  gameManager->vipSetDays();

  while (gameManager->GetVIPStage() != VIPStages::Invitation) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };

  const char* oldName = gameManager->VIPSwapName(this->Username.c_str());

  while (gameManager->GetVIPStage() != VIPStages::Arriving) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };

  gameManager->VIPDropWaitTime();

  while (gameManager->GetVIPStage() != VIPStages::Departed) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };

  gameManager->VIPSetScore(this->Score);

  while (gameManager->GetVIPStage() != VIPStages::None) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };
  while (!*gameManager->isFaxOpen) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  while (*gameManager->isFaxOpen) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  gameManager->VIPSwapName(oldName);

  return true;
}