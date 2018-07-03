#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#define PORT 50009

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    char recv1[20];
    char recv2[20];
    char *resp1 = "B";
    char *resp2 = "S";
    pid_t pid;


    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );


    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while (1){
       //printf("Waiting for connection,,,\n");
       if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
       {
           perror("accept");
           exit(EXIT_FAILURE);
       }
       pid = fork();
       if (pid < 0){
           perror("Error in fork\n");
           return 0;
       }
       if (pid == 0){
          close(server_fd);
          valread = read( new_socket , buffer, 20);
          printf("Received %s\n",buffer );
          //sleep(10);
          if (rand() % 2 == 0){
             send(new_socket , resp1 , strlen(resp1) , 0 );
             printf("Sent:%s\n",resp1);
          }
          else {
             send(new_socket , resp2 , strlen(resp2) , 0 );
             printf("Sent:%s\n",resp2);
          }
          valread = read( new_socket , buffer, 20);
          printf("Received %s\n",buffer );
          //sleep(10);
          if (rand() % 2 == 0){
             send(new_socket , resp1 , strlen(resp1) , 0 );
             printf("Sent:%s\n",resp1);
          }
          else {
             send(new_socket , resp2 , strlen(resp2) , 0 );
             printf("Sent:%s\n",resp2);
          }
          //printf("Hello message sent\n");
          close(new_socket);
          return 0;
       }
       else {
        close(new_socket);
       }
    }
    return 0;
}



#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
//#define PORT 50009

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char msg[20];
    char buffer[1024] = {0};
    int port;
    char resp1[20];
    char resp2[20];
    port = atoi(argv[2]);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);


    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("\nEnter input for prisoner B:");
    scanf("%s",msg);

    send(sock , msg , strlen(msg) , 0 );
    printf("Sent:%s\n",msg);
    valread = read( sock , resp1, 20);
    printf("Recived:%c\n",resp1[0]);
    printf("\nEnter input for prisoner A:");
    scanf("%s",msg);

    send(sock , msg , strlen(msg) , 0 );
    printf("Sent:%s\n",msg);
    valread = read( sock , resp2,20);
    printf("Recived:%c %c\n",resp1[0], resp2[0]);
    if (resp1[0] == 'B' && resp2[0] == 'B'){
       printf("2 years imprisonment for prisoner A and B\n");
    }
    else if (resp1[0] == 'S' && resp2[0] == 'B'){
       printf("B is free and 3 years for A\n");
    }
    else if (resp1[0] == 'B' && resp2[0] == 'S'){
       printf("A is free and 3 years for B\n");
    }
    else if (resp1[0] == 'S' && resp2[0] == 'S'){
       printf("1 year for A and B\n");
    }

    printf("%s\n",buffer );
    return 0;
}
