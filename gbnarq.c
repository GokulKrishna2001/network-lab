//Sender
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

void itoa(int number, char numberString[]){
	numberString[0] = (char)(number + 48);
	numberString[1] = '\0';
}

int main(){
	//Initialization
	int sockfd, newSockFd, size, windowStart=1, windowCurrent=1, windowEnd=4, oldWindowStart;
	char buffer[100];
	socklen_t len;
	struct sockaddr_in server, client;
	
	//Socket
	server.sin_family = AF_INET;
	server.sin_port = 3033;
	server.sin_addr.s_addr = INADDR_ANY;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//Binding
	printf("\nStarting up...");
	int k;
	k = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
	if(k == -1)
		printf("\nError in binding!");
		
	//Accepting
	len = sizeof(client); 
	listen(sockfd, 1);
	newSockFd = accept(sockfd, (struct sockaddr *)&client, &len);
	
	//Sending
	recv(newSockFd, buffer, 100, 0);
	fcntl(newSockFd, F_SETFL, O_NONBLOCK);
	printf("\nRecieved a request from client, Sending packets one by one...");
	do{
		if(windowCurrent != windowEnd){
			itoa(windowCurrent, buffer);
			send(newSockFd, buffer, 100, 0);
			printf("\nPacket Sent: %d\n", windowCurrent);
			windowCurrent++;
		}
		recv(newSockFd, buffer, 100, 0);
		
		if(buffer[0] == 'R'){
			printf("\n**Received a RETRANSMIT packet %c.\n\nResending packet: %c...",buffer[1], buffer[1]);
			itoa((atoi(&buffer[1])), buffer);
			send(newSockFd, buffer, 100, 0);
			windowCurrent = atoi(&buffer[0]);
			windowCurrent++;
			
		}
		else if(buffer[0] == 'A'){
			oldWindowStart = windowStart;
			windowStart = atoi(&buffer[1])+1;
			windowEnd += (windowStart - oldWindowStart);
			printf("\n**Recieved ACK %c. Moving window boundary.", buffer[1]);
		}
	}while(windowCurrent != 10);
	printf("\n**Recieved ACK 9!!!");
	
	close(sockfd);
	close(newSockFd);
	
	printf("\nSending complete. Socket closed. Exiting...\n");
	return(0);
}


//Receiver
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	int sockfd, newSockFd, size, firstTime=1, currentPacket, wait=3;
	char data[100], digit[2];
	struct sockaddr_in client;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	client.sin_family = AF_INET;
	client.sin_port=3033;
	client.sin_addr.s_addr = INADDR_ANY;
	
	printf("\nStarting up...");
	size = sizeof(client);
	printf("\nEstablishing Connection...");
	connect(sockfd, (struct sockaddr *)&client, size);
	
	sprintf(data, "REQUEST");
	send(sockfd, data, strlen(data), 0);
	
	do{
		recv(sockfd, data, 100, 0);
		currentPacket = atoi(data);
		printf("\nGot packet: %d", currentPacket);
		
		if(currentPacket==3 && firstTime){
			printf("\n**Simulation: Packet data corrupted or incomplete.");
			printf("\n***Sending RETRANSMIT for packet 1.");
			memset(&data, 0, sizeof(data));
			sprintf(data, "R1");
			send(sockfd, data, strlen(data), 0);
			firstTime = 0;
			wait = 3;
		}
		else{
			wait--;
			if(!wait){
				if(wait == 0)
					printf("\n***Packet Accepted -> Sending ACK");
				else
					printf("\n***Packet Accepted");
				wait = 3;
				sprintf(data, "A");
				digit[0] = (char)(currentPacket + 48);
				digit[1] = '\0';
				strcat(data, digit);
				send(sockfd, data, strlen(data), 0);
			}
		}
	}while(currentPacket != 9);
	
	printf("\nAll packets recieved...Exiting.");
	close(sockfd);
	return(0);
}

/*output

Sender
Starting up...
Recieved a request from client, Sending packets one by one...
Packet Sent: 1

Packet Sent: 2

Packet Sent: 3

**Received a RETRANSMIT packet 1.

Resending packet: 1...
Packet Sent: 2

Packet Sent: 3

**Recieved ACK 3. Moving window boundary.
Packet Sent: 4

Packet Sent: 5

Packet Sent: 6

**Recieved ACK 6. Moving window boundary.
Packet Sent: 7

Packet Sent: 8

Packet Sent: 9

**Recieved ACK 9!!!
Sending complete. Socket closed. Exiting...


Receiver

Starting up...
Establishing Connection...
Got packet: 1
Got packet: 2
Got packet: 3
**Simulation: Packet data corrupted or incomplete.
***Sending RETRANSMIT for packet 1.
Got packet: 1
Got packet: 2
Got packet: 3
***Packet Accepted -> Sending ACK
Got packet: 4
Got packet: 5
Got packet: 6
***Packet Accepted -> Sending ACK
Got packet: 7
Got packet: 8
Got packet: 9
***Packet Accepted -> Sending ACK
All packets recieved...Exiting.

*/