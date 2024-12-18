#include <winsock2.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

vector<SOCKET> clients;
mutex clientsMutex;

void handle_client(SOCKET clientSocket) {
    char buffer[512];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            cout << "Cliente desconectado." << endl;
            closesocket(clientSocket);
            {
                lock_guard<mutex> lock(clientsMutex);
                clients.erase(remove(clients.begin(), clients.end(), clientSocket), clients.end());
            }
            break;
        }
        buffer[bytesReceived] = '\0';
        cout << "Mensaje recibido: " << buffer << endl;

        {
            lock_guard<mutex> lock(clientsMutex);
            for (SOCKET client : clients) {
                if (client != clientSocket) {
                    send(client, buffer, bytesReceived, 0);
                }
            }
        }
    }
}

int main() {
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    cout << "Servidor en espera de conexiones..." << endl;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        cout << "Cliente conectado." << endl;

        {
            lock_guard<mutex> lock(clientsMutex);
            clients.push_back(clientSocket);
        }

        thread(handle_client, clientSocket).detach();
    }

    WSACleanup();
    return 0;
}
