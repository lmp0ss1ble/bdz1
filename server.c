#include "server.h"

SOCKET Connections[100];
int Counter = 0;

void ClientHandler(int idx) {
    while (1) {
        char msg[2000] = {0};
        recv(Connections[idx], (char*)msg, sizeof(msg), 0);
        if (sizeof(msg) != 0) {
            for (int j = 0; j < Counter; j++) {
                if (j == idx) {
                    continue;
                }
                send(Connections[j], (char*)msg, sizeof(msg), 0);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    setlocale(0, "");
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        printf("Error\n");
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    SOCKET newConnection;
    for (int i = 0; i < 100; i++) {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

        if (newConnection == 0) {
            printf("Error #2\n");
        } else {
            printf("Connected!\n");
            Connections[Counter] = newConnection;
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(Counter), 0, NULL);

            Counter++;
        }
    }
    system("pause");
    return 0;
}
