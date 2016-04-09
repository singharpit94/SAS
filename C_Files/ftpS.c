/*FTP client File 
  Written by
  Arpit Kumar Singh(13/CS/31)
  Neetesh Kumar (13/CS/28)
  Group No 19
  Batch no 1
  */






#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <stdint.h>

#define BUFSIZE 20
#define LIMIT 50
#define S_C 1
#define S_D 0

#define WRONG_START_COMMAND 503
#define RIGHT_COMMAND 200
#define ERROR_START_COMMAND 550
#define ERROR_DIRECTORY_COMMAND 501
#define ERROR_BAD_FILE 550
#define EXIT_COMMAND 421
#define ERROR_BAD_COMMAND 502
#define ERROR_EXTRA_ARGUMENTS 501

int semid,status,shmid,shmid_s,shmid_d,*shmptr,status,m,n,i;
char *shmptr_s,*shmptr_d;

union semun
{
	int val;
    	struct semid_ds *buf;
   	ushort *array;
} seminfo;

struct shmid_ds shminfo;

struct sembuf WaitC={S_C,-1,0};//for stopping SC
struct sembuf StartC={S_C,1,0};//for starting SC
struct sembuf WaitD={S_D,-1,0};//for stopping SD 
struct sembuf StartD={S_D,1,0};//for starting SD

void refresh(uint16_t x)
{
	int tcp ;
	struct sockaddr_in serv_addr;
	if ((tcp = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		printf("Refreshing not possible");
	serv_addr.sin_family= AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(x);
	close(tcp);
	shutdown(tcp,SHUT_WR);
	
}
main()
{
	semid=semget(IPC_PRIVATE, 3, 0666);
	char a[80];
	char b[80];
	int index=0;
	int k=0;
	int port;
	
	seminfo.val=1;
	semctl(semid,S_C, SETVAL,seminfo);
	
	seminfo.val=0;
	semctl(semid,S_D, SETVAL,seminfo);

	shmid=shmget(IPC_PRIVATE, 2, 0666);
	shmid_s =shmget(IPC_PRIVATE, 100, 0666);
	shmid_d =shmget(IPC_PRIVATE, 100, 0666);
	
	shmptr=(int *)shmat(shmid, 0, 0);
	shmptr_s=(char *)shmat(shmid_s, 0, 0);
	shmptr_d=(char *)shmat(shmid_d, 0, 0);

	*(shmptr)=0;
	*(shmptr+1)=0;

	for(i=0;i<100;i++)
	{	
		*(shmptr_s + i)='\0';
		*(shmptr_d + i)='\0';
	}

	int sc = getpid();
	int sd = fork();
	
	//Server Control Process
	if(getpid() == sc)
	{
		//printf("In SC...");
		
		int tcpS1,newtcpS1,clilen;
		char buf[100];
		struct sockaddr_in serv_addr,clientAddr;
	
		

		refresh(15070);
		//Socket Creation
		if ((tcpS1 = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
		{
			printf("Unable to create socket\n");
			exit(0);
		}
		
		//Initializing the socket variables
		serv_addr.sin_family= AF_INET;
		serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
		serv_addr.sin_port=htons(50000);
	
		//Binding the TCP socket
		if (bind(tcpS1, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		{
			printf("Unable to bind local address\n");
			exit(0);
		}
		
		//Listening to 5 calls
		listen(tcpS1, 5);
		while(1)
		{
			//printf("In SC.. waiting for client..\n");
			newtcpS1 = accept(tcpS1, (struct sockaddr *) &clientAddr,&clilen) ;
			if (newtcpS1 < 0)
			{
				printf("Accept error S1\n");
				exit(0);
			}
			for(i=0;i<100;i++)
				buf[i]='\0';
			read(newtcpS1,buf,100);
			k=0;index=0;
			
			while(1)
			{
				if(buf[k]==' ' || buf[k]=='\0')
					break;
				else
				{
					a[index]=buf[k];
					index++;
				}
				k++;
			}
			a[index]='\0';
				
			if(strcmp(a,"port")==0)//first command is port
			{
                   		k++;
                   		index=0;
                   		while(1)
				{  
					if(buf[k]=='\0' || buf[k]=='\n' || buf[k]==' ')
						break;
					else
					{
						b[index]=buf[k];
						index++;
					}
					k++;
				}
				b[index]='\0';
				port=atoi(b);
				int32_t conv;
				int code,flag=0;

				if(port>=1024 && port<=65535)
					code = RIGHT_COMMAND;
				else
					code = ERROR_START_COMMAND;
				if(buf[k]==' ')
					code = ERROR_EXTRA_ARGUMENTS;
				
				conv = htonl(code);	
				write(newtcpS1,&conv,sizeof(conv));//code sent to client
				if(code == RIGHT_COMMAND)
				{
					while(1)
					{
						//further commands
						semop(semid,&WaitC,1);
						//printf("\nIn SC starting...");
						for(i=0;i<100;i++)
							buf[i]='\0';
						read(newtcpS1,buf,100);
						index = 0;
						k=0;
						while(1)
						{
							if(buf[k]==' ' || buf[k]=='\0')
								break;
							else
							{
								a[index]=buf[k];
								if(strcmp(a,"quit")==0)
								{
									//printf("In quit block...");
									code = EXIT_COMMAND;
									conv = htonl(code);	
									write(newtcpS1,&conv,sizeof(conv));
									semop(semid,&StartC,1);
									break;
								}	
								index++;
							}
							k++;
						}
						if(strcmp(a,"quit")==0)
							break;
						a[index]='\0';	
						k++;
		                   		index=0;
		                   		while(1)
						{  
							if((strcmp(a,"quit")==0) || buf[k]=='\0' || buf[k]==' ')
								break;
							else
							{
								b[index]=buf[k];
								index++;
							}
							k++;
						}
						b[index-1]='\0';
						flag = 0;
						if(buf[k]==' ')
							flag = 1;
						if(strcmp(a,"cd")==0)
						{
							
							int p = chdir(b);
							if (p == 0)//directory changed successfully
							{
        							code = RIGHT_COMMAND;
    							}
							else//some error occurred
							{
        							code = ERROR_DIRECTORY_COMMAND;
    							}
							if(flag == 1)
								code = ERROR_EXTRA_ARGUMENTS;//extra arguments passed	
							
							conv = htonl(code);	
							write(newtcpS1,&conv,sizeof(conv));//code sent to client
							strcpy(shmptr_d,b);
							semop(semid,&StartC,1);//control process resumed
						}
						else if(strcmp(a,"get")==0)
						{
							shmptr=(int *)shmat(shmid, 0, 0);
							*(shmptr) = port;
							*(shmptr + 1) = 0;

							FILE *f = fopen(b,"r");//file checked
							if(f == NULL)
								code = ERROR_BAD_FILE;//error in file opening
							else
								code = RIGHT_COMMAND;//no errors
							if(flag == 1)
								code = ERROR_EXTRA_ARGUMENTS;//extra arguments
							
							conv = htonl(code);	
							write(newtcpS1,&conv,sizeof(conv));//code passed to client
							shmptr_s=(char *)shmat(shmid_s, 0, 0);
							strcpy(shmptr_s,b);
							if(code == ERROR_BAD_FILE || code == ERROR_EXTRA_ARGUMENTS)
							{
								semop(semid,&StartC,1);//control process resumed
								continue;
							}
							else
							{
								semop(semid,&StartD,1);//data process started
								continue;
							}
						}
						else if(strcmp(a,"put")==0)
						{
							//printf("put received");
							shmptr=(int *)shmat(shmid, 0, 0);
							*(shmptr) = port;
							*(shmptr + 1) = 1;
							FILE *f = fopen(b,"w");//file checked
							if(f == NULL)
								code = ERROR_BAD_FILE;//error in file opening
							else
								code = RIGHT_COMMAND;//no errors
							if(flag == 1)
								code = ERROR_EXTRA_ARGUMENTS;//extra arguments
							conv = htonl(code);	
							write(newtcpS1,&conv,sizeof(conv));

							shmptr_s=(char *)shmat(shmid_s, 0, 0);
							strcpy(shmptr_s,b);
							if(code == ERROR_BAD_FILE || code == ERROR_EXTRA_ARGUMENTS)
							{
								semop(semid,&StartC,1);//control process resumed
								continue;
							}
							else
							{
								read(newtcpS1,&conv,sizeof(conv));
								code = ntohl(conv);
								if(code == RIGHT_COMMAND)
								{
									semop(semid,&StartD,1);//data process resumed
									continue;
								}
								else
								{
									semop(semid,&StartC,1);//control process resumed
									continue;
								}
							}
						}
						else
						{
							//some other command has been given
							semop(semid,&StartC,1);
							code = 	ERROR_BAD_COMMAND;
							conv = htonl(code);	
							write(newtcpS1,&conv,sizeof(conv));
							continue;	
						}
						
					}
				}

			}
			else
			{
				int code = WRONG_START_COMMAND;
				int32_t conv = htonl(code);
				write(newtcpS1,&conv,sizeof(conv));
			}	
			
		}
	}
	//Server Data Process
	else
	{
		
		while(1)
		{
			semop(semid,&WaitD,1);
			int sd = getpid();

			shmptr=(int *)shmat(shmid, 0, 0);
			int port = *(shmptr);
			int command = *(shmptr + 1);

			shmptr_s=(char *)shmat(shmid_s, 0, 0);
			shmptr_d=(char *)shmat(shmid_d, 0, 0);			
			int tcpS2 ;
			struct sockaddr_in serv_addr;
			int i;
			char buf[100];
			strcpy(buf,shmptr_s);
			
			//Creation of S2 
			if ((tcpS2 = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
			{
				printf("Unable to create socket\n");
				exit(0);
			}

			sleep(3);
			
			//Initialing the socket variables
			serv_addr.sin_family= AF_INET;
			serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
			serv_addr.sin_port=htons(port);

			
			//Connecting to client
			if ((connect(tcpS2, (struct sockaddr *) &serv_addr,sizeof(serv_addr))) < 0) 
			{
				printf("Unable to connect to client\n");
				exit(0);
			}	
			
			char buffer[100];
			char last[2],c;
			int len;
			int32_t num;
			chdir(shmptr_d);
			//get command
			if(command == 0)
			{
				FILE *f;
				f=fopen(buf,"r");
				while(1)//transfer block by block
				{
					len = 0;
					for(i=0;i<100;i++)
						buffer[i]='\0';
					for(i=0;i<2;i++)
						last[i]='\0';
					while(len<99 && (c = fgetc(f))!= EOF)
					{
					
						buffer[len]=c;
						len++;
						
					}
					buffer[len]='\0';
					if(len<99)
						last[0]='L';//if last block
					else
						last[0]='A';//if not the last block
					last[1]='\0';
					write(tcpS2,last,2);
					num = htonl(len);
					write(tcpS2,&num,sizeof(num));
					write(tcpS2,buffer,strlen(buffer)+1);
					if(len<99)
					{
						
						break;					
					}
				}
				fclose(f);
			}
			//put command
			else if(command == 1)
			{
				FILE *f;
				f=fopen(buf,"w");
				while(1)//received block by block
				{
					for(i=0;i<100;i++)
						buffer[i]='\0';
					for(i=0;i<2;i++)
						last[i]='\0';
					read(tcpS2,last,2);
					read(tcpS2,&num,sizeof(num));
					len = ntohl(num);
					read(tcpS2,buffer,100);
					fprintf(f,"%s",buffer);
					if(last[0]=='L')
						break;
					
				}
				fclose(f);
			}
			close(tcpS2);
			semop(semid,&StartC,1);
		}		
	}
}
