#pragma once
#include "Commands.h"
#include "../GameManager/GameManager.h"

class DisasterCommand : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(DisasterCommand, (), (Name, Type, Run), (), ());
public:
  DisasterCommand(std::string body);
  std::string Name;
  uint8_t Type;

  bool Run(std::shared_ptr<GameManager> gameManager) const override;
};