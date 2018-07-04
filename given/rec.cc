#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

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
