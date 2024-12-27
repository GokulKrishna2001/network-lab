//udp client
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

    //initializing client
    struct sockaddr_in client;

    client.sin_family=AF_INET;
    client.sin_port=3003;
    client.sin_addr.s_addr=INADDR_ANY;

    //taking the string as the input
    char buff[100];
    printf("Enter the string to be sent:");
    fgets(buff,100,stdin);

    int k=sendto(sock_desc,buff,100,0,(struct sockaddr*)&client,sizeof(client));
    if(k==-1)
        printf("Failed to send\n");
    else
        printf("Successfully Sent\n");
    
    close(sock_desc);
}