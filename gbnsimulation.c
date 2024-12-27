//go back n simulation
/*
Sender
-> sends n frames at a time(here, 3)
-> after receiving ack for one frame, the window slides back and sends the other n frames
-> if a sender loses a frame, it sends the frames in the window back again

Receiver
-> sends ack for each of the frames
-> discards the duplicate frames
-> makes the sender resend the frames if ack is lost

In this program
we send the packets 3 times in total
the window size is 3
*/

#include<stdio.h>

struct frame
{
    int info,seq;
}f={11,1};//frame initial values

int terminate=0;//to terminate the loops
int errorframe;//for the sender
int errorack;//for the receiver
int duplicate=0;//if duplicate exists, it is 1
int count=0;//for loops

void sender()
{
    errorframe=rand()%2;//making every 2nd send as an error
    if(duplicate==1)//when a duplicate frame is to be sent
    {
        while (count!=3)//sending the 3 frames because window size=3
        {
            printf("Duplicate Frame: %d-%d has been sent.\n",f.info+count,f.seq+count);
            count++;
        }
        count=0;
    }
    else if(errorframe==0)//when there is an error in sending a frame
    {
        printf("Error in sending the Frame: %d-%d.\n",f.info,f.seq);
        sender();
    }
    else//normal condition
    {
        while(count!=3)
        {
            printf("Sending the Frame: %d-%d.\n",f.info+count,f.seq+count);
            count++;
        }
        count=0;
    }
}

void receiver()
{
    errorack=rand()%2;

    if(duplicate==1)//discarding the duplicate frames
    {
        while (count!=3)
        {
            printf("Received the Duplicate Frame: %d-%d and has been discarded.\n",f.info+count,f.seq+count);
            count++;
        }
        count=0;
        duplicate=0;
    }
    
    if(errorack==0)//printing the countdown and sending the frames again
    {
        printf("Countdown:\n");
        for(int i=0;i<5;i++)
            printf("%d.\n",i);
        
        printf("Error. Acknowledgement not sent for Frame: %d-%d.\n",f.info,f.seq);
        duplicate=1;
        sender();
        receiver();
    }
    else//for conditions where ack has been sent properly
    {
        while (count!=3)//printing the ack for the values in the window
        {
            printf("Acknowledgement received for Frame: %d-%d.\n",f.info,f.seq);
            //changing the values in the window
            f.info++;
            f.seq++;
            count++;
        }
        count=0;
        if(f.seq!=10)//f.seq will only go before 9
            printf("Sending request for the Frame: %d-%d.\n",f.info,f.seq);
        else
            printf("Sent all Frames.\n");
    }
}

void main()
{
    while(terminate!=3)//only using the loop 3 times
    {
        sender();
        receiver();
        terminate++;
    }
}

/*
Sending the Frame: 11-1.
Sending the Frame: 12-2.
Sending the Frame: 13-3.
Countdown:
0.
1.
2.
3.
4.
Error. Acknowledgement not sent for Frame: 11-1.
Duplicate Frame: 11-1 has been sent.
Duplicate Frame: 12-2 has been sent.
Duplicate Frame: 13-3 has been sent.
Received the Duplicate Frame: 11-1 and has been discarded.
Received the Duplicate Frame: 12-2 and has been discarded.
Received the Duplicate Frame: 13-3 and has been discarded.
Acknowledgement received for Frame: 11-1.
Acknowledgement received for Frame: 12-2.
Acknowledgement received for Frame: 13-3.
Sending request for the Frame: 14-4.
Sending the Frame: 14-4.
Sending the Frame: 15-5.
Sending the Frame: 16-6.
Acknowledgement received for Frame: 14-4.
Acknowledgement received for Frame: 15-5.
Acknowledgement received for Frame: 16-6.
Sending request for the Frame: 17-7.
Error in sending the Frame: 17-7.
Error in sending the Frame: 17-7.
Sending the Frame: 17-7.
Sending the Frame: 18-8.
Sending the Frame: 19-9.
Acknowledgement received for Frame: 17-7.
Acknowledgement received for Frame: 18-8.
Acknowledgement received for Frame: 19-9.
Sent all Frames.
*/