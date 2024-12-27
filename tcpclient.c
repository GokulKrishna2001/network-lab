//server program(2/2)
//client side
/*
#include<sys/socket.h>
#include<netinet/in.h>
*/
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
    char buff[100];
    int k, sock_desc;
    struct sockaddr_in client;
    
    sock_desc=socket(AF_INET,SOCK_STREAM,0);

    if(sock_desc==-1)
        printf("Socket Creation Error\n");
    
    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3005;

    //to create a connection with the server
    k=connect(sock_desc,(struct sockaddr*)&client, sizeof(client));

    if(k==-1)
        printf("Server Connection Error\n");
    
    printf("Enter the data to be sent:");
    fgets(buff,100,stdin);//stdin acts as a pointer

    //to send the data to the server
    k=send(sock_desc,buff,100,0);//o is for flags
    
    close(sock_desc);
}