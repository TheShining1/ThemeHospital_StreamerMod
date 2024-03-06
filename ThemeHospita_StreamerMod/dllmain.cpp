// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <thread>
#include "dllmain.h"
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/json.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

void do_session(tcp::socket socket)
{
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

      std::cout << "Waiting for message" << std::endl;
      // Read a message
      ws.read(buffer);
      std::cout << beast::make_printable(buffer.data()) << std::endl;

      std::string data = beast::buffers_to_string(buffer.data());
      std::cout << data << std::endl;
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
      std::cerr << "Error: " << se.code().message() << std::endl;
  }
  catch (std::exception const& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void WS_Start(const char* targetAddress, const char* targetPort)
{
  std::cout << "Starting WebSocket server" << std::endl;
  std::cout << "Host " << targetAddress << std::endl;
  std::cout << "Port " << targetPort << std::endl;

  try
  {
    auto const address = net::ip::make_address(targetAddress);
    auto const port = static_cast<unsigned short>(std::atoi(targetPort));

    // The io_context is required for all I/O
    net::io_context ioc{ 1 };

    // The acceptor receives incoming connections
    tcp::acceptor acceptor{ ioc, {address, port} };
    for (;;)
    {
      // This will receive the new connection
      tcp::socket socket{ ioc };

      std::cout << "Waiting for connection" << std::endl;
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
    std::cerr << "Error: " << e.what() << std::endl;
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

void hookThread()
{
  HANDLE hConsole = NULL;
  if (hConsole == NULL) {
    hConsole = CreateConsole();
  }

  puts("Theme Hospital Streamer Mod DLL injected");

  WS_Start("127.0.0.1", "9099");
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

