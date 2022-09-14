#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

pthread_t readerT[100], writerT[100];
#define S 10

int read=0, counter=5;
sem_t mutex, queue, resource; 


void *reader(void *arg)
{
  sem_wait(&queue);               
  sem_wait(&mutex);                 
  read++;                
  if (read == 1)         
    sem_wait(&resource);               
  sem_post(&queue);                  
  sem_post(&mutex);                 
  
  printf("I am reader %d and I am reading %d\n", *(int *)(arg), counter);

  sem_wait(&mutex);
  read--;                
  if (read == 0)      
    sem_post(&resource);

  sem_post(&mutex);                 
}


void *writer(void *arg)
{
  sem_wait(&queue);                  
  sem_wait(&resource);
  sem_post(&queue); 

  counter=counter*2;
  printf("I am writer %d and I am writing %d\n", *(int *)(arg), counter);     

  sem_post(&resource);             
}

int main()
{
    sem_init(&mutex,0,1);
    sem_init(&resource,0,1);
    sem_init(&queue,0,1);
    for(int i=0;i<S;i++)
    {
      int *a;
      a = (int *) malloc( sizeof(int) );
      *a=i;
        pthread_create(&writerT[i],NULL,writer,(void*) a);
        pthread_create(&readerT[i],NULL,reader,(void*) a);
    }

    for(int i=0;i<S;i++)
    {
        pthread_join(readerT[i],NULL);
        pthread_join(writerT[i],NULL);
    }
    
}

