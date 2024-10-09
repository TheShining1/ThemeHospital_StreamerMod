#pragma once
#include <string>
#include <boost/describe.hpp>

struct WS_Config
{
  std::string Host;
  std::string Port;
};

BOOST_DESCRIBE_STRUCT(WS_Config, (), (Host, Port));
