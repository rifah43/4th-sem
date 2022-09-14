#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

sem_t mutex,wrt;
pthread_t writerthreads[100],readerthreads[100];
int read = 0, counter = 0, n2 = 5;

void *reader(void* arg)
{
    sem_wait(&mutex);
    read++;
    if(read==1)
    sem_wait(&wrt);
    sem_post(&mutex);
    printf("%d reader is inside reading %d\n",read,counter);
    sem_wait(&mutex);
    read--;
    if(read==0)
    {
        sem_post(&wrt);
    }
    sem_post(&mutex);
}

void *writer(void* arg)
{
    sem_wait(&wrt);
    counter++;
    printf("The writer edited %d\n",counter);
    sem_post(&wrt);
}

int main()
{
    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);
    for(int i=0;i<n2;i++)
    {
        pthread_create(&readerthreads[i],NULL,reader,NULL);
        pthread_create(&writerthreads[i],NULL,writer,NULL);
    }
    for(int i=0;i<n2;i++)
    {
        pthread_join(readerthreads[i],NULL);
        pthread_join(writerthreads[i],NULL);
    }

}
