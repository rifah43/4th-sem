#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
// 3child jekhane 1ta actual child 2ta grandchild
int main()
{
    int arr[5]={2,5,81,43,13};

    pid_t pid,pid1;
    pid = fork();
    pid1=fork();
    //printf("hihi %d, %d\n",pid,pid1);
    if(pid!= 0 && pid1!=0)
    {
        printf("I am parent\n");
    }
    
    if(pid== 0 && pid1 !=0)
    {
        printf("I am 1st child\n");
        int sum=0;
        for(int i=0;i<5;i++)
        {
            if(arr[i]%2==0)
            {
                sum+=arr[i];
            }
        }
        printf("The sum of even numbers is: %d",sum);
        exit(0);
    }
    if(pid==0 && pid1!=0)
    {
        printf("I am 2nd child\n");
        int sum=0;
        for(int i=0;i<5;i++)
        {
            if(arr[i]%2==0)
            {
                sum++;
            }
        }
        printf("The number of even numbers is: %d",sum);
        exit(0);
    }
    if(pid==0 && pid1==0)
    {
        printf("I am 3rd child\n");
        int sum=0;
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(arr[i]>arr[i+1])
                {
                    int temp;
                    temp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = temp;
                }
            }
        }
        printf("The number of even numbers is: %d",sum);
        exit(0);
    }
}
