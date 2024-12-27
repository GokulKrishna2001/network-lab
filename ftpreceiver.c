//ftp receiver(server)
//follows the method of TCP
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define size 1024

void write_file(int socket_desc)//writing the input to the new file
{
    FILE *fp=fopen("receive.txt","w");
    char buffer[size];

    while(1)
    {
        //recv(socket description, char array, sizeof(array),flag=0)
        int n=recv(socket_desc,buffer,size,0);
        if(n<=0)
        {
            break;
            return;
        }

        //printing the input to the new file
        fprintf(fp,"%s",buffer);//fprintf(file pointer,"%s",char array)
        puts(buffer);
        bzero(buffer,size);
    }
}

int main()
{
    int socket_desc, socket_desc2;
    struct sockaddr_in server, new_addr;
    socklen_t addr_size;//to find the address size of the socket

    //creating the socket
    socket_desc=socket(AF_INET,SOCK_STREAM,0);
    if(socket_desc==-1)
    {
        printf("Socket Creation Error\n");
        exit(1);
    }
    else
        printf("Socket Creation Successful\n");

    //server defaults
    server.sin_family=AF_INET;
    server.sin_port=3033;
    server.sin_addr.s_addr=INADDR_ANY;

    //bind(socket description, (struct sockaddr*)&server,sizeof(server))
    int e=bind(socket_desc,(struct sockaddr*)&server,sizeof(server));
    if(e==-1)
    {
        printf("Binding Error\n");
        exit(1);
    }
    else
        printf("Binding Successful\n");

    if(listen(socket_desc,1)==0)//10=queue length
    {
        printf("Listening..\n");
    }    
    else
    {
       printf("Unable to listen\n");
       exit(1);
    }
        
    //for taking the file content as the input
    addr_size=sizeof(new_addr);
    //accept(Socket description old,(struct sockaddr*)&new_addr,&addr_size)
    socket_desc2=accept(socket_desc,(struct sockaddr*)&new_addr,&addr_size);

    write_file(socket_desc2);
    printf("Writing Successful\n");
}