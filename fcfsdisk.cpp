#include<iostream>
#include<cmath>
using namespace std;

int main()
{
int n,head,stime=0;

cout<<"Enter the length of queue:\n";
cin>>n;
int queue[n];
cout<<"\nEnter the Queue :-\n";
for(int i=0;i<n;i++)
{
cin>>queue[i];
}
cout<<"\nEnter the starting head :\n";
cin>>head;

stime = abs(head - queue[0]);
for(int i=1;i<n;i++)
{
stime = stime + abs(queue[i-1]-queue[i]) ;
}

cout<<"\nTotal Seek time : "<<stime;
cout<<"\nAverage Seek time :"<<(stime/(float)n);
}
