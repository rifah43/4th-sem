#include <stdio.h>
#include<unistd.h>

int main()
{
    fork();
    while(1)
    {
    	printf("Hello World :)");
    }
}
//here the print is done infinitely and loop is created twice
