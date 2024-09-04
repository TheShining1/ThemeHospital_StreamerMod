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
  //std::shared_ptr<EpidemyManager> em = EpidemyManager::Get(0x00400000);

  //em->CreatePatients(this->Disease, this->Amount);

  //return em->WaitDone();
  return false;
}