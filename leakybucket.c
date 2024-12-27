//leaky bucket
#include<stdio.h>

void main()
{
    int bucket_size, incoming_size, outgoing_rate, n, store=0;
    //store for the packets remaining in the bucket

    printf("Enter the bucket size:");
    scanf("%d",&bucket_size);
    printf("Enter the outgoing rate:");
    scanf("%d",&outgoing_rate);
    printf("Enter the number of inputs:");
    scanf("%d",&n);

    while(n!=0)
    {
        printf("\nEnter the packet size:");
        scanf("%d",&incoming_size);

        printf("\nThe Number of packets entering:%d\n",incoming_size);

        //conditions
        if(incoming_size<=bucket_size-store)//when the packets fit inside the bucket
        {
            store+=incoming_size;
            printf("The buffer size: %d out of %d\n",store,bucket_size);
            //the stored value of the bucket at that time
        }
        else//for overflow condition
        {
            printf("The buffer size: %d out of %d\n",store,bucket_size);
            printf("Dropped %d packets from the buckets\n",(incoming_size+store-bucket_size));
            store=bucket_size;//after dropping, the store size will be the bucket size
        }
        store=store-outgoing_rate;//removing the packets from the bucket
        printf("%d packets are left after outgoing from the bucket of size %d\n",store,bucket_size);
        n--;
    }
}


/*
Enter the bucket size:500
Enter the outgoing rate:200
Enter the number of inputs:5

Enter the packet size:200

The Number of packets entering:200
The buffer size: 200 out of 500
0 packets are left after outgoing from the bucket of size 500

Enter the packet size:700

The Number of packets entering:700
The buffer size: 0 out of 500
Dropped 200 packets from the buckets
300 packets are left after outgoing from the bucket of size 500

Enter the packet size:500

The Number of packets entering:500
The buffer size: 300 out of 500
Dropped 300 packets from the buckets
300 packets are left after outgoing from the bucket of size 500

Enter the packet size:450

The Number of packets entering:450
The buffer size: 300 out of 500
Dropped 250 packets from the buckets
300 packets are left after outgoing from the bucket of size 500

Enter the packet size:400

The Number of packets entering:400
The buffer size: 300 out of 500
Dropped 200 packets from the buckets
300 packets are left after outgoing from the bucket of size 500
*/