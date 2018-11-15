#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
int main(int argc,char **argv)
{
     struct dirent** namelist;
    int n;
    if(argc<1)
     exit(EXIT_FAILURE);
    else if(argc==1)
       n = scandir(".",&namelist,NULL,alphasort);
     if(n<0)
    {
    perror("scandir");
    exit(EXIT_FAILURE);
}
  else
   {
     int cnt =0;
     while(n--)
{
      printf("%s\n",namelist[n]->d_name);
     free(namelist[n]);
    cnt++;
}
free(namelist);
 printf("Total no of dir:%d\n", cnt);
}
exit(EXIT_SUCCESS);
}
