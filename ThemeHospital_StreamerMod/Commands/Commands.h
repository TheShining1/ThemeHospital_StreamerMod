#pragma once
#include "ICommand.h"
#include <boost/describe.hpp>
#include "../Logger.h"

enum Commands
{
  Unknown,
  Close,
  Quake
};
BOOST_DESCRIBE_ENUM(Commands, Close, Quake)

class CommandsFactory
{
public:
  static ICommand* Generate(Commands name, std::string body);  
};

class CommandUnknown : public ICommand
{
private:
  //std::string id;
  BOOST_DESCRIBE_CLASS(CommandUnknown, (), (Run), (), ());
public:
  bool Run() const override;
  //std::string ID() override;
};

class CommandClose : public ICommand
{
private:
  //std::string id;
  //BOOST_DESCRIBE_CLASS(CommandClose, (), (Name, Code, (CommandClose (std::string)) Parse, Run), (), ());
  BOOST_DESCRIBE_CLASS(CommandClose, (), (Name, Code, Run), (), ());
public:
  CommandClose(std::string body);
  std::string Name;
  int Code;

  //static CommandClose* Parse(std::string body);
  bool Run() const override;
  //std::string ID() override;
};

class CommandQuake : public ICommand
{
private:
  //std::string id;
  //BOOST_DESCRIBE_CLASS(CommandQuake, (), (Name, Severity, (CommandQuake (std::string)) Parse, Run), (), ());
  BOOST_DESCRIBE_CLASS(CommandQuake, (), (Name, Severity, Run), (), ());
public:
  CommandQuake(std::string body);
  std::string Name;
  int Severity;

  //static CommandQuake* Parse(std::string body);
  bool Run() const override;
  //std::string ID() override;
};