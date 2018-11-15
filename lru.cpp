#include<iostream>
using namespace std;

int lru[3];
int frame[3];

int main()
{
int n,i,j=0,small=0,ph=1;
cout<<"\t------> Page Replacement Algorithm (LRU) <------\n\n";
cout<<"Enter the no. of pages:\t";
cin>>n;

int pr[n];

cout<<"\nEnter Page Request:\n";
for(int j=0;j<n;j++)
{
cin>>pr[j];
}

for(i=0;i<3;i++)
{
lru[i]=-1;
frame[i]=-1;
}

int p=0;

while(p<n)
{
int has = 0;

for(i=0;i<3;i++)
{
if(frame[i]==pr[p])
{
has=1;
lru[i]=p;
cout<<"\t\t Page hit = "<<ph++ <<"\n";
}
}

if(has==0)
{

for(j=0;j<3;j++)
{
if(lru[j]<lru[small])
{
small=j;
}
}

lru[small] = p ;
frame[small] = pr[p];
}



cout<<"\npages loaded are : ";

for(int j=0;j<3;j++)
{
cout<<frame[j]<<" ";
}
p++;
}
cout<<"\n\nTotal Page faults = "<<(n-ph+1) ;
return 0;
}
