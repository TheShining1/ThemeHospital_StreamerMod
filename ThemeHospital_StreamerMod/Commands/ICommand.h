#pragma once
#include <string>
#include <boost/describe.hpp>

class ICommand
{
private:
  BOOST_DESCRIBE_CLASS(ICommand, (), (Run), (), ());
public:
  virtual bool Run() const = 0;
  //virtual std::string ID() = 0;
};