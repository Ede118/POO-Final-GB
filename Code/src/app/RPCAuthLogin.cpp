#include "app/RPCAuthLogin.h"
using namespace XmlRpc;

RpcAuthLogin::RpcAuthLogin(XmlRpcServer* srv, AppServer& app)
  : XmlRpcServerMethod("auth.login", srv), app_(app) {}

void RpcAuthLogin::execute(XmlRpcValue& params, XmlRpcValue& result) {
  // Esperamos un struct con claves: username, password
  if (params.getType() != XmlRpcValue::TypeArray || params.size() != 1 ||
      params[0].getType() != XmlRpcValue::TypeStruct ||
      !params[0].hasMember("username") || !params[0].hasMember("password")) {
    result["status"]["code"] = 400;
    result["status"]["msg"]  = "BAD_REQUEST";
    result["payload"] = ""; // sin payload
    return;
  }

  XmlRpcValue& req = params[0];
  std::string username = std::string(req["username"]);
  std::string password = std::string(req["password"]);

  auto lr = app_.auth().login(username, password);

  result["status"]["code"] = lr.code;
  result["status"]["msg"]  = lr.msg;
  if (lr.code == 0) {
    result["payload"]["token"] = lr.token;
  } else {
    result["payload"] = ""; // sin payload
  }
}
