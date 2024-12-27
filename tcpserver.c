//server program(1/2)
//server side

#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
    int sock_desc,tempsockd;//for storing the socket description
    struct sockaddr_in server, client;
    char buff[100];//to store the characters to send or receive
    int k,len;

    sock_desc=socket(AF_INET,SOCK_STREAM,0);//default format

    if(sock_desc==-1)
        printf("Socket Creation Error\n");
    
    //to assign addresses to server and client
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=3005;

    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3005;

    //used to associate the socket with the address
    //binding the socket description,address and size
    k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));

    if(k==-1)
        printf("Binding Error\n");

    k=listen(sock_desc,1);//to wait for the connection

    if(k==-1)
        printf("Listening Error\n");

    len=sizeof(client);

    //to accept the connection
    tempsockd=accept(sock_desc,(struct sockaddr*)&client,&len);

    if(tempsockd==-1)
        printf("Temporary Socket Creation Error\n");

    //to receive the message
    k=recv(tempsockd,buff,100,0);

    if(k==-1)
        printf("Receiving Error\n");

    printf("Message received from the client: %s",buff);

    close(tempsockd);   
}