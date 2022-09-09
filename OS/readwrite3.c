#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>

sem_t mutex,wrt;
pthread_t writerthreads[100],readerthreads[100];
int read = 0, counter = 0, n2 = 5;

void *reader(void* param)
{
    sem_wait(&mutex);
    read++;
    if(read==1)
    sem_wait(&wrt);
    sem_post(&mutex);
    printf("\n%d reader is inside reading %d",read,counter);
    sem_wait(&mutex);
    read--;
    if(read==0)
    {
        sem_post(&wrt);
    }
    sem_post(&mutex);
}

void *writer(void* param)
{
    sem_wait(&wrt);
    counter++;
    printf("\nThe writer edited %d",counter);
    sem_post(&wrt);
}

int main()
{
    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);
    for(int i=0;i<n2;i++)
    {
        pthread_create(&readerthreads[i],NULL,reader,NULL);
    }
    
    for(int i=0;i<n2;i++)
    {
        pthread_join(readerthreads[i],NULL);
    }
    for(int i=0;i<n2;i++)
    {
        pthread_create(&writerthreads[i],NULL,writer,NULL);
    }
    for(int i=0;i<n2;i++)
    {
        pthread_join(writerthreads[i],NULL);
    }

}