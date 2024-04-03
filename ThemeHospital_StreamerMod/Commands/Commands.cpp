#include "pch.h"
#include "Commands.h"
#include <boost/json.hpp>
#include "../Logger.h"
#include "../Quake/QuakeManager.h"

ICommand* CommandsFactory::Generate(Commands name, std::string body)
{
  switch (name)
  {
  case Commands::Close:
    return new CommandClose(body);
    break;
  case Commands::Quake:
    return new CommandQuake(body);
    break;
  default:
    return new CommandUnknown();
    break;
  }
}

CommandClose::CommandClose(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool CommandClose::Run() const
{
  LOG_DEBUG("Running close command");
  return false;
}

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

  return qm->WaitDone();
}

bool CommandUnknown::Run() const {
  return false;
}