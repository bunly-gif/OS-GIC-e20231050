
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

const std::string SERVER_IP = "192.168.1.33";
const int PORT = 9001;

int main(int argc, char* argv[]) {
    std::string student_name = "Student B";

    if (argc > 1) {
        student_name = argv[1];
    }

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP.c_str(), &server_address.sin_addr);

    if (connect(sock, (sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        std::cerr << "Connection failed\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    send(sock, student_name.c_str(), static_cast<int>(student_name.size()), 0);

    char buffer[1024] = {0};
    int received = recv(sock, buffer, sizeof(buffer) - 1, 0);

    if (received > 0) {
        std::cout << "Server response: " << buffer;
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}

