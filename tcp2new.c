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