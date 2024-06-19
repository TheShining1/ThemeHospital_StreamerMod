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

class CommandVIP : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CommandVIP, (), (Name, Username, Score, Run), (), ());
public:
  CommandVIP(std::string body);
  std::string Name;
  std::string Username;
  int Score;

  bool Run() const override;
};

class CommandEpidemy : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CommandEpidemy, (), (Name, Disease, Amount, Run), (), ());
public:
  CommandEpidemy(std::string body);
  std::string Name;
  BYTE Disease;
  BYTE Amount;

  bool Run() const override;
};

class CommandDisaster : public ICommand
{
private:
  BOOST_DESCRIBE_CLASS(CommandDisaster, (), (Name, Type, Run), (), ());
public:
  CommandDisaster(std::string body);
  std::string Name;
  int Type;

  bool Run() const override;
};