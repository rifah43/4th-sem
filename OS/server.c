#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <netinet/in.h>
#include <dirent.h>
#include <pthread.h>
#include <signal.h>
#define PORT 4040
#define SIZE 4096
#define MAX_CLIENT 10

int server_socket;
struct sockaddr_in server_address;
int address_length = sizeof(struct sockaddr_in);

typedef struct
{
    struct sockaddr_in client_address;
    pthread_t tid;
    int *cid;
    int socket_fd;
    char username[10];
} client_structure;
client_structure *client_infos[MAX_CLIENT];

static int ccounter = 0;
static int client_id = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void client_add(client_structure *client)
{
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < MAX_CLIENT; i++)
    {
        if (!client_infos[i])
        {
            client_infos[i] = client;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
}

void client_remove(client_structure *client)
{
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < MAX_CLIENT; i++)
    {
        if (client_infos[i] && *client_infos[i]->cid == *client->cid)
        {
            client_infos[i] = NULL;
            break;
        }
    }
    ccounter--;
    free(client);
    pthread_mutex_unlock(&mutex);
}

char *name_entry(char *array, int length)
{

    char *b = (char *)malloc(sizeof(char) * 32);
    int count = 0;
    int i;
    for (i = 0; i < length; i++)
    {
        if (array[i - 1] == '@')
            break;
    }

    int j = 0;
    for (; i < length; i++)
    {
        if (array[i] == ':')
            break;

        b[j++] = array[i];
    }
    b[j] = '\0';
    return b;
}

char *take_message(char *array, int length)
{
    char *c = (char *)malloc(sizeof(char) * SIZE);
    int i;
    int count = 0;
    for (i = 0; i < length; i++)
    {
        if (array[i - 1] == ':')
        {
            count++;
            if (count == 2)
                break;
        }
    }

    int j = 0;
    for (; i < length; i++)
    {
        c[j++] = array[i];
    }
    c[j] = '\0';
    return c;
}

void connect_reciever(char *message, char *sender_name, int cid)
{

    char *receiver_name = name_entry(message, strlen(message));
    char *message1 = take_message(message, strlen(message));

    pthread_mutex_lock(&mutex);
    if (strcmp(receiver_name, "all") == 0)
    {
        for (int i = 0; i < MAX_CLIENT; i++)
        {
            if (client_infos[i] && *client_infos[i]->cid != cid)
            {
                send(client_infos[i]->socket_fd, "\n", strlen("\n"), 0);
                send(client_infos[i]->socket_fd, sender_name, strlen(sender_name), 0);
                send(client_infos[i]->socket_fd, ": ", strlen(": "), 0);
                send(client_infos[i]->socket_fd, message1, strlen(message1), 0);
                send(client_infos[i]->socket_fd, "\n\n", strlen("\n\n"), 0);
            }
        }
    }
    else
    {
        for (int i = 0; i < MAX_CLIENT; i++)
        {
            if (client_infos[i] && strcmp(client_infos[i]->username, receiver_name) == 0)
            {
                send(client_infos[i]->socket_fd, "\n", strlen("\n"), 0);
                send(client_infos[i]->socket_fd, sender_name, strlen(sender_name), 0);
                send(client_infos[i]->socket_fd, ": ", strlen(": "), 0);
                send(client_infos[i]->socket_fd, message1, strlen(message1), 0);
                send(client_infos[i]->socket_fd, "\n\n", strlen("\n\n"), 0);
            }
        }
    }
    pthread_mutex_unlock(&mutex);
}


void *client_handler(void *Client)
{

    client_structure *client_socket = (client_structure *)Client;
    int client_id = *client_socket->cid;

    char buffer[SIZE];
    char name[10];
    ccounter++;
    int flag = 0;

    send(client_socket->socket_fd, "\nEnter username: \n", strlen("\nEnter username: \n"), 0);
    if (recv(client_socket->socket_fd, name, 10, 0) <= 0 || strlen(name) < 1 || strlen(name) > 10)
    {
        printf("Invalid username\n");
        flag = 1;
    }
    else
    {
        char a[] = "Message format: @user_name:message\nType \"exit\"\n\n";
        send(client_socket->socket_fd, a, strlen(a), 0);
        name[strlen(name)-1]='\0';
        strcpy(client_socket->username, name);
        client_add(client_socket);
        sprintf(buffer, "%s is connected\n\n", client_socket->username);
        printf("%s", buffer);
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < MAX_CLIENT; i++)
        {
            if (client_infos[i] && *client_infos[i]->cid != *client_socket->cid)
                send(client_infos[i]->socket_fd, buffer, strlen(buffer), 0);
        }
        pthread_mutex_unlock(&mutex);
    }
    bzero(buffer, sizeof(buffer));

    while (1)
    {
        if (flag)
            break;
        int r = recv(client_socket->socket_fd, buffer, sizeof(buffer), 0);
        if (r > 0 && strlen(buffer) > 0 && strcmp(buffer, "exit\r\n") != 0)
        {
            char buffer1[8192];
            change_newline_to_null(buffer, strlen(buffer));
            sprintf(buffer1, "%s:%s", client_socket->username, buffer);
            connect_reciever(buffer1, client_socket->username, *client_socket->cid);
            printf("%s- %s\n", client_socket->username, buffer);
        }
        else if (r == 0 || strcmp(buffer, "exit\r\n") == 0)
        {
            sprintf(buffer, "%s is disconnected\n", client_socket->username);
            printf("%s\n", buffer);
            pthread_mutex_lock(&mutex);
            for (int i = 0; i < MAX_CLIENT; i++)
            {
                if (client_infos[i] && *client_infos[i]->cid != *client_socket->cid)
                    send(client_infos[i]->socket_fd, buffer, strlen(buffer), 0);
            }
            pthread_mutex_unlock(&mutex);
            flag = 1;
        }
        else
        {
            perror("An error occured");
            flag = 1;
        }
        bzero(buffer, sizeof(buffer));
    }
    close(client_socket->socket_fd);
    client_remove(client_socket);
    pthread_detach(pthread_self());
}

int main(int argc, char *argv[])
{
    system("clear");
    int option_value = 1;

    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket < 0)
    {
        perror("Socket creation Unsuccessful");
        exit(EXIT_FAILURE);
    }

    signal(SIGPIPE, SIG_IGN);

    if (setsockopt(server_socket, SOL_SOCKET, (SO_REUSEADDR | SO_REUSEPORT), &option_value, sizeof(option_value)) < 0)
    {
        perror("setsockoption_value");
        exit(EXIT_FAILURE);
    }

    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Binding Unsuccessful");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CLIENT) < 0)
    {
        perror("Listen Unsuccessful");
        exit(EXIT_FAILURE);
    }
    printf("\nServer Ready\n");

    while (1)
    {
        client_structure *client = (client_structure *)malloc(sizeof(client_structure));
        client->socket_fd = accept(server_socket, (struct sockaddr *)&client->client_address, &address_length);
        client->cid = (int *)malloc(sizeof(int));
        *client->cid = client_id++;
        pthread_create(&client->tid, NULL, &client_handler, (void *)client);
    }
    return 0;
}