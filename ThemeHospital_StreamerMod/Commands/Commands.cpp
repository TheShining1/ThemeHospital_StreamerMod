#include "pch.h"
#include "Commands.h"
#include <boost/json.hpp>
#include "../Logger.h"
#include "../Quake/QuakeManager.h"
#include "../Emergency/EmergencyManager.h"
#include "../VIP/VIPManager.h"
#include "../Disaster/DisasterManager.h"
#include "../Epidemy/EpidemyManager.h"

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
  case Commands::Emergency:
    return new CommandEmergency(body);
    break;
  case Commands::VIP:
    return new CommandVIP(body);
    break;
  case Commands::Disaster:
    return new CommandDisaster(body);
    break;
  case Commands::Epidemy:
    return new CommandEpidemy(body);
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