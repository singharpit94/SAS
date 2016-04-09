#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 

#include <netdb.h>
void *get_in_addr(struct sockaddr *sa)
{
if (sa->sa_family == AF_INET) {
return &(((struct sockaddr_in*)sa)->sin_addr);
}
return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void main()
{
	fd_set master;
	fd_set read_fds;
	int fdmax;
	int clilen;
	int listener;
	struct sockaddr_in serv_addr,clientAddr;
	socklen_t addr_size;
      // listening socket descriptor
    int newfd;
    // newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;
    char buf[256];
    int nbytes;
    char remoteIP[INET6_ADDRSTRLEN];
    int yes=1;
    int i, j, rv;
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		printf("Unable to create socket\n");
		exit(0);
	}
	//socket variables gets initialized
	serv_addr.sin_family= AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(50031);

	//Binding TCP socket
	if (bind(listener, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	{
		printf("Unable to bind local address\n");
		exit(0);
	}
	
	listen(listener, 5);

	// add the listener to the master set
FD_SET(listener, &master);
FD_SET(listener, &read_fds);
// keep track of the biggest file descriptor
fdmax = listener; // so far, it's this one
while(1)
{
	read_fds = master; // copy it
    if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
    perror("select");
    exit(0);
                    }

      for(i = 0; i <= fdmax; i++) {
                if (FD_ISSET(i, &read_fds)) { // we got one!!
                                    if (i == listener) {
// handle new connections
                                        addrlen = sizeof remoteaddr;
                                        newfd = accept(listener,(struct sockaddr *)&remoteaddr,&addrlen);
                                        if(newfd==-1)
                                        {
                                        	perror("eccept	");
                                        }
                                        else
                                        {
                                        	     FD_SET(newfd, &master); // add to master set
                                        	     FD_SET(newfd, &read_fds); 
                                                  if (newfd > fdmax) {
// keep track of the max
                                                                     fdmax = newfd;
                                                                     }
                                                  printf("selectserver: new connection from %s on socket %d\n",inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr*)&remoteaddr),remoteIP, INET6_ADDRSTRLEN),newfd);
                                        }

                                    }
                                    else
                                    {
                                    	if ((nbytes = read(i, buf, sizeof buf)) <= 0) {
// got error or connection closed by client
                                            if (nbytes == 0) {
                                                  printf("selectserver: socket %d hung up\n", i);

                                            }
                                            else
                                            	perror("recv");

                                             close(i); // bye!
                                             FD_CLR(i, &master);

                                                                                            } 

                                        else
                                        {
                                                      for(j=0;j<=fdmax;j++)
                                                      {
                                                      	if (FD_ISSET(j, &master))
                                                      	{
                                                      		if (j != listener && j != i)
                                                      		{
                                                      			write(j, buf, nbytes) ;
                                                      			
                                                      		}
                                                      	}
                                                      }
                                        }                                                                                     

// connection closed
                                    }




















       }

          }
                }

}


