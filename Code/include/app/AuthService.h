#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>

struct LoginResult {
  int code;              // 0 OK, 301 AUTH_INVALID
  std::string msg;       // "OK" o motivo
  std::string token;     // no vacío si code==0
};

class AuthService {
public:
    AuthService();

    LoginResult login(const std::string& username, const std::string& password,
                    const std::string& client_ip = "");

    bool validateToken(const std::string& token) const;

private:
    std::unordered_map<std::string, std::string> users_;  // user -> password (demo)
    std::unordered_set<std::string> tokens_;              // tokens emitidos

    static std::string issueToken_();
};
