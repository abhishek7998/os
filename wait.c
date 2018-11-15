#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
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
{
     printf("waiting...\n");
    pid_t cpid = wait(NULL);
   printf("par here\n id = %d \n child id = %d \n",getpid(),cpid);
}
   printf("pid = %d\n",idx);
}
