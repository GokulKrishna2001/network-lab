//UDP program(1/2)
//Server Side
//Gokul Krishna S, S6R2, 25

#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
    int sock_desc;//for storing the socket description
    struct sockaddr_in server, client;
    char buff[100];//to store the characters to send or receive
    int k,len;

    sock_desc=socket(AF_INET,SOCK_DGRAM,0);//default format
    //AF_INET for interprocess communication
    //SOCK_DGRAM is to send one datagram, get the reply and then terminate.

    if(sock_desc==-1)
        printf("Socket Creation Error\n");
    
    //to assign addresses to server and client
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=3010;

    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3010;

    //binding the socket description,address and size
    k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));

    if(k==-1)
        printf("Binding Error\n");

    k=recvfrom(sock_desc,buff,100,0,(struct sockaddr*)&client,sizeof(client));

    printf("The message received from the client is: %s\n",buff);
    close(sock_desc);
}




//UDP program(2/2)
//Client Side

#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
    char buff[100];
    int k, sock_desc;
    struct sockaddr_in client,server;

    sock_desc=socket(AF_INET,SOCK_DGRAM,0);//default format

    if(sock_desc==-1)
        printf("Socket Creation Error\n");
    
    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3010;

    printf("Enter the data to be sent:");
    fgets(buff,100,stdin);//stdin acts as a pointer

    k=sendto(sock_desc,buff,100,0,(struct sockaddr*)&client,sizeof(client));

    close(sock_desc);

}