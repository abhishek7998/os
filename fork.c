#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
void main()
{
     pid_t idx;
      idx = fork();
   printf("hello\n");
     if(!idx)
{
       printf("child here\n id = %d \n parent id = %d \n",getpid(),getppid());
    }
  else
   printf("par here\n id = %d \n parent id = %d \n",getpid(),getppid());
   printf("pid = %d\n",idx);
}
