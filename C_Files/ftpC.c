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
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdint.h>

#define BUFSIZE 20
#define LIMIT 50
#define C_C 1
#define C_D 0

#define WRONG_START_COMMAND 503
#define RIGHT_COMMAND 200
#define ERROR_START_COMMAND 550
#define ERROR_DIRECTORY_COMMAND 501
#define ERROR_BAD_FILE 550
#define RIGHT_FILE_TRANSFER 250
#define EXIT_COMMAND 421
#define ERROR_BAD_COMMAND 502
#define ERROR_EXTRA_ARGUMENTS 501

int semid,status,shmid,shmid_s,*shmptr,status,m,n,i;
char *shmptr_s;

union semun
{
	int val;
    	struct semid_ds *buf;
   	ushort *array;
} seminfo;

struct shmid_ds shminfo;


struct sembuf WaitC={C_C,-1,0};//for stopping process CC
struct sembuf StartC={C_C,1,0};//for starting process CC
struct sembuf WaitD={C_D,-1,0};//for stopping process CD
struct sembuf StartD={C_D,1,0};//for starting process CD

//refreshing port x
void refresh(int x)
{
	int tcp ;
	struct sockaddr_in serv_addr;
	if ((tcp = socket(AF_INET, SOCK_STREAM, 0)) < 0) ;
	serv_addr.sin_family= AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(x);
	close(tcp);
	shutdown(tcp,SHUT_WR);
}
	

main()
{
	semid=semget(IPC_PRIVATE, 3, 0666);
	
	seminfo.val=1;
	semctl(semid,C_C, SETVAL,seminfo);
	
	seminfo.val=0;
	semctl(semid,C_D, SETVAL,seminfo);

	shmid=shmget(IPC_PRIVATE, 2, 0666);//for storing command and port
	shmid_s =shmget(IPC_PRIVATE, 100, 0666);//for storing file name
	
	shmptr=(int *)shmat(shmid, 0, 0);
	shmptr_s=(char *)shmat(shmid_s, 0, 0);

	*(shmptr)=0;
	*(shmptr+1)=0;

	
	int cc = getpid();
	int cd = fork();
	int d= 4;
	int32_t conv;
	int code;
	
	//Control Process of Client
	if(getpid() == cc)
	{
		
		//printf("In CC...");
		int tcpC1 ;
		struct sockaddr_in serv_addr;
		int i;
		char buf[100];
		
		
		//Socket Creation
		if ((tcpC1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		{
			printf("Unable to create socket\n");
			exit(0);
		}

		//Initialing the socket variables
		serv_addr.sin_family= AF_INET;
		serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
		serv_addr.sin_port=htons(50000);

		//Connecting to server
		if ((connect(tcpC1, (struct sockaddr *) &serv_addr,sizeof(serv_addr))) < 0) 
		{
			printf("Unable to connect to server\n");
			exit(0);
		}	
		
		for(i=0;i<100;i++)
			buf[i]='\0';
		
		while(1)
		{
			semop(semid,&WaitC,1);
			printf(">");
			fgets(buf,100,stdin);
			write(tcpC1, buf, strlen(buf) + 1);//sending command to server
			
			int k =0,index =0;
			char a[100],b[100];

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
			a[index]='\0';//command saved
			
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
			b[index]='\0';//argument saved

			int flag = 0;
			
			//port command received and port number stored
			if(strcmp(a,"port")==0)
			{
				*(shmptr)=atoi(b);
				semop(semid,&StartC,1);
				flag = 1;
			}
			//cd command received
			else if(strcmp(a,"cd")==0)
			{
				semop(semid,&StartC,1);
				flag=2;
			}
			//get command received and file name stored		
			else if(strcmp(a,"get")==0)
			{
				shmptr=(int *)shmat(shmid, 0, 0);
				*(shmptr + 1) = 0;

				shmptr_s=(char *)shmat(shmid_s, 0, 0);
				int len = strlen(b);
				char filename[100];
				index = 0;
				for(i=0;i<len;i++)
				{
					if(b[i]=='/')
						index=0;
					else
					{
						filename[index]=b[i];
						index++;
					}		
				}
				filename[index]='\0';
				strcpy(shmptr_s,filename);

				read(tcpC1,&conv,sizeof(conv));
				code = ntohl(conv);
				if(code == ERROR_BAD_FILE)
				{	
					printf("%d Bad file error!\n",code);
					semop(semid,&StartC,1);
					continue;
				}
				else if(code == ERROR_EXTRA_ARGUMENTS)
				{	
					printf("%d Extra arguments!\n",code);
					semop(semid,&StartC,1);
					continue;
				}
				semop(semid,&StartD,1);
				continue;
			}
			//put command received and file name stored
			else if(strcmp(a,"put")==0)
			{
				//printf("put received");
				shmptr=(int *)shmat(shmid, 0, 0);
				*(shmptr + 1) = 1;

				shmptr_s=(char *)shmat(shmid_s, 0, 0);
				strcpy(shmptr_s,b);
				read(tcpC1,&conv,sizeof(conv));
				code = ntohl(conv);
				if(code == RIGHT_COMMAND)
				{
					
					int len = strlen(b);
					b[len-1]='\0';
					FILE *f = fopen(b,"r");
					if(f == NULL)
						code = ERROR_BAD_FILE;
					conv = htonl(code);	
					write(tcpC1,&conv,sizeof(conv));
	
				}
				if(code == ERROR_BAD_FILE)
				{	
					printf("%d Bad file error!\n",code);
					fflush(stdout);
					semop(semid,&StartC,1);
					continue;
				}
				else if(code == ERROR_EXTRA_ARGUMENTS)
				{	
					printf("%d Extra arguments!\n",code);
					semop(semid,&StartC,1);
					continue;
				}
				semop(semid,&StartD,1);
				continue;
			}
				
			read(tcpC1,&conv,sizeof(conv));
			code = ntohl(conv);
			//codes checking

			if(code == WRONG_START_COMMAND)
			{	
				printf("%d Wrong Start command!\n",code);
				exit(0);
			}
			else if(code == RIGHT_COMMAND)
			{
				printf("%d Command executed successfully!\n",code);
			}
			else if(code == ERROR_START_COMMAND)
			{
				printf("%d Error in Start command!\n",code);
				exit(0);
			}
			else if(code == ERROR_DIRECTORY_COMMAND && flag==2)
			{
				printf("%d Wrong Directory change command!\n",code);
			}
			else if(code == EXIT_COMMAND)
			{
				printf("%d Client exiting!\n",code);
				close(tcpC1);
				shutdown(tcpC1,SHUT_WR);
				exit(0);
			}
			else if(code == ERROR_BAD_COMMAND)
			{
				printf("%d Command does not exist!\n",code);
				fflush(stdout);
				semop(semid,&StartC,1);
			}
			else if(code == ERROR_EXTRA_ARGUMENTS)
			{
				printf("%d Extra arguments!\n",code);
				fflush(stdout);
				semop(semid,&StartC,1);
				if(flag == 1)
					exit(0);
			}
							
		}	
	}
	//Data process of client
	else
	{
		cd = getpid();
		while(1)
		{
			semop(semid,&WaitD,1);

			int tcpC2,newtcpC2,clilen;
			char buf[100];
			char buffer[100],last[2],c;
			int num, len;
			struct sockaddr_in serv_addr,clientAddr;

			shmptr=(int *)shmat(shmid, 0, 0);
			int port = *(shmptr);
			int command = *(shmptr + 1);

			shmptr_s=(char *)shmat(shmid_s, 0, 0);
			strcpy(buf,shmptr_s);
			len = strlen(buf);
			buf[len-1]='\0';
			//printf("%s....file",buf);
			
			refresh(port);

			if ((tcpC2 = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
			{
				printf("Unable to create socket\n");
				exit(0);
			}
			
			//Initializing the socket variables
			serv_addr.sin_family= AF_INET;
			serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
			serv_addr.sin_port=htons(port);
		
			//Binding the TCP socket
			if (bind(tcpC2, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
			{
				printf("Unable to bind local address\n");
				exit(0);
			}
		
			//Listening to 5 calls
			listen(tcpC2, 5);

			newtcpC2 = accept(tcpC2, (struct sockaddr *) &clientAddr,&clilen) ;
			if (newtcpC2 < 0)
			{
				printf("Accept error C2\n");
				exit(0);
			}
			//if get received
			if(command == 0)
			{
				FILE *f;
				f=fopen(buf,"w");
				while(1)
				{
					for(i=0;i<100;i++)
						buffer[i]='\0';
					for(i=0;i<2;i++)
						last[i]='\0';
					read(newtcpC2,last,2);
					read(newtcpC2,&num,sizeof(num));
					len = ntohl(num);
					read(newtcpC2,buffer,100);
					fprintf(f,"%s",buffer);
					//printf("%s..",last);
					if(last[0]=='L')
						break;
					
				}
				code = RIGHT_FILE_TRANSFER;
				if(code == RIGHT_FILE_TRANSFER)
				{	
					printf("%d File transfered successfully!\n",code);
					fflush(stdout);
				}
				fclose(f);
			}
			//if put received
			else if(command ==1)
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
					write(newtcpC2,last,2);
					int32_t num = htonl(len);
					write(newtcpC2,&num,sizeof(num));
					write(newtcpC2,buffer,strlen(buffer)+1);
					//printf("%s  ",last);
					//printf("%s ",buffer);
					//printf("%d\n",len);
					if(len<99)
					{
						
						break;					
					}
				}
				int code = RIGHT_FILE_TRANSFER;
				if(code == RIGHT_FILE_TRANSFER)
				{	
					printf("%d File transfered successfully!\n",code);
					fflush(stdout);
				}
				fclose(f);
                	      
			}	
			sleep(1);
			close(newtcpC2);
			shutdown(newtcpC2, SHUT_WR); 
			close(tcpC2);
			shutdown(tcpC2, SHUT_WR); 
			//printf("Closing...");
			//fflush(stdout);
			semop(semid,&StartC,1);
		}
	}	

}
