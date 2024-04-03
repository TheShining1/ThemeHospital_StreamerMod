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

//std::string CommandClose::ID()
//{
//  return this->id;
//}

bool CommandClose::Run() const
{
  LOG_DEBUG("Running close command");
  return false;
}

//CommandClose CommandClose::Parse(std::string body)
//{
//  CommandClose cc;
//  boost::json::error_code ec;
//  boost::json::parse_into(cc, body, ec);
//  if (ec) {
//    return CommandClose();
//  }
//
//  return cc;
//}

CommandQuake::CommandQuake(std::string body)
{
  boost::json::parse_into(*this, body);
}

//std::string CommandQuake::ID()
//{
//  return this->id;
//}

bool CommandQuake::Run() const
{
  LOG_DEBUG("Running quake command");

  std::shared_ptr<QuakeManager> qm = QuakeManager::Get(0x00400000);
  qm->UnsetLastIndex();

  QuakeNext qn = QuakeNext(0, this->Severity, true);
  qm->ReplaceQuakeNext(qn);

  return qm->WaitDone();
}

//CommandQuake CommandQuake::Parse(std::string body)
//{
//  CommandQuake cq;
//  boost::json::error_code ec;
//  boost::json::parse_into(cq, body, ec);
//  if (ec) {
//    LOG_DEBUG("Error");
//    LOG_DEBUG(ec);
//    return CommandQuake();
//  }
//
//  return cq;
//}

//std::string CommandUnknown::ID()
//{
//  return this->id;
//}

bool CommandUnknown::Run() const {
  return false;
}