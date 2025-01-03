#pragma once
#include <boost/describe.hpp>

struct DisastersOffsets
{
	uint32_t VomitLimit;			// 0xc481a
	uint32_t DoctorPopupText;	// 0xdcb92
};
BOOST_DESCRIBE_STRUCT(DisastersOffsets, (), (VomitLimit, DoctorPopupText))

enum DisasterType : uint8_t
{
	NoDisaster,
	BoilerDown,
	BoilerUp,
	VomitWave
};
BOOST_DESCRIBE_ENUM(DisasterType, NoDisaster, BoilerDown, BoilerUp, VomitWave)

const char8_t HEATMIN = 0;
const char8_t HEATMAX = 10;

const uint16_t doctorPopupTextIndexes[3] = { 11,10,13 };