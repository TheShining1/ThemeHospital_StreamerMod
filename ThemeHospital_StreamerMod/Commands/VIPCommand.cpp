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

  while (gameManager->GetVIPStage() != VIPStages::Invitation) {};

  const char* oldName = gameManager->VIPSwapName(this->Username.c_str());

  while (gameManager->GetVIPStage() != VIPStages::Arriving) {};

  gameManager->VIPDropWaitTime();

  while (gameManager->GetVIPStage() != VIPStages::Departed) {};

  gameManager->VIPSetScore(this->Score);

  while (gameManager->GetVIPStage() != VIPStages::None) {};
  while (!*gameManager->isFaxOpen) {}
  while (*gameManager->isFaxOpen) {}

  gameManager->VIPSwapName(oldName);

  //std::shared_ptr<VIPManager> vm = VIPManager::Get(0x00400000, 0xdd124);
  //vm->SetDays();
  //while (vm->GetStage() != 1) {};
  //const char* nameOld = vm->SwapName(Username.c_str());
  //while (vm->GetStage() != 2) {};
  //vm->DropWaitTime();
  //while (vm->GetStage() != 4) {};
  //vm->SetScore(Score);
  //while (vm->GetStage() != 0) {}
  //while (!vm->IsFaxOpen()) {}
  //while (vm->IsFaxOpen()) {}
  //vm->SwapName(nameOld);

  //return vm->WaitDone();
  return false;
}