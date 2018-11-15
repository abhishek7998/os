#include<iostream>
using namespace std;

int frame[3];
int opt[3];

int main()
{
int n,i,k=0,j=0,index=0,max=0,ph=0;
cout<<"\t------> Page Replacement Algorithm (Optimal) <------\n\n";
cout<<"Enter the no. of pages:\t"; cin>>n;

int pr[n];

cout<<"\nEnter Page Request:\n";
for(int j=0;j<n;j++) { cin>>pr[j];
}

for(i=0;i<3;i++)
{
opt[i]=-1;
frame[i]=-1;
}

for(int i=0;i<n;i++)
{
int has = 0;
for(int j=0;j<3;j++)
{
if(frame[j]==pr[i])
{
has=1;
cout<<"\t\t Page hit = "<< ++ph <<"\n";
}
}
if(has==0)
{
for(int j=0;j<3;j++)
{
for(int k=i+1;k<n;k++)
{
opt[j]=0;
if(frame[j]==pr[k])
{
opt[j]=k-i;
break;
}
}
}

int tag=0;
for(int j=0;j<3;j++)
{
if(opt[j]==0)
{
index=j;
tag=1;
break;
}
}
if(tag==0)
{
max=opt[0];
index=0;
for(int k=1;k<3;k++)
{
if(max<opt[k])
{
max=opt[k];
index=k;
}
}

}
frame[index]=pr[i];
}
cout<<"\nPages loaded are : ";
for(int k=0;k<3;k++)
cout<<frame[k]<<" ";
}
cout<<"\n Total page fault "<<(n-ph);
}
