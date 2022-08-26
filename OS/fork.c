#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(){
    printf("without fork PID %d\n",getpid());
    fork();
    printf("with fork PID %d\n",getpid());
}