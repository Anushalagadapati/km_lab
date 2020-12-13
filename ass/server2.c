/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include<pthread.h>
char ch[20]="hi";
int client_sockfd;
int main()
{
    int server_sockfd,res;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    void *thread_function(void *arg);
/*  Create an unnamed socket for the server.  */

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket.  */

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = 9733;
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

/*  Create a connection queue and wait for clients.  */

    listen(server_sockfd, 5);
    while(1) {
        char ch;

        printf("server waiting\n");

/*  Accept a connection.  */

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_len);

pthread_t a_thread;
res=pthread_create(&a_thread,NULL,thread_function,(void*)ch);
if(res!=0)
{
printf("thread creation failed\n");
exit(EXIT_FAILURE);
}
}
}
void * thread_function(void *arg)
{
char ch1;
/*  We can now read/write to client on client_sockfd.  */
	while(1)
	{
	 read(client_sockfd, &ch, 10);
	sleep(5);
	printf("from client= %s\n",ch);
	printf("enter message\n");
	scanf("%s",ch);
        write(client_sockfd, &ch, 10);
	//printf("y or n\n");
	//scanf("%c",&ch1);
	}
	//while(ch1=='y');
        close(client_sockfd);
    }


