#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

//Declare 
int terminate = 0, duplicate = 0, ack_error = 1, send_error = 1;
struct frame {int seq,info;};
struct frame f = {1,101};
int ws = 0;
//sender function
void sender() {
	send_error = rand()%2; //every 2nd send has error 
	if(duplicate == 1) {
		while(ws!=3) {
			printf("\nResending frames with seqno %d and info %d!",f.seq+ws,f.info+ws);
			ws++;
		}
		ws=0;
	}
	else if(send_error == 0) {
		printf("\nError in sending frame.. %d",f.seq);
		sender();
	}
	else { 
		while(ws!=3) {
			printf("\nSending frame with seqno %d and info %d!",f.seq+ws,f.info+ws);
			ws++;
		}
		ws = 0;
	}	
}

//receiver function 
void receiver() {

	ack_error = rand()%2;
	if(duplicate == 1) {
		duplicate = 0;
		printf("\nDuplicate frame received have been discarded");;
		}
	if(ack_error == 0) 
		{
			//being countdown at sender
			printf("\nCountdown at Sender Starting:\n");
			for(int i=5;i>=0;i--)
				printf("%d\n",i);
			printf("Error - Acknowledgment not sent for %d..",f.seq);
			duplicate = 1;
			sender();
			receiver();
		}
	else { 
	 	while(ws!=3) { 
		 	f.seq++;
		 	f.info++;
		 	ws++;
	 	}
	 	ws = 0;
	 	if(f.seq!=10) 
			printf("\nCumulative Ack Sent for %d!\nSending Request for frame with seqno %d!",f.seq-1,f.seq);
		else
			printf("\nSending Complete!!");
	}
}

void main() {
	while(terminate++ !=3) //only 3 sends
	{
		sender();
		receiver();
	}
	printf("\n");
}
/*
Sending frame with seqno 1 and info 101!
Sending frame with seqno 2 and info 102!
Sending frame with seqno 3 and info 103!
Countdown at Sender Starting:
5
4
3
2
1
0
Error - Acknowledgment not sent for 1..
Resending frames with seqno 1 and info 101!
Resending frames with seqno 2 and info 102!
Resending frames with seqno 3 and info 103!
Duplicate frame received have been discarded
Cumulative Ack Sent for 3!
Sending Request for frame with seqno 4!
Sending frame with seqno 4 and info 104!
Sending frame with seqno 5 and info 105!
Sending frame with seqno 6 and info 106!
Cumulative Ack Sent for 6!
Sending Request for frame with seqno 7!
Error in sending frame.. 7
Error in sending frame.. 7
Sending frame with seqno 7 and info 107!
Sending frame with seqno 8 and info 108!
Sending frame with seqno 9 and info 109!
Sending Complete!!
*/