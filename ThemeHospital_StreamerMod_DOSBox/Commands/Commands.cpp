#include "pch.h"
#include "Commands.h"
#include <boost/json.hpp>
#include "../Logger.h"

#include <windows.h>
#include <psapi.h>
#include <iostream>

ICommand* CommandsFactory::Generate(Commands name, std::string body)
{
  switch (name)
  {
  case Commands::Close:
    return new CloseCommand(body);
    break;
  case Commands::UnlockCamera:
    return new UnlockCameraCommand(body);
    break;
  case Commands::Quake:
    return new QuakeCommand(body);
    break;
  case Commands::Emergency:
    return new EmergencyCommand(body);
    break;
  case Commands::VIP:
    return new VIPCommand(body);
    break;
  case Commands::Disaster:
    return new DisasterCommand(body);
    break;
  case Commands::Epidemic:
    return new EpidemicCommand(body);
    break;
  case Commands::Piss:
    return new PissCommand(body);
    break;
  case Commands::Leave:
    return new LeaveCommand(body);
    break;
  default:
    return new UnknownCommand();
    break;
  }
}

bool UnknownCommand::Run(std::shared_ptr<GameManager> gameManager) const {
  return false;
}

DWORD GetReferenceCount(HMODULE hModule)
{
  MODULEINFO modInfo;
  if (GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO)))
  {
    return modInfo.SizeOfImage;  // SizeOfImage is repurposed here for simplicity
  }
  else
  {
    LOG_DEBUG(GetLastError());
    return 0;
  }
}

HMODULE GetHModule()
{
  HMODULE hModule = NULL;
  GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
    (LPCTSTR)"ThemeHospital_StreamerMod.dll", &hModule);
  
  return hModule;
}

void UnloadDLL()
{
  HMODULE hModule = GetHModule();
  if (hModule)
  {
    LOG_DEBUG(hModule);
    LOG_DEBUG(GetReferenceCount(hModule));
    FreeLibraryAndExitThread(hModule, 0);
  }
}

CloseCommand::CloseCommand(std::string body)
{
  boost::json::parse_into(*this, body);
}

bool CloseCommand::Run(std::shared_ptr<GameManager> gameManager) const
{
  LOG_DEBUG("Running close command");

  //UnloadDLL();

  return false;
}