#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>


#define PORT 8888


int main()
{
    int socket_desc, client_sock, read_size;
    int client_size;
    int new_socket;
    pid_t child_PID;
    struct sockaddr_in server, client;

    char client_message[1024];
    char to_send[1024];

    /* create the socket */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 1)
    {
        printf("Failed to create socket\n");
        return 1;
    }

    printf("Socket created\n");

    /* set up the struct */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    /* bind */
    if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Bind failed\n");
        return 1;
    }

    printf("Bind complete\n");

    /* listen to maximum of 5 connections */
    listen(socket_desc, 5);

    client_size = sizeof(struct sockaddr_in);

/*     client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&client_size); */ 

/*     if (client_sock < 0) */
/*     { */
/*         printf("Accepted failed!\n"); */
/*         return 1; */
/*     } */

/*     printf("Connection accepted\n"); */

    while (1)
    {
        new_socket = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&client_size);

        if (new_socket < 0)
        {
            exit(1);
        }

        printf("Connection from: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        if ((child_PID = fork()) == 0)
        {
            close(socket_desc);

            while(1)
            {
                recv(client_sock, client_message, 1024, 0);

                if (strcmp(client_message, "exit") == 0)
                {
                    printf("Disconected from: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
                    break;
                }
                else
                {
                    printf("Message from: %s:%d\t%s\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), client_message);
                    send(client_sock, client_message, strlen(client_message), 0);
                    memset(client_message, '\0', strlen(client_message));
                }
            }
        }

    }
    /* while((read_size = read(client_sock, client_message, sizeof(client_message))) > 0) */
    /* { */
    /*     printf("Message: %s\n", client_message); */
    /*     write(client_sock, client_message, strlen(client_message)); */
    /*     memset(&client_message, '\0', strlen(client_message)); */
    /* } */

    if (read_size == 0)
    {
        printf("Client disconnected\n");
    }



    return 0;
}
