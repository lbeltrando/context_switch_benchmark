/*
* Lionel Beltrando TP3
*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#include <sys/types.h>

#define nbProcessus 100000

int main()
{
  struct timespec start, end;
  pid_t pid;

  int i;
  long s, ns, t;

  clock_gettime(CLOCK_MONOTONIC, &start);
  for(i = 0 ; i < nbProcessus ; i++) {
    pid = fork();
    //printf("PID : %d\n", pid);
    wait(NULL);
    if(pid == 0)
      exit(0);
    }
  //wait(NULL);
  clock_gettime(CLOCK_MONOTONIC, &end);
  s = end.tv_sec - start.tv_sec;
  ns = end.tv_nsec - start.tv_nsec;
  if(ns < 0) {
    ns += 1000000000ULL;
    s--;
  }
  long sfor, nsfor;
  clock_gettime(CLOCK_MONOTONIC, &start);
  for(i = 0 ; i < nbProcessus; i++);
  clock_gettime(CLOCK_MONOTONIC, &end);
  sfor = end.tv_sec - start.tv_sec;
  nsfor = end.tv_nsec - start.tv_nsec;
  if(nsfor < 0) {
    nsfor += 1000000000ULL;
    sfor--;
  }
  t = (1000000000ULL*(s-sfor) + (ns-nsfor)) / nbProcessus;
  s = t / 1000000000ULL;
  ns = t % 1000000000ULL;
  if(s > 0)
    printf("Le temps d'ouverture, fermeture et notification d'un processus est de %ld secondes et %ld nanosecondes\n",s, ns);
  else
    printf("Le temps d'ouverture, fermeture et notification d'un processus est de %ld microsecondes (%ld nanosecondes)\n", ns/1000, ns);
  return 0;
}
