# Gerenciamento de processos 1
## Professor: Hélio Crestana Guardia
## Universidade Federal de São Carlos
---

## Criação de processos
Já estamos acostumados a ouvir que um processo é um programa em execução. Mas como são criados novos processos?

Sim, com duplo-clique num ícone no ambiente gráfico, ou, para quem estudou o shell, digitando uma linha de comando. Mas como o gerente do ambiente gráfico, o gerenciador de arquivos e o shell criam um novo processo?

É o SO quem faz essa criação. Para solicitar esse serviço existe uma chamada de sistema: `fork(2) ($ man 2 fork :-)`

Ao executar a chamada fork o SO faz uma cópia do processo atual. Para tanto, é preciso inicialmente alocar um novo descritor de processos que, no Linux, chama-se task-struct.

Caberá ao SO determinar um identificador único para esse novo processo, chamado PID. Além do pid, o SO mantém vários identificadores associados a um processo, como ppid (Parent PID), pgid, uid e gid, que indicam o processo pai, o grupo de processo (process group), o usuário e o grupo base associados ao processo. Enquanto o grupo de processos é usado para o envio de sinais no terminal, as identificações de usuário e grupo servem para o controle das permissões associadas ao processo. As permissões são herdadas do usuário ao qual o processo está associado, a menos que o arquivo executável tenha o atributo setuid ou setgid, que o fazem herdar os privilégios associados ao dono ou ao grupo do arquivo.

Prioridades, identificadores da política de escalonamento, contadores de uso de recursos, referências a threads associadas ao processo, e outras tantas informações, são mantidas pelo SO Linux na task_struct de um processo. Outras informações importantes incluem o vetor de arquivos abertos e uma estrutura para tratamento de sinais.

Como num ambiente multitarefa há um isolamento entre as áreas de memória dos processos, usando memória virtual, é preciso alocar áreas de memória para o processo filho sendo criado. Como veremos ao estudar gerenciamento de memória virtual, o SO cria uma nova page table para o processo. Essa tabela será mantida pelo SO com informações sobre a presença e localização das páginas de memória de código e dados deste processo, e será usada pela MMU do processador para traduzir endereços lógicos em endereços físicos.

Para que as traduções de endereço ocorram automaticamente na unidade de gerenciamento de memória do processador, o SO deve ajustar o endereço da tabela de páginas em registrador específico do processador ao restaurar o contexto de execução de um processo. Para acelerar as traduções de endereço, é comum que as informações da page table acabem sendo armazenadas numa memória cache do processador chamada TLB (translation lookaside buffer). 

Se o processo filho é uma cópia do pai, o SO deve copiar informações do descritor do processo pai para o descritor do processo filho. Também é preciso copiar áreas de memória de código e dados (segmento de dados, variáveis estáticas, heap e pilha, e outros mapeamentos). Para melhorar o tempo de criação de processos, contudo, Linux usa uma estratégia chamada copy-on-write. Neste caso, o SO apenas copia a tabela de páginas do processo pai para o filho, apontando para as mesmas páginas de memória do processo pai. Deste modo, se o processo filho terminar em seguida ou se fizer uma chamada para sobrepor sua área de código com a função exec, não houve gasto desnecessário com duplicações de memória. Por outro lado, se o processo filho ou o pai tentarem modificar qualquer página, é preciso gerar uma cópia desta página para o filho antes. Daí o termo cópia na escrita!

Bons estudos,

Hélio

Programas:

O que é preciso saber com esta unidade:

- conhecer identificadores associados aos processos pelo SO
- criar processos com a chamada fork
estruturas de controle mantidas pelo SO para cada processo
- áreas de memória associadas a um processo e estratégia copy-on-write (e conhecer vfork, por razões históricas:)
- espera por processos com wait e waitpid, tratamento de zombies 
- identificação de processos e envio de sinais com chamada kill 
- formas de término de um processo: return, exit (+ atexit), _exit

---
## Fork

De maneira resumida, a chamada de sistema fork cria uma cópia do processo atual. Após a criação, os 2 processos vão para a fila de processos prontos e, quando selecionados pelo escalonador, voltam à execução na instrução seguinte à chamada fork.

Uma questão importante na execução desses 2 processos (pai e filho) é como diferenciar o código do processo pai do processo filho após a execução da chamada fork(). Isso é feito analisando-se o valor de retorno da chamada fork. Para o processo pai, fork() retorna o PID do processo filho criado. Para o filho, o valor de retorno é 0 (zero), que indica sucesso na operação.

Sabendo no código qual processo é o pai e qual é o processo filho, é possível executar atividades diferentes em cada uma dessas cópias. Há situações em que pai e filho vão executar as mesmas operações e há situações em que uma chamada de função distinta é feita para cada um deles. Também há casos em que o processo filho é criado para executar um código completamente novo. Isso é o que comumente é feito pelo shell, ao tratar a linha de comandos digitada pelo usuário.

Vejamos um exemplo de código:

```
pid_t ret = fork();

if (ret==-1)  { 
  printf("Erro na execucao do fork, processo filho nao foi criado.\n"); 
  exit(0); 
} 

// se código chegou aqui é porque o fork funcionou. Há 2 processos executando a partir daqui.

if (ret==0) {  
   printf("Processo filho: %d\n",(int)getpid()); 

} else { // esse é o processo pai. Valor de retorno do fork é o pid do filho criado
   printf("Processo %d, pai de %d\n", (int)getpid(), (int)ret); 
}

// Os 2 processos prosseguem e vão executar a linha seguinte!
printf("%d terminando...\n");
 ```
 Neste caso, o processo que estava executando chama fork para criar outro processo (uma cópia de si). Depois do fork, como os processos pai e filho estão executando o mesmo código, é preciso diferenciá-los. Isso é feito analisando o valor de retorno da chamada fork. 

 O processo filho será aquele para o qual o fork retornou 0. Para o processo pai, o valor de retorno da chamada fork é o pid do filho recém criado. Vejam que os 2 processos estão executando o mesmo código, salvo por diferenciações feitas como no comando if usado. Ambos executam o resto do código. No exemplo, ambos vão imprimir seus pids e o texto " terminando...".

Um exemplo interessante de aplicação que usa múltiplos processos é o navegador Chrome.

---
## vfork

*"Disclaimer": vamos tratar de vfork aqui, mas essa é provavelmente uma chamada que não deve ser usada em seus códigos :-)*

**A chamada de sistema vfork é uma variação da chamada fork().**

De maneira geral, vfork tem o mesmo efeito de fork, ao criar um processo filho como uma "cópia" do processo pai. 

A diferença fundamental ente as chamadas é o fato de o processo filho compartilhar as áreas de memória do processo pai, ao invés do sistema copiar as áreas de memória. Isso significa que as mesmas tabelas de páginas do processo pai são usadas pelo processo filho. 

Outra diferença significativa é que o processo pai, que emitiu a chamada, fica bloqueado até que o processo filho realize uma chamada execve(), pedindo que seu código seja alterado, ou _exit(), para terminar.

Essa chamada foi inicialmente criada como uma forma de melhorar o desempenho dos programas que criavam processos filhos. Se o processo sabe que vai fazer um fork + execve no filho, ao usar vfork não há gasto de tempo com cópias de áreas de memória que seriam sobrepostas logo a seguir com a chamada execve. 

Como se pode perceber, contudo, há vários riscos ao comportamento do processo pai se o processo filho criado com vfork fizer alterações nas áreas de memória, compartilhadas com ele. Além disso, à medida que os sistemas passaram a usar a estratégia de copy-on-write na criação de processos filhos, o uso de vfork perdeu o sentido.

```
int
main()
{
   pid_t result;
   int a=10;  // variavel para testar compartilhamento

/*
   pid_t vfork(void);

   (From SUSv2 / POSIX draft.)  The vfork() function has the same effect as fork(), except
   that the behaviour is undefined if the process created by vfork() either  modifies  any
   data  other  than a variable of type pid_t used to store the return value from vfork(),
   or returns from the function in which vfork() was called, or calls any  other  function
   before successfully calling _exit() or one of the exec() family of functions.

   vfork()  differs  from  fork()  in that the parent is suspended until the child makes a
   call to execve(2) or _exit(2).  The child shares all memory with its parent,  including
   the  stack,  until execve() is issued by the child.  The child must not return from the
   current function or call exit(), but may call _exit().

   Signal handlers are inherited, but not shared.  Signals to the parent arrive after  the
   child releases the parent's memory.
*/

   // pid_t vfork(void);
   result=vfork();

   if(result==-1) {
      perror("Erro em vfork");
      exit(0);
   }

   if(!result) {  // filho
      // dorme antes do exec para ver se pai espera!
      sleep(15);

      // altera variavel no filho. Na pratica, diferentemente do fork, 
      // neste caso, aponta para a propria area de memoria do pai...
      // vfork compartilha area de memoria do pai, para melhorar 
      // tempo de resposta, supondo que filho apenas vai usar exec()
      a+=5;

      /* sobrepoe o processo atual com um novo processo */
      result=execlp("hello","hello",NULL);

      perror("Erro em execl");
      exit(0);

   }else {  // pai
      printf("Pai retomou a execucao. a=%d\n",a);
   }

   return(0);
}
```

---
## exit e wait

**E, se um processo é criado com a chamada fork(), como ele termina?**

Salvo nas condições em que um processo é terminado pelo recebimento de um sinal (gerado por erro na execução ou enviado por outro processo) um processo deve concluir sua execução fazendo uma chamada explícita ao sistema operacional para terminar.

Na prática, em programas C, o simples retorno da função main() vai ser tratado pelo compilador com a inclusão automática de uma chamada à função exit(3). Também é possível terminar o processo chamando explicitamente a função C exit() a partir de qualquer parte do código.

Já a função atexit() permite que o programador programe (!) a execução automática de uma função específica, uma espécie de "destrutor", quando a função exit for chamada. 

Ao final da execução da função exit() é feita uma chamada de sistema _exit(). 

Um programa também pode executar a a chamada de sistema _exit() em qualquer ponto do código, fazendo com que o programa seja terminado imediatamente, sem executar quaisquer funções programadas com atexit().

Resumindo, é a chamada de sistema _exit() que faz com que o SO termine o processo, liberando os recursos que ele tinha alocado.

Em todos os casos, seja com return da função main, exit() ou _exit(), o valor de retorno fornecido pelo programa vai indicar se o programa terminou de maneira bem sucedida ou não. Os valores pré-definidos para essas condições são expressos pelas constantes EXIT_SUCCESS e EXIT_FAILURE, respectivamente.

Espera por conclusão ou alteração de estado de processo filho

E o que acontece com o processo pai, em relação aos processos filhos que cria?

Quando um processo cria outro processo filho, é comum que o resultado da execução desse novo processo seja relevante para o criador. Por exemplo, uma aplicação pode criar um processo filho para fazer parte de suas atividades e é necessário saber se o programa filho terminou com sucesso ou não. Ou seja, se conseguiu executar o que era previsto ou não.

Além disso, pode ser que o processo pai só possa prosseguir sua execução após a conclusão do processo filho. 

Em sistemas POSIX, a família de chamadas de sistema baseadas em wait() permite essa sincronização entre processos pais e filhos. Isso inclui as chamadas wait(), waitpid(), waitid() e wait4().  Essas chamadas servem apenas para um processo pai esperar alterações no estado de algum de seus processos filhos, e variam em função da identificação do processo e das condições de retorno aguardadas.

O trecho de código a seguir foi copiado da página de manual de um sistema Linux e ilustra o uso da chamada waitpid().

```
$ man wait
...  
 The following shell session demonstrates the use of the program:

 $ ./a.out &
 Child PID is 32360
 [1] 32359
 $ kill -STOP 32360
 stopped by signal 19
 $ kill -CONT 32360
 continued
 $ kill -TERM 32360
 killed by signal 15
 [1]+  Done                    ./a.out
 $

 Program source

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{  
   pid_t cpid, w;
   int wstatus;
   
   cpid = fork();
   if (cpid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
   }
   
   if (cpid == 0) {             /* Code executed by child */
      printf("Child PID is %ld\n", (long) getpid());
      
      if (argc == 1)                 
         pause();                 /* Wait for signals */
         _exit(atoi(argv[1]));  
  
   } else {                    /* Code executed by parent */
      do { 
         w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
         if (w == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
         }
            
         if (WIFEXITED(wstatus)) {
            printf("exited, status=%d\n", WEXITSTATUS(wstatus))
         } else if (WIFSIGNALED(wstatus)) { 
            printf("killed by signal %d\n", WTERMSIG(wstatus));
         } else if (WIFSTOPPED(wstatus)) {
            printf("stopped by signal %d\n", WSTOPSIG(wstatus));
         } else if (WIFCONTINUED(wstatus)) {
            printf("continued\n");
         }
      } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
      exit(EXIT_SUCCESS);
   }
}   
```
---
## execve

Como vimos, a chamada fork cria um novo processo fazendo uma cópia do processo que emite a chamada. Assim, ambos os processos (pai e filho) executam o mesmo código a partir da linha seguinte à chamada fork. O valor de retorno da chamada fork permite diferenciar o que será feito por cada um deles. Falta saber agora como carregar a imagem de um outro processo sobre a imagem do processo atual.

Pensemos no funcionamento de um programa shell, por exemplo, que recebe linhas de comando digitadas pelo usuário e cria processos a partir desses comandos. Se a única forma de criar um novo processo é duplicar o processo atual via chamada fork, como fazer para executar um processo diferente especificado pelo usuário?

Isso é feito com a chamada de sistema execve, que contém entre seus parâmetros a indicação do nome de um arquivo executável.

Assim, o shell cria um (ou mais) processo(s) e, no processo filho, faz uma nova chamada de sistema, execve, para sobrepor a imagem do processo atual em função do comando digitado pelo usuário.

Ao ser invocada por um processo, a chamada de sistema execve pede ao SO que substitua a imagem do processo corrente pelo processo contido num arquivo executável indicado como parâmetro. Assim, essa chamada é responsável por abrir o arquivo informado, identificar as áreas de memória que são necessárias para o novo processo, adequar o espaço de memória em uso e carregar as diversas sessões do arquivo (código, dados estáticos, etc.) para a memória, sobrepondo o código e as demais áreas do processo atual. Também é criado um novo contexto de execução para o processo que passa a ser executado do seu início (função main, por exemplo, ou outra função de controle inserida pelo compilador e o gerador de código).

Resumindo, a chamada execve mantém o descritor do processo atual, seu identificador de processo e várias outras informações, mas substitui as áreas de código e de dados, zera a área de pilha e ajusta o contexto para a execução do novo processo.

Retomando a operação do shell, de maneira simplificada, o que ele faz é criar um novo processo com o comando fork e, no processo filho criado, faz a chamada execve. Bem, há muitos detalhes nessa operação, mas acho que já dá para entender o conceito :-)

Além da chamada de sistema execve, há outras funções da biblioteca C que facilitam o uso dessa chamada, com parâmetros em formatos variados. Todas essas chamadas são convertidas em chamadas à syscall execve. Seus formatos e parâmetros podem ser consultados pela família de chamadas exec : 

```
int execl(const char *pathname, const char *arg, ... /* (char  *) NULL */);
int execlp(const char *file, const char *arg, ... /* (char  *) NULL */);
int execle(const char *pathname, const char *arg, ... /*, (char *) NULL, char *const envp[] */);
int execv(const char *pathname, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[], char *const envp[]);
Vejamos um exemplo de código:

pid_t ret = fork();

if (ret==-1)  { 
  printf("Erro na execucao do fork, processo filho nao foi criado.\n"); 
  exit(0); 
}
if (ret==0) {  // filho 
   // sobrepoe o processo atual com um novo processo 
   // execlp informa parâmetros na forma de uma lista terminada por NULL
   execlp ("./hello","hello",NULL); 

   // Processo nao continua depois do exec, sua imagem foi sobreposta!
   // Se chegou aqui, é porque exec falhou...
   printf("Processo filho: erro na execucao do execl\n");

} else { // esse é o processo pai. Valor de retorno do fork é o pid do filho criado
   // Processo pai pode esperar pelo filho 
   // wait(...); 
}
...
```

