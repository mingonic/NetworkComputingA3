#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//using namespace std;

int main(int argc,char *argv[])
{
  int clientSocket;
  char *IpAddress;
  int Portno;
  char response_buffer[100];
  char request_buffer[100];
  char buf[100];
  time_t curtime;
  struct tm *loc_time;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  if(argc<3)
  {
        printf("\nPlease Pass IP address and Port Number and Message as a Parameter");
        exit(0);
  }

  IpAddress=argv[1]; //Assigning first Arguement as a IPaddress.
  printf("\nThe Ip address is : %s",IpAddress);
  Portno=atoi(argv[2]);    //Assigning Second Arguement as a Port Number.
  cout<<"\nThe Port Number is: "<<Portno<<endl;
  request_buffer=argv[3];

  //create The Socket Connection
  if(!(clientSocket = socket(PF_INET, SOCK_STREAM, 1)))
  {
      printf("\nFailed to create a Scoket:\n");
  }

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(Portno);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  addr_size = sizeof serverAddr;

  //Connecting with IPaddress
  if(connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size)<0)
  {
      printf("Connect Error:\n");
      exit(0);
  }

  curtime = time (NULL);
  loc_time = localtime (&curtime);
  strftime (buf, 140, "Time is %I:%M %p.\n", loc_time);
  fputs (buf, stdout);

  //Send Request to The Server
  send(clientSocket,request_message,sizeof(request_message),0);
  printf("\nRequest Successfully sent to the server:\n");

  //Receive Response from the Server
  recv(clientSocket, response_buffer, sizeof(response_buffer), 0);
  printf("\nReceived Response from the Server is %s",response_buffer);
  return 0;
}
