/*
* Programa para testar problema de sincronização e praticar o gerenciamento de threads com posix
* Problema clássico de sincronização
*   Cigarette Smokers Problem
*/

/* 
* Bibliotecas 
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>

/*
* Variáveis globais (compartilhadas por todas as threads)
*/
#define MAX 128

// Semáforos dos materiais e do agente que os produz
sem_t agentSem, tobacco, paper, matches;

// Semáforos dos fumantes que possuem tais materiais
sem_t tobaccoSem, paperSem, matchesSem;

// mutex para o pusher
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Variáveis compartilhadas que serão utilizadas pelos pushers para saber qual smoker será 'avisado'
int isTobacco = 0, isPaper = 0, isMatches = 0;

/*
* Agente  (age como 3 threads)
*/
// Agente A
void *providesTobaccoPaper(void *var) {
  while (1) {
    sem_wait(&agentSem);
    printf("Providenciando tabaco e papel\n");
    // dorme por até 3 segundos
    sleep(rand() % 3);
    sem_post(&tobacco);
    sem_post(&paper);
  }
  pthread_exit(NULL);
}

// Agente B
void *providesPaperMatches(void *var) {
  while (1) {
    sem_wait(&agentSem);
    printf("Providenciando papel e fósforos\n");
    sleep(rand() % 3);
    sem_post(&paper);
    sem_post(&matches);
  }
  pthread_exit(NULL);
}

// Agente C
void *providesTobaccoMatches(void *var) {
  while (1) {
    sem_wait(&agentSem);
    printf("Providenciando tabaco e fósforos\n");
    sleep(rand() % 3);
    sem_post(&tobacco);
    sem_post(&matches);
  }
  pthread_exit(NULL);
}

/*
* Threads auxiliares(pushers)
*/
// Quando há tabaco na mesa
void *pusherA(void *var){
  while (1) {
    sem_wait(&tobacco);
    printf("Pusher A: tabaco está na mesa!\n");
    pthread_mutex_lock(&mutex);
    if (isPaper) {
      isPaper = 0;
      sem_post(&matchesSem);
    } else if (isMatches) {
      isMatches = 0;
      sem_post(&paperSem);
    } else isTobacco = 1;
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
}

// Quando há papel na mesa
void *pusherB(void *var){
  while(1) {
    sem_wait(&paper);
    printf("Pusher B: papel está na mesa!\n");
    
    pthread_mutex_lock(&mutex);
    if(isTobacco){
      isTobacco = 0; 
      sem_post(&matchesSem);
    }
    else if(isMatches){
      isMatches = 0;
      sem_post(&tobaccoSem);
    }
    else isPaper = 1;
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
}

// Quando há fósforos na mesa
void *pusherC(void *var){
  while(1){
    sem_wait(&matches);
    printf("Pusher C: fósforos estão na mesa!\n");
    pthread_mutex_lock(&mutex);
    if(isTobacco){
      isTobacco = 0;
      sem_post(&paperSem);
    }
    else if(isPaper){
      isPaper = 0;
      sem_post(&tobaccoSem);
    }
    else isMatches = 1;
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
}

/*
* Funções lúdicas
*/
//produzindo o baseado
void produceCigarette() {
  printf("  Montando o baseado...\n");
  sleep(5);
}
//degustando o baseado
void smoking() {
  printf("  Brincando de linguagem de fumaça que nem índio... hehe\n\n");
  sleep(5);
}

/*
* Fumantes(consumidores)
*/
//Fumante com tabaco
void *smokerTobacco(void *var){
  while(1) {
    sem_wait(&tobaccoSem);
    printf("\n  Fumante com tabaco:");
    produceCigarette();
    smoking();
    sem_post(&agentSem);
  }
}

//Fumante com papel
void *smokerPaper(void *var) {
  while (1) {
    sem_wait(&paperSem);
    printf("\n  Fumante com papel:");
    produceCigarette();
    smoking();
    sem_post(&agentSem);
  }
  pthread_exit(NULL);
}

//Fumante com fósforos
void *smokerMatches(void *var){
  while(1){
    sem_wait(&matchesSem);
    printf("\n  Fumante com fósforos:");
    produceCigarette();
    smoking();
    sem_post(&agentSem);
  }
}

int main(void) {
  //threads do agente(produtor), dos pushers, e dos fumantes(consumidor)
  pthread_t th_agent_a, th_agent_b, th_agent_c;
  pthread_t th_pusher_a, th_pusher_b, th_pusher_c;
  pthread_t th_smoker_tobacco, th_smoker_paper, th_smoker_matches;

  char err_msg[MAX];

  //INICIALIZANDO OS SEMÁFOROS
  
  // Inicializa semáforo agentSem com valor 1
  if (sem_init(&agentSem, 0, 1)) {
    strerror_r(errno, err_msg, MAX);
    printf("Erro ao inicializar agentSem: %s\n", err_msg);
    exit(1);
  }
  
  // Inicializa semáforo tobacco com valor 0
  if (sem_init(&tobacco, 0, 0)) {
    strerror_r(errno, err_msg, MAX); 
    printf("Erro ao inicializar tobacco: %s\n", err_msg);
    exit(1);
  }
  // Inicializa semáforo paper com valor 0
  if (sem_init(&paper, 0, 0)) {
    strerror_r(errno, err_msg, MAX); 
    printf("Erro ao inicializar paper: %s\n", err_msg);
    exit(1);
  }
  // Inicializa semáforo matches com valor 0
  if (sem_init(&matches, 0, 0)) {
    strerror_r(errno, err_msg, MAX); 
    printf("Erro ao inicializar matches: %s\n", err_msg);
    exit(1);
  }
  
  // Inicializa semáforo tobaccoSem com valor 0
  if (sem_init(&tobaccoSem, 0, 0)) {
    strerror_r(errno, err_msg, MAX); 
    printf("Erro ao inicializar tobaccoSem: %s\n", err_msg);
    exit(1);
  }
  // Inicializa semáforo paperSem com valor 0
  if (sem_init(&paperSem, 0, 0)) {
    strerror_r(errno, err_msg, MAX); 
    printf("Erro ao inicializar paperSem: %s\n", err_msg);
    exit(1);
  }
  // Inicializa semáforo matchesSem com valor 0
  if (sem_init(&matchesSem, 0, 0)) {
    strerror_r(errno, err_msg, MAX); 
    printf("Erro ao inicializar matchesSem: %s\n", err_msg);
    exit(1);
  }

  //CRIANDO AS THREADS DOS AGENTES
  
  // Criando thread Agent A
  if (pthread_create(&th_agent_a, NULL, providesTobaccoPaper, NULL) != 0) {
    strerror_r(errno, err_msg, MAX);
    printf("Erro ao inicializar thread Agent A: %s\n", err_msg);
    exit(1);
  }
  // Criando thread Agent B
  if (pthread_create(&th_agent_b, NULL, providesPaperMatches, NULL) != 0) {
    strerror_r(errno, err_msg, MAX);
    printf("Erro ao inicializar thread Agent B: %s\n", err_msg);
    exit(1);
  }
  // Criando thread Agent C
  if (pthread_create(&th_agent_a, NULL, providesTobaccoMatches, NULL) != 0)   {
    strerror_r(errno, err_msg, MAX);
    printf("Erro ao inicializar thread Agent C: %s\n", err_msg);
    exit(1);
  }
  
  // Criando thread Pusher A
  if (pthread_create(&th_pusher_a, NULL, pusherA, NULL) != 0) {
    strerror_r(errno, err_msg, MAX);
    printf("Erro ao inicializar thread Pusher A: %s\n", err_msg);
    exit(1);
  }
  // Criando thread Pusher B
  if (pthread_create(&th_pusher_b, NULL, pusherB, NULL) != 0) {
    strerror_r(errno, err_msg, MAX);
    printf("Erro ao inicializar thread Pusher B: %s\n", err_msg);
    exit(1);
  }
  // Criando thread Pusher C
  if (pthread_create(&th_pusher_c, NULL, pusherC, NULL) != 0) {
    strerror_r(errno, err_msg, MAX);
    printf("Erro ao inicializar thread Pusher C: %s\n", err_msg);
    exit(1);
  }
  
  // CRIANDO THREADS FUMANTES
  
  // Criando thread Smoker Tobacco
  if (pthread_create(&th_smoker_tobacco, NULL, smokerTobacco, NULL) != 0) {
    strerror_r(errno, err_msg, MAX);
    printf("Erro ao inicializar thread Smoker Tobacco: %s\n", err_msg);
    exit(1);
  }
  // Criando thread Smoker Paper
  if (pthread_create(&th_smoker_paper, NULL, smokerPaper, NULL) != 0) {
    strerror_r(errno, err_msg, MAX);
    printf("Erro ao inicializar thread Smoker Paper: %s\n", err_msg);
    exit(1);
  }
  // Criando thread Smoker Matches
  if (pthread_create(&th_smoker_matches, NULL, smokerMatches, NULL)!= 0) {
    strerror_r(errno, err_msg, MAX);
    printf("Erro ao inicializar thread Smoker Matches: %s\n", err_msg);
    exit(1);
  }
  
  //A main deve aguardar algumas threads criadas antes de finalizar
  //pthread_join(th_agent_a, NULL);
  //pthread_join(th_agent_b, NULL);
  //pthread_join(th_agent_c, NULL);
  pthread_join(th_pusher_a, NULL);
  pthread_join(th_pusher_b, NULL);
  pthread_join(th_pusher_c, NULL);
  //pthread_join(th_smoker_tobacco, NULL);
  //pthread_join(th_smoker_paper, NULL);
  //pthread_join(th_smoker_matches, NULL);
  
  return 0;
}