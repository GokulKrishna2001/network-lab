//stop and wait program
//Gokul Krishna S, S6R2, 25
/*
#include<stdio.h>
#include<stdlib.h>

//the sending and receiving frame will have 2 members
struct frame
{
    int info;
    int seq;
}p;

int ak;
int t=5, k;
int disconnect=0;
int errorframe=1,errorack=1;
//former while sending and the other while receiving
char turn='s';

void sender()
{
    static int flag=0;
    if(turn=='s')//for sending
    {
        if(errorack==0)//to send a packet
        {
            printf("SENDER: sent packet with the sequence number:%d\n",p.seq);
            errorframe=rand()%4;//rand() to generate numbers in random
            printf("%s\n",(errorframe==0?"Error While sending the Packet":""));
            turn='r';
        }
        else//to acknowledge and send a packet
        {
            if(flag==1)
                printf("SENDER: received ACK for packet %d\n",ak);
            
            if(p.seq==10)
            {    
                disconnect=1;
                return;
            }

            p.info++;
            p.seq++;
            printf("SENDER: sent packet with sequence number:%d\n",p.seq);
            errorframe=rand()%4;
            printf("%s\n",(errorframe==0?"Error While Sending Packet":"")); 

            turn='r';
            flag=1;   
        }   
    }
    else//when turn='r'
    {
        t--;
        printf("SENDER time reducing\n");
        if(t==0)
        {
            turn='s';
            errorack=0;
            t=5;
        }
    }
}

void receiver()
{
    static int frexp=1;
    if(turn=='r')//for receiving 
    {
        if(errorframe!=0)//if the sender sent a data
        {
            if(p.seq==frexp)//for new and unique packets
            {
                printf("RECEIVER: received the packet with sequence number %d\n",p.seq);
                ak=p.seq;
                frexp++;
                turn='s';
                errorack=rand()%4;
                printf("%s\n",(errorack==0?"Error While Sending ACK":""));
            }
            else//for packets with dupliacte sequence number
            {
                printf("RECEIVER: duplicated packet with the sequence number: %d\n",frexp-1);
                ak=frexp-1;
                turn='s';
                errorack=rand()%4;
                printf("%s\n",(errorack==0?"Error While Sending ACK":""));
            }
        }
    }
}

void main()
{
    p.info=0;
    p.seq=0;
    while(!disconnect)
    {
        sender();
        for(k=1;k<=10000000;k++)
            receiver();
    }
}
*/
/*
OUTPUT
SENDER: sent packet with sequence number:1

RECEIVER: received the packet with sequence number 1

SENDER: received ACK for packet 1
SENDER: sent packet with sequence number:2

RECEIVER: received the packet with sequence number 2

SENDER: received ACK for packet 2
SENDER: sent packet with sequence number:3

RECEIVER: received the packet with sequence number 3

SENDER: received ACK for packet 3
SENDER: sent packet with sequence number:4

RECEIVER: received the packet with sequence number 4
Error While Sending ACK
SENDER: sent packet with the sequence number:4

RECEIVER: duplicated packet with the sequence number: 4

SENDER: received ACK for packet 4
SENDER: sent packet with sequence number:5

RECEIVER: received the packet with sequence number 5

SENDER: received ACK for packet 5
SENDER: sent packet with sequence number:6

RECEIVER: received the packet with sequence number 6

SENDER: received ACK for packet 6
SENDER: sent packet with sequence number:7

RECEIVER: received the packet with sequence number 7

SENDER: received ACK for packet 7
SENDER: sent packet with sequence number:8
Error While Sending Packet
SENDER time reducing
SENDER time reducing
SENDER time reducing
SENDER time reducing
SENDER time reducing
SENDER: sent packet with the sequence number:8

RECEIVER: received the packet with sequence number 8
Error While Sending ACK
SENDER: sent packet with the sequence number:8
Error While sending the Packet
SENDER time reducing
SENDER time reducing
SENDER time reducing
SENDER time reducing
SENDER time reducing
SENDER: sent packet with the sequence number:8

RECEIVER: duplicated packet with the sequence number: 8
Error While Sending ACK
SENDER: sent packet with the sequence number:8

RECEIVER: duplicated packet with the sequence number: 8

SENDER: received ACK for packet 8
SENDER: sent packet with sequence number:9

RECEIVER: received the packet with sequence number 9

SENDER: received ACK for packet 9
SENDER: sent packet with sequence number:10

RECEIVER: received the packet with sequence number 10

SENDER: received ACK for packet 10
*/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
struct frame{
int data,seqn;
};
struct frame f={101,1};
int count=0,duplicate=0; //1 means duplicate
int ack_error=1,send_error=1; //0 means error
void sender(){
send_error=rand()%4;
printf("Send error=%d\n",send_error);
if(duplicate==1)
printf("\nresending frame |%d|%d|",f.data,f.seqn);
else if(send_error==0){
printf("\nerror in sending frame with seqn %d",f.seqn);
sender();
}
else{
printf("\nframe sent successfully |%d|%d|",f.data,f.seqn);
}
}
void receiver(){
    int i=0;
ack_error=rand()%4;
printf("Error ack=%d\n",ack_error);
if(duplicate==1){
printf("\nduplicate frame |%d|%d| received",f.data,f.seqn);
duplicate=0;
}
if(ack_error==0){
printf("\ntimer active");
printf("\n%d",i);
printf("\nno ack received for frame with seqn %d",f.seqn);
duplicate=1;
sender();
receiver();
}
else{
printf("\nack received for frame |%d|%d|",f.data,f.seqn);
f.data++;
f.seqn++;
}
}
int main(){
while(count++ !=10){
sender();
receiver();
}
return 0;
}

