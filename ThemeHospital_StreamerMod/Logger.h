#pragma once
#include <memory>
#include <boost/log/trivial.hpp>

#define LOG_DEBUG_OBJ BOOST_LOG_TRIVIAL(debug)
#define LOG(MODE, a) MODE << a
#define LOG_DEBUG(a) LOG(LOG_DEBUG_OBJ, a)

class Logger
{
private:
  static std::shared_ptr<Logger> instance;

  Logger();

public:
  static std::shared_ptr<Logger> Get();
};