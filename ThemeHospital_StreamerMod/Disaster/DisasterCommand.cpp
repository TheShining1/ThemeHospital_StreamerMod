#include "pch.h"
#include <boost/json.hpp>
#include "DisasterCommand.h"
#include "DisasterManager.h"

CommandDisaster::CommandDisaster(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool CommandDisaster::Run() const
{
  LOG_DEBUG("Running Disaster command");

  std::shared_ptr<DisasterManager> dm = DisasterManager::Get(0x00400000, 0xdd124);

  short oldLimit = 0;
  if (this->Type == 1 || this->Type == 2)
  {
    dm->BreakBoiler(this->Type);
  }
  else {
    oldLimit = dm->SwapVomitLimit(0);
  }

  dm->SetPopup(this->Type);
  dm->SetLength();
  dm->SetType(this->Type);

  dm->ResetDays();

  if (this->Type == 3)
  {
    while (dm->GetType() != 0) {}
    dm->SwapVomitLimit(oldLimit);
  }

  return dm->WaitDone();
}