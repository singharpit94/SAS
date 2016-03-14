/*Group no:19 Batch 1 
Arpit Kumar Singh(13/CS/31)
Neetesh Kumar(13/CS/25)*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

main()
{
	/*Declaring the variables*/

	int TCPsoc,UDPsoc,newTCPsoc ;
	int i,rv,p,clilen,maxsoc,flag,len;
	struct sockaddr_in serv_addr,clientAddr;
  	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	fd_set readfds;

	
	char buffer1[100], buffer2[100];

	//TCP socket information

	//TCP socket created
	if ((TCPsoc = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
	{
		printf("Unable to create socket\n");
		exit(0);
	}
	//socket variables gets initialized
	serv_addr.sin_family= AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(50031);

	//Binding TCP socket
	if (bind(TCPsoc, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	{
		printf("Unable to bind local address\n");
		exit(0);
	}
	
	listen(TCPsoc, 5);


	//UDP Socket information

	//UDP socket
	if ((UDPsoc = socket(PF_INET, SOCK_DGRAM, 0)) <0)
	{
		printf("Unable to create socket\n");
		exit(0);
	}

	//Initializing the variables
	serv_addr.sin_family = AF_INET;
  	serv_addr.sin_port = htons(50031);
  	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  	memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);

	//Binding the UDP socket
	if (bind(UDPsoc, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("Unable to bind local address\n");
		exit(0);
	} 

	addr_size = sizeof serverStorage;

	//highest socket descriptor
	if (TCPsoc > UDPsoc)
    		maxsoc = (TCPsoc + 1);
	else   
    		maxsoc = (UDPsoc + 1);


	while(1)
	{
		FD_ZERO(&readfds); //socket set cleared
		FD_SET(TCPsoc, &readfds);//TCP socket added to the socket set for reading
		FD_SET(UDPsoc, &readfds);//UDP socket added to the socket set for reading
		rv = select(maxsoc, &readfds, NULL, NULL, NULL);
	
		if (rv == -1) 
		{
			perror("select"); // error occurred in select()
		} 
		else if (rv == 0) 
		{
			printf("Data not received...");
		} 
		else 
		{
			if (FD_ISSET(TCPsoc, &readfds)) 
			{
			
				for(i=0;i<100;i++)
					buffer1[i]='\0';
				
				//the TCP client connection	
				clilen = sizeof(clientAddr);
				newTCPsoc = accept(TCPsoc, (struct sockaddr *) &clientAddr,&clilen) ;
				if (newTCPsoc < 0)
				{
					printf("Accept error\n");
					exit(0);
				}
	
				//reading message from client
				read(newTCPsoc, buffer1, 100);
				
				len = strlen(buffer1);
				flag = 1;
				printf("Word at TCP socket is %s",buffer1);
				printf("\n........................\n");
	
				//checking word is pallindrome or not
				len = strlen(buffer1);
				for(i=0;i<=(len-1)/2;i++)
				{					
					if(buffer1[i]!=buffer1[len-1-i])
					{	
						flag =0;
						break;
					}
				}
				if(flag == 1)
					strcpy(buffer1,"Pallindrome");
				else
					strcpy(buffer1,"Not Pallindrome");
	
				//sending the result to client		
				write(newTCPsoc,buffer1,strlen(buffer1)+1);
		
				//clearing the buffer for next iteration			
				for(i=0;i<100;i++)
					buffer1[i]='\0';
				
			}
			if (FD_ISSET(UDPsoc, &readfds)) 
			{
				//clearing the buffer
				for(i=0;i<100;i++)
					buffer2[i]='\0';
				
				//receiving from UDP client 			
				p = recvfrom(UDPsoc,buffer2,100,0,(struct sockaddr *)&serverStorage, &addr_size);
				len = strlen(buffer2);
				printf("Word at UDP socket is %s",buffer2);
				printf("\n...................\n");
				flag = 1;
	
				//checking word is pallindrome or not
				len = strlen(buffer2);
				for(i=0;i<=(len-1)/2;i++)
				{					
					if(buffer2[i]!=buffer2[len-1-i])
					{	
						flag =0;
						break;
					}
				}
				if(flag == 1)
					strcpy(buffer2,"Pallindrome");
				else
					strcpy(buffer2,"Not Pallindrome");
	
				//sending result back to client			
				sendto(UDPsoc,buffer2,strlen(buffer2)+1,0,(struct sockaddr *)&serverStorage,addr_size);
	
				//clearing the buffer for next iteration		
				for(i=0;i<100;i++)
					buffer2[i]='\0';
				
			}
		}
	}
}

