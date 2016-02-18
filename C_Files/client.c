/*
* Program for client 
* Written by Arpit Kumar Singh (13/CS/31)
            and Neetesh Kumar(13/CS/28)
            
            */


#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


main()
{
	int sockfd ;
	struct sockaddr_in serv_addr;
	int i;
               int temp;
               int length;
	char input_buffer[100];

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		printf("Unable to create socket\n");
		exit(0);
	}

	serv_addr.sin_family= AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(50031);

	for(i=0; i < 100; i++) 
		input_buffer[i] = '\0';


	if ((connect(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr))) < 0) 
	{
		printf("Unable to connect to server\n");
		exit(0);
	}

	while(1)
	{
		printf("Enter the expression to evaluate:");
		scanf("%s",input_buffer);
		//Sending the expression to server to compute the expression
		length=0;
		while(length<strlen(input_buffer))
		{
			printf("Sending to server\n***********************\n");
			temp=send(sockfd, input_buffer, strlen(input_buffer) + 1, 0);
			if(temp<0)
			{
				printf("Error in sending to server\n");
				exit(0);
			}
			length = length + temp;
				
		}
			
	

		//Receiving the Result from the server
		length=0;
		while(length<strlen(input_buffer))
		{
			printf("Recieving from server\n\n");
			temp=recv(sockfd, input_buffer, 100, 0);
			if(temp<0)
			{
				printf("Error in reciving from server\n");
				exit(0);
			}
			length = length + temp;
			
				
				
		}
			
		if(strcmp(input_buffer,"exit")==0)
		{
			printf("Exit from client....\n"); 			
			exit(0);
		}	
	
		printf("Value recieved from the server:");
		printf("%s\n",input_buffer);
		printf("\n");
	}
	close(sockfd);
	
}
