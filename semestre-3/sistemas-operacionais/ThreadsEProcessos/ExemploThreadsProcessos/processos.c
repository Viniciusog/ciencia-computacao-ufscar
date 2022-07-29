#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

int main() {

  int result;  
  int qtd = 0;
  int status;
  struct timespec tInicio, tFinal;

  if (clock_gettime(CLOCK_REALTIME, &tInicio) < 0)
    printf("Erro em clock_gettime. Inicio\n");

  while (result != -1) {
    result = fork();
    qtd++;
    
    if (result == -1) {
      printf("Erro ao criar processo.\n");
      break;
    } 
    // Processo filho
    else if (result == 0) {
      printf("Processo %d foi criado. PID: %d\n", qtd, getpid());
      // Espera 20 segundos para acumular processos
      sleep(20);
      // Remove as áreas de memória e deixa somente a tas_struct dos processos
      exit(0);
    }
  }

  if (clock_gettime(CLOCK_REALTIME, &tFinal) < 0)
    printf("Erro em clock_gettime. Fim\n");
  // Agora irá esperar para que todos os processos sejam finalizados (kill)
  wait(&status);
  
  printf("Processos criados: %d\n", qtd);
  float tempo = (tFinal.tv_sec + tFinal.tv_nsec/10e9) - (tInicio.tv_sec + tInicio.tv_nsec/10e9);
  printf("TEMPO: %lf segundos\n", tempo);
  printf("ERRNO: %d\n", errno);
  
  if (errno == 11) {
    printf("ERRNO: Uma tentativa para criar um novo processo falhou pois não existem mais espaços disponíveis para processos, ou não há memória necessária, ou o nível máximo de aninhamento foi alcançado.\n");
  }
}