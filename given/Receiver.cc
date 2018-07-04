#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main(int argc,char *argv)
{

  int Server_Socket, newSocket;
  char response_buffer[500];
  char request_buffer[1000];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  if(!(Server_Socket = socket(PF_INET, SOCK_STREAM, 0))<0)
  {
        printf("Socket Error:\n");
        exit(0);
  }

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8888);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  bind(Server_Socket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  if(listen(Server_Socket,5)==0)
  {
        printf("Listening\n");
  }
  else
  {
        printf("Error\n");
        exit(0);
  }

  addr_size = sizeof serverStorage;
  newSocket = accept(Server_Socket, (struct sockaddr *) &serverStorage, &addr_size);
  strcpy(response_buffer,"\nHello Welcome Please wait!:\n");
  recv(newSocket, request_buffer, sizeof(request_buffer), 0);
  printf("\nReceived Request from the Client is :%s",request_buffer);
  send(newSocket,response_buffer,sizeof(response_buffer),0);
  printf("\nResponse Sent to the client Successfully:\n");
  return 0;
}
