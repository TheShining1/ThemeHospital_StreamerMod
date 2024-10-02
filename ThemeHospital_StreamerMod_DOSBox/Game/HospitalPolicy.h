#pragma once
#include <minwindef.h>

struct HospitalPolicy {
  WORD StopProcedire;
  WORD GuessAtCure;
  WORD SendHome;
  WORD GoToStaffRoom;
  BYTE StaffLeaveRooms;
};