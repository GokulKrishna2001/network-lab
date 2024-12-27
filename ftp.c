//FTP Server
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

#define size 1024

void write_file(int sockfd)
{
    int n;
    FILE *fp;
    char buffer[size];

    fp=fopen("recv.txt","w");
    while(1)
    {
        n=recv(sockfd,buffer,size,0);
        if(n<=0)
        {
            break;
            return;
        }
        fprintf(fp,"%s",buffer);
        puts(buffer);
        bzero(buffer,size);

    }
    return;
}

int main()
{
    int e;
    int sockfd,new_sock;
    struct sockaddr_in server_addr,new_addr;
    socklen_t addr_size;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
    {
        perror("[-] Error in the socket.\n");
        exit(1);
    }
    printf("[+] Server socket created successfully.\n");

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=3033;
    server_addr.sin_addr.s_addr=INADDR_ANY;

    e=bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));

    if(e<0)
    {
        perror("[-] Error in the bind./n");
        exit(1);
    }
    printf("[+] Binding Successful.\n");

    if(listen(sockfd,10)==0)
    {
        printf("[+] Listening...\n");
    }
    else
    {
        perror("[-] Error in listening\n");
        exit(1);
    }

    addr_size=sizeof(new_addr);
    new_sock=accept(sockfd,(struct sockaddr*)&new_addr,&addr_size);
    write_file(new_sock);
    printf("[+] Data has been successfully written.\n");

    return 0;
}

//FTP Client
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define size 1024

void send_file(FILE *fp, int sockfd)
{
    char data[size]={0};

    while(fgets(data,size,fp)!=NULL)
    {
        if(send(sockfd,data,sizeof(data),0)==-1)
        {
            perror("[-] Error in sending the file.\n");
            exit(1);
        }
        puts(data);
        bzero(data,size);
    }
}


void main()
{
    int e;
    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    if(sockfd,0)
    {
        perror("[-] Error in the socket.\n");
        exit(1);
    }
    printf("[+] Server socket created successfully.\n");

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=3033;
    server_addr.sin_addr.s_addr=INADDR_ANY;

    e=connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));

    if(e==-1)
    {
        perror("[-] Error in the socket.\n");
        exit(1);
    }

    printf("[+] Connected to the server.\n");
    
    fp=fopen("send.txt","r");
    if(fp==NULL)
    {
        perror("[-] Error in reading the file.\n");
        exit(1);
    }

    send_file(fp,sockfd);
    printf("[+] File Data Sent Successfully\n");
    printf("[+] closing the connection.\n");

}

//Output
/*
Server
[+] Server socket created successfully.
[+] Binding Successful.
[+] Listening...
Hello there
[+] Data has been successfully written.

Client
[+] Server socket created successfully.
[+] Connected to the server.
Hello there
[+] File Data Sent Successfully
[+] closing the connection.
*/
