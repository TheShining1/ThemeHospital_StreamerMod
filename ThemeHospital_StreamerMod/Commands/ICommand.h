#pragma once
#include <string>
#include <boost/describe.hpp>

class ICommand
{
private:
  BOOST_DESCRIBE_CLASS(ICommand, (), (Name, Run), (), ());
public:
  std::string Name;

  virtual void Run() const = 0;
};