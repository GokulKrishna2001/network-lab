//udp client
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

void main()
{
    int sockdesc;
    char buff[100];
    struct sockaddr_in server, client;

    sockdesc=socket(AF_INET, SOCK_DGRAM, 0);
    if(sockdesc==-1)
        printf("Creation failed\n");
    
    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3005;

    printf("Enter the string:");
    fgets(buff,100,stdin);

    int k=sendto(sockdesc,buff,100,0,(struct sockaddr*)&client, sizeof(client));

    close(sockdesc);
}