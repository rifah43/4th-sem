#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 300000
#define LEFT (phnum-1+N)%N
#define RIGHT (phnum + 1) % N

int phil[N];

sem_t mutex;
sem_t chopStick[N];

void take_chopStick(int phnum)
{
    printf("%d is Hungry\n\n",phnum+1);
	sem_wait(&mutex);
	printf("Philosopher %d takes chopStick %d and %d while eating\n\n",phnum + 1, LEFT+1, phnum + 1);
	sem_post(&mutex);
}

void put_chopStick(int phnum)
{
	sem_wait(&mutex);
    printf("Philosopher %d leaving\n\n", phnum+1);
	sem_post(&mutex);
}

void* philosopher(void* num)
{
    int i =*(int*) num, k=0;

  while(1)
  {
    sem_wait(&chopStick[i]);
    sem_wait(&chopStick[(i+1)%N]);
    take_chopStick(i);
    sem_post(&chopStick[i]);
    sem_post(&chopStick[(i+1)%N]);
    k++;
    put_chopStick(i);
  }
}

int main()
{
	int i;
	pthread_t philThread[N];
	sem_init(&mutex, 0, 1);

	for (i = 0; i < N; i++)
    {
		sem_init(&chopStick[i], 0, 1);
    }
    for (i = 0; i < N; i++)
    {
		phil[i]=i;
    }
	for (i = 0; i < N; i++)
    {
		pthread_create(&philThread[i], NULL,philosopher, (void*) &phil[i]);
		printf("Philosopher %d is thinking\n\n", i + 1);
	}

	for (i = 0; i < N; i++)
    {
		pthread_join(philThread[i], NULL);
    }
}
