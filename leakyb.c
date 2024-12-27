//Leaky Bucket
#include<stdio.h>

int main()
{
    int incoming,outgoing,buck_size,n,store=0;
    printf("Enter bucket size,outgoing rate and number of inputs:");
    scanf("%d%d%d",&buck_size,&outgoing,&n);

    while(n!=0)
    {
        printf("Enter the incoming packet size:");
        scanf("%d",&incoming);
        
        printf("Incoming packet size %d\n",incoming);
        if(incoming<=(buck_size-store))
        {
            store+=incoming;
            printf("Bucket Buffer Size %d out of %d\n",store,buck_size);
        }
        else
        {
            printf("Dropped %d number of packets\n",incoming-(buck_size-store));
            printf("Bucket buffer size %d out of %d\n",store,buck_size);
            store=buck_size;
        }
        store=store-outgoing;
        printf("After outgoing %d packet left out of %d in buffer\n",store,buck_size);
        n--;
    }
}