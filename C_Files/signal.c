/* Roll No:  12/CS/39, 12/CS/40
 * Name:     Soumyadip Mitra, Saikat Kumar Dey
 * Group No: 19 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
//#include <sys/wait.h>
#include <signal.h>

int s=1;

void childAlarm(int x)
{
	if(s==1)
               {printf("One\n");
                  s++;
               }
               else if(s==2)
                {printf("Two\n");
                    s++;}
               else if(s==3)
               {
                   printf("Three\n");
                      s=1;
                 }
}



void main()
{
           signal(SIGINT,childAlarm);
            while(1)
{
      sleep(1000);
}	
}

