#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    char buffer[1024] = {0};

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);    

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    listen(serverSocket, 3);

    cout << "Esperant connexions..." << endl;

    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);

    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << "Missatge rebut del client: " << buffer << endl;

    const char* response = "Hola des del servidor!";
    send(clientSocket, response, strlen(response), 0);
    cout << "Resposta enviada al client." << endl;

    closesocket(clientSocket);
    closesocket(serverSocket);

    WSACleanup();

    return 0;
}  