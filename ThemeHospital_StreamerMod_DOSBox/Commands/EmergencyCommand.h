#pragma once
#include "Commands.h"
#include "../GameManager/GameManager.h"

class EmergencyCommand : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(EmergencyCommand, (), (Name, Bonus, Illness, Amount, PercWin, Run), (), ());
public:
  EmergencyCommand(std::string body);
  std::string Name;
  uint16_t Bonus;
  uint8_t Illness;
  uint8_t Amount;
  uint8_t PercWin;

  bool Run(std::shared_ptr<GameManager> gameManager) const override;
};