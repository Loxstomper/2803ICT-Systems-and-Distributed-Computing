#include "common.h"

#include <time.h>

char* get_system_time()
{
    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    return asctime(timeinfo);
}

void get_host_name(char* buffer, int buff_size)
{
    gethostname(buffer, buff_size);
}

char* get_OS_type()
{
    #ifdef __linux__
    return "linux";
    #else
    return "windows";
    #endif
}

int main(int argc, char ** argv)
{
    printf("Server starting\n");
    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;

    char client_message[1024];

    /* create the socket */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -1) 
    {
        printf("Failed to create socket\n"); 
        return -1;
    }
    printf("Socket created\n");

    /* set up the struct */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(9999);

    /* bind */
    if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Bind Fail\n");
        return -1;
    }

    printf("Bind complete\n");

    listen(socket_desc, 3);
    
    c = sizeof(struct sockaddr_in);

    client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c);

    while((read_size = read(client_sock, client_message, sizeof(client_message))) > 0)
    {
        printf("Message: %s\n", client_message);
    }

    if (read_size == 0)
    {
        printf("Client desconnected\n");
    }

    return 0;
}
