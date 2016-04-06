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

int semid,status,shmid,shmid_s,shmid_d,*shmptr,status,m,n,i;
char *shmptr_s,*shmptr_d;

union semun
{
	int val;
    	struct semid_ds *buf;
   	ushort *array;
} seminfo;

struct shmid_ds shminfo;

struct sembuf WaitC={S_C,-1,0};
struct sembuf StartC={S_C,1,0};
struct sembuf WaitD={S_D,-1,0};
struct sembuf StartD={S_D,1,0};

void refresh(int x)
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
	
	if(getpid() == sc)
	{
		printf("In SC...");
		int tcpS1,newtcpS1,clilen;
		char buf[100];
		struct sockaddr_in serv_addr,clientAddr;

		if ((tcpS1 = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
		{
			printf("Unable to create socket\n");
			exit(0);
		}
		
		refresh(9328);

		//Initializing the socket variables
		serv_addr.sin_family= AF_INET;
		serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
		serv_addr.sin_port=htons(9328);
	
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
			//printf("%s",buf);
			//fflush(stdout);
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
			//printf("%s....",a);
			if(strcmp(a,"port")==0)
			{
                   		k++;
                   		index=0;
                   		while(1)
				{  
					if(buf[k]=='\0' || buf[k]=='\n')
						break;
					else
					{
						b[index]=buf[k];
						index++;
					}
					k++;
				}
				b[index]='\0';
				//printf("%s\n",b);
				port=atoi(b);
				//printf("%d\n",port);
				int32_t conv;
				int code ;
				if(port>=1024 && port<=65535)
					code = RIGHT_COMMAND;
				else
					code = ERROR_START_COMMAND;
				conv = htonl(code);	
				write(newtcpS1,&conv,sizeof(conv));
				if(code == RIGHT_COMMAND)
				{
					while(1)
					{
						//further commands
						/*If any file transfer command occurs... thn do semop(semid,&StartD,1) to start SD*/  
						/*Also synchronise SC as possible*/
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
							if((strcmp(a,"quit")==0) || buf[k]=='\0')
								break;
							else
							{
								b[index]=buf[k];
								index++;
							}
							k++;
						}
						b[index-1]='\0';
						if(strcmp(a,"cd")==0)
						{
							//printf("cd command received");
							//printf("%s",b);
							//printf(".....");
							//fflush(stdout);
							int p = chdir(b);
							if (p == 0)
							{
        							code = RIGHT_COMMAND;
    							}
							else
							{
        							code = ERROR_DIRECTORY_COMMAND;
    							}
						
							conv = htonl(code);	
							write(newtcpS1,&conv,sizeof(conv));
							strcpy(shmptr_d,b);
							semop(semid,&StartC,1);
						}
						else if(strcmp(a,"get")==0)
						{
							//printf("get received");
							shmptr=(int *)shmat(shmid, 0, 0);
							*(shmptr) = port;
							*(shmptr + 1) = 0;

							FILE *f = fopen(b,"r");
							if(f == NULL)
								code = ERROR_BAD_FILE;
							else
								code = RIGHT_COMMAND;
							conv = htonl(code);	
							write(newtcpS1,&conv,sizeof(conv));
							shmptr_s=(char *)shmat(shmid_s, 0, 0);
							strcpy(shmptr_s,b);
							semop(semid,&StartD,1);
							continue;
						}
						else if(strcmp(a,"put")==0)
						{
							//printf("put received");
							shmptr=(int *)shmat(shmid, 0, 0);
							*(shmptr) = port;
							*(shmptr + 1) = 1;
							FILE *f = fopen(b,"r");
							if(f == NULL)
								code = ERROR_BAD_FILE;
							else
								code = RIGHT_COMMAND;
							conv = htonl(code);	
							write(newtcpS1,&conv,sizeof(conv));

							shmptr_s=(char *)shmat(shmid_s, 0, 0);
							strcpy(shmptr_s,b);
							semop(semid,&StartD,1);
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
			//printf("In SC...");
			//fflush(stdout);
			//sleep(2);
			//semop(semid,&StartC,1);//to ensure running of while loop of SC
		}
	}
	else
	{
		
		while(1)
		{
			semop(semid,&WaitD,1);
			//printf("In SD...");
			//fflush(stdout);
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
			//printf("%d Port  %d command %s file",port,command,buf);
			//fflush(stdout);
			if ((tcpS2 = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
			{
				printf("Unable to create socket\n");
				exit(0);
			}

			//printf("In S2...");
			//fflush(stdout);
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
			//printf("In SD...");
			//fflush(stdout);
			char buffer[100];
			char last[2],c;
			int len;
			int32_t num;
			chdir(shmptr_d);
			if(command == 0)
			{
				FILE *f;
				f=fopen(buf,"r");
				while(1)
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
						last[0]='L';
					else
						last[0]='A';
					last[1]='\0';
					write(tcpS2,last,2);
					num = htonl(len);
					write(tcpS2,&num,sizeof(num));
					write(tcpS2,buffer,strlen(buffer)+1);
					//printf("%s  ",last);
					//printf("%s ",buffer);
					//printf("%d\n",len);
					if(len<99)
					{
						
						break;					
					}
				}
				//fflush(stdout);
				fclose(f);
			}
			else if(command == 1)
			{
				FILE *f;
				f=fopen(buf,"w");
				while(1)
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
					//printf("%s..",last);
					if(last[0]=='L')
						break;
					
				}
				fclose(f);
			}
			//printf("Going to SC");
			//fflush(stdout);
			close(tcpS2);
			semop(semid,&StartC,1);
		}		
	}
}
