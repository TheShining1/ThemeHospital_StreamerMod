#pragma once
#include "Commands.h"
#include "../GameManager/GameManager.h"

class UnlockCameraCommand : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(UnlockCameraCommand, (), (Run), (), ());
public:
  UnlockCameraCommand(std::string body);

  bool Run(std::shared_ptr<GameManager> gameManager) const override;
};