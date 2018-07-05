#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(void)
{
  int listenfd = 0,connfd = 0;

  struct sockaddr_in serv_addr;

  char sendBuff[1025];
  int numrv;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("socket retrieve success\n");

  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(5000);

  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

  if(listen(listenfd, 10) == -1){
      printf("Failed to listen\n");
      return -1;
  }

  while(1)
    {
      connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
      //got char containing b or s
      char client[1] = 'B';
      int ran = rand() % 2;
      char server[1];
      if (ran == 0)
        server[0] = 'S';
      else if (ran == 1)
        server[0] = 'B';

      if (server == 'B' && client == "B"){
        strcpy(sendBuff, "2 years of imprisoment for the client and the server.");
      }
      else if (server == 'S' && client == 'B'){
        strcpy(sendBuff, "Client is free and Server is imprisoned for 3 years.");
      }
      else if (server == 'B' && client == 'S'){
        strcpy(sendBuff, "Server is free and Client is imprisoned for 3 years.");
      }
      else if (server == 'S' && client == 'S'){
        strcpy(sendBuff, "1 year of prison for Server and Client");
      }

      write(connfd, sendBuff, strlen(sendBuff));

      close(connfd);
      sleep(1);
    }

  return 0;
}
