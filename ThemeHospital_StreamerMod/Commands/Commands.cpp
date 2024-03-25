#include "pch.h"
#include "Commands.h"
#include <boost/json.hpp>
#include "../Logger.h"
#include "../Quake/QuakeManager.h"

CommandClose CommandClose::Parse(std::string body)
{
  CommandClose cc;
  boost::json::error_code ec;
  boost::json::parse_into(cc, body, ec);
  if (ec) {
    return CommandClose();
  }

  return cc;
}
void CommandClose::Run()
{
  LOG_DEBUG("Running close command");
}

CommandQuake CommandQuake::Parse(std::string body)
{
  CommandQuake cq;
  boost::json::error_code ec;
  boost::json::parse_into(cq, body, ec);
  if (ec) {
    LOG_DEBUG("Error");
    LOG_DEBUG(ec);
    return CommandQuake();
  }

  return cq;
}

void CommandQuake::Run()
{
  LOG_DEBUG("Running quake command");

  std::shared_ptr<QuakeManager> qm = QuakeManager::Get(0x00400000);
  qm->UnsetLastIndex();

  QuakeNext qn = QuakeNext(0, this->Severity, true);
  qm->ReplaceQuakeNext(qn);
}