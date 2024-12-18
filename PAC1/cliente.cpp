#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    char buffer[1024] = {0};

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    cout << "Connexió establerta amb el servidor." << endl;

    const char* message = "Hola servidor!";
    send(clientSocket, message, strlen(message), 0);
    cout << "Enviant missatge: " << message << endl;

    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << "Resposta del servidor: " << buffer << endl;

    closesocket(clientSocket);

    WSACleanup();

    return 0;
}