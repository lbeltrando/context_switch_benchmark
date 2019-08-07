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

#include <sys/types.h>

#define nbThread 100000

void *thread() {
  pthread_exit(NULL);
}
int main()
{
  struct timespec start, end;
  pthread_t tid;

  int i;
  long s, ns, t;

  clock_gettime(CLOCK_MONOTONIC, &start);
  for(i = 0 ; i < nbThread ; i++) {
      if(pthread_create(&tid, NULL, thread, NULL))
        pthread_join(tid, NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    s = end.tv_sec - start.tv_sec;
    ns = end.tv_nsec - start.tv_nsec;
    if(ns < 0) {
      ns += 1000000000ULL;
      s--;
    }
    t = (1000000000ULL*s + ns) / nbThread;
    s = t / 1000000000ULL;
    ns = t % 1000000000ULL;
    if(s > 0)
      printf("Le temps d'ouverture, fermeture et notification d'une thread est de %ld secondes et %ld nanosecondes\n",s, ns);
    else
      printf("Le temps d'ouverture, fermeture et notification d'une thread est de %ld microsecondes (%ld nanosecondes)\n", ns/1000, ns);
  return 0;
}
