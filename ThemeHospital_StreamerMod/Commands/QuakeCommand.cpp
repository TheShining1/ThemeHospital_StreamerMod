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

  QuakeNext qn = QuakeNext(this->GameClock, this->Severity, this->Enabled);

  gameManager->quakeUnsetLastIndex();

  *gameManager->quakeNext = qn;
  *gameManager->quakeNextClock = 0;

  //std::shared_ptr<QuakeManager> qm = QuakeManager::Get(0x00400000);
  //qm->UnsetLastIndex();

  //QuakeNext qn = QuakeNext(0, this->Severity, true);
  //qm->ReplaceQuakeNext(qn);
  //qm->DropWaitTime();

  //return qm->WaitDone();
  return false;
}