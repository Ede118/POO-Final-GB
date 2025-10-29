#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <netinet/in.h>
#include <unistd.h>

std::string procesarRPC(const std::string& body) {
    // Responde a <methodName>sumar</methodName>
    if (body.find("<methodName>sumar</methodName>") != std::string::npos) {
        int a = 0, b = 0;
        size_t posA = body.find("<int>");
        if (posA != std::string::npos) {
            a = std::stoi(body.substr(posA + 5, body.find("</int>", posA) - posA - 5));
            size_t posB = body.find("<int>", posA + 1);
            b = std::stoi(body.substr(posB + 5, body.find("</int>", posB) - posB - 5));
        }
        int suma = a + b;
        std::ostringstream xml;
        xml << "<?xml version=\"1.0\"?>\n"
            << "<methodResponse><params><param><value><int>"
            << suma
            << "</int></value></param></params></methodResponse>";
        return xml.str();
    }
    // Si no reconoce método
    return "<?xml version=\"1.0\"?><methodResponse><fault><value><string>Metodo no reconocido</string></value></fault></methodResponse>";
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    bind(server_fd, (sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);

    std::cout << "Servidor XML-RPC escuchando en puerto 8080..." << std::endl;

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) continue;

        char buffer[4096] = {0};
        read(client_fd, buffer, sizeof(buffer));

        std::string body(buffer);
        auto pos = body.find("\r\n\r\n");
        if (pos != std::string::npos) body = body.substr(pos + 4);

        std::string xmlResponse = procesarRPC(body);

        std::ostringstream response;
        response << "HTTP/1.1 200 OK\r\n"
                 << "Content-Type: text/xml\r\n"
                 << "Content-Length: " << xmlResponse.size() << "\r\n\r\n"
                 << xmlResponse;

        write(client_fd, response.str().c_str(), response.str().size());
        close(client_fd);
    }
    close(server_fd);
    return 0;
}