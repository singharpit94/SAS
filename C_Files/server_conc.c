/*Sammita Chakravarti(13/CS/18)
Shreya Ghosh(13/CS/25)*/


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
	int i,res,op,fin = 0,p,l,flag=0;
	char buf[100],c;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		printf("Cannot create socket\n");
		exit(0);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(50018);

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

		if(fork() == 0)
		{
			close(sockfd);
			printf("Server got connection from client %s\n", inet_ntoa(cli_addr.sin_addr));

			while(1)	
			{

				if(flag == 1)
					break;			
				res=0;
			/*printf("%d",res);
				for(i=0; i < 100; i++) 
					buf[i] = '\0';
			
			//send(newsockfd,"send",100,0);*/

			//sleep(5);
				l=0;
				while(l<strlen(buf))
				{
					printf("Recieving from client\n**********\n");
					p=recv(newsockfd, buf, 100, 0);
					if(p<0)
					{
						printf("Error in reciving from client");
						exit(0);
					}
					l = l + p;
					//printf("%d",l);
					
				}
	
						
				//printf("%d",res);
				/*//printf("%s",buf);*/
				for(i=0;i<strlen(buf);i++)
				{
					c=buf[i];
					if((int)c>=48 && (int)c<=57)
						res = res * 10+((int)c - 48) ;
					else
						break;
				}
				fin = res;
				if(res == 0 && i==0)
				{
					flag = 1;
					printf("%d",flag);
				}
				while(i<strlen(buf))
				{
					if(buf[i]=='+')
							op = 1;
					else if(buf[i] == '-')
						op = 2;
					else if(buf[i] == '*')
						op = 3;
					else if(buf[i] == '/')
						op = 4;				
					i++;
					res = 0;
					while(i<strlen(buf))
					{
						c=buf[i];
						if((int)c>=48 && (int)c<=57)
						{
							res = res *10 + ((int)c - 48);
							i++;
						}
						else
							break;
					}	
					if(op == 1)
						fin = fin + res;
					else if(op == 2)
						fin = fin - res;
					else if(op == 3)
						fin = fin * res;
					else if(op == 4)
						fin = fin / res;
				}

		//printf("%s\n", buf);
			//printf("%d",fin);
				for(i=0; i < 100; i++) 
					buf[i] = '\0';
				if(flag == 1)
				{
					strcpy(buf,"exit");
					p=send(newsockfd, buf, strlen(buf) + 1, 0);
					break;
				}
				sprintf(buf, "%d", fin);

				printf("Value computed at server:%d\n**********\n",fin);
				l=0;
				while(l<strlen(buf))
				{
					printf("Sending to client\n**********\n");
					p=send(newsockfd, buf, strlen(buf) + 1, 0);
					if(p<0)
					{
						printf("Error in sending to client\n");
						exit(0);
					}
					l = l + p;
					//printf("%d",l);
				
				}
			
			}	
			close(newsockfd);
			exit(0);
		}
		close(newsockfd);
		exit(0);	
	}
}

