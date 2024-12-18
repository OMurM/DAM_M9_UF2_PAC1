#include <winsock2.h>
#include <iostream>

using namespace std;

int main() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cerr << "Error inicializando Winsock: " << result << endl;
        return 1;
    }
    cout << "Sockets configurats correctament" << endl;
    WSACleanup();
    return 0;
}