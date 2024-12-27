//udp server
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

void main()
{
    int sockdesc;
    struct sockaddr_in server, client;
    char buff[100];

    sockdesc=socket(AF_INET,SOCK_DGRAM,0);
    if(sockdesc==-1)
        printf("Error in creation\n");
    
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=3005;

    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3005;

    int k=bind(sockdesc,(struct sockaddr*)&server,sizeof(server));
    if(k==-1)
        printf("Binding error\n");
    
    k=recvfrom(sockdesc,buff,100,0,(struct sockaddr*)&client,sizeof(client));

    printf("%s\n",buff);

    close(sockdesc);

    
}