#pragma once
#include "XmlRpc.h"
#include "app/AppServer.h"

class RpcAuthLogin : public XmlRpc::XmlRpcServerMethod {
public:
  RpcAuthLogin(XmlRpc::XmlRpcServer* srv, AppServer& app);

  void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result) override;
  std::string help() override { return "auth.login: {username, password} -> token"; }

private:
  AppServer& app_;
};
