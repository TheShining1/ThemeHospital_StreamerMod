#pragma once
#include "../Commands/Commands.h"

class CommandVIP : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CommandVIP, (), (Name, Username, Score, Run), (), ());
public:
  CommandVIP(std::string body);
  std::string Name;
  std::string Username;
  int Score;

  bool Run() const override;
};