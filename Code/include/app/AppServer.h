#pragma once
#include "app/AuthService.h"

class AppServer {
public:
  AuthService& auth() { return auth_; }
  const AuthService& auth() const { return auth_; }

private:
  AuthService auth_;
};
