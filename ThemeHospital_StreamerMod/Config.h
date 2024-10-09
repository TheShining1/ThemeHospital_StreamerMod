#pragma once

#include "WebSocket.h"
#include "Game/Game.h"
#include <boost/describe.hpp>

struct Config
{
  WS_Config wsConfig;
  std::string gameOffsetsFilename;
};

BOOST_DESCRIBE_STRUCT(Config, (), (wsConfig, gameOffsetsFilename));