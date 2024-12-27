#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 
int main() {
 
char buf[100]; //data to be shared
int k; //return value for func
int len;
int sock_desc; // 2 socket descriptors, one for server, temp for client
 
struct sockaddr_in server,client;

sock_desc = socket(AF_INET,SOCK_DGRAM,0); //creating a new socket with Address Family Domain, the type sharing data(SOCK_STREAM) & TCP (0)  - Default

if(sock_desc==-1)
printf("Socket Creation Failed\n");
 
//initialiZe server and client
 
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY; //sin_addr is another structure
server.sin_port = 3010;
 
client.sin_family = AF_INET;
client.sin_addr.s_addr = INADDR_ANY; //sin_addr is another structure
client.sin_port = 3010;
 
k = bind(sock_desc, (struct sockaddr*)&server,sizeof(server)); //socket descriptor, socket address & length of server socket
 
if(k==-1)
printf("Error in binding\n");

 
k= recvfrom(sock_desc,buf,100,0,(struct sockaddr*)&client,sizeof(client)); // recieve buffer from client of length 100
 


printf("Message recieved from client is : %s", buf);
 
close(sock_desc);
 
return 0;
 
}
