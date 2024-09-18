#include "pch.h"
#include <iostream>
#include <fstream>
#include <thread>
#include "dllmain.h"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/json.hpp>

#include "Logger.h"
#include "WebSocket.h"
#include "Message.h"

#include "./GameManager/GameManager.h"
#include "./Commands/Commands.h"

HMODULE hModuleSelf;

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

void processMessage(websocket::stream<tcp::socket>& ws, beast::flat_buffer buffer)
{
  std::string incommingMessage = beast::buffers_to_string(buffer.data());
  LOG_DEBUG(incommingMessage);

  Message message = Message::Parse(incommingMessage);

  LOG_DEBUG(message.CommandName);

  std::shared_ptr<GameManager> gm = GameManager::Get();

  if (message.CommandName != Commands::Close && !gm->IsHospitalReady())
  {
    boost::json::object response = {};
    response["ID"] = message.ID;
    response["Complete"] = false;

    std::string outgoingMessage = boost::json::serialize(response);
    LOG_DEBUG(outgoingMessage);

    ws.write(net::buffer(outgoingMessage));
    return;
  }

  ICommand* command = CommandsFactory::Generate(message.CommandName, message.Command);
  bool complete = command->Run(gm);
  LOG_DEBUG(complete);

  boost::json::object response = {};
  response["ID"] = message.ID;
  response["Complete"] = complete;

  std::string outgoingMessage = boost::json::serialize(response);
  LOG_DEBUG(outgoingMessage);

  ws.write(net::buffer(outgoingMessage));
}

void do_session(tcp::socket socket)
{
  try
  {
    websocket::stream<tcp::socket> ws{ std::move(socket) };

    ws.set_option(websocket::stream_base::decorator(
      [](websocket::response_type& res)
      {
        res.set(http::field::server,
          std::string(BOOST_BEAST_VERSION_STRING) +
          " websocket-server-sync");
      }));

    ws.accept();

    for (;;)
    {
      beast::flat_buffer buffer;

      LOG_DEBUG("Waiting for message");
      ws.read(buffer);

      std::thread(&processMessage, std::ref(ws), buffer).detach();
    }
  }
  catch (beast::system_error const& se)
  {
    if (se.code() != websocket::error::closed)
      std::cerr << "Error: " << se.code().message();
  }
  catch (std::exception const& e)
  {
    std::cerr << "Error: " << e.what();
  }
}

void WS_Thread(WS_Config* wsConfig)
{
  LOG_DEBUG("Starting WebSocket server");
  LOG_DEBUG("Host " << wsConfig->Host);
  LOG_DEBUG("Port " << wsConfig->Port);

  try
  {
    auto const address = net::ip::make_address(wsConfig->Host);
    auto const port = static_cast<unsigned short>(std::stoi(wsConfig->Port));

    net::io_context ioc{ 1 };

    tcp::acceptor acceptor{ ioc, {address, port} };
    for (;;)
    {
      tcp::socket socket{ ioc };

      LOG_DEBUG("Waiting for connection");
      acceptor.accept(socket);

      std::thread(
        &do_session,
        std::move(socket)
      ).detach();
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what();
    return;
  }
}

HANDLE CreateConsole()
{
  BOOL res = AllocConsole();
  if (!res) return NULL;

  FILE* fDummy;
  freopen_s(&fDummy, "CONIN$", "r", stdin);
  freopen_s(&fDummy, "CONOUT$", "w", stderr);
  freopen_s(&fDummy, "CONOUT$", "w", stdout);

  return GetStdHandle(STD_OUTPUT_HANDLE);
}

//void Commands_Thread()
//{
//  //std::shared_ptr<QuakeManager> quakeManager = QuakeManager::Get(lpModuleBaseAddress);
//  //std::shared_ptr<EmergencyManager> emergencyManager = EmergencyManager::Get(lpModuleBaseAddress, ptHospitalDataOffset);
//  //std::shared_ptr<VIPManager> vipManager = VIPManager::Get(lpModuleBaseAddress, ptHospitalDataOffset);
//  //std::shared_ptr<DisasterManager> disasterManager = DisasterManager::Get(lpModuleBaseAddress, ptHospitalDataOffset);
//  //std::shared_ptr<EpidemyManager> epidemyManager = EpidemyManager::Get(lpModuleBaseAddress);
//
//  unlockCamera(lpModuleBaseAddress);
//}

void Init()
{
  LOG_DEBUG("Init");

  std::ifstream config = std::ifstream("ThemeHospital_StreamerMod_config.json", std::ifstream::binary);
  //LOG_DEBUG(config.rdbuf());
  //uint32_t lpModuleBaseAddress = 0x00400000;

  //GlobalsOffset globalsOffset = {
  //  .howContagious = 0xc47ce,
  //  .leaveMax = 0xc4808,
  //  .bowelOverflows = 0xc4818,
  //  .mayorLaunch = 0xc4828,
  //  .langTextSections = 0xdaf60,
  //  .isFaxOpen = 0xdefb0,
  //  .hospital = 0xdd124,
  //  .isPaused = 0xe10b1,
  //  .cameraPositionLimit = 0xe11c2,
  //  .gameClock = 0xe48a8,
  //  .rooms = 0xe5208
  //};
  //GlobalsOffset globalsOffset = {};
  GameOffsets gameOffset = {};
  boost::system::error_code ec;

  boost::json::parse_into(gameOffset, config, ec);
  if (ec.failed())
  {
    LOG_DEBUG(ec.message());
  }

  /*DisastersOffsets disastersOffsets = {
    .VomitLimit = 0xc481a,
    .DoctorPopupText = 0xdcb92
  };

  QuakeOffsets quakeOffsets = {
    .NextClock = 0xe117b,
    .Stage = 0xe117f,
    .Next = 0xe11b7,
    .IndexUsed = 0xe11db
  };

  EmergencyOffsets emergencyOffsets = {
     .Next = 0xe11ad,
     .SkippedCount = 0xe11ce,
     .IndexUsed = 0xe11eb
  };

  EpidemicOffsets epidemicOffsets = {
    .createPatientObjFunc = 0x36bf0,
    .spawnObjectFunc = 0x6c120
  };

  GameOffsets gameOffset = {
    .globalsOffset = globalsOffset,
    .disastersOffsets = disastersOffsets,
    .emergencyOffsets = emergencyOffsets,
    .quakeOffsets = quakeOffsets,
    .epidemicOffsets = epidemicOffsets
  };*/

  GameManager::Get(gameOffset.lpModuleBaseAddress, gameOffset);
}

void hookThread()
{
  HANDLE hConsole = NULL;
  if (hConsole == NULL) {
    hConsole = CreateConsole();
  }

  LOG_DEBUG("Theme Hospital Streamer Mod DLL injecting");

  Init();

  WS_Config* wsConfig = new WS_Config{ "127.0.0.1", "9099" };

  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WS_Thread, wsConfig, 0, NULL);
  //CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Commands_Thread, NULL, 0, NULL);

  LOG_DEBUG("Theme Hospital Streamer Mod DLL injected");
  LOG_DEBUG(hModuleSelf);
}

BOOL APIENTRY DllMain(HMODULE hModule,
  DWORD  ul_reason_for_call,
  LPVOID lpReserved
)
{
  hModuleSelf = hModule;

  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)hookThread, NULL, 0, NULL);
    break;
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}

