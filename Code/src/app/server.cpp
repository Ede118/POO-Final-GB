#include "XmlRpc.h"
#include "app/AppServer.h"
#include "app/RPCAuthLogin.h"
#include <iostream>

int main(int argc, char** argv) {
  int port = (argc > 1) ? std::atoi(argv[1]) : 8080;

  XmlRpc::setVerbosity(1);
  XmlRpc::XmlRpcServer server;
  AppServer app;

  // Registrar métodos
  RpcAuthLogin m_login(&server, app);

  // Opcional: introspección
  server.enableIntrospection(true);

  // Escuchar y atender
  if (!server.bindAndListen(port)) {
    std::cerr << "No se pudo bindear al puerto " << port << "\n";
    return 1;
  }
  std::cout << "Servidor RPC escuchando en puerto " << port << "\n";

  // loop simple
  while (true) {
    server.work(0.1); // 100 ms
  }
  // server.shutdown(); // nunca se alcanza en este loop
  return 0;
}
