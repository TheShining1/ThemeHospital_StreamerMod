#pragma once
#include "ICommand.h"
#include <boost/describe.hpp>
#include "../Logger.h"

enum Commands
{
  Close,
  Quake
};
BOOST_DESCRIBE_ENUM(Commands, Close, Quake)

//class CommandsFactory
//{
//public:
//  //static ICommand Generate(Commands name, std::string body);
//  ICommand* Generate(Commands name, std::string body)
//  {
//    switch (name)
//    {
//    case Commands::Close:
//      return CommandClose::Parse(body);
//      break;
//    case Commands::Quake:
//      return CommandQuake::Parse(body);
//      break;
//    default:
//      break;
//    }
//    return CommandClose::Parse(body);
//  }
//};

class CommandClose
{
private:
  BOOST_DESCRIBE_CLASS(CommandClose, (), (Name, Code, (CommandClose(std::string)) Parse, Run), (), ());
public:
  std::string Name;
  int Code;

  static CommandClose Parse(std::string body);
  void Run();
};

class CommandQuake
{
private:
  BOOST_DESCRIBE_CLASS(CommandQuake, (), (Name, Severity, (CommandQuake(std::string)) Parse, Run), (), ());
public:
  std::string Name;
  int Severity;

  static CommandQuake Parse(std::string body);
  void Run();
};