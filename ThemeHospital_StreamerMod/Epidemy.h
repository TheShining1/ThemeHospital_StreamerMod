#pragma once

class Epidemy
{
private:
  DWORD _lpModuleBaseAddress;

  DWORD _randomSeedFuncOffset = 0x66010;

  DWORD _ptRoomsOffset = 0xe5208;

  DWORD _createPatientObjFuncOffset = 0x36bf0;
  DWORD _spawnObjectFuncOffset = 0x6c120;

  BYTE _disease;
  DWORD _count;

public:

  Epidemy(DWORD lpModuleBaseAddress, BYTE disease, DWORD Count);
};