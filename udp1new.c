//udp server

#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>

void main()
{
    //socket creation
    int sock_desc=socket(AF_INET,SOCK_DGRAM,0);
    //SOCK_DGRAM used to send one datagram and close the connection
    if(sock_desc==-1)
        printf("Socket Creation Error\n");
    else
        printf("Socket Creation Successful\n");
    
    //initializing server and client
    struct sockaddr_in server,client;

    server.sin_family=AF_INET;
    server.sin_port=3003;
    server.sin_addr.s_addr=INADDR_ANY;

    client.sin_family=AF_INET;
    client.sin_port=3003;
    client.sin_addr.s_addr=INADDR_ANY;

    //binding
    int k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
    if(k==-1)
        printf("Binding Error\n");
    else
        printf("No Binding Error\n");
    
    //receiving the message
    char buff[100];//to receive the string
    k=recvfrom(sock_desc,buff,100,0,(struct sockaddr*)&client,sizeof(client));
    
    printf("The Message Received:%s\n",buff);
    
    close(sock_desc);
}