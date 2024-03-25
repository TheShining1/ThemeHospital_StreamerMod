#include "pch.h"
#include "Message.h"

Message::Message() {};

Message Message::Parse(std::string_view rawMessage)
{
  Message m;
  boost::json::error_code ec;
  boost::json::parse_into(m, rawMessage, ec);
  if (ec) {
    return Message();
  }

  return m;
}