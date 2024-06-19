#pragma once
#include "../Commands/Commands.h"

class CommandQuake : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CommandQuake, (), (Name, Severity, Run), (), ());
public:
  CommandQuake(std::string body);
  std::string Name;
  int Severity;

  bool Run() const override;
};