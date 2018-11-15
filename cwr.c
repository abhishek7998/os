#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
int main()
{
     FILE *i = fopen("foo.txt","w+");
    char text[] = "hello world\n";
    fputs(text,i);
    rewind(i);
   char str1[100], str2[100];
   fscanf(i,"%s%s",str1,str2);
   printf("contents of file:%s %s\n",str1,str2);
}
