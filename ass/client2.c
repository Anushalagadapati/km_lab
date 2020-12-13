/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch[10],ch1;

/*  Create a socket for the client.  */
while(1)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9733;
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client2");
        exit(1);
    }

/*  We can now read/write via sockfd.  */

	printf("enter message to server\n");
	scanf("%s",ch);
    write(sockfd, &ch, 10);
    read(sockfd, &ch, 10);
    printf("message from server = %s\n", ch);
//	printf("y or n\n");
//	scanf("%c",&ch1);

//while(ch1=='y');
    close(sockfd);
}
    //exit(0);
}
