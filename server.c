/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
	 char sendBuff[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
	 
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
	 
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
	 
     if (sockfd < 0) 
        error("ERROR opening socket");
	
     bzero((char *) &serv_addr, sizeof(serv_addr));
	 
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
	 
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
		  
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
				 
     if (newsockfd < 0) 
          error("ERROR on accept");
	  
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
	 
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %c\n",buffer[0]);
	
	srand(time(NULL));
	int ran = rand() % 2;
	char server;

	if (!ran)
		server = 'B';
	else 
		server = 'S';
		
	if (server == 'B' && buffer[0] == 'B'){
        strcpy(sendBuff, "2 years of imprisoment for the client and the server.");
	}
	else if (server == 'S' && buffer[0] == 'B'){
        strcpy(sendBuff, "Client is free and Server is imprisoned for 3 years.");
	}
	else if (server == 'B' && buffer[0] == 'S'){
		strcpy(sendBuff, "Server is free and Client is imprisoned for 3 years.");
	}
	else if (server == 'S' && buffer[0] == 'S'){
		strcpy(sendBuff, "1 year of prison for Server and Client");
	}
	n = write(newsockfd, sendBuff , strlen(sendBuff));

	if (n < 0) error("ERROR writing to socket");
	close(newsockfd);
	close(sockfd);
	return 0; 
}