#pragma once
#include "Commands.h"
#include "../GameManager/GameManager.h"

class VIPCommand : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(VIPCommand, (), (Name, Username, Score, Run), (), ());
public:
  VIPCommand(std::string body);
  std::string Name;
  std::string Username;
  int Score;

  bool Run(std::shared_ptr<GameManager> gameManager) const override;
};