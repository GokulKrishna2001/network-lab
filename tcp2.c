//tcp client

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

void main()
{
    int sockdesc;//socket description variables
    struct sockaddr_in client;
    char buff[100]; //to store the incomming character array

    //socket function
    sockdesc=socket(AF_INET, SOCK_STREAM, 0);
    if(sockdesc==-1)
        printf("Error in socket creation\n");
    
    //setting up the address profile for server and client

    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3005;

    //connect(server descriptor,(struct sockaddr_in*)&server/client,size in bytes)
    int k=connect(sockdesc,(struct sockaddr*)&client,sizeof(client));
    if(k==-1)
        printf("Connection error\n");
    
    printf("Enter the string to be sent:");
    fgets(buff,100,stdin);

    k=send(sockdesc,buff,100,0);
    if(k==-1)
        printf("Sending error\n");
    close(sockdesc);

}