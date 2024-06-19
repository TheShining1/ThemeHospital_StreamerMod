#pragma once
#include "../Commands/Commands.h"

class CommandEpidemy : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CommandEpidemy, (), (Name, Disease, Amount, Run), (), ());
public:
  CommandEpidemy(std::string body);
  std::string Name;
  BYTE Disease;
  BYTE Amount;

  bool Run() const override;
};