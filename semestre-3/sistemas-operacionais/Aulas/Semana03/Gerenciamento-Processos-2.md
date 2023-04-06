# Gerenciamento de processos 2
## Professor: Hélio Crestana Guardia
## Universidade Federal de São Carlos
---

## Prioridades e escalonamento

**Prioridades estáticas**

Na seleção de tarefas para execução, também é preciso que o escalonador respeite suas prioridades. O padrão POSIX, por exemplo, define um valor de prioridade estática associado aos processos, chamado de  valor de nice. Esse valor varia de -20 a 19, com maior prioridade associada aos valores menores (prio -20 > pro -19 > ... prio 0 > prio 1 > ... > prio 19). Tipicamente, processos têm valor de  nice 0, o que corresponde à prioridade intermediária, atribuída por padrão aos processos. 

E qual é a influência das prioridades estáticas (valor de nice, nesse caso) dos processos? É de se esperar que o escalonador do sistema operacional atribua o uso da(s) CPU(s) com maior frequência e/ou por mais tempo para os processos mais prioritários. 

Por padrão, processos iniciados via shell têm valor de nice igual a 0, mas esse valor pode ser determinado pelo usuário. Usando o comando nice, é possível especificar a prioridade do processo sendo iniciado, como ilustrado a seguir:

`$ proc_normal & `
`$ nice -n 10 proc_demorado &`

Nesse caso, o processo chamado proc_normal vai ser executado com valor de nice padrão, igual a 0. Já o processo proc_demorado vai ser executado com nível de nice 10, menos prioritário que o padrão.

Também é possível modificar a prioridade estática (nível de nice) de um processo já em execução. Isso é feito com o comando renice, ilustrado a seguir:

`$ renice -n 19 -p 1024`
Nesse caso, se o usuário atual tiver permissão sobre o processo de pid 1024, sua prioridade estática será ajustada para o valor 19, que é o menor valor possível.

Mas como será que os programas nice e renice fazem para ajustar as prioridades estáticas dos processos? Em ambos os casos, nice e renice, esses programas utilitários vão realizar chamadas às syscalls nice(2) setpriority(2), que permitem ajustar a prioridade estática de processos e grupos de processos.

A chamada de sistema nice é bem simples e serve apenas para somar um valor à prioridade estática do processo corrente:

int nice(int inc);
Já a chamada setpriority permite especificar diretamente o pid do processo cuja prioridade se deseja alterar e o novo valor da prioridade (-20...19).

int getpriority(int which, id_t who);
int setpriority(int which, id_t who, int prio);
Um aspecto a ressaltar aqui é a questão das permissões. Um usuário só pode ajustar a prioridade de seus próprios processos, ou seja, daqueles  que têm o seu uid associado. Além disso, apenas o usuário root e usuários que têm uma permissão específica (CAP_SYS_NICE, e.g.) podem atribuir valores de prioridade estática entre -20 e -1. Aos demais usuários, só é possível atribuir valores positivos (prioridades menores) e sempre valores que incrementam a prioridade.


**Políticas de escalonamento**

Além de tratar de valores de prioridade estática, diferentes algoritmos de escalonamento podem ser implementados por um SO. O padrão POSIX, por exemplo, especifica as seguintes políticas para processos que não possuem restrições de tempo real:

>SCHED_OTHER the standard round-robin time-sharing policy;
SCHED_BATCH for "batch" style execution of processes; and
SCHED_IDLE for running very low priority background jobs.

Para processos de tempo real, há ainda duas outras políticas:

>SCHED_FIFO a first-in, first-out policy; and
SCHED_RR a round-robin policy.

Alguns atributos mantidos pelo SO para cada processo ou thread permitem ajustar seus escalonamentos. Embora a política de escalonamento SCHED_OTHER seja associada por padrão a todo processo, a função sched_setcheduler(2), por exemplo, permite alterar a política de escalonamento. Vale observar, contudo, que é preciso privilégio de super usuário para alterar a política de escalonamento para SCHED_FIFO ou SCHED_RR, que conferem propriedades de suporte a tempo real a um processo. A chamada sched_getscheduler(2) permite consultar parâmetros do escalonamento de um processo. 

Além da diferença na política de escalonamento, também é possível alterar atributos associados às prioridades dos processos e threads.  A mesma chamada sched_setscheduler permite definir atributos de prioridade, ou pode-se também fazer isso usando as funções sched_getparam(2) / sched_setparam(2). Atualmente, apenas um valor, que caracteriza a prioridade de tempo real de um processo ou thread é definido.

Bons estudos,

Hélio

O que é preciso saber com esta unidade:

- conhecer o conceito de prioridade estática e chamadas de sistema para seus ajustes
- conhecer as políticas de escalonamento de processos
- conhecer as chamadas de sistema para ajuste da política de escalonamento e do valor de prioridade de tempo real

--- 
## Afinidade de CPUs

Cabe ao SO gerenciar de maneira eficiente o uso dos processadores existentes. Isso significa expandir suas estratégias de escalonamento para todos os processadores, procurando mantê-los todos ocupados, quando há carga, e maximizando o desempenho das aplicações. 

Para tanto, é comum que sejam mantidas filas (ou outro mecanismo de organização, como árvores) de threads prontas separadas para cada processador. Por um lado, isso significa que as threads ativas tendem a ser executadas no mesmo processador, aumentando a eficiência do cache. Por outro lado, cabe ao SO evitar desbalanceamentos nas cargas dos processadores, movendo processos entre as filas quando necessário para manter as filas equilibradas.

Originalmente, todo processo ou thread está apto a ser executado em qualquer processador disponível. É possível, contudo, tratar explicitamente a afinidade de threads a processadores, criando um balanceamento de carga definido pela aplicação. Isso é feito através de uma máscara de afinidade de CPU, que define em quais processadores um processo ou thread pode ser executado.

`int sched_setaffinity (pid_t pid, size_t cpusetsize, const cpu_set_t *mask);`

A syscall `sched_setaffinity` define os processadores em que um processo pode executar. A identificação dos processadores é feita na forma de um bitmap passado como parâmetro da chamada.

Com esta chamada, um programador pode, por exemplo, deixar threads executando de maneira exclusiva em processadores específicos.

De maneira geral, contudo, espera-se que o SO já seja capaz de manter todos os processadores ocupados de maneira balanceada e justa. 

---
## Consumo de recursos

O SO aloca recursos para a execução de cada tarefa, mas mantém registros das contabilizações de uso desses recursos. Assim, toda vez que uma CPU é redirecionada da execução de uma tarefa para o SO, o SO contabiliza quanto tempo esta tarefa passou (na CPU) tendo suas instruções executadas (user time).

O tempo gasto pelo SO prestando serviço para um processo também é contabilizado (system time). Ambos os valores (utime e stime) são salvos de maneira incremental no descritor da tarefa. 

Informações sobre o tamanho máximo ocupado na memória e sobre o consumo de outros recursos também são mantidas pelo SO. 

Todos os parâmetros contabilizados pelo SO para uma tarefa podem ser consultados usando a chamada de sistema getrusage(2). Na chamada, pode-se solicitar valores do processo atual (RUSAGE_SELF), dos seus processos filhos (RUSAGE_CHILDREN) ou da thread corrente (RUSAGE_THREAD). 

O retorno da chamada é uma estrutura rusage, ilustrada a seguir:

```
struct rusage {
   struct timeval ru_utime; /* user time used */
   struct timeval ru_stime; /* system time used */
   long ru_maxrss; /* max resident set size */
   long ru_ixrss; /* integral shared text memory size */
   long ru_idrss; /* integral unshared data size */
   long ru_isrss; /* integral unshared stack size */
   long ru_minflt; /* page reclaims */
   long ru_majflt; /* page faults */
   long ru_nswap; /* swaps */
   long ru_inblock; /* block input operations */
   long ru_oublock; /* block output operations */
   long ru_msgsnd; /* messages sent */
   long ru_msgrcv; /* messages received */
   long ru_nsignals; /* signals received */
   long ru_nvcsw; /* voluntary context switches */
   long ru_nivcsw; /* involuntary context switches */
};
```

Mas para que serve saber do consumo de recursos por uma tarefa?

A chamada getrusage pode ser usada, por exemplo, por um programa como o utilitário time, que exibe o tempo gasto na execução de um processo [embora time parece fazer isso usando a chamada de sistema wait4()].

Pensando num programa que deseje determinar seu consumo de recursos, total ou em um trecho de código, isto é possível usando as chamadas gettimeofday(2) (ou clock_gettime(2)) e getrusage(2). 

Vejamos um exemplo de código com medição de tempo:

```
struct timeval inic,fim;
struct rusage r1, r2;

// determina o instante atual (gettimeofday)
// int gettimeofday(struct timeval *tv, struct timezone *tz);
gettimeofday(&inic, 0);

// determina quanto foi consumido de recursos até aqui (getrusage)
getrusage(RUSAGE_SELF, &r1);

// aqui entra a função cujo tempo se quer avaliar

// determina o instante atual (gettimeofday)
gettimeofday(&fim,0);

// determina quanto foi consumido de recursos até aqui (getrusage)
getrusage(RUSAGE_SELF, &r2);

// diferença entre r2 e r1 (ru_utime e ru_stime) indica consumo de recursos para o trecho de código
// diferença entre fim e inic inica o tempo decorrido (elapsed time)
```

**Limites para o uso de recursos**

Além de contabilizar o consumo de recursos pelas tarefas, o SO também oferece mecanismos para limitar esse consumo. Uma vez estabelecidos limites para um processo, isso vale para ele e para seus descendentes. 

Ao interagir com o shell, por exemplo, é possível fazer certos ajustes que definam os valores máximos que vão ser atribuídos aos processos que o shell criar nessa sessão de uso. Por padrão, o programa shell mantém informações sobre os limites no consumo de recursos e ajusta esses valores nos pedidos de criação de novos processos.

A consulta e o ajuste de limites no shell podem ser feitos com o comando interno (builtin) ulimit.

```
$ man bash
/ulimit
ulimit [-SHacdefilmnpqrstuvx [limit]]
Provides control over the resources available to the shell and to processes started by it, on  systems  that  allow  such  control.  
...
If limit is omitted, the current value of the soft limit of the resource is printed...
Other options are interpreted as follows:
 -a     All current limits are reported
...
 -d     The maximum size of a process's data segment
 -i      The maximum number of pending signals
 -m    The maximum resident set size
 -n     The maximum number of open file descriptors (most systems do not allow this value to be set)
 -t     The maximum amount of cpu time in seconds
 -u    The maximum number of processes available to a single user
...
```

 Efetivamente, o ajuste feito pelo shell, e que pode ser realizado por qualquer processo, é feito com a chamada setrlimit(2). Valores vigentes podem ser consultados com getrlimit(2). Parâmetros que podem ser restringidos incluem:

>RLIMIT_AS, RLIMIT_CORE, RLIMIT_CPU, RLIMIT_DATA, RLIMIT_FSIZE, RLIMIT_LOCKS, RLIMIT_MEMLOCK, RLIMIT_MSGQUEUE, RLIMIT_NICE, RLIMIT_NOFILE, RLIMIT_NPROC, RLIMIT_RSS, RLIMIT_RTPRIO, RLIMIT_RTTIME, RLIMIT_RTTIME, RLIMIT_STACK

Para cada um desses valores, é possível estabelecer limites. O limite hard é usado pelo administrador para estabelecer um teto máximo para o limite de consumo de um recurso. Já o limite soft é um valor estabelecido por um processo para o consumo de recursos realizado por ele e por seus processos descendentes.

Aparentemente, estudar também tem limite, mas o tempo máximo é bem grande :-)

Bons estudos,

Hélio

O que é preciso saber com esta unidade:

- conhecer as chamadas de sistema para consulta do consumo de recursos pelos processos
- conhecer os recursos consumidos por processos que são contabilizados pelo kernel
- conhecer elapsed time, system time e user time e saber como obtê-los num programa
- conhecer formas de monitorar o consumo de recursos
saber como limitar o consumo de recursos
- conhecer  recursos cujo consumo pode ser limitado pelo SO

---
## Tratamento de sinais

Sinais são um mecanismo de notificação para processos, comumente associados a eventos ocorridos durante suas execuções. Sinais também podem ser enviados a um grupo de processos em decorrência de uma combinação de teclas pressionadas por um usuário do terminal. Ainda é possível enviar sinais de forma explícita, através da chamada de sistema kill(2), realizada por outro processo do mesmo usuário ou do usuário root.

De acordo com padrões POSIX, há 2 grupos de sinais: reliable signals (que são os sinais normais) e real-time signals. Os sinais normais estão associados a eventos pré-definidos e têm números associados de 1 a 31, enquanto os sinais de tempo real, com valores definidos pelas macros SIGRTMIN (33) e SIGRTMAX (64), podem ser gerados de acordo com a lógica do programa que os utiliza.

Alguns dos sinais normais, com seus números, nomes, ações default e eventos que os geram são listados a seguir:

```
No    Name         Default Action       Description
 1    SIGHUP       terminate process    terminal line hangup
 2    SIGINT       terminate process    interrupt program
 3    SIGQUIT      create core image    quit program
 4    SIGILL       create core image    illegal instruction
 5    SIGTRAP      create core image    trace trap
 6    SIGABRT      create core image    abort program (formerly SIGIOT)
 7    SIGEMT       create core image    emulate instruction executed
 8    SIGFPE       create core image    floating-point exception
 9    SIGKILL      terminate process    kill program
10    SIGBUS       create core image    bus error
11    SIGSEGV      create core image    segmentation violation
12    SIGSYS       create core image    non-existent system call invoked
13    SIGPIPE      terminate process    write on a pipe with no reader
14    SIGALRM      terminate process    real-time timer expired
15    SIGTERM      terminate process    software termination signal
16    SIGURG       discard signal       urgent condition present on socket
17    SIGSTOP      stop process         stop (cannot be caught or ignored)
18    SIGTSTP      stop process         stop signal generated from keyboard
19    SIGCONT      discard signal       continue after stop
20    SIGCHLD      discard signal       child status has changed
21    SIGTTIN      stop process         background read attempted from control terminal
22    SIGTTOU      stop process         background write attempted to control terminal
23    SIGIO        discard signal       I/O is possible on a descriptor (see fcntl(2))
24    SIGXCPU      terminate process    cpu time limit exceeded (see setrlimit(2))
25    SIGXFSZ      terminate process    file size limit exceeded (see setrlimit(2))
26    SIGVTALRM    terminate process    virtual time alarm (see setitimer(2))
27    SIGPROF      terminate process    profiling timer alarm (see setitimer(2))
28    SIGWINCH     discard signal       Window size change
29    SIGINFO      discard signal       status request from keyboard
30    SIGUSR1      terminate process    User defined signal 1
31    SIGUSR2      terminate process    User defined signal 2
```

Para poder tratar o envio e o recebimento de sinais, o SO mantém estruturas de dados de controle de sinais para cada processo. Essas estruturas permitem que um processo ignore o recebimento de um sinal específico, que seja instalada uma rotina de tratamento para um sinal, ou que o recebimento de um sinal seja bloqueado. Apenas os sinais SIGKILL e SIGSTOP não podem ser capturados, ignorados ou bloqueados por um processo. 

Sinais que não são tratados explicitamente por um processo têm ações pré-definidas pelo SO, caso ocorram. Dependendo do sinal, essas ações podem significar terminar a execução do processo, terminar a execução e gerar um arquivo com a imagem do processo na memória (core dump), parar ou continuar a execução do processo, ou simplesmente ignorar o sinal. As ações padrão podem ser vistas na 3a coluna da tabela acima. 

Ainda de acordo com padrões POSIX, threads de um processo compartilham o tratamento de sinais do processo ao qual estão associadas, mas cada uma pode ter sua própria máscara de recebimento de sinais.

Além de receber sinais em função da ocorrência de certos eventos, um processo pode receber sinais enviados explicitamente através da chamada de sistema kill(). Essa chamada permite especificar o PID de um processo, ou a identificação de um grupo de processos, para o qual se deseja enviar um sinal. Na programação com threads POSIX é possível ainda enviar sinais para threads específicas de um processo, usando a função C pthread_kill(3) que, no Linux, é implementada sobre a chamada de sistema (Linux specific) tgkill(2).

Já a função raise(3) permite enviar um sinal para a thread corrente. Para o envio de sinais de tempo real para as threads do processo atual, com dados associados, é possível usar a função sigqueue(3).

Também é possível bloquear a execução da thread (ou processo) corrente à espera de um sinal. A chamada de sistema pause(2) bloqueia o processo (ou a thread) atual à espera do recebimento de algum sinal. O mesmo ocorre com a chamada sigsuspend(2), que permite esperar pelo recebimento de um sinal ao mesmo tempo em que uma máscara temporária bloqueia sinais não desejados. 

Sinais normais (reliable) não são cumulativos, de forma que pode haver apenas uma pendência de cada sinal. Para sinais de tempo real pode haver várias ocorrências pendentes.

A entrega de um sinal para um processo depende de encontrar o descritor do processo indicado na chamada kill. Encontrada a estrutura nas listas de tarefas, o SO verifica a permissão de envio do sinal, que depende de ser um processo do mesmo usuário. 

Mas, na prática, como e quando uma tarefa recebe um sinal que lhe foi enviado?

O recebimento efetivo de um sinal (signal delivery) ocorre quando o processo já teve seu contexto restaurado depois de ter sido selecionado para execução pelo escalonador. Isso significa que 

Isso ocorre porque é preciso ajustar o contexto do processo alvo, restaurando sua tabela de páginas e ponteiros de código e pilha, além de retornar o processador ao user mode antes de executar uma rotina de tratamento associada. Assim, exceto pelos sinais SIGKILL e SIGSTOP, que têm tratamento imediato no envio, os demais sinais, que não foram ignorados por um processo, apenas são marcados como pendentes no envio. O tratamento apropriado vai ocorrer apenas quando o processo voltar à execução, com contexto restaurado, mas antes de retomar as atividades interrompidas.

O recebimento de um sinal também pode acordar um processo bloqueado em condições específicas, recolocando-o na fila de processos prontos. 

De maneira geral, uma rotina de tratamento de sinais deve ser breve e é preciso cautela na escolha das funções usadas nesse código. Como a entrega de sinais é assíncrona, é possível haver reentrância de código usado na função de tratamento com outras atividades sendo realizadas no fluxo normal de execução do processo e de suas threads. Assim, há preocupação com reentrância de código e com segurança devido ao sincronismo (asynchronous safety). O código de tratamento de um sinal deve poder ser interrompido a qualquer momento sem causar estados inconsistentes no processo.

Bons estudos,

Hélio

O que é preciso saber com esta unidade:

- conhecer o que são sinais
- conhecer os sinais pré-definidos e as situações em que eles são enviados
- conhecer os sinais associados a combinações de teclas no terminal (ctrl c, ctrl z, ctrl s, ctrl q, ctrl /)
- conhecer os sinais associados a exceções (divisão por zero, acesso ilegal de memória, operação ilegal, ...)
- conhecer os sinais associados a operações de entrada e saída de dados (escrita em pipe sem leitor, E/S pronta, leitura e escrita em background, dados urgentes em socket)
- conhecer os sinais associados à parada e à continuidade da execução de um processo (sigtstp, sigstop, sigcont)
- conhecer o sinal associado a eventos de temporização (sigalarm)
- conhecer o sinal associado à mudança de estado de processo filho (sigchld) ou do líder do grupo de processos (sighup)
- conhecer sinais reservados para sincronizações entre processos (sigusr1 e sigusr2)
- conhecer chamadas de sistema para ignorar, capturar e bloquear o recebimento de sinais (signal(), sigaction(), sigprocmask())
- conhecer estruturas de dados usadas pelo SO para o controle de sinais nos processos

---
## Tratando e enviando sinais

Como vimos, sinais são usados pelo SO para a notificação de eventos pré-definidos aos processos. Para todos os sinais há ações padrão definidas, como o término, a parada ou a continuidade da execução do processo que o recebe.

Quase todos os sinais, exceto por SIGKILL e SIGSTOP, podem ser ignorados, capturados e bloqueados pelos processos. Para tanto, o SO mantém alguma estrutura interna associada ao descritor do processo, indicando o tratamento de cada sinal.

Vejamos algumas syscalls relacionadas ao tratamento e ao envio de sinais.

**1. Signal: usada para ignorar um sinal ou para instalar uma rotina de tratamento**

sighandler_t signal (int signum, sighandler_t handler);
A função de tratamento deve seguir a seguinte estrutura:

`typedef void (*sighandler_t)(int);`

Em uso:

```c
#include <signal.h>

void term_hand(int signo)
{
  printf("Signal %d recebido\n",signo);
}

int main()
{
  ...
  // instalando rotina para tratar o sinal SIGTERM
  if(signal(SIGTERM, term_hand)==SIG_ERR) {
    perror("Erro capturando tratamento do sinal");
    return(0);
  }
  // ignorando o sinal SINGINT
  if(signal(SIGINT,SIG_IGN)==SIG_ERR)
    perror("Erro ignorando SIGINT");
  ...
  for(;;);
  ...
  return 0;
}
```

O que será que vai acontecer com esse processo se for digitado <*ctrl*><*C*> durante sua execução?

E se for usado o comando kill para enviar um sinal padrão (15) para o pid deste processo?

**2. Sigaction: usada para tratar ou ignorar um sinal**

`int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`

Sigaction provê as mesmas funcionalidades de signal, mas ainda permite bloquear o recebimento de sinais durante a execução da rotina de tratamento. Também permite salvar o estado anterior do tratamento como retorno da chamada. 

```
void tstp_hand(int signo)
{
  printf("Sinal %d recebido.\n", signo);
}

int
main(int argc, char **argv)
{
  struct sigaction actor;
  // instala rotina de tratamento do sinal SIGTSTP (enviado por <ctrl><z>
  actor.sa_handler = int_hand;  // identifica a rotina de tratamento
  sigemptyset(&actor.sa_mask);  // "zera" máscara de sinais que serão 
                                // bloqueados durante a execução da rotina de tratamento
  actor.sa_flags = SA_RESTART;  // flags opcionais: neste caso, para restaurar a rotina após cada ocorrência do sinal

  if(sigaction(SIGTSTP, &actor, NULL) == -1)
    printf("Erro na captura do signal\n"); 
  ...
}
```

**3. Kill: envio de sinal para processo definido pelo seu pid**

int kill(pid_t pid, int sig);
No caso a seguir, pode-se observar o efeito dos sinais SIGTOP, SIGCONT e SIGKILL.

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
   pid_t pid;
   int cont = 0;

   if((pid=fork())==-1) {
      printf("Erro na execucao do fork\n");
      return 0;
   }
   if(pid==0) { // filho 
      while(1) { // Até ser interrompido...
         printf("%d ",++cont);
         fflush(stdout);  // apenas para forçar a exibição no terminal
         sleep(1);
      }
   }else { // pai 
      sleep(5);
      kill(pid, SIGSTOP);  // Qual é o efeito?
      sleep(5);
      kill(pid, SIGCONT);  // Qual é o efeito?
      sleep(5);
      kill(pid, SIGTERM);  // Qual é o efeito?
   }

   return 0;
}
```

**3. Outros sinais de interese**

Considerando a lista de sinais apresentada a seguir, quais usos será que podem ser feitos com os seus tratamentos?!

O que acontece quando a janela de um programa é fechada?

```
1     SIGHUP       terminate process    terminal line hangup

Será que o programa poderia terminar de maneira ordenada se o usuário digitar <ctrl><c>?

2     SIGINT       terminate process    interrupt program

**Alguém já usou o comando assert?**

6     SIGABRT      create core image    abort program (formerly SIGIOT)
```

Puxa, vejam essas exceções! Será que dá para evitar um "segmentation fault, core dumped" se esquecermos do malloc?!

```
4     SIGILL       create core image    illegal instruction
8     SIGFPE       create core image    floating-point exception
10    SIGBUS       create core image    bus error
11    SIGSEGV      create core image    segmentation violation
```

É possível gerar uma syscall inexistente? Viram o comando syscall do Linux?
```
12    SIGSYS       create core image    non-existent system call invoked
```

Seria útil programar um timer para daqui há um tempinho, e ter uma rotina executada automaticamente depois desse tempo!

```
14    SIGALRM      terminate process    real-time timer expired
26    SIGVTALRM    terminate process    virtual time alarm (see setitimer(2))

Novamente, que bom terminar de maneira ordenada no recebimento de um sinal padrão...

15    SIGTERM      terminate process    software termination signal

Vejam, é possível receber uma notificação quando um processo filho termina!

20    SIGCHLD      discard signal       child status has changed
```
Pensando em entrada e saída, pode ser legal fazer um programa não bloqueante, que é avisado 
quando há dados prontos para ler, ou se já é possível escrever...

```
21    SIGTTIN      stop process         background read attempted from control terminal
22    SIGTTOU      stop process         background write attempted to control terminal

23    SIGIO        discard signal       I/O is possible on a descriptor (see fcntl(2))

Vejam, há 2 sinais que os processos podem usar como quiserem em suas sincronizações!

30    SIGUSR1      terminate process    User defined signal 1
31    SIGUSR2      terminate process    User defined signal 2
```

E aí? Sinais são um mecanismo poderoso!

Faz sentido? Bons estudos, e bons tratamentos de sinais!

Hélio