#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
  pid_t pid=fork();
  // had create a sub process with pid, and sub process execute same code with main
  // father process always finish earlier
  int a = 1024;
  int b = 2048;
  printf("add result: %d\n", a+b);
  if(pid<0)
  {
    fprintf(stderr,"wrong！");
  }
  else if(pid > 0)
  {
    printf("this is father process ! sub process id=%d\n",pid);
    printf("father a: %d\n",a);
    exit(0);
  }
  else{
    printf("b: %d this is sub process！\n",b);
  }
  exit(0);
}
