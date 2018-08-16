#include "common.h"


int main(int argc, char ** argv)
{
    char message[1024];
    char reply[2048];
    int sock;

    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1)
    {
        printf("Could not create socket\n");
        return -1;
    }

    printf("Created socket\n");

    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(9999);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Connection Failed!\n");
        return -1;
    }

    printf("Connected\n");

    while (1)
    {
        printf("\nRequest: ");
        scanf("%s", message);

        if (send(sock, message, strlen(message), 0) < 0)
        {
            printf("Send Failed!\n");
            return -1;
        }

        if (recv(sock, reply, 2048, 0) < 0)
        {
            printf("Recv Failed!\n");
            return -1;
        }

        printf("Reply: %s\n", reply);
        memset(&reply, '\0', strlen(reply));
    }

    close(sock);

    return 0;
}
