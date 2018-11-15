#include<stdio.h>

int main()
{
int a[10],w[10],b[10],awt=0,tat[10],n,i;
float wsum=0;
float tsum=0;
printf("\t\t --First Come First Serve Scheduling--\n\n");
printf("Enter the number of processes :\n");
scanf("%d",&n);
for(i=0;i<n;i++)
{
printf("Burst time for process %d : ",i+1);
scanf("%d",&b[i]);
printf("Arrival time for process %d : ",i+1);
scanf("%d",&a[i]);
}

printf("\nPROCESS\tBURST TIME\tARRIVAL TIME\n");
for(i=0; i<n; i++)
{
printf("%dt %dt %dtn",i+1,b[i],a[i]);
}
w[0]=0;
for(i=1; i<n; i++)
{
w[i]=b[i-1]-a[i]+w[i-1];
wsum=wsum+w[i];
}
printf("\nTotal Waiting Time : %f\n", wsum);
printf("Average Waiting Time : %f\n", wsum/n);

tat[0]=b[0]-a[0];
tsum=tat[0];
for(i=1; i<n; i++)
{
tat[i]=b[i]-a[i]+tat[i-1];
tsum=tsum+tat[i];
}

printf("\nTotal Turn Around Time : %f",tsum);
printf("\nAverage Turn Around Time : %f",(tsum/n));
}
