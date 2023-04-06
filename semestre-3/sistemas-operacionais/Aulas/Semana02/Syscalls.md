# Syscalls
## Professor: Hélio Crestana Guardia
## Universidade Federal de São Carlos
---

## Syscalls
Chamadas de sistema, system calls ou syscalls, são os nomes dados às solicitações dos serviços oferecidos por um sistema operacional aos programas. Serviços típicos de  um SO incluem aqueles que oferecem acesso a dispositivos, como as operações de entrada e saída (I/O) e de acesso ao sistema de arquivos, e mecanismos para criação, gerenciamento e comunicação entre processos.

Com as chamadas de sistema, o SO serve de intermediário para as ações que requerem privilégio de execução, como as instruções para acesso ao barramento (in e out) e aquelas usadas para o controle de interrupção (cli e sti), na arquitetura x86. Essas são algumas instruções que não podem ser executadas no anel de privilégio 3 do processador, usado para a execução de processos de usuário. Além disso, ao oferecer os serviços, o SO pode promover a melhor utilização compartilhada dos recursos, de forma eficiente, segura e justa.

As chamadas de sistema normalmente não são invocadas diretamente, mas através de funções definidas numa interface em C. Isso favorece a portabilidade dos programas. Cabe a essas funções em alto nível (wrapper functions) fazer ajustes necessários e realizar o acesso ao kernel de forma adequada à plataforma de hardware disponível. Normalmente, a implementação da função intermediária apenas faz uma cópia dos parâmetros para **registradores** e invoca a chamada de sistema via uma instrução de interrupção ou via instruções específicas desenvolvidas pelos processadores para chamada explícita ao kernel. Essas instruções, denominadas sysenter e syscall, estão presentes em processadores Intel e AMD, por exemplo. Pode caber à função de alto nível (wrapper) decidir qual mecanismo de chamada será utilizado para desviar o processador para a execução da rotina apropriada do código do SO.

É claro que a área do código do SO onde estão as rotinas das chamadas de sistema devem estar mapeadas no espaço de endereçamento de todas as tarefas.

Outro aspecto relevante da chamada de sistema é o ajuste do nível de execução para o o anel 0 (mais privilegiado). Isso ocorre ao desviar-se o processador da execução da aplicação para a execução do código do SO. Bits nos descritores de segmento do endereço desse código indicam o anel 0 de privilégio. Também o ponteiro da pilha é redirecionado  para uma área específica para esse nível de execução (o SO precisa reservar uma área de pilha para cada anel de privilégio para cada tarefa). 

**Valor de retorno das syscalls e tratamento de erros**

Voltando à função intermediária (wrapper), o valor de retorno das chamadas de sistema em C que forem bem sucedidas varia, mas, em geral, é 0 (zero). Quando não são bem sucedidas, a maior parte das chamadas de sistema retorna um valor de erro negativo. Neste caso, a função equivalente em C da chamada de sistema copia o valor absoluto do código de erro na variável errno(3) e retorna o valor -1 para o programa que executou a chamada.

Funções da biblioteca C, como perror(3) e strerror(3), podem ser usadas nos programas para a tradução de um código de erro numa mensagem apropriada.

**Interface genérica e Fast system calls**

A implementação das funções de acesso às chamadas de sistema é feita pela biblioteca libc, ou glibc, em sistemas GNU/Linux. A biblioteca glibc ainda permite o acesso direto às chamadas de sistema, sem fazer a intermediação típica das chamadas (wrapping). Para tanto, é implementada uma função chamada syscall, que permite especificar o número da chamada de sistema e os parâmetros relevantes. A função syscall é útil principalmente quando se deseja usar uma chamada de sistema ainda não implementada pela versão da glibc disponível na distribuição Linux em uso.

Um outro aspecto interessante das interfaces de chamada de sistema é a otimização do acesso em algumas chamadas de sistema frequentes e que envolvem apenas a leitura de informações mantidas pelo kernel. Esse é o caso, por exemplo, das chamadas  gettimeofday(2),  clock_gettime(2),  getcpu(2) e time(2). 

Uma estratégia para realizar a chamada gettimeofday, por exemplo, de forma rápida consiste em fazer o kernel manter as informações sobre o horário atual em uma localização fixa da memória, que é mapeada no espaço de endereçamento de todos os processos. Desta forma, a interface em alto nível da chamada de sistema pode apenas ler o valor e retorná-lo ao processo, sem gerar uma mudança do processador para modo kernel.

Da mesma maneira, algumas outras chamadas de sistema poderiam ser implementadas apenas através de acesso à memória. No Linux, essas implementações de chamadas de sistema que evitam a mudança do modo de execução do processador para o kernel space (nível 0) eram tratadas na biblioteca vsyscalls e passaram a ser implementadas na biblioteca vdso (Virtual Dynamic Shared Object). Ambas são mapeadas para o espaço de endereçamento de cada processo quando ele é carregado para execução.

De maneira resumida, quando um processo (ou uma de suas threads) faz uma chamada de sistema, o SO entra em ação através de um desvio do ponteiro de instruções do processador. Do mesmo modo que no tratamento de interrupções, a instrução int vai gerar o salvamento do valor atual do ponteiro de instruções (registradores CS e EIP) antes de alterar seu valor. Isso é feito pelo próprio processador, tipicamente copiando seus valores na pilha da tarefa atual.

Usando agora o número da interrupção (informado pelo controlador de interrupção - IO APIC), da exceção, ou da instrução int, o processador (SO não entrou em ação ainda) consulta o vetor de interrupções (IDT - Interrupt Description Table) para obter um novo valor para os FLAGS e valores para os registradores CS e EIP. Pronto, o processador volta ao ciclo de busca e execução de instruções, agora desviado para a rotina de tratamento.

Do modo equivalente, na chamada de sistema via instruções syscall / sysenter, a execução dessas instruções pelo processador faz com que o o valor do registrador RIP (PC, na arquitetura 64 bits) seja salvo e seja substituído pelo endereço da rotina de entrada do SO. O endereço a ser atribuído ao RIP, contudo, agora é obtido a partir de registradores internos da CPU, cujos valores foram preenchidos pelo SO. 

É claro que para que o processador consiga localizar os endereços que devem ser atribuídos ao PC na ocorrência de interrupções ou do desvio para syscall, o SO deve ter colocado os valores apropriados em locais específicos da memória e em registradores. Normalmente, na fase inicial (boot), o SO carrega sua rotina de tratamento das chamadas de sistema para a memória e ajusta seu endereço no vetor de interrupções na memória e nos registradores de endereço específicos. Assim, sempre que uma chamada de sistema é feita, seja através da instrução de interrupção ou das instruções syscall / sysenter, o SO entra em ação porque o valor dos registradores [FLAGS,] CS e EIP (ou RIP) são salvos e alterados para o endereço do SO (de sua rotina de tratamento).

Processadores Intel e AMD têm instruções logicamente equivalente para chamada de sistema rápida: sysenter e syscall. Em processadores Intel, syscall é o modo padrão de acesso ao kernel no modo x86-64. Sysenter é usado no modo 32 bits. Aparentemente, o uso da chamada via int 0x80 não é mais o modo preferido de acesso. De todo modo, aplicações que queiram fazer chamadas de sistema podem invocar VDSO, que é uma biblioteca mapeada no espaço de endereçamento de todo processo. Cabe a essa forma de acesso tratar dos detalhes mais complexos da chamada via syscall ou sysenter.

Bons estudos,

Hélio

O que é preciso saber com esta unidade:

- categorias de serviço oferecidos pelas chamadas de sistema
- interface C para acesso às rotinas do kernel
- tratamento de valores de retorno e códigos de erro de chamadas de sistema
- acesso às syscalls usando instrução de interrupção

---
## syscalls & libc (wrapper functions)

**System calls and library wrapper functions**

>$ man syscalls
  ...
  System  calls are generally not invoked directly, but rather via wrapper functions in glibc (or per-
  haps some other library)...  Often, but  not always, the name of the wrapper function is the same as
  the name of the system call that it invokes. For example, glibc contains a function truncate() which 
  invokes the underlying  "truncate" system call.

  >Often  the  glibc  wrapper function is quite thin, doing little work other than copying arguments to
  the right registers before invoking the system call, and then setting errno appropriately after  the
  system  call has returned.  (These are the same steps that are performed by syscall(2), which can be
  used to invoke system calls for which no wrapper function is provided.)  Note: system calls indicate
  a  failure  by returning a negative error number to the caller; when this happens, the wrapper func-
  tion negates the returned error number (to make it positive), copies it to errno, and returns -1  to
  the caller of the wrapper.

  >Sometimes,  however, the wrapper function does some extra work before invoking the system call.  For
  example, nowadays there are (for reasons described below) two related system calls, truncate(2)  and
  truncate64(2), and the glibc truncate() wrapper function checks which of those system calls are pro-
  vided by the kernel and determines which should be employed.

---
## Linux syscalls

**Quais são as chamadas de sistema providas por um SO?**

No caso do sistema Linux, segue-se as especificações de padrões como POSIX e BSD. Para ver uma lista das syscalls nesse sistema pode-se usar o comando man. Também é possível usar o comando man para saber detalhes de cada uma delas. No manual, além de informações sobre os parâmetros, valores de retorno, trata-se do comportamento da chamada, das condições de erro, etc.


The Linux System Calls (https://en.wikibooks.org/wiki/The_Linux_Kernel/Syscalls)


**$ man syscalls**

>SYSCALLS(2)

>The system call is the fundamental interface between an application and the Linux kernel. As of Linux 2.4.17, there are 1100 system calls listed in /usr/src/linux/include/asm-*/unistd.h. 

>This man page lists those that are common to most platforms.

>_llseek() _newselect() _sysctl() accept() accept4() access() acct() add_key() adjtimex() alarm() alloc_hugepages() bdflush() bind() break() brk() cacheflush() capget() capset() chdir() chmod() chown() chown32() chroot() clock_getres() clock_gettime() clock_nanosleep() clock_settime() clone() close() connect() creat() create_module() delete_module() dup() dup2() dup3() epoll_create() epoll_create1() epoll_ctl() epoll_pwait() epoll_wait() eventfd() eventfd2() execve() _exit() exit_group() faccessat() fadvise64() fadvise64_64() fallocate() fchdir() fchmod() fchmodat() fchown() fchown32() fchownat() fcntl() fcntl64() fdatasync() fgetxattr() flistxattr() flock() fork() free_hugepages() fremovexattr() fsetxattr() fstat() fstat64() fstatat64() fsync() ftruncate() ftruncate64() futex() futimesat() get_kernel_syms() get_mempolicy() get_robust_list() get_thread_area() getcpu() getcwd() getdents() getdents64() getegid() getegid32() geteuid() geteuid32() getgid() getgid32() getgroups() getgroups32() getitimer() getpeername() getpagesize() getpgid() getpgrp() getpid() getppid() getpriority() getresgid() getresgid32() getresuid() getresuid32() getrlimit() getrusage() getsid() getsockname() getsockopt() gettid() gettimeofday() getuid() getuid32() getxattr() init_module() inotify_add_watch() inotify_init() inotify_init1() inotify_rm_watch() io_cancel() io_destroy() io_getevents() io_setup() io_submit() ioctl() ioperm() iopl() ioprio_get() ioprio_set() ipc() kexec_load() keyctl() kill() lchown() lchown32() lgetxattr() link() linkat() listen() listxattr() llistxattr() lookup_dcookie() lremovexattr() lseek() lsetxattr() lstat() lstat64() madvise() madvise1() mbind() migrate_pages() mincore() mkdir() mkdirat() mknod() mknodat() mlock() mlockall() mmap() mmap2() modify_ldt() mount() move_pages() mprotect() mq_getsetattr() mq_notify() mq_open() mq_timedreceive() mq_timedsend() mq_unlink() mremap() msgctl() msgget() msgrcv() msgsnd() msync() munlock() munlockall() munmap() nanosleep() nfsservctl() nice() oldfstat() oldlstat() oldolduname() oldstat() olduname() open() openat() pause() pciconfig_iobase() pciconfig_read() pciconfig_write() personality() pipe() pipe2() pivot_root() poll() ppoll() prctl() pread64() preadv() pselect6() ptrace() pwrite64() pwritev() query_module() quotactl() read() readahead() readdir() readlink() readlinkat() readv() reboot() recv() recvfrom() recvmsg() remap_file_pages() removexattr() rename() renameat() request_key() restart_syscall() rmdir() rt_sigaction() rt_sigpending() rt_sigprocmask() rt_sigqueueinfo() rt_sigreturn() rt_sigsuspend() rt_sigtimedwait() sched_get_priority_max() sched_get_priority_min() sched_getaffinity() sched_getparam() sched_getscheduler() sched_rr_get_interval() sched_setaffinity() sched_setparam() sched_setscheduler() sched_yield() select() semctl() semget() semop() semtimedop() send() sendfile() sendfile64() sendmsg() sendto() set_mempolicy() set_robust_list() set_thread_area() set_tid_address() set_zone_reclaim() available to userspace) setdomainname() setfsgid() setfsgid32() setfsuid() setfsuid32() setgid() setgid32() setgroups() setgroups32() sethostname() setitimer() setpgid() setpriority() setregid() setregid32() setresgid() setresgid32() setresuid() setresuid32() setreuid() setreuid32() setrlimit() setsid() setsockopt() settimeofday() setuid() setuid32() setxattr() sgetmask() shmat() shmctl() shmdt() shmget() shutdown() sigaction() sigaltstack() signal() signalfd() signalfd4() sigpending() sigprocmask() sigreturn() sigsuspend() socket() socketcall() socketpair() splice() spu_create() spu_run() ssetmask() stat() stat64() statfs() statfs64() stime() swapoff() swapon() symlink() symlinkat() sync() sync_file_range() sysfs() sysinfo() syslog() tee() tgkill() time() timer_create() timer_delete() timer_getoverrun() timer_gettime() timer_settime() timerfd_create() timerfd_gettime() timerfd_settime() times() tkill() truncate() truncate64() ugetrlimit() umask() umount() umount2() uname() unlink() unlinkat() unshare() uselib() ustat() utime() utimensat() utimes() vfork() vhangup() vm86old() vmsplice() wait4() waitid() waitpid() write() writev()

>Of the above, 9 are obsolete, namely getrlimit, oldfstat, oldlstat, oldolduname, oldstat, olduname, readdir, select and vm86old (see also obsolete(2)), and 15 are unimplemented  in  the  standard  kernel, namely afs_syscall, break, ftime, getpmsg, gtty, idle, lock, mpx, phys, prof, profil, putpmsg, security, stty and ulimit (see also unimplemented(2)).  However, ftime(3), profil(3) and ulimit(3) exist as library routines.  The slot for phys is in use since 2.1.116  for  umount;  phys will never be implemented. The getpmsg and putpmsg calls are for kernels patched to support streams, and may never be in the standard kernel. The security call is for future use.

>Roughly speaking, the code belonging to the system call with number __NR_xxx defined in /usr/include/asm/unistd.h can be found in the kernel source in the routine sys_xxx().   (The dispatch table for i386 can be found in /usr/src/linux/arch/i386/kernel/entry.S.)  There are many exceptions, however, mostly because older system calls were superseded by newer ones, and this has been treated somewhat unsystematically. On platforms with proprietary OS emulation, such as  parisc,  sparc, sparc64 and alpha, there are many additional system calls; mips64 also contains a full set of 32-bit system calls.

---
## Syscalls em baixo nível

Como já vimos, normalmente há uma interface em linguagem de alto nível para acesso às chamadas de sistema. Em algumas linguagens de alto nível, contudo, há tantas abstrações que quem programa nem chega perto das syscalls. 

Consideremos java. Ao fazer uma chamada como:

  `...
  System.out.println("Hello, quarantined World!");
  ...`

quem programa nem pensa nas syscalls; está apenas usando um método de uma classe, que vai formatar os dados e imprimir os dados, fazendo a syscall apropriada.

O mesmo vale para um comando como:

  `... 
  printf("Já são %d dias em quarentena....\n", today - início); 
  ...`

Nesse caso, quem usa a chamada à função printf deseja formatar a saída, apresentando o número resultante da expressão como um valor decimal e incluindo uma quebra de linha. Cabe então à função printf fazer os ajustes da formatação e realizar uma chamada para que o conteúdo seja apresentado na janela do terminal.

Vamos considerar agora o uso de uma chamada de função em linguagem C que é mapeada diretamente a uma syscall.

Antes, para quem não se lembra da chamada write(), ela tem os seguintes parâmetros:

```
  $ man write
  ...
   ssize_t write(int fildes, const void *buf, size_t nbyte);
  ...
   write() attempts to write nbyte of data to the object referenced by the descriptor fildes from the buffer pointed to by buf.
  ...
```
Qual é então o código gerado quando se usa a linha a seguir?

  `write (STDOUT_FILENO, "Teste... 1,2,3,...\n", 19);`

Neste caso, o programa está usando a chamada função write, que, em tempo de execução, vai fazer uma chamada de sistema write para escrever 19 bytes, a partir do início da string indicada, no arquivo apontado pela posição 1 do vetor de arquivos abertos (que é denominado STDOUT!).

Vejamos o código a seguir [código 1]:

```c
1 #include <stdio.h>
2 #include <unistd.h>
3
4 int main()
5 {
6    printf("Teste... 1,2,3,...\n");
7    write (STDOUT_FILENO, "Teste... 1,2,3,...\n", 19);
8
9    return 0;
10 }
```
A compilação desse programa num sistema Linux com gcc, pode ser feita como segue:

`$ gcc prog.c -o prog`

Podemos agora executar esse programa de forma a verificar (num sistema Linux) quais são as chamadas de sistema feitas pelo programa. Isso pode ser feito com o comando strace. [ para instalar strace em Debian e afins: $ sudo apt install strace ]

```
$ strace ./prog
execve("./prog", ["./prog"], 0x7fff24cb4f50 /* 24 vars */) = 0
mmap(...
...                  // ignorando algumas linhas do trace...
brk(...
...                  // ignorando algumas linhas do trace...
...
write(1, "Teste... 1,2,3,...\n", 19Teste... 1,2,3,...
)    = 19
write(1, "Teste... 1,2,3,...\n", 19Teste... 1,2,3,...
)    = 19
exit_group(0)                           = ?
+++ exited with 0 +++
```

Vejam só: tanto a chamada da função printf quando a chamada da função write acabaram resultando em chamadas à syscall write!

**Código assembly gerado**

Se a função write vai fazer a chamada de sistema em tempo de execução, como será o código assembly gerado para tanto?

Ah, por que estamos falando em assembly mesmo? Porque o compilador tem que gerar código em linguagem de máquina com instruções do repertório de instruções do processador alvo. Vale lembrar que há uma correspondência direta entre comandos assembly e os opcodes binários que representam as instruções para o processador.

Vocês se lembram das instruções SYSCALL e INT? Pois é, alguma delas será usada no código gerado pelo compilador. 

Usando o compilador gcc, contudo, não é tão simples examinar o código gerado.

Primeiro, vejamos o código assembly gerado para a função main do código 1. Isso pode ser feito usando o utilitário objdump:

```
$ objdump -d -j .text prog
...
0000000000001145 <main>:
    1145: 55                    push   %rbp
    1146: 48 89 e5              mov    %rsp,%rbp
    1149: 48 8d 3d b4 0e 00 00  lea    0xeb4(%rip),%rdi        # 2004 <_IO_stdin_used+0x4>
    1150: e8 db fe ff ff        callq  1030 <puts@plt>
    1155: ba 13 00 00 00        mov    $0x13,%edx
    115a: 48 8d 35 b6 0e 00 00  lea    0xeb6(%rip),%rsi        # 2017 <_IO_stdin_used+0x17>
    1161: bf 01 00 00 00        mov    $0x1,%edi
    1166: e8 d5 fe ff ff        callq  1040 <write@plt>
    116b: b8 00 00 00 00        mov    $0x0,%eax
    1170: 5d                    pop    %rbp
    1171: c3                    retq   
    1172: 66 2e 0f 1f 84 00 00  nopw   %cs:0x0(%rax,%rax,1)
    1179: 00 00 00 
    117c: 0f 1f 40 00           nopl   0x0(%rax)
...
```
No trecho acima, na linha 1150 vê-se uma  chamada à função puts@plt. A sigla PLT significa Procedure Linkage Table, que indica que o programa não vai chamar a função puts, mas uma wrapper dessa função. Isso é comum em código com bibliotecas de link dinâmico, em que o endereço efetivo da função (puts) na memória não é sabido em tempo de compilação, mas somente quando o programa for carregado. No código da wrapper puts@plt vão estar alguns ajustes e uma chamada para um endereço que for conhecido no momento da chamada.

De maneira equivalente, na linha 1166 vê-se uma chamada para a wrapper write@plt.

Analisando código estático

Que tal se compilarmos o código de nosso programa usando link estático?

Para tanto, pode-se usar um parâmetro para o compilador gcc:

 `$ gcc prog.c -o prog --static `
Usando o utilitário objdump novamente, podemos direcionar o resultado do disassembly para um arquivo:

 `$ objdump -D prog > prog.s `
Agora podemos visualizar o arquivo prog.s, buscando pelo código assembly gerado pela inclusão da wrapper das syscalls da libc no programa (confuso ?:-) 

Vejamos o código da função main:
```
 1072 0000000000401b9d <main>:
  1073   401b9d:   55                      push   %rbp
  1074   401b9e:   48 89 e5                mov    %rsp,%rbp
  1075   401ba1:   48 8d 3d 5c b4 07 00    lea    0x7b45c(%rip),%rdi        # 47d004 <_IO_stdin_used+0x4>
  1076   401ba8:   e8 d3 77 00 00          callq  409380 <_IO_puts>
  1077   401bad:   ba 13 00 00 00          mov    $0x13,%edx
  1078   401bb2:   48 8d 35 5e b4 07 00    lea    0x7b45e(%rip),%rsi        # 47d017 <_IO_stdin_used+0x17>
  1079   401bb9:   bf 01 00 00 00          mov    $0x1,%edi
  1080   401bbe:   e8 6d b1 03 00          callq  43cd30 <__libc_write>
  1081   401bc3:   b8 00 00 00 00          mov    $0x0,%eax
  1082   401bc8:   5d                      pop    %rbp
  1083   401bc9:   c3                      retq
  1084   401bca:   66 0f 1f 44 00 00       nopw   0x0(%rax,%rax,1)
```
Na linha 1076 vemos uma chamada à função _IO_puts e na linha 1080 uma chamada a __libc_write. Examinemos o código da função __libc_write:

```
 59781 000000000043cd30 <__libc_write>:
 59782   43cd30:   8b 05 d6 ba 06 00       mov    0x6bad6(%rip),%eax        # 4a880c <__libc_multiple_threads >
 59783   43cd36:   85 c0                   test   %eax,%eax
 59784   43cd38:   75 16                   jne    43cd50 <__libc_write+0x20 >
 59785   43cd3a:   b8 01 00 00 00          mov    $0x1,%eax
 59786   43cd3f:   0f 05                   syscall
 59787   43cd41:   48 3d 00 f0 ff ff       cmp    $0xfffffffffffff000,%rax
 59788   43cd47:   77 57                   ja     43cda0 <__libc_write+0x70>
 59789   43cd49:   c3                      retq
 59790   43cd4a:   66 0f 1f 44 00 00       nopw   0x0(%rax,%rax,1)
 59791   43cd50:   41 54                   push   %r12
 59792   43cd52:   49 89 d4                mov    %rdx,%r12
 59793   43cd55:   55                      push   %rbp
 59794   43cd56:   48 89 f5                mov    %rsi,%rbp
 59795   43cd59:   53                      push   %rbx
 59796   43cd5a:   89 fb                   mov    %edi,%ebx
 59797   43cd5c:   48 83 ec 10             sub    $0x10,%rsp
 59798   43cd60:   e8 2b 1f 00 00          callq  43ec90 <__libc_enable_asynccancel>
 59799   43cd65:   4c 89 e2                mov    %r12,%rdx
 59800   43cd68:   48 89 ee                mov    %rbp,%rsi
 59801   43cd6b:   89 df                   mov    %ebx,%edi
 59802   43cd6d:   41 89 c0                mov    %eax,%r8d
 59803   43cd70:   b8 01 00 00 00          mov    $0x1,%eax
 59804   43cd75:   0f 05                   syscall
 ...
```

No trecho de código acima, vê-se na linha 59804 uma chamada à instrução syscall. É ali que está sendo feita a chamada de sistema pela wrapper function write da glibc!

Nas linhas anteriores, vê-se o ajuste de parâmetros para a chamada de sistema usando registradores.

Examinando a documentação do código de entrada das chamadas de sistema usando a instrução SYSCALL no sistema Linux, vê-se que:

```
; * 64-bit SYSCALL saves rip to rcx, clears rflags.RF, then saves rflags to r11,
; * then loads new ss, cs, and rip from previously programmed MSRs.
; * rflags gets masked by a value from another MSR (so CLD and CLAC
; * are not needed). SYSCALL does not save anything on the stack
; * and does not change rsp.
; *
; * Registers on entry:
; * rax  system call number
; * rcx  return address
; * r11  saved rflags (note: r11 is callee-clobbered register in C ABI)
; * rdi  arg0
; * rsi  arg1
; * rdx  arg2
; * r10  arg3 (needs to be moved to rcx to conform to C ABI)
; * r8   arg4
; * r9   arg5
```

Agora sabendo que o valor no registrador rax é o número da chamada de sistema, podemos examinar no código do kernel do sistema Linux qual é a chamada cujo valor foi copiado para o registrador eax antes da chamada:

```
# 64-bit system call numbers and entry vectors
#
# The format is:
# <number> <abi> <name> <entry point>
#
# The __x64_sys_*() stubs are created on-the-fly for sys_*() system calls
#
# The abi is "common", "64" or "x32" for this file.
#
0	common	read			__x64_sys_read
1	common	write			__x64_sys_write
2	common	open			__x64_sys_open
3	common	close			__x64_sys_close
4.      ...
```

Viram que na linha 59803 o valor 1 foi atribuído ao registrador eax? Viram que o código da syscall write é 1?
Pois é, todas as chamadas de sistema são feitas da mesma maneira, passando valores pelos registradores. Dentro da chamada, o valor que estiver no registrador eax vai indicar qual é a syscall solicitada.

Faz sentido?

**Exemplo de chamada de sistema usando a instrução SYSCALL**

```
; sc.asm
; 
; Para compilar;
; $ nasm -f elf64 sc.asm && ld sc.o -o sc && rm -f sc.o
;
; * Registers on entry:
; * rax  system call number
; * rcx  return address
; * r11  saved rflags (note: r11 is callee-clobbered register in C ABI)
; * rdi  arg0
; * rsi  arg1
; * rdx  arg2
; * r10  arg3 (needs to be moved to rcx to conform to C ABI)
; * r8   arg4
; * r9   arg5
; * (note: r12-r15, rbp, rbx are callee-preserved in C ABI)
; *
; * Only called from user space.
; *
; * When user can change pt_regs->foo always force IRET. That is because
; * it deals with uncanonical addresses better. SYSRET has trouble
; * with them due to bugs in both AMD and Intel CPUs.
;
section .data
   msg     db      "Hello, world!", 0x0a   ; the string and newline char

section .text
   global _start       ; Default entry point for ELF linking

_start:

   ; SysCall: ssize_t write(int fd, const void *buf, size_t count);

   mov     rax, 1      ; código da syscall write (*) 
   mov     rdi, 1      ; arquivo 1 = STDOUT
   mov     rsi, msg    ; endereço da mensagem
   mov     rdx, 14     ; número de bytes a escrever
   syscall

   ; SysCall: void _exit(int status);

   mov    rax, 60       ; código da syscall _exit syscall (*)
   mov    rdi, 0        ; valor de retorno
   syscall

; (*) /usr/include/x86_64-linux-gnu/asm/unistd_64.h 
; #define __NR_write 1
; #define __NR_exit 60
```
**Para compilar o programa acima, chamado sc.asm:**

[ Para instalar ferramentas para compilação assembly em Debian e afins: `$ sudo apt install nasm` ]


 `$ nasm -f elf64 sc.asm && ld sc.o -o sc && rm -f sc.o`
Para executá-lo:

 `$ ./sc`

**Exemplo de chamada de sistema usando a instrução INT**
```
; int.asm
;
; Para compilar: 
; $ nasm -f elf64 int.asm && ld int.o -o int && rm -f int.o
;
; * Arguments:
; * eax  system call number
; * ebx  arg1
; * ecx  arg2
; * edx  arg3
; * esi  arg4
; * edi  arg5      
; * ebp  arg6
;
; Depois da chamada, valor de retorno é colocado em eax. 
   
section .data       ; data segment
   msg     db      "Hello, world!", 0x0a   ; the string and newline char

section .text       ; text segment
   global _start    ; Default entry point for ELF linking
   
_start:    
   ; SysCall: ssize_t write(int fd, const void *buf, size_t count);
   mov eax, 4        ; eax: número da syscall (*)e
   mov ebx, 1        ; ebx: primeiro argumento: fd (1 = STDOUT)
   mov ecx, msg      ; ecx: buff
   mov edx, 14       ; edx: count (tamanho da string)
   int 0x80          ; sycall via int 0x80
   
   ; SysCall: void _exit(int status);
   mov eax, 1        ; eax: número da syscall (*)
   mov ebx, 0        ; ebx: código de saída (0 = EXIT_SUCCESS)
   int 0x80          ; syscall via int 0x80
   
; (*) /usr/include/x86_64-linux-gnu/asm/unistd_32.h 
; #define __NR_exit 1
```

**Para compilar o programa acima, chamado int.asm:**

 `$ nasm -f elf64 int.asm && ld int.o -o int && rm -f int.o`

**Para executá-lo:**

`$ ./int`

Funcionou?

Fez sentido?

Bons estudos!

Hélio