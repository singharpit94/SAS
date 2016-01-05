#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define S_MUTEX 0
#define S_Barber 1
#define S_Customer 2

union semun
{
	int val;
    	struct semid_ds *buf;
   	 ushort *array;
} seminfo;

struct shmid_ds shminfo; 
struct sembuf Waitmutex={S_MUTEX,-1,0}; 
struct sembuf Startmutex={S_MUTEX,1,0}; 
struct sembuf Waitb={S_Barber,-1,0};
struct sembuf Startb={S_Barber,1,0};
struct sembuf Waitc={S_Customer,-1,0};
struct sembuf Startc={S_Customer,1,0};

void barber(int);
void customer(int);

int semid,shmid,*shmptr,waiting=0,status,cust,chair=2;

void main()
{
	int i;
	printf("Enter the no. of customers:");
	scanf("%d",&cust);
	semid=semget(IPC_PRIVATE, 3, 0666 | IPC_CREAT);//id of semaphore with 3 variables
	
	seminfo.val=1;
	semctl(semid,S_MUTEX, SETVAL,seminfo);
	
	
	seminfo.val=0;
	semctl(semid,S_Barber,SETVAL,seminfo);

	seminfo.val=0;
	semctl(semid,S_Customer,SETVAL,seminfo);

	shmid=shmget(IPC_PRIVATE,2,0666);

	shmptr=(int *)shmat(shmid,0,0);
	shmptr[0]=shmptr[1]=0;

	for(i=0;i<cust;i++)
  	{
        	if(fork()==0)
        	{
			//printf("ggvg");	
               		customer(i);
               		exit(0);
        	}
  	}
	if(fork()==0)
		barber(cust);	
	while(wait(&status)>0);

	
}

void barber(int cust)
{
	int i=0;
	shmptr=(int *)shmat(shmid,0,0);
	while(shmptr[1]<cust)
	{
		semop(semid,&Waitc,1);
		//printf("Customer %d gets haircut done...\n",i);
		i++;
		printf("Barber cutting...\n");	
		semop(semid,&Waitmutex,1);
		shmptr[0]--;
		//printf("In barber %d",shmptr[0]);
		semop(semid,&Startb,1);
		if(shmptr[1]<cust)
			break;
		semop(semid,&Startmutex,1);
		if(shmptr[1]<cust)
			break;
		
	}
}

void customer(int i)
{
	//printf("%d",chair);
	shmptr=(int *)shmat(shmid,0,0);
	semop(semid,&Waitmutex,1);
	printf("Customer %d entering ...\n",i);
	shmptr[1]++;
	printf("%d\n",shmptr[1]);
	if(shmptr[0]<chair)
	{
		printf("Barber finished...%d\n",shmptr[1]);
		printf("Customer %d got a seat\n",i); 
		shmptr[0]++;
		semop(semid,&Startc,1);
		semop(semid,&Startmutex,1);
		semop(semid,&Waitb,1);
		
	}
	else 
	{
		printf("Customer %d leaving as no chair empty....\n",i);		
		semop(semid,&Startmutex,1);
	}
}	

