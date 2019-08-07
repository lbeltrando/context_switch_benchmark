/*
* Lionel Beltrando TP3
*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h>

#include <sys/types.h>

#define nbContext 1000000

int main()
{
  struct timespec *start, *end;
  long s, ns, t;

  sem_t *sem1, *sem2;
  sem1 = (sem_t*) mmap(NULL, sizeof(sem1), PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  sem2 = (sem_t*) mmap(NULL, sizeof(sem1), PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  start = (struct timespec*) mmap(NULL, sizeof(start), PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  end = (struct timespec*) mmap(NULL, sizeof(end), PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  sem_init(sem1, 1, 1); // Vaut 1
  sem_init(sem2, 1, 0); // Vaut 0
  start = (struct timespec *)malloc(sizeof(struct timespec));
  end = (struct timespec *)malloc(sizeof(struct timespec));

  pid_t pid = fork();
  //Processus fils
  if(pid == 0) {
    int i;
    for(i = 0 ; i < nbContext ; i++) {
      //printf("pid : %d\n", pid);
      sem_wait(sem1);
      sem_post(sem2);
    }
    exit(0);
  }
  //Processus pere
  else {
    int i;
    clock_gettime(CLOCK_MONOTONIC, start);
    for(i = 0 ; i < nbContext ; i++) {
      //printf("pid : %d\n", pid);
      sem_wait(sem2);
      sem_post(sem1);
    }
    clock_gettime(CLOCK_MONOTONIC, end);

  s = end->tv_sec - start->tv_sec;
  ns = end->tv_nsec - start->tv_nsec;
  if(ns < 0) {
    ns += 1000000000ULL;
    s--;
  }
  //On divise par deux fois nbContext car on a eu 2*nbContext changements de contexte
  t = (1000000000ULL*s + ns) / (2*nbContext);
  s = t / 1000000000ULL;
  ns = t % 1000000000ULL;

  if(waitpid(pid, NULL, WUNTRACED) == -1)
    exit(EXIT_FAILURE);
}
  if(s > 0)
    printf("Le temps d'un changement de contexte entre des processus est de %ld secondes et %ld nanosecondes\n", s,ns);
  else
    printf("Le temps d'un changement de contexte entre des processus est de %ld microsecondes (%ld nanosecondes)\n", ns/1000 + (ns%1000 < 500 ? 0 : 1), ns);

  return 0;
}
