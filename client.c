#include "client.h"

SOCKET Connection;

void ClientHandler() {
    while (1) {
        char msg[2000] = {0};
        recv(Connection, (char*)msg, sizeof(msg), 0);
        if (sizeof(msg) != 0) {
            printf("\n%s\n", msg);
        }
    }
}

int main(int argc, char* argv[]) {
    setlocale(0, "");
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        printf("Error: WSAStartup failed!\n");
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    Connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        printf("Error connecting to server\n");
        return 1;
    }
    printf("Connected to server\n");

    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, 0, NULL);
    char msg[2000] = {0};
    while (1) {
        gets(msg);
        send(Connection, (char*)msg, sizeof(msg), 0);
        Sleep(10);
    }
    system("pause");
    return 0;
}
