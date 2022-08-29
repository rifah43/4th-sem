#include <stdio.h>
#include<unistd.h>

int main()
{
    int pid;
    printf("I'm the original process with PID %d and PPID %d. \n", getpid(),getppid());
    pid = fork();
    printf("%d\n",pid);
    if(pid!= 0)
    {
        printf("I'm the parent process with PID %d and PPID %d. \n", getpid(),getppid());
        printf("My child's PID is %d\n", pid);
    }
    else
    {
        printf("I'm child process with PID %d and PPID %d. \n", getpid(),getppid());
    }
    printf("PID %d terminates\n",getpid());
}


