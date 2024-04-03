#pragma once
#include <string>
#include <boost/describe.hpp>
#include <boost/json.hpp>
#include "./Commands/Commands.h"

class Message
{
private:
	BOOST_DESCRIBE_CLASS(Message, (), (App, ID, CommandName, Command, (Message(std::string_view)) Parse), (), ());

public:
	std::string App;
	std::string ID;
	Commands CommandName;
	std::string Command;

	Message();

	static Message Parse(std::string_view rawMessage);
};