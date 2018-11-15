#include<iostream>
using namespace std;

int frame[3];

int main()
{
int n,i,flag,k=0,j=0;
cout<<"\t------> Page Replacement Algorithm (FIFO) <------\n\n";
cout<<"Enter the no. of pages:\t"; cin>>n;

int pr[n];

cout<<"\nEnter Page Request:\n";
for(int j=0;j<n;j++) { cin>>pr[j];
}

for(int i=0;i<3;i++)
{
frame[i]=-1;
}

int p=0,pf=1;

while(p<n)
{
flag=0;
for(i=0;i<3;i++)
{
if(frame[i]==pr[p])
flag=1;
}
if(flag==1)
cout<<"\t\t Hit:"<<pf++<<"\n\n";

if(flag==0)
{
frame[k%3]=pr[p];
k++;
}

cout<<"\n Frame :- ";
for(j=0;j<3;j++)
{
cout<<frame[j]<<" ";
}

p++;
}
cout<<"\n\nTotal Page hits are : "<<(pf-1);

return 0;
}
