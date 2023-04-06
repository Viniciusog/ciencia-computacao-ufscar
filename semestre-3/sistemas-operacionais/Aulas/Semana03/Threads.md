# Syscalls
## Professor: Hélio Crestana Guardia
## Universidade Federal de São Carlos
---

## Threads

**Threads: linhas de execução de um processo**

Como vimos, o SO precisa manter uma estrutura com informações de controle para cada processo. Além disso, o SO mantém áreas de memória separadas para cada um. Mecanismos do funcionamento do processador multitarefa conseguem tratar as referências de endereços relativos dos processos em endereços efetivos, sem interferências entre eles.

Bem, olhemos para o código do processo, agora sob a perspectiva do programador.

Há muitas situações em que programas ficam bloqueados à espera de dados ou de alguma condição que precisa ser satisfeita. Nesses casos, se houver algo mais, outra parte do código do programa, que possa ser executada, poderia ser interessante não bloquear o processo como um todo, mas apenas desviar o processador para execução de outro trecho de código deste programa.

Já a multiplicidade de recursos funcionais num computador, como múltiplos cores, sugere explorar o paralelismo de código para obtenção de alto desempenho na execução de aplicações. A paralelização é tipicamente feita na forma de uma decomposição das atividades a serem executadas na aplicação, usando estratégias como as propostas em [1] (dbpp).

De maneira geral, duas estratégias de decomposição são usadas: decomposição funcional e decomposição de dados.  Na decomposição funcional, deve-se identificar os trechos de código do programa que podem ser executados de maneira independente / simultânea. Já na decomposição de dados, examina-se a(s) maior(es) estrutura(s) de dados manipuladas no programa e decide-se uma estratégia para sua manipulação em paralelo.

Percebe-se assim que seria interessante ter várias partes de um programa sendo executadas em paralelo, compartilhando a mesma área de código, seja para a execução de funções diferentes ou para a execução simultânea de múltiplas instâncias de uma mesma função, cada uma manipulando partes distintas dos dados.

Pois é nesse contexto que surgem as threads. Threads correspondem a linhas (fluxos) de execução associada(o)s a um processo. Todo processo tem ao menos uma thread, associada à função main (para programas em C), e pode criar mais. A criação e a destruição de threads podem ocorrer de forma dinâmica ao longo do ciclo de vida de um processo.

Threads de um processo compartilham a maior parte de seus recursos. As áreas de memória do processo, apontadas por suas tabelas de páginas e por outras estruturas de controle mantidas pelo SO, são usadas por todas as suas threads. Assim, referências a uma mesma posição lógica de memória feitas por qualquer uma das threads de um processo são mapeadas para a mesma página física na memória. É claro que esse compartilhamento não vale entre threads de processos diferentes, já que há um isolamento entre processos.

Como a memória é compartilhada entre as threads de um processo, elas podem comunicar-se usando estruturas de dados (variáveis) globais deste processo. A sincronização desses acessos, se for relevante, não é feita pelo SO mas cabe à lógica da aplicação. 

Outras estruturas de controle mantidas pelo SO para um processo também são compartilhadas entre suas threads. O vetor de arquivos abertos, por exemplo, é compartilhado. Assim, arquivos, pipes, named pipes, unix e inet domain sockets (e outros sockets) abertos são representados numa estrutura do processo que qualquer uma de suas threads pode usar. Por consequência, as entradas e saídas de dados do terminal feitas por qualquer thread do processo vão estar associadas ao mesmo terminal de controle, indicado pelas posições iniciais do vetor de arquivos abertos deste processo.

O tratamento de sinais também tem caráter global ao processo e é compartilhado por suas threads, embora cada uma possa ter uma máscara para o bloqueio de seus recebimentos. Informações de identificação de usuário, de grupo, valor da prioridade estática (nice), que têm sentido para um processo como um todo, também são compartilhadas.

Compartilhamento significa economia de recursos e de tempo que seria gasto com replicação. Assim, o código de uma thread é tipicamente associado a alguma função dentro do código do processo.

Para ser usada por mais de uma thread ao mesmo tempo, contudo, uma função precisa ser reentrante. Isso significa que essas funções devem apresentar comportamento correto mesmo quando executadas simultaneamente por diversas threads do mesmo processo. O uso de parâmetros nas funções, ao invés de variáveis globais, favorece a reentrância de código. Funções reentrantes não são necessariamente thread safe, o que implicaria poderem ser executadas simultaneamente por mais de uma threads do mesmo processo. 

Thread safety comumente pode ser obtida encapsulando (wrapping) a função original em uma nova, que utiliza um mecanismo de controle de acesso (mutex) antes e depois de acessar um recurso compartilhado. De maneira geral, as funções comuns da biblioteca C e as chamadas de sistema são non-thread-safe, a menos que indicado o contrário.

Em um programa multi-threaded, diversas funções podem ser selecionadas para execução simultânea. Para tanto, alguns recursos de controle devem ser replicados para cada thread. Por exemplo, cada thread deve ter alguma área para salvamento de sua cópia dos valores dos registradores, que constituem o contexto de hardware para suas execuções. Ao manter cópias dos valores dos registradores para cada thread, o SO permite que elas sejam executadas simultaneamente nos cores disponíveis e também possam ser suspensas, com seus contextos salvos para posterior continuação.

Assim, threads compartilham a mesma memória global (dados e heap) do processo, mas cada uma possui sua própria pilha (stack).  Indicada pelo registrador ESP, a pilha é comumente usada para a passagem de parâmetros em chamadas de função e alocação de variáveis automáticas (automatic variables) declaradas no escopo das funções associadas às threads ou chamadas por elas. Além disso, a(s) pilha(s) têm papel fundamental no tratamento de interrupções, servindo para o salvamento do valor dos Flags, CS e EIP (PC), antes que o processador sobreponha os valores desses registradores com o endereço da rotina de tratamento apropriada.

O compartilhamento de recursos do processo entre suas threads pode ser entendido pela figura a seguir:
```
+-----------------------------------------------------------------------+ 
| Process                                                               | 
|   +-------+     +-------------+  +-------------+  +-------------+     | 
|   | Files |     | Thread      |  | Thread      |  | Thread      |     | 
|   +-------+     |+-----------+|  |+-----------+|  |+-----------+|     | 
|                 || Registers ||  || Registers ||  || Registers ||     | 
|                 |+-----------+|  |+-----------+|  |+-----------+|     | 
| ....................................................................  | 
| . Memory        |             |  |             |  |             |  .  | 
| .               | +---------+ |  | +---------+ |  | +---------+ |  .  | 
| . +--------+    | |  Stack  | |  | |  Stack  | |  | |  Stack  | |  .  | 
| . |  Heap  |    | |         | |  | |         | |  | |         | |  .  | 
| . +--------+    | |         | |  | |         | |  | |         | |  .  | 
| .               | |         | |  | |         | |  | |         | |  .  | 
| . +--------+    | |         | |  | |         | |  | |         | |  .  | 
| . | Static |    | |         | |  | |         | |  | |         | |  .  | 
| . +--------+    | |         | |  | |         | |  | |         | |  .  | 
| .               | |         | |  | |         | |  | |         | |  .  | 
| . +--------+    | |         | |  | |         | |  | |         | |  .  | 
| . |  Code  |    | +---------+ |  | +---------+ |  | +---------+ |  .  | 
| . +--------+    +-------------+  +-------------+  +-------------+  .  | 
| ....................................................................  | 
+-----------------------------------------------------------------------+ 
    (From the DECthreads manual)
```

Além do benefício com a paralelização da manipulação de grandes estruturas / volumes de dados, há outras características de aplicações que favorecem o uso de threads. A possibilidade de sobreposição de operações de entrada e saída, seja de arquivos, do terminal ou da rede, com a execução de outros trechos do código de um programa é um benefício da programação com threads.

Sempre que há eventos assíncronos no programa também pode ser vantajoso usar threads separadas para seus atendimentos, ao invés de bloquear o processo todo. Servidores WWW, por exemplo, costumam usar threads distintas para ficar à espera de pedidos de conexão TCP, e uma nova thread é criada para tratar cada conexão estabelecida. Isso melhora o tempo de resposta aos clientes remotos.

Da mesma maneira, uma aplicação de edição de texto pode usar threads para sobrepor a leitura dos dados digitados com atividades de correção automática e outros processamentos. Jogos que envolvem a comunicação em rede e a manipulação de múltiplos objetos distintos animados na tela também se favorecem com o uso de threads independentes.

Comparada com a programação de várias atividades em paralelo usando processos, a programação com múltiplas threads no mesmo processo tem vantagens. Isso inclui a maior rapidez na criação de threads, a eficiência da comunicação com memória compartilhada e a economia de recursos. 

Do ponto de vista da seleção de atividades para execução, talvez já seja possível perceber que são as threads de um processo é que são colocadas em execução. Ou seja, um processo tem ao menos uma thread e pode ter mais. As threads são as entidades escalonáveis em um SO!

É importante observar que, num sistema multithreaded, ou seja, quando o SO dá suporte para que cada processo tenha múltiplas threads, cada thread tem seu estado de execução, podendo ser bloqueada ou estar pronta para execução. 

**Modelos de programação com threads**

Threads podem ser criadas e encerradas dinamicamente durante o ciclo de vida de um processo. Do ponto de vista da organização do código e da sincronização das threads, contudo, é comum que alguns modelos de programação sejam utilizados:

Mestre / escravo (master / slave): nesse modelo, a função main é comumente usada para criar e para esperar pela conclusão de outras threads do processo. Várias rodadas de criação e de sintonização podem ocorrer, mas a thread master é sempre responsável pela sincronização, sem efetivamente tomar parte na execução do código paralelo.
Pipeline: atividades a executar são quebradas em suboperações, executadas em série, mas de maneira concorrente, por threads diferentes. Os dados manipulados por uma thread são tipicamente encaminhados para a próxima depois de serem processados. A manutenção da estrutura de dados manipulada pelas threads numa área de memória global facilita as comunicações entre elas.
Peer: semelhante ao modelo mestre / escravo mas, depois de criar os escravos, thread principal participa na execução do trabalho.
É claro, contudo, que outros modelos de programação híbridos, que misturam essas estratégias, também são possíveis.

**Programação com threads**

A criação de programas portáveis que utilizam threads é normalmente feita usando a API pthreads (POSIX Threads).

Outras plataformas, como os sistemas Windows, também têm suporte para o modelo de programação com threads. 

[https://docs.microsoft.com/en-us/windows/win32/procthread/about-processes-and-threads] Acesso em 2/4/2020


>"... Each process provides the resources needed to execute a program. A process has a virtual address space, executable code, open handles to system objects, a security context, a unique process identifier, environment variables, a priority class, minimum and maximum working set sizes, and at least one thread of execution. Each process is started with a single thread, often called the primary thread, but can create additional threads from any of its threads.

>A thread is the entity within a process that can be scheduled for execution. All threads of a process share its virtual address space and system resources. In addition, each thread maintains exception handlers, a scheduling priority, thread local storage, a unique thread identifier, and a set of structures the system will use to save the thread context until it is scheduled. The thread context includes the thread's set of machine registers, the kernel stack, a thread environment block, and a user stack in the address space of the thread's process. Threads can also have their own security context, which can be used for impersonating clients.... " 

Hélio

[1] Foster, I. Designing and Building Parallel Programs. MIT Press 1999. www-unix.mcs.anl.gov/dbpp. Acesso em 2/4/2020.
[2] https://computing.llnl.gov/tutorials/parallel_comp/. Acesso em 2/4/2020.

---
## Sobre a implementação de threads
**Threads no espaço do usuário**

Quando o conceito de threads foi inicialmente proposto, SOs não tinham suporte para várias linhas de execução associadas a um processo. Assim, as primeiras implementações de threads foram realizadas na forma de bibliotecas no espaço de usuário.

Ou seja, criou-se uma biblioteca que tinha funções para criar threads para executar o código de alguma função dentro do programa. Cabia a essa biblioteca manter uma tabela de threads lógicas criadas pela aplicação, com as devidas informações de controle sobre cada uma delas. Contextos e áreas de pilha tinham que ser salvos para cada thread dessa tabela.

A maior dificuldade era a alternância entre as "pseudo" tarefas. Uma função específica chamada thread_yield foi inventada para que uma thread voluntariamente liberasse o processador para outra. No fundo, essa função gerava uma chamada ao pseudo-escalonador das threads. Nem sempre era possível usar essa chamada de forma eficiente nos códigos das threads. 

Além disso, como fazer para que o processo todo não ficasse bloqueado numa chamada feita dentro de uma thread, mas que o processador fosse direcionado para execução do código de outra tarefa?

Outro aspecto era como salvar o "contexto" dessas threads lógicas ao alternar-se o uso do processador entre elas, permitindo retomá-las posteriormente onde haviam parado.

Para evitar o bloqueio do processo como um todo e possibilitar redirecionar o processador uma estratégia era substituir as chamadas de sistema bloqueantes para leitura e escrita por operações não bloqueantes.

Por exemplo, antes de fazer uma operação de leitura com read(), era feita uma chamada de sistema do tipo select(), que permite verificar, entre outros aspectos, a disponibilidade de dados para leitura num arquivo. Se houver dados, a chamada read() é feita. Caso contrário, é feita uma troca de contexto entre as threads lógicas desse processo. Quando essa thread voltar a executar, o procedimento de teste é feito novamente, antes de liberar o acesso à operação read().

Outra abordagem consistia em ajustar o modo de operação do arquivo, tornando-o não-bloqueante. Isso pode ser feito com a chamada fcntl e o parâmetro F_SETFL e o atributo O_NONBLOCK. Quaisquer chamadas de sistema para leitura nesse arquivo agora retornam imediatamente, com sucesso e os dados requisitados, ou com erro, indicando que não havia dados prontos. Neste caso, a biblioteca de threads aproveitava e transferia o processador para executar código de outra thread! Posteriormente, quando essa thread voltasse a ocupar a CPU, a operação era tentada novamente.

A mesma lógica não bloqueante era aplicada a outras chamadas de sistema.

E se as pseudo threads não tivessem operações de leitura ou escrita, como fazer a alternância entre elas?

Uma solução era usar um mecanismo de temporização provido pelo SO, associado ao tratamento de sinais. Resumidamente, instalava-se uma rotina de tratamento de sinal para o timer (SIGALRM) e instaurava-se um temporizador periódico com setitimer().  

Pronto! Periodicamente, um sinal do TIMER era gerado para o processo que, em sua rotina de tratamento do sinal, salvava o contexto da thread corrente, selecionava outra thread pronta, restaurava seu pseudo-contexto e direcionava o processador para executar seu código. Isso pode ser feito com a chamada de sistema setjmp(). 

Puxa, que trabalho! Tudo para não bloquear o processo e ficar alternando entre suas threads. Se houvesse mais de um processadores, contudo, apenas 1 poderia ser usado, já que o SO enxergava apenas 1 processo!

Ainda bem que os SOs passaram a incorporar suporte para threads! Deixemos por conta do SO toda a estória de contexto, trocas, bloqueios, escalonamentos, balanceamentos e afins...

**Threads no espaço do kernel**

Não demorou pare que desenvolvedores de SO percebessem os benefícios da programação com threads e as vantagens de implementar no kernel mecanismos para identificação de cada linha de execução e para a alternância do uso do(s) processador(es) entre threads. 

No sistema Linux, por exemplo, há uma syscall específica para a criação de threads, chamada clone(). Na verdade, essa chamada tornou-se tão flexível e poderosa que ela permite tanto criar um novo processo quanto criar uma nova thread, ou ainda algo misto entre uma coisa e outra!

```c
 int clone(int (*fn)(void *), void *stack, int flags, void *arg, ...
           /* pid_t *parent_tid, void *tls, pid_t *child_tid */ );
```
Isso é possível porque a chamada leva como parâmetro um conjunto de flags que determina quais informações de controle da entidade chamadora desta função serão compartilhadas com a nova entidade criada.

Entre as estruturas de controle que podem ser compartilhadas, podem ser destacadas:

- CLONE_CLEAR_SIGHAND : signal dispositions in the child thread are the same as in the parent.
- CLONE_FILES : the calling process and the child process share the same file descriptor table. If CLONE_FILES is not set, the child process inherits a copy of all file descriptors opened in the calling process at the time of the clone call.
- CLONE_FS : indicates if the caller and the child process share the same filesystem information (the root of the filesystem, the current working directory, and the umask).
- CLONE_IO : if set, then the new process shares an I/O context with the calling process.
- ...
- CLONE_PARENT : if set, then the parent of the new child (as returned by getppid(2)) will be the same as that of the calling process.
- CLONE_PID : if set, the child process is created with the same process ID as the calling process.
- CLONE_SIGHAND : if set, the calling process and the child process share the same table of signal handlers.
- CLONE_THREAD : if set, the child is placed in the same thread group as the calling process.
- CLONE_VFORK : if set, the execution of the calling process is suspended until the child releases its virtual memory resources via a call to execve(2) or _exit(2) (as with vfork(2)).
- CLONE_VM : if set, the calling process and the child process run in the same memory space. If CLONE_VM is not set, the child process runs in a separate copy of the memory space of the calling process at the time of the clone call.
Por exemplo, utilizando o utilitário strace num sistema Linux para analisar o uso de chamadas de sistema relacionada ao gerenciamento de processos, foram identificadas as chamadas por 3 programas: um que fazia chamada à função pthread_create(), outro que usava a chamada fork() e um terceiro que usava vfork().

```
(1) 
$ strace -f -e trace=process thread_program
execve("./t", ["t"], [/* 45 vars */])   = 0
arch_prctl(ARCH_SET_FS, 0x7f33569b3700) = 0
clone(child_stack=0x7f33561f2ff0, flags=CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_THREAD|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID, parent_
tidptr=0x7f33561f39d0, tls=0x7f33561f3700, child_tidptr=0x7f33561f39d0) = 9480
exit_group(0)                           = ?
+++ exited with 0 +++
```

```
(2)
$ strace -f -e trace=process fork_program
execve("./p", ["p"], [/* 45 vars */])   = 0
arch_prctl(ARCH_SET_FS, 0x7f14ba10f700) = 0
clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7f14ba10f9d0) = 9484
exit_group(0)                           = ?
+++ exited with 0 +++
```

```
(3)
$ strace -e trace=process vfork_program
execve("./vf", ["vf"], 0x7ffdc27d0b20 /* 24 vars */) = 0
arch_prctl(ARCH_SET_FS, 0x7f16bdcf4740) = 0
vfork()                                 = 21844
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=21844, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
exit_group(0)                           = ?
+++ exited with 0 +++
```

No caso (1), em que o programa usa a rotina pthread_create(), essa chamada foi mapeada pela biblioteca glibc numa chamada à syscall clone do Linux. Ali, vê-se que o parâmetro flag foi usado para indicar quais estruturas deveriam ser compartilhadas com a nova thread criada: 

```
flags=CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_THREAD|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID
```

Como threads de um processo devem compartilhar seu espaço de endereçamento, o tratamento de sinais, o vetor de arquivos abertos, a visão do sistema de arquivos, e mais alguma particularidade dependente de sistema, esses parâmetros são indicados nos flags!

No caso (2), em que o programa cria um novo processo fazendo chamada à função fork(), vê-se que a glibc gerou código fazendo uma chamada à syscall clone também. Nesse caso, contudo os flags indicavam apenas parâmetros específicos da chamada, sem compartilhar o espaço de endereçamento ou estruturas de controle. Assim, é de se esperar que o SO faça uma cópia de tudo do processo pai para o novo processo filho criado.

No caso (3), a chamada da função vfork() no programa foi mapeada para a syscall vfork().

Processos, threads e tarefas no sistema Linux

Analisando as chamadas de criação de processos e threads no sistema Linux, que são mapeadas para a syscall clone(), é possível observar que, num sistema Linux, as entidades escalonáveis são representadas praticamente da mesma forma. Internamente, tudo é tratado com uma tarefa, representada por uma task_struct. 

Por fim, o que vai diferenciar uma tarefa da outra criada a partir dela são os recursos que serão compartihados ou copiados! Se a nova entidade sendo criada é um novo processo, copiam-se as estruturas de controle. Se o objetivo é criar uma nova thread do processo corrente, compartilham-se as áreas de memória, o vetor de arquivos, abertos, o tratamento de sinais, o PID e outras estruturas de controle.

Do ponto de vista da implementação interna, parece bem sensato e prático, não acham?

Ah, o que muda na seleção de tarefas para execução? Nada! Ao escalonador, basta selecionar a próxima tarefa, independentemente de logicamente ela ser um processo ou uma thread.

Considerando que, logicamente, todo processo tem ao menos uma thread, associada à função main(), são as threads é que entram nas filas de execução. Num sistema Linux, tudo é tarefa (task) e pronto!

Ai, ficou claro? Estou à disposição para tratar das dúvidas...

Hélio

---
## POSIX threads: pthreads

Seja no espaço de usuário ou providas pelo kernel, thread são úteis na programação que envolve múltiplas atividades dentro do mesmo programa.

Cada SO pode prover suporte específico para a programação com threads. Sistemas Windows, por exemplo oferecem uma API específica: CreateThread  [https://docs.microsoft.com/en-us/windows/win32/procthread/creating-threads - acessado em 7/4/2020].

Para apoiar a criação de programas portáveis com threads, que podem ser recompilados em diferentes plataformas computacionais, há um padrão POSIX que define funções para isso. Ele é chamado de Posix Threads ou, simplesmente, pthreads. 

$man pthreads
  
 POSIX.1 specifies a set of interfaces (functions, header files) for
 threaded programming commonly known as POSIX threads, or Pthreads.  A
 single process can contain multiple threads, all of which are
 executing the same program.  These threads share the same global
 memory (data and heap segments), but each thread has its own stack
 (automatic variables).

 POSIX.1 also requires that threads share a range of other attributes
 (i.e., these attributes are process-wide rather than per-thread):

 - process ID
 - parent process ID
 - process group ID and session ID
 - controlling terminal
 - user and group IDs
 - open file descriptors
 - record locks (see fcntl(2))
 - signal dispositions
 - file mode creation mask (umask(2))
 - current directory (chdir(2)) and root directory (chroot(2))
 - interval timers (setitimer(2)) and POSIX timers (timer_create(2))
 - nice value (setpriority(2))
 - resource limits (setrlimit(2))
 - measurements of the consumption of CPU time (times(2)) and resources (getrusage(2))

 As well as the stack, POSIX.1 specifies that various other attributes are distinct for each thread, including:

 - thread ID (the pthread_t data type)
 - signal mask (pthread_sigmask(3))
 - the errno variable
 - alternate signal stack (sigaltstack(2))
 - real-time scheduling policy and priority (sched(7))

 The following Linux-specific features are also per-thread:

 - capabilities (see capabilities(7))
 - CPU affinity (sched_setaffinity(2))

Examinando o padrão, é possível ver uma definição completa das funções.

>The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright © 2001-2018 IEEE and The Open Group

>pthread.h (https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html) - acessado em 7/4/2020
int   pthread_atfork(void (*)(void), void (*)(void), void(*)(void));
int   pthread_attr_destroy(pthread_attr_t *);
int   pthread_attr_getdetachstate(const pthread_attr_t *, int *);
int   pthread_attr_getguardsize(const pthread_attr_t *restrict, size_t *restrict);
int   pthread_attr_getinheritsched(const pthread_attr_t *restrict, int *restrict);
int   pthread_attr_getschedparam(const pthread_attr_t *restrict, struct sched_param *restrict);
int   pthread_attr_getschedpolicy(const pthread_attr_t *restrict, int *restrict);
int   pthread_attr_getscope(const pthread_attr_t *restrict, int *restrict);
int   pthread_attr_getstack(const pthread_attr_t *restrict, void **restrict, size_t *restrict);
int   pthread_attr_getstacksize(const pthread_attr_t *restrict, size_t *restrict);
int   pthread_attr_init(pthread_attr_t *);
int   pthread_attr_setdetachstate(pthread_attr_t *, int);
int   pthread_attr_setguardsize(pthread_attr_t *, size_t);
int   pthread_attr_setinheritsched(pthread_attr_t *, int);
int   pthread_attr_setschedparam(pthread_attr_t *restrict, const struct sched_param *restrict);
int   pthread_attr_setschedpolicy(pthread_attr_t *, int);
int   pthread_attr_setscope(pthread_attr_t *, int);
int   pthread_attr_setstack(pthread_attr_t *, void *, size_t);
int   pthread_attr_setstacksize(pthread_attr_t *, size_t);
int   pthread_barrier_destroy(pthread_barrier_t *);
int   pthread_barrier_init(pthread_barrier_t *restrict, const pthread_barrierattr_t *restrict, unsigned);
int   pthread_barrier_wait(pthread_barrier_t *);
int   pthread_barrierattr_destroy(pthread_barrierattr_t *);
int   pthread_barrierattr_getpshared(const pthread_barrierattr_t *restrict, int *restrict);
int   pthread_barrierattr_init(pthread_barrierattr_t *);
int   pthread_barrierattr_setpshared(pthread_barrierattr_t *, int);
int   pthread_cancel(pthread_t);
int   pthread_cond_broadcast(pthread_cond_t *);
int   pthread_cond_destroy(pthread_cond_t *);
int   pthread_cond_init(pthread_cond_t *restrict, const pthread_condattr_t *restrict);
int   pthread_cond_signal(pthread_cond_t *);
int   pthread_cond_timedwait(pthread_cond_t *restrict, pthread_mutex_t *restrict, const struct timespec *restrict);
int   pthread_cond_wait(pthread_cond_t *restrict, pthread_mutex_t *restrict);
int   pthread_condattr_destroy(pthread_condattr_t *);
int   pthread_condattr_getclock(const pthread_condattr_t *restrict, clockid_t *restrict);
int   pthread_condattr_getpshared(const pthread_condattr_t *restrict, int *restrict);
int   pthread_condattr_init(pthread_condattr_t *);
int   pthread_condattr_setclock(pthread_condattr_t *, clockid_t);
int   pthread_condattr_setpshared(pthread_condattr_t *, int);
int   pthread_create(pthread_t *restrict, const pthread_attr_t *restrict, void *(*)(void*), void *restrict);
int   pthread_detach(pthread_t);
int   pthread_equal(pthread_t, pthread_t);
void  pthread_exit(void *);
int   pthread_getconcurrency(void);
int   pthread_getcpuclockid(pthread_t, clockid_t *);
int   pthread_getschedparam(pthread_t, int *restrict, struct sched_param *restrict);
void *pthread_getspecific(pthread_key_t);
int   pthread_join(pthread_t, void **);
int   pthread_key_create(pthread_key_t *, void (*)(void*));
int   pthread_key_delete(pthread_key_t);
int   pthread_mutex_consistent(pthread_mutex_t *);
int   pthread_mutex_destroy(pthread_mutex_t *);
int   pthread_mutex_getprioceiling(const pthread_mutex_t *restrict, int *restrict);
int   pthread_mutex_init(pthread_mutex_t *restrict, const pthread_mutexattr_t *restrict);
int   pthread_mutex_lock(pthread_mutex_t *);
int   pthread_mutex_setprioceiling(pthread_mutex_t *restrict, int, int *restrict);
int   pthread_mutex_timedlock(pthread_mutex_t *restrict, const struct timespec *restrict);
int   pthread_mutex_trylock(pthread_mutex_t *);
int   pthread_mutex_unlock(pthread_mutex_t *);
int   pthread_mutexattr_destroy(pthread_mutexattr_t *);
int   pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *restrict, int *restrict);
int   pthread_mutexattr_getprotocol(const pthread_mutexattr_t *restrict, int *restrict);
int   pthread_mutexattr_getpshared(const pthread_mutexattr_t *restrict, int *restrict);
int   pthread_mutexattr_getrobust(const pthread_mutexattr_t *restrict, int *restrict);
int   pthread_mutexattr_gettype(const pthread_mutexattr_t *restrict, int *restrict);
int   pthread_mutexattr_init(pthread_mutexattr_t *);
int   pthread_mutexattr_setprioceiling(pthread_mutexattr_t *, int);
int   pthread_mutexattr_setprotocol(pthread_mutexattr_t *, int);
int   pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);
int   pthread_mutexattr_setrobust(pthread_mutexattr_t *, int);
int   pthread_mutexattr_settype(pthread_mutexattr_t *, int);
int   pthread_once(pthread_once_t *, void (*)(void));
int   pthread_rwlock_destroy(pthread_rwlock_t *);
int   pthread_rwlock_init(pthread_rwlock_t *restrict, const pthread_rwlockattr_t *restrict);
int   pthread_rwlock_rdlock(pthread_rwlock_t *);
int   pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict, const struct timespec *restrict);
int   pthread_rwlock_timedwrlock(pthread_rwlock_t *restrict, const struct timespec *restrict);
int   pthread_rwlock_tryrdlock(pthread_rwlock_t *);
int   pthread_rwlock_trywrlock(pthread_rwlock_t *);
int   pthread_rwlock_unlock(pthread_rwlock_t *);
int   pthread_rwlock_wrlock(pthread_rwlock_t *);
int   pthread_rwlockattr_destroy(pthread_rwlockattr_t *);
int   pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *restrict, int *restrict);
int   pthread_rwlockattr_init(pthread_rwlockattr_t *);
int   pthread_rwlockattr_setpshared(pthread_rwlockattr_t *, int);
pthread_t pthread_self(void);
int   pthread_setcancelstate(int, int *);
int   pthread_setcanceltype(int, int *);
int   pthread_setconcurrency(int);
int   pthread_setschedparam(pthread_t, int, const struct sched_param *);
int   pthread_setschedprio(pthread_t, int);
int   pthread_setspecific(pthread_key_t, const void *);
int   pthread_spin_destroy(pthread_spinlock_t *);
int   pthread_spin_init(pthread_spinlock_t *, int);
int   pthread_spin_lock(pthread_spinlock_t *);
int   pthread_spin_trylock(pthread_spinlock_t *);
int   pthread_spin_unlock(pthread_spinlock_t *);
void  pthread_testcancel(void);


>The following may be declared as functions, or defined as macros, or both. If functions are declared, function prototypes shall be provided.
    pthread_cleanup_pop()
    pthread_cleanup_push()

---
