//link state using dijkstra's

#include<stdio.h>

void main()
{
    int i,j,min,v,w,count,source;
    int cost_matrix[100][100],dist[100],flag[100],last[100];
    //cost matrix for the vertex distances
    //dist for the shortest distance from the source vertex
    //flag for checking if the vertex is completely used
    //last for storing the previous vertex
    
    //for the number of routers
    printf("Enter the number of routers:");
    scanf("%d",&count);

    //entering the cost matrix values
    printf("Enter 1000 for unreachable distance\n");
    printf("Enter 0 for self loops\n");
    printf("Enter the cost matrix values:\n");
    for(i=0;i<count;i++)
        for(j=0;j<count;j++)
        {
            printf("%d->%d:",i,j);
            scanf("%d",&cost_matrix[i][j]);
        }
            
    
    //enter source
    printf("Enter the source:");
    scanf("%d",&source);

    //assuming
    for(i=0;i<count;i++)
    {
        flag[i]=0;//inititalizing the node
        last[i]=source;//vertex before it as source
        dist[i]=cost_matrix[source][i];//the cost from the source vertex(direct)
    }

    flag[source]=1;//making the source vertex as done

    for(i=0;i<count;i++)
    {
        min=1000;//1000 is similar to infinity
        for(w=0;w<count;w++)
        {
            if(!flag[w])//flag!=1
                if(dist[w]<min)
                {
                    v=w;//position of min
                    min=dist[w];//min gets changed
                }
        }

        flag[v]=1;//the last vertex with v gets completed
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

    //for printing
    printf("Printing the shortest paths from the source vertex:\n");
    for(i=0;i<count;i++)
    {
        printf("%d->%d\n",source,i);
        printf("The path:%d",i);

        //backtracking
        w=i;
        while(w!=source)
        {
            printf("<-%d",last[w]);
            w=last[w];
        }
        printf("\n");
        printf("Shortest Distance:%d\n",dist[i]);//printing the distance
    }
}

/*
Enter the number of routers:5
Enter 1000 for unreachable distance
Enter 0 for self loops
Enter the cost matrix values:
0->0:0
0->1:6
0->2:1000
0->3:1
0->4:1000
1->0:6
1->1:0
1->2:5
1->3:2
1->4:2
2->0:1000
2->1:5
2->2:0
2->3:1000
2->4:5
3->0:1
3->1:2
3->2:1000
3->3:0
3->4:1
4->0:1000
4->1:2
4->2:5
4->3:1
4->4:0
Enter the source:0
Printing the shortest paths from the source vertex:
0->0
The path:0
Shortest Distance:0
0->1
The path:1<-3<-0
Shortest Distance:3
0->2
The path:2<-4<-3<-0
Shortest Distance:7
0->3
The path:3<-0
Shortest Distance:1
0->4
The path:4<-3<-0
Shortest Distance:2
*/