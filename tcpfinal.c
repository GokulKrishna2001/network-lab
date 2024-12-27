//tcp server
//use #include<arpa/inet.h> for all socket programs

#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>

void main()
{
    //socket creation, socket(domain,type(2 way connection, for tcp),unspecified protocol)
    int sock_desc=socket(AF_INET,SOCK_STREAM,0);
    if(sock_desc==-1)
        printf("Socket Creation Error\n");
    else
        printf("Socket Creation Successful\n");
    
    //initializing the server and client
    struct sockaddr_in server,client;

    server.sin_family=AF_INET;
    server.sin_port=3003;
    server.sin_addr.s_addr=INADDR_ANY;

    client.sin_family=AF_INET;
    client.sin_port=3003;
    client.sin_addr.s_addr=INADDR_ANY;

    //binding
    //bind(socket desc,(struct sockaddr*)&server,sizeof(server))
    int k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
    if(k==-1)
        printf("Binding Error\n");
    else
        printf("No Binding Error\n");
    
    //listening
    if(listen(sock_desc,1)==-1)
        printf("Listening Error\n");
    else
        printf("Listening...\n");
    
    int len=sizeof(client);
    //accept(sockdesc,(struct sockaddr*)&client,&len)
    int tempsock=accept(sock_desc,(struct sockaddr*)&client,&len);
    if(tempsock==-1)
        printf("Temporary Socket Creation Error\n");
    else
        printf("Temporary Socket Creation Successful\n");

    //receiving
    //recv(temp sock desc, buff, size of buff, 0 flag)
    char buff[100];//to store the incoming message
    k=recv(tempsock,buff,100,0);

    if(k==-1)
        printf("Error in receiving the message from the client\n");
    else
        printf("The Message Received:%s\n",buff);
    
    //closing the connection
    close(tempsock);
}

//tcp client

#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>

void main()
{
    //socket creation
    int sock_desc=socket(AF_INET, SOCK_STREAM,0);
    if(sock_desc==-1)
        printf("Socket Creation Error\n");
    else
        printf("Socket Creation Successful\n");
    
    //initializing the client
    struct sockaddr_in client;
    client.sin_family=AF_INET;
    client.sin_port=3003;
    client.sin_addr.s_addr=INADDR_ANY;

    //connecting
    int k=connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
    if(k==-1)
        printf("Connection Error\n");
    else
        printf("Connection Established\n");
    
    char buff[100];//to input the string
    printf("Enter the string to be sent:");
    fgets(buff,100,stdin);//stdin-pointer variable

    //sending the string to the server
    k=send(sock_desc,buff,100,0);
    if(k==-1)
        printf("Sending Error\n");
    else
        printf("Sent Successfully\n");
    close(sock_desc);
}

/*
Output

Server
Socket Creation Successful
No Binding Error
Listening...
Temporary Socket Creation Successful
The Message Received:Hello There

Client
Socket Creation Successful
Connection Established
Enter the string to be sent:Hello There
Sent Successfully
*/