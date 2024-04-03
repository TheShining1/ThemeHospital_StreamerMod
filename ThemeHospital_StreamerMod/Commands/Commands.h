#pragma once
#include "ICommand.h"
#include <boost/describe.hpp>
#include "../Logger.h"

enum Commands
{
  Unknown,
  Close,
  Quake,
  Emergency
};
BOOST_DESCRIBE_ENUM(Commands, Close, Quake, Emergency)

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

class CommandQuake : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CommandQuake, (), (Name, Severity, Run), (), ());
public:
  CommandQuake(std::string body);
  std::string Name;
  int Severity;

  bool Run() const override;
};

class CommandEmergency: public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CommandEmergency, (), (Name, Bonus, Illness, Amount, PercWin, Run), (), ());
public:
  CommandEmergency(std::string body);
  std::string Name;
  WORD Bonus;
  BYTE Illness;
  BYTE Amount;
  BYTE PercWin;

  bool Run() const override;
};