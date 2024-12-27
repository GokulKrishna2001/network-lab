//tcp server 
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int sockdesc, tempsockd;//socket description variables
    struct sockaddr_in client, server;
    char buff[100], buff1[100]; //to store the incomming character array

    //socket function
    sockdesc=socket(AF_INET, SOCK_STREAM, 0);
    if(sockdesc==-1)
        printf("Error in socket creation\n");
    
    //setting up the address profile for server and client
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=3005;

    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3005;

    //bind(server descriptor,(struct sockaddr_in*)&server/client,size in bytes)
    int k=bind(sockdesc,(struct sockaddr*)&server,sizeof(server));

    if(k==-1)
        printf("Error in binding\n");
    
    //listening
    k=listen(sockdesc,1);
    if(k==-1)
        printf("Listening error\n");
    
    //accept function
    int len=sizeof(client);
    tempsockd=accept(sockdesc,(struct sockaddr*)&client,&len);

    if(tempsockd==-1)
        printf("Error in socket creation");
    
    //receiving the string
    k=recv(tempsockd,buff,100,0);
    if(k==-1)
        printf("Receiving error\n");

    printf("%s\n",buff);
    
    //for reversing
    /*
    int bufflen=strlen(buff);
    printf("Length of buff=%d\n", bufflen);

    int i,j=0;
    for(i=bufflen-2;i>=0;i--)
    {
        buff1[j]=buff[i];
        j++;
    }
    printf("Reversed array:%s\n",buff1);
    */

   //for checking if it is palindrome
   /*
   int bufflen=strlen(buff);
   int i,j=bufflen-2,m=0;
   for(i=0;i<bufflen-2;i++)
   {
        if(buff[i]==buff[j])
        {
            m++;
            j--;
        }
        else
            break;
   }
   
   if(m==bufflen-2)
    printf("palindrome\n");
   else
    printf("Not palindrome\n"); 
    */
   
    close(tempsockd);    

}