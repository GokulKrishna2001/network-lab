//ftp sender(client)
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>

#define size 1024 

void send_file(FILE *fp, int socket_desc)
{
    char buffer[size]={0};//initializing the characters as 0
    
    //reading the file
    //fgets(character array, size of it, file pointer)
    while (fgets(buffer,size,fp)!=NULL)
    {
        //send(socket description, char array, sizeof(array),flag=0)
        if(send(socket_desc,buffer,sizeof(buffer),0)==-1)
        {
            printf("Sending Error\n");
            exit(1);
        }
        puts(buffer);//sending the data to the stream
        bzero(buffer,size);//places 0s in the buffer then of size 'size'
    }
    
}

void main()
{
    //socket creation
    int socket_desc=socket(AF_INET,SOCK_STREAM,0);
    if(socket_desc==-1)
    {
        printf("Socket Creation Error\n");
        exit(1);
    }
    else
        printf("Socket creation successful\n");
    
    //initializing the server
    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=3033;
    server.sin_addr.s_addr=INADDR_ANY;

    //creating the connection
    //connect(socket description, (struct sockaddr*)&server,sizeof(server))
    int e=connect(socket_desc,(struct sockaddr*)&server, sizeof(server));
    if(e==-1)
        printf("Connection Error\n");
    else
        printf("Connection Established\n");
    
    FILE *fp;//file pointer
    fp=fopen("send.txt","r");//to read the contents of the file
    if(fp==NULL)
    {
        printf("Unable to read the file\n");
        exit(1);
    }

    send_file(fp,socket_desc);
    printf("File has been successfully sent\n");
    fclose(fp);
    printf("File has been closed\n");
}