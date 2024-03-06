// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <thread>
#include "dllmain.h"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/json.hpp>

#include "WebSocket.h"
#include "./Quake/QuakeManager.h"

namespace logging = boost::log;
namespace src = boost::log::sources;

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

void do_session(tcp::socket socket)
{
  using namespace logging::trivial;
  src::severity_logger<severity_level> lg;

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

       BOOST_LOG_SEV(lg, debug) << "Waiting for message";
      // Read a message
      ws.read(buffer);
       BOOST_LOG_SEV(lg, debug) << beast::make_printable(buffer.data());

      std::string data = beast::buffers_to_string(buffer.data());
       BOOST_LOG_SEV(lg, debug) << data;
      //Message message = Message::Parse(data);

      //std::cout << message.App << std::endl;
      //std::cout << message.CommandName << std::endl;

      /*CommandQuake cq;
      switch (message.CommandName)
      {
      case Commands::Close:
        std::cout << "Close command" << std::endl;
        ws.close(beast::websocket::close_code::none);
        return;
        break;
      case Commands::Quake:
        std::cout << "Quake command" << std::endl;
        cq = CommandQuake::Parse(message.Command);
        std::cout << cq.Name << std::endl;
        std::cout << cq.Severity << std::endl;
        break;
      default:
        std::cout << "Unknown command" << std::endl;
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
  using namespace logging::trivial;
  src::severity_logger<severity_level> lg;

   BOOST_LOG_SEV(lg, debug) << "Starting WebSocket server";
   BOOST_LOG_SEV(lg, debug) << "Host " << wsConfig->Host;
   BOOST_LOG_SEV(lg, debug) << "Port " << wsConfig->Port;

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

       BOOST_LOG_SEV(lg, debug) << "Waiting for connection";
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
  DWORD lpModuleBaseAddress = 0x00400000;

  QuakeManager quakeManager = QuakeManager(lpModuleBaseAddress);
}

void hookThread()
{
  logging::add_file_log("logs.log");
  logging::add_common_attributes();
  using namespace logging::trivial;
  src::severity_logger<severity_level> lg;

  HANDLE hConsole = NULL;
  if (hConsole == NULL) {
    hConsole = CreateConsole();
  }

  BOOST_LOG_SEV(lg, debug) << "Theme Hospital Streamer Mod DLL injecting";
  //std::cout << "Theme Hospital Streamer Mod DLL injecting" << std::endl;

  WS_Config* wsConfig = new WS_Config{ "127.0.0.1", "9099" };

  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WS_Thread, wsConfig, 0, NULL);
  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Commands_Thread, NULL, 0, NULL);

  BOOST_LOG_SEV(lg, debug) << "Theme Hospital Streamer Mod DLL injected";
  //std::cout << "Theme Hospital Streamer Mod DLL injected" << std::endl;
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

