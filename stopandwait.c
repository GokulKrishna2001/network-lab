//stop and wait simulation
/*
#include<stdio.h>

struct frame
{
    int info, seq;//the information and sequence part of the frame
};

struct frame f={101,1};//initializing the info and seq part

int counter=0;
int duplicate=0;//1- duplicate exists
int errorframe=1;//in sender
int errorack=1;//in receriver

void sender()
{
    //setting up the errorframe
    errorframe=rand()%4;
    //checking for duplicates
    if(duplicate==1)
        printf("Resending Frame: %d-%d\n",f.info,f.seq);
    else if(errorframe==0)
    {
        printf("Error in sending the Frame: %d-%d\n",f.info,f.seq);
        sender();//going back to send the frame again
    }
    else//normal cases
    {
        printf("Sent the Frame: %d-%d\n",f.info,f.seq);
    }
}

void receiver()
{
    //setting up the errorack
    errorack=rand()%4;
    if(duplicate==1)//checking for the duplicate
    {
        printf("Received the Duplicate Frame: %d-%d\n",f.info,f.seq);
        duplicate=0;
    }
    else if(errorack==0)
    {
        printf("Timer Active:\n");
        for(int i=1;i<=5;i++)
            printf("%d\n",i);
        printf("Did not receive Acknowledgement for Frame: %d-%d\n",f.info,f.seq);
        duplicate=1;//making the duplicate active as we are making the sender send the frame again
        //sending the frame again
        sender();
        receiver();
    }
    else//during normal conditions
    {
        printf("Acknowledgement received for Frame: %d-%d\n",f.info,f.seq);
        //incrementing the structure values
        f.info++;
        f.seq++;
    }
}


void main()
{
    while(counter!=10)
    {
        sender();
        receiver();
        counter++;
    }
}
*/

//stop and wait simulation
//prime number packets and imput n number
#include<stdio.h>

struct frame
{
    int info, seq;//the information and sequence part of the frame
};

struct frame f={10,1};//initializing the info and seq part

int counter=0;
int duplicate=0;//1- duplicate exists
int errorframe=1;//in sender
int errorack=1;//in receriver

void sender()
{
    //setting up the errorframe
    errorframe=rand()%4;
    //checking for duplicates
    if(duplicate==1)
        printf("Resending Frame: %d-%d\n",f.info,f.seq);
    else if(errorframe==0)
    {
        printf("Error in sending the Frame: %d-%d\n",f.info,f.seq);
        sender();//going back to send the frame again
    }
    else//normal cases
    {
        printf("Sent the Frame: %d-%d\n",f.info,f.seq);
    }
}

void receiver()
{
    int i,j,n;
    //setting up the errorack
    errorack=rand()%4;
    if(duplicate==1)//checking for the duplicate
    {
        printf("Received the Duplicate Frame: %d-%d\n",f.info,f.seq);
        duplicate=0;
    }
    if(errorack==0)
    {
        printf("Timer Active:\n");
        for(i=1;i<=5;i++)
            printf("%d\n",i);
        printf("Did not receive Acknowledgement for Frame: %d-%d\n",f.info,f.seq);
        duplicate=1;//making the duplicate active as we are making the sender send the frame again
        //sending the frame again
        sender();
        receiver();
    }
    else//during normal conditions
    {
        printf("Acknowledgement received for Frame: %d-%d\n",f.info,f.seq);
        //incrementing the structure values
        f.seq++;
        f.info++;
        /*
        //for prime numbers
        for(i=f.info;i<100;i++)
        {
            n=0;
            for(j=1;j<=i;j++)
            {
                if(i%j==0)
                    n++;
            }
            if(n==2)
            {
                f.info=i;
                break;
            }
        }
        */
    }
}


void main()
{
    printf("Enter the number of packets to be sent:");
    scanf("%d",&counter);
    while(counter!=0)
    {
        sender();
        receiver();
        counter--;
    }
}