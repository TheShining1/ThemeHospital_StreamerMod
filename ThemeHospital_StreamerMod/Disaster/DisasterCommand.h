#pragma once
#include "../Commands/Commands.h"

class CommandDisaster : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CommandDisaster, (), (Name, Type, Run), (), ());
public:
  CommandDisaster(std::string body);
  std::string Name;
  int Type;

  bool Run() const override;
};