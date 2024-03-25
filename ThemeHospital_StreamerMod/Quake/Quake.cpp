#include "pch.h"
#include "Quake.h"

Quake::Quake(WORD startMonth, WORD endMonth, WORD severity)
{
	this->_startMonth = startMonth;
	this->_endMonth = endMonth;
	this->_severity = severity;
}