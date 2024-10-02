#pragma once
#include <memory>
#include <string>
#include <boost/describe.hpp>
#include "../GameManager/GameManager.h"

class ICommand
{
private:
  BOOST_DESCRIBE_CLASS(ICommand, (), (Run), (), ());
public:
  virtual bool Run(std::shared_ptr<GameManager> gameManager) const = 0;
};