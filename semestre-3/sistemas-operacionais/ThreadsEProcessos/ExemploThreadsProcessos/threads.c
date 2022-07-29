#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

//função de será executada pela thread
void *exec(void *var) {
  printf("Thread %ld\n", pthread_self());
  return NULL;
}
 
static int cont = 0;
 
int main() {
  struct timespec tInicio, tFinal;
 
  pthread_t th;
 
  clock_gettime(CLOCK_REALTIME, &tInicio);
  while (pthread_create(&th, NULL, exec, NULL) == 0) {
    cont++;
    printf("Criando thread..%d\n", cont);
    //printf("Criando thread... %d, %ld\n", cont, pthread_self());
  }
  clock_gettime(CLOCK_REALTIME, &tFinal);
 
  float tempo = (tFinal.tv_sec + tFinal.tv_nsec/10e9) - (tInicio.tv_sec + tInicio.tv_nsec/10e9);
 
  printf("O tempo decorrido para criação das threads em segundos: %lf\n", tempo);
 
  printf("Threads criadas: %d\n", cont);
  printf("ERRNO: %d\n", errno);
  return 0;
}
