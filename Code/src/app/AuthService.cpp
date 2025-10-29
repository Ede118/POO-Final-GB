#include "app/AuthService.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>


AuthService::AuthService() {
    // Demo: usuarios “quemados” para probar el puente. Cambiarás esto por MySQL.
    users_.emplace("admin", "1234");
    users_.emplace("user",  "abcd");
    }

    static std::string randHex_(size_t n) {
    static thread_local std::mt19937_64 rng{std::random_device{}()};
    static std::uniform_int_distribution<unsigned long long> dist;
    std::ostringstream os;
    while (n > 0) {
        auto v = dist(rng);
        size_t take = std::min<std::size_t>(n, sizeof(v) * 2);
    for (size_t i = 0; i < take/2; ++i) {
        unsigned byte = (v >> (i*8)) & 0xFFu;
        os << std::hex << std::setw(2) << std::setfill('0') << byte;
    }
    n -= take;
    }
    return os.str();
}

std::string AuthService::issueToken_() {
    return randHex_(32); // 32 hex chars ~ 128 bits
}

LoginResult AuthService::login(const std::string& username, const std::string& password,
                                const std::string& /*client_ip*/) {
    auto it = users_.find(username);
    if (it == users_.end() || it->second != password) {
        return {301, "AUTH_INVALID", ""};
    }
    std::string t = issueToken_();
    tokens_.insert(t);
    return {0, "OK", t};
}

bool AuthService::validateToken(const std::string& token) const {
    return tokens_.count(token) > 0;
}
