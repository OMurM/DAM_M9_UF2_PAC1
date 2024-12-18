#include <winsock2.h>
#include <iostream>
#include <thread>

using namespace std;

void receive_messages(SOCKET clientSocket) {
    char buffer[512];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            cout << "Desconectado del servidor." << endl;
            break;
        }
        buffer[bytesReceived] = '\0';
        cout << "Mensaje recibido: " << buffer << endl;
    }
}

int main() {
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); 
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Error al conectar al servidor." << endl;
        return 1;
    }
    cout << "Conectado al servidor." << endl;

    thread(receive_messages, clientSocket).detach();

    char buffer[512];
    while (true) {
        cin.getline(buffer, sizeof(buffer));
        send(clientSocket, buffer, strlen(buffer), 0);
    }

    WSACleanup();
    return 0;
}
