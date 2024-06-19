#pragma once
#include "../Commands/Commands.h"

class CommandEmergency : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CommandEmergency, (), (Name, Bonus, Illness, Amount, PercWin, Run), (), ());
public:
  CommandEmergency(std::string body);
  std::string Name;
  WORD Bonus;
  BYTE Illness;
  BYTE Amount;
  BYTE PercWin;

  bool Run() const override;
};