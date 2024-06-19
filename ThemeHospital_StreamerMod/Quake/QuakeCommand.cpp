#include "pch.h"
#include <boost/json.hpp>
#include "QuakeCommand.h"
#include "QuakeManager.h"

CommandQuake::CommandQuake(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool CommandQuake::Run() const
{
  LOG_DEBUG("Running quake command");

  std::shared_ptr<QuakeManager> qm = QuakeManager::Get(0x00400000);
  qm->UnsetLastIndex();

  QuakeNext qn = QuakeNext(0, this->Severity, true);
  qm->ReplaceQuakeNext(qn);
  qm->DropWaitTime();

  return qm->WaitDone();
}