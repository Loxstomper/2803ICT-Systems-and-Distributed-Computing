#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 8888

int main()
{
    char message[1024];
    char reply[1024];

    int sock;

    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 1)
    {
        printf("Could not create socket\n");
        return 1;
    }

    printf("Socket created\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Connection to server failed\n");
        return 1;
    }

    printf("Connection successfull\n");

    while (1)
    {
        printf("\nRequest: ");
        scanf("%s", message);


        if (send(sock, message, strlen(message), 0) < 0)
        {
            printf("Send Failed!\n");
            return 1;
        }

        if (strcmp(message, "quit") == 0)
        {
            break;
        }

        if (recv(sock, reply, 1024, 0) < 0)
        {
            printf("Recv Failed!\n");
            return 1;
        }

        printf("Reply: %s \n", reply);

        memset(&reply, '\0', strlen(reply));
    }

    close(sock);

    return 0;
}
