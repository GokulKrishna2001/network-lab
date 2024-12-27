//stop and wait 
/*
Sender:
-> can send a packet normally
-> to send back the frame after the request when the acknowledgement has been failed

Receiver:
-> to send an acknowledgement
-> to identify the duplicate frame

Problems:
-> data lost while being sent
-> lost acknowledgement
-> delayed acknowledgement
*/

#include<stdio.h>

struct frame
{
    int seq,info;//for the sequence number and info
}f={1,10};

int counter;//number of packets to be sent
int duplicate=0;//if 1, duplicate frame is to be sent and so
int errorframe;//used in sender because we send the frame
int errorack;//used in receiver because we send the acknowledgement

void sender()
{
    errorframe=rand()%4;//getting a random number

    if(duplicate==1)//sending the duplicate frame
        printf("Duplicate Frame: %d-%d has been sent.\n",f.info,f.seq);
    else if(errorframe==0)//simulating an error to show that the frame has not been sent
    {
        printf("Failed to send the Frame: %d-%d.\n",f.info,f.seq);
        sender();
    }
    else//sending the frame
        printf("The Frame: %d-%d has been sent successfully.\n",f.info,f.seq);
}

void receiver()
{
    errorack=rand()%4;
    if(duplicate==1)//receiving the duplicate frame
    {
        printf("Received the Duplicate Frame: %d-%d.\n",f.info,f.seq);
        duplicate=0;//no more duplicate of that frame
    }

    if(errorack==0)//error in ack leading to resending of the frame
    {
        //creating a timer
        for(int i=0;i<5;i++)
            printf("%d.\n",i);
        printf("Did not receive the acknowledgement for the Frame: %d-%d.\n",f.info,f.seq);

        duplicate=1;//because, we are going to resend the frame
        sender();//sending the duplicate frame
        receiver();//receiving the duplicate frame
    }
    else//when the frames had no duplicates and no error acks
    {
        printf("Acknowledgement received for the Frame: %d-%d.\n",f.info,f.seq);
        
        //chaning the values
        f.info++;
        f.seq++;
    }
}

void main()
{
    printf("Enter the number of packets to be sent:");
    scanf("%d",&counter);

    //sending the packets
    while(counter!=0)
    {
        sender();
        receiver();
        counter--;
    }
}

/*
Output
Enter the number of packets to be sent:10
The Frame: 10-1 has been sent successfully.
Acknowledgement received for the Frame: 10-1.
The Frame: 11-2 has been sent successfully.
Acknowledgement received for the Frame: 11-2.
The Frame: 12-3 has been sent successfully.
Acknowledgement received for the Frame: 12-3.
The Frame: 13-4 has been sent successfully.
0.
1.
2.
3.
4.
Did not receive the acknowledgement for the Frame: 13-4.
Duplicate Frame: 13-4 has been sent.
Received the Duplicate Frame: 13-4.
Acknowledgement received for the Frame: 13-4.
The Frame: 14-5 has been sent successfully.
Acknowledgement received for the Frame: 14-5.
The Frame: 15-6 has been sent successfully.
Acknowledgement received for the Frame: 15-6.
The Frame: 16-7 has been sent successfully.
Acknowledgement received for the Frame: 16-7.
Failed to send the Frame: 17-8.
The Frame: 17-8 has been sent successfully.
0.
1.
2.
3.
4.
Did not receive the acknowledgement for the Frame: 17-8.
Duplicate Frame: 17-8 has been sent.
Received the Duplicate Frame: 17-8.
Acknowledgement received for the Frame: 17-8.
Failed to send the Frame: 18-9.
The Frame: 18-9 has been sent successfully.
Acknowledgement received for the Frame: 18-9.
The Frame: 19-10 has been sent successfully.
Acknowledgement received for the Frame: 19-10.
*/