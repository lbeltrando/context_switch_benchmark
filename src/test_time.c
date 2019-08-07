/*
* Lionel Beltrando TP3
*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define precision 10000000ULL
#define useGettimeofday 1
#define use

int main()
{
  struct timespec start, end;
  long s, ns;
  long smin, nsmin;
  int i;
  int first = 0;
  for(i = 0 ; i < precision ; i++) {
    clock_gettime(CLOCK_MONOTONIC, &start);
    clock_gettime(CLOCK_MONOTONIC, &end);
    s = end.tv_sec - start.tv_sec;
    ns = end.tv_nsec - start.tv_nsec;
    if(ns < 0) {
      ns += 1000000000ULL;
      s--;
    }
    if(s >= 0 && ns > 0 && first == 0) {
        smin = s;
        nsmin = ns;
        first = 1;
    }
    if(s >= 0 && ns > 0 && first == 1) {
      if(s < smin || (s == smin && ns < nsmin)) {
        smin = s;
        nsmin = ns;
      }
    }
  }
  long sfor, nsfor;
  clock_gettime(CLOCK_MONOTONIC, &start);
  for(i = 0 ; i < precision ; i++);
  clock_gettime(CLOCK_MONOTONIC, &end);
  sfor = end.tv_sec - start.tv_sec;
  nsfor = end.tv_nsec - start.tv_nsec;
  if(nsfor < 0) {
    nsfor += 1000000000ULL;
    sfor--;
  }
  printf("La difference de temps minimale non nulle mesure avec clock_gettime est de %ld microsecondes (%ld nanosecondes)\n", ns/1000 + (ns%1000 < 500 ? 0 : 1), ns);
  printf("Temps d'éxécution d'une boucle for qui ne fait rien %llu de fois : %ld secondes et %ld microsecondes (%ld nanosecondes)\n", precision, sfor, nsfor/1000 + (nsfor%1000 < 500 ? 0 : 1), nsfor);
  return 0;
}
