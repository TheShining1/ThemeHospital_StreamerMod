#pragma once
#include "ICommand.h"
#include <boost/describe.hpp>
#include "../Logger.h"
#include "../GameManager/GameManager.h"

#include "UnlockCameraCommand.h"
#include "DisasterCommand.h"
#include "EmergencyCommand.h"
#include "EpidemicCommand.h"
#include "QuakeCommand.h"
#include "VIPCommand.h"

enum Commands
{
  Unknown,
  Close,
  UnlockCamera,
  Quake,
  Emergency,
  VIP,
  Disaster,
  Epidemic,
};
BOOST_DESCRIBE_ENUM(Commands, Unknown, Close, UnlockCamera, Quake, Emergency, VIP, Disaster, Epidemic)

class CommandsFactory
{
public:
  static ICommand* Generate(Commands name, std::string body);  
};

class UnknownCommand : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(UnknownCommand, (), (Run), (), ());
public:
  bool Run(std::shared_ptr<GameManager> gameManager) const override;
};

class CloseCommand : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CloseCommand, (), (Name, Code, Run), (), ());
public:
  CloseCommand(std::string body);
  std::string Name;
  int Code;

  bool Run(std::shared_ptr<GameManager> gameManager) const override;
};

HMODULE GetHModule();
DWORD GetReferenceCount(HMODULE hModule);
void UnloadDLL();