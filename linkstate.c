//Link state

#include<stdio.h>
#include<string.h>

int main()
{
    int count,src_router,i,j,k,w,v,min;
    int cost_matrix[100][100],dist[100],last[100];
    int flag[100];

    printf("Enter the number of routers:");
    scanf("%d",&count);

    printf("Enter the cost matrix values:\n");
    for(i=0;i<count;i++)
    {
        for(j=0;j<count;j++)
        {
            printf("%d->%d:",i,j);
            scanf("%d",&cost_matrix[i][j]);
            if(cost_matrix[i][j]<0)
                cost_matrix[i][j]=1000;
        }
    }

    printf("Enter the source router:");
    scanf("%d",&src_router);

    //assumptions
    for(v=0;v<count;v++)
    {
        flag[v]=0;//not covered
        last[v]=src_router;//final postion
        dist[v]=cost_matrix[src_router][v];//initial distance from src
    }
    flag[src_router]=1;

    for(i=0;i<count;i++)
    {
        min=1000;
        //checking the shortest in the a row
        for(w=0;w<count;w++)
        {
            if(!flag[w])
                if(dist[w]<min)
                {
                    v=w;
                    min=dist[w];
                }
        }
        flag[v]=1;
        for(w=0;w<count;w++)
        {
            if(!flag[w])
                if(min+cost_matrix[v][w]<dist[w])
                {
                    dist[w]=min+cost_matrix[v][w];
                    last[w]=v;
                }
        }
    }

    for(i=0;i<count;i++)
    {
        printf("%d-->%d:\nPath taken:%d",src_router,i,i);
        w=i;
        while(w!=src_router)
        {
            printf("<--%d",last[w]);
            w=last[w];
        }
        printf("\n");
        printf("Shortest path cost:%d\n",dist[i]);
    } 
}