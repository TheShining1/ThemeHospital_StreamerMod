#pragma once
#include "Commands.h"
#include "../GameManager/GameManager.h"

class QuakeCommand : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(QuakeCommand, (), (Name, GameClock, Severity, Enabled, Run), (), ());
public:
  QuakeCommand(std::string body);
  std::string Name;
  int GameClock;
  int Severity;
  bool Enabled;

  bool Run(std::shared_ptr<GameManager> gameManager) const override;
};