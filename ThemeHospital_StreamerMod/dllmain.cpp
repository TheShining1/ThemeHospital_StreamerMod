// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <thread>
#include "dllmain.h"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/json.hpp>

#include "Logger.h"
#include "WebSocket.h"
#include "Message.h"
#include "./Commands/Commands.h"
#include "./Quake/QuakeManager.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//void UnhookDLL()
//{
//  BOOST_LOG_SEV(lg, debug) << "Theme Hospital Streamer Mod DLL unload";
//
//  HMODULE hDll = GetModuleHandle(NULL);
//  BOOST_LOG_SEV(lg, debug) << "hDll " << hDll;
//   FreeLibraryAndExitThread(hDll,0);
//}

void do_session(tcp::socket socket)
{
  //Logger logger = Logger();
  //using namespace logging::trivial;
  //src::severity_logger<severity_level> lg;

  try
  {
    // Construct the stream by moving in the socket
    websocket::stream<tcp::socket> ws{ std::move(socket) };

    // Set a decorator to change the Server of the handshake
    ws.set_option(websocket::stream_base::decorator(
      [](websocket::response_type& res)
      {
        res.set(http::field::server,
        std::string(BOOST_BEAST_VERSION_STRING) +
        " websocket-server-sync");
      }));

    // Accept the websocket handshake
    ws.accept();

    for (;;)
    {
      // This buffer will hold the incoming message
      beast::flat_buffer buffer;

      LOG_DEBUG("Waiting for message");
      //logger.Log("Waiting for message");
      // Read a message
      ws.read(buffer);

      std::string incommingMessage = beast::buffers_to_string(buffer.data());
      LOG_DEBUG(incommingMessage);
      //logger.Log(data);

      Message message = Message::Parse(incommingMessage);

      //logger.Log(message.App);
      //logger.Log(message.CommandName);
      LOG_DEBUG(message.App);
      LOG_DEBUG(message.CommandName);
      //std::cout << message.App << std::endl;
      //std::cout << message.CommandName << std::endl;

      //CommandsFactory* cf = new CommandsFactory();
      ICommand* command = CommandsFactory::Generate(message.CommandName, message.Command);
      //LOG_DEBUG(command->ID());
      //logger.Log(command.Name);
      //LOG_DEBUG(command->Name);
      bool complete = command->Run();
      LOG_DEBUG(complete);

      boost::json::object response = {};
      response["App"] = message.App;
      response["ID"] = message.ID;
      response["Complete"] = complete;

      std::string outgoingMessage = boost::json::serialize(response);
      LOG_DEBUG(outgoingMessage);

      ws.write(net::buffer(outgoingMessage));
      //CommandQuake cq;

      /*CommandClose cc = CommandClose();
      CommandQuake cq = CommandQuake();

      switch (message.CommandName)
      {
      case Commands::Close:
        cc = CommandClose::Parse(message.Command);
        cc.Run();
        break;
      case Commands::Quake:
        cq = CommandQuake::Parse(message.Command);
        cq.Run();
        break;
      default:
        break;
      }*/
    }
  }
  catch (beast::system_error const& se)
  {
    // This indicates that the session was closed
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
  //Logger logger = Logger();
  //using namespace logging::trivial;
  //src::severity_logger<severity_level> lg;

  //logger.Log("Starting WebSocket server");
  //logger.Log(wsConfig->Host);
  //logger.Log(wsConfig->Port);
  LOG_DEBUG("Starting WebSocket server");
  LOG_DEBUG("Host " << wsConfig->Host);
  LOG_DEBUG("Port " << wsConfig->Port);

  try
  {
    auto const address = net::ip::make_address(wsConfig->Host);
    auto const port = static_cast<unsigned short>(std::stoi(wsConfig->Port));

    // The io_context is required for all I/O
    net::io_context ioc{ 1 };

    // The acceptor receives incoming connections
    tcp::acceptor acceptor{ ioc, {address, port} };
    for (;;)
    {
      // This will receive the new connection
      tcp::socket socket{ ioc };

      LOG_DEBUG("Waiting for connection");
      //logger.Log("Waiting for connection");
      // Block until we get a connection
      acceptor.accept(socket);

      // Launch the session, transferring ownership of the socket
      std::thread(
        &do_session,
        std::move(socket)).detach();
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

  //freopen_s(&fDummy, "inputs.txt", "r", stdin);
  //freopen_s(&fDummy, "logs.txt", "a+", stdout);
  //freopen_s(&fDummy, "error.txt", "a+", stderr);

  return GetStdHandle(STD_OUTPUT_HANDLE);
}

void Commands_Thread()
{
  //Logger logger = Logger();

  DWORD lpModuleBaseAddress = 0x00400000;

  //QuakeManager quakeManager = QuakeManager(logger, lpModuleBaseAddress);
  std::shared_ptr<QuakeManager> quakeManager = QuakeManager::Get(lpModuleBaseAddress);
}

void hookThread()
{
 /* logging::add_file_log("logs.log");
  logging::add_common_attributes();
  using namespace logging::trivial;
  src::severity_logger<severity_level> lg;*/

  HANDLE hConsole = NULL;
  if (hConsole == NULL) {
    hConsole = CreateConsole();
  }

  //Logger logger = Logger();
  //log_init();

  LOG_DEBUG("Theme Hospital Streamer Mod DLL injecting");
  //std::cout << "Theme Hospital Streamer Mod DLL injecting" << std::endl;

  WS_Config* wsConfig = new WS_Config{ "127.0.0.1", "9099" };

  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WS_Thread, wsConfig, 0, NULL);
  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Commands_Thread, NULL, 0, NULL);

  LOG_DEBUG("Theme Hospital Streamer Mod DLL injected");
  //std::cout << "Theme Hospital Streamer Mod DLL injected" << std::endl;

  //Sleep(15000);

  //UnhookDLL();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
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

