#pragma once
#include "ICommand.h"
#include <boost/describe.hpp>
#include "../Logger.h"

enum Commands
{
  Unknown,
  Close,
  Quake,
  Emergency,
  VIP,
  Disaster,
  Epidemy
};
BOOST_DESCRIBE_ENUM(Commands, Close, Quake, Emergency, VIP, Disaster, Epidemy)

class CommandsFactory
{
public:
  static ICommand* Generate(Commands name, std::string body);  
};

class CommandUnknown : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CommandUnknown, (), (Run), (), ());
public:
  bool Run() const override;
};

class CommandClose : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CommandClose, (), (Name, Code, Run), (), ());
public:
  CommandClose(std::string body);
  std::string Name;
  int Code;

  bool Run() const override;
};