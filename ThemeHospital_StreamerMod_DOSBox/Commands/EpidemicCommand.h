#pragma once
#include "Commands.h"
#include "../GameManager/GameManager.h"

class EpidemicCommand : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(EpidemicCommand, (), (Name, Disease, Amount, Run), (), ());
public:
  EpidemicCommand(std::string body);
  std::string Name;
  uint8_t Disease;
  uint8_t Amount;

  bool Run(std::shared_ptr<GameManager> gameManager) const override;
};