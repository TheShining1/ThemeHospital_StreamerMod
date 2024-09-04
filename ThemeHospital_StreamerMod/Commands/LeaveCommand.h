#pragma once
#include "Commands.h"
#include "../GameManager/GameManager.h"

class LeaveCommand : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(LeaveCommand, (), (Name, Duration, Run), (), ());
public:
  LeaveCommand(std::string body);
  std::string Name;
  int Duration;

  bool Run(std::shared_ptr<GameManager> gameManager) const override;
};