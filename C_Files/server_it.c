/*
* Program for iterative server 
* Written by Arpit Kumar Singh (13/CS/31)
            and Neetesh Kumar(13/CS/28)
            
            */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
/* The following three files must be included for network programming */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
main()
{
	int sockfd, newsockfd ; /* Socket descriptors */
	int clilen;
	struct sockaddr_in cli_addr, serv_addr;
	
	int i,p,length;
	int result;
	int operator;
	int temp=0;
	int flag=0;
	
	char input_buffer[100],c;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		printf("Error in creating the  socket\n");
		exit(0);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(50031);

	memset(serv_addr.sin_zero, '\0', sizeof (serv_addr.sin_zero));

	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	{
		printf("Unable to bind local address\n");
		exit(0);
	}

	listen(sockfd, 5);

	 
	while(1)
	{
		flag =0;
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,&clilen) ;
		if (newsockfd < 0)
		{
			printf("Accept error\n");
			exit(0);
		}

		printf("Server got connection from client %s\n", inet_ntoa(cli_addr.sin_addr));
                              //Receiving Data from client
		while(1)
		{

			if(flag == 1)
				break;			
			result=0;
			length=0;
			while(length<strlen(input_buffer))
			{             // if(length<=0)
                                                             //exit(0);
				printf("Recieving  Data from client\n\n");
				p=recv(newsockfd, input_buffer, 100, 0);
				if(p<0)
				{
					printf("Error in reciving from client");
					exit(0);
				}
				length = length + p;
				
				
			}
                                             //Evaluating the expression 
			for(i=0;i<strlen(input_buffer);i++)
			{
				c=input_buffer[i];
				if((int)c>=48 && (int)c<=57)
					result = result * 10+((int)c - 48) ;
				else
					break;
			}
			temp = result;
			if(result == 0 && i==0)
			{
				flag = 1;
				printf("%d",flag);
			}
                                             //Detecting the correct operator
			while(i<strlen(input_buffer))
			{
				if(input_buffer[i]=='+')
					operator = 1;
				else if(input_buffer[i] == '-')
					operator = 2;
				else if(input_buffer[i] == '*')
					operator = 3;
				else if(input_buffer[i] == '/')
					operator = 4;				
				i++;
				result = 0;
				while(i<strlen(input_buffer))
				{
					c=input_buffer[i];
					if((int)c>=48 && (int)c<=57)
					{
						result = result *10 + ((int)c - 48);
						i++;
					}
					else
						break;
				}
				if(operator == 1)
					temp = temp + result;
				else if(operator == 2)
					temp = temp - result;
				else if(operator == 3)
					temp = temp * result;
				else if(operator == 4)
					temp = temp / result;
			}

	
			for(i=0; i < 100; i++) 
				input_buffer[i] = '\0';
			if(flag == 1)
			{
				strcpy(input_buffer,"exit");
				p=send(newsockfd, input_buffer, strlen(input_buffer) + 1, 0);
				break;
			}
			sprintf(input_buffer, "%d", temp);

			printf("Result evaluated at server:%d\n\n",temp);
			length=0;
                                             //sending the result to the client
			while(length<strlen(input_buffer))
			{
				printf("Sending  Result to client\n\n");
				p=send(newsockfd, input_buffer, strlen(input_buffer) + 1, 0);
				if(p<0)
				{
					printf("Error in sending to client\n");
					exit(0);
				}
				length = length + p;
				//printf("%d",l);
				
			}
			
		}	
		close(newsockfd);
	}	
}

