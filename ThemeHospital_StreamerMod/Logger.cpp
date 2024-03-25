#include "pch.h"
#include "Logger.h"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

std::shared_ptr<Logger> Logger::instance = nullptr;

Logger::Logger()
{
  namespace logging = boost::log;
  namespace src = boost::log::sources;
  namespace keywords = boost::log::keywords;
  using namespace logging::trivial;
  src::severity_logger< severity_level > lg;

  auto console_sink = logging::add_console_log(std::cout, keywords::format = "[%TimeStamp%]: %Message%");
  console_sink->locked_backend()->auto_flush(true);

  auto file_sink = logging::add_file_log("logs.log", keywords::format = "[%TimeStamp%]: %Message%");
  file_sink->locked_backend()->auto_flush(true);

  logging::core::get()->set_filter
  (
    logging::trivial::severity >= logging::trivial::debug
  );

  logging::add_common_attributes();
}

std::shared_ptr<Logger> Logger::Get()
{
  if (instance == nullptr)
    instance.reset(new Logger());
  return instance;
}

//void Logger::Log(std::string text)
//{
//  BOOST_LOG_SEV(lg, debug) << text;
//}
//void Logger::Log(int text)
//{
//  BOOST_LOG_SEV(lg, debug) << text;
//}