#pragma once
#include "Commands.h"
#include "../GameManager/GameManager.h"

class PissCommand : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(PissCommand, (), (Name, Duration, Run), (), ());
public:
  PissCommand(std::string body);
  std::string Name;
  int Duration;

  bool Run(std::shared_ptr<GameManager> gameManager) const override;
};