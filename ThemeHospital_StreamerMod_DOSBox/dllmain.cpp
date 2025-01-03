#include "pch.h"
#include <iostream>
#include <fstream>
#include <thread>
#include "dllmain.h"
#include "Config.h"

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
std::string CONFIG_FILENAME = "ThemeHospital_StreamerMod_DOSBox_config.json";

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

bool ReadOffsets(std::string filename, GameOffsets* gameOffsets)
{
  std::ifstream config = std::ifstream(filename, std::ifstream::binary);

  boost::system::error_code ec;
  boost::json::parse_into(*gameOffsets, config, ec);
  if (ec.failed())
  {
    LOG_DEBUG("Can't read game offsets");
    LOG_DEBUG(ec.message());
    return false;
  }

  return true;
}

bool ReadConfig(Config* config)
{
  std::ifstream configStream = std::ifstream(CONFIG_FILENAME, std::ifstream::binary);

  boost::system::error_code ec;
  boost::json::parse_into(*config, configStream, ec);
  if (ec.failed())
  {
    LOG_DEBUG("Can't read config");
    LOG_DEBUG(ec.message());
    return false;
  }

  return true;
}

bool Init(Config* config)
{
  LOG_DEBUG("Init");

  if (!ReadConfig(config)) return false;

  GameOffsets gameOffset = {};
  if (!ReadOffsets(config->gameOffsetsFilename, &gameOffset)) return false;

  GameManager::Get(gameOffset);
  return true;
}

void hookThread()
{
  HANDLE hConsole = NULL;
  if (hConsole == NULL) {
    hConsole = CreateConsole();
  }

  LOG_DEBUG("Theme Hospital Streamer Mod DLL injecting");

  Config* config = new Config{};

  if (!Init(config)) return;

  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WS_Thread, &config->wsConfig, 0, NULL);

  LOG_DEBUG("Theme Hospital Streamer Mod DLL injected");
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

