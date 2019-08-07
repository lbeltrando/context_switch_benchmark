/*
* Lionel Beltrando TP3
*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define nbThread 1000000
/*
struct timeval start, end;
long long unsigned int s,ms;
*/
struct timespec start, end;
long s,ns; // secondes et nanosecondes
sem_t sem1, sem2;

/*C'est le thread1 qui va calculer le temps*/
void *thread1()
{
  int i;
  long t;
  clock_gettime(CLOCK_MONOTONIC, &start);
  for(i = 0 ; i < nbThread ; i++) {
    sem_wait(&sem1);
    sem_post(&sem2);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  s = end.tv_sec - start.tv_sec;
  ns = end.tv_nsec - start.tv_nsec;
  if(ns < 0) {
    ns += 1000000000ULL;
    s--;
  }
  t = (1000000000ULL*s + ns) / (2*nbThread);
  s = t / 1000000000ULL;
  ns = t % 1000000000ULL;
  pthread_exit(NULL);
}

void *thread2()
{
  int i;
  for(i = 0 ; i < nbThread ; i++) {
    sem_wait(&sem2);
    sem_post(&sem1);
  }

  pthread_exit(NULL);
}

int main()
{
  sem_init(&sem1, 0, 1); // Vaut 1
  sem_init(&sem2, 0, 0); // Vaut 0
  pthread_t t1, t2;

  if (pthread_create(&t1, NULL, thread1, NULL)) {
		perror("pthread_create");
		return 1;
	}
	if (pthread_create(&t2, NULL, thread2, NULL)) {
		perror("pthread_create");
		return 1;
	}
	if (pthread_join(t1, NULL)) {
		perror("pthread_join");
		return 1;
	}
	if (pthread_join(t2, NULL)) {
		perror("pthread_join");
		return 1;
	}
  printf("Precision de la mesure avec clock_gettime : \n");
  if(s > 0)
    printf("Le temps d'un changement de contexte entre des thread est de %ld secondes et %ld nanosecondes\n", s,ns);
  else
    printf("Le temps d'un changement de contexte entre des thread est de %ld microsecondes (%ld nanosecondes)\n", ns/1000 + (ns%1000 < 500 ? 0 : 1), ns);
  return 0;
}
