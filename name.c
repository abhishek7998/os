#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
void main()
{
     int i =0;
   char s[] = "shubham";
  for(int i=0;i<7;i++)
{
     printf("%c\n",s[i]);
   fflush(stdout);
   sleep(i+1);
}
}
