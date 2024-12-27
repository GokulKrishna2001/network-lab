#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
char buf[100];//input to the server
int k;
int sock_desc;
struct sockaddr_in client,server;
sock_desc=socket(AF_INET,SOCK_DGRAM,0);//sock_stream =tcp AF_INET is default family
if(sock_desc==1)
printf("ERROR");
client.sin_family=AF_INET;
client.sin_addr.s_addr=INADDR_ANY;
client.sin_port=3010;
printf("Enter data to send  ");
fgets(buf,100,stdin);//used to get input from user in char format
k=sendto(sock_desc,buf,100,0,(struct sockaddr*)&client,sizeof(client));
close(sock_desc);
return 0;
}

