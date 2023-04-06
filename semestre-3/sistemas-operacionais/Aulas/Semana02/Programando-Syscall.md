# Programando para syscalls
## Professor: Hélio Crestana Guardia
## Universidade Federal de São Carlos
---

## Programando
Chamadas de sistema, que compõem o conjunto de serviços oferecidos por um SO aos programas, normalmente são padronizadas.

Neste quesito, Linux procura atender as especificações definidas pelos padrões POSIX, utilizados em sistemas Unix[-like]. Considerando que grande parte do sistema operacional Unix foi à época [re]escrita em linguagem C, também as chamadas de sistema Unix tiveram suas interfaces definidas nesta linguagem.

Cabe a cada SO que oferece chamadas de sistema POSIX implementar os serviços associados, de acordo com suas estruturas internas e funcionalidades. As interfaces das chamadas e os comportamentos estabelecidos têm que ser atendidos.

Antes de estudarmos os diferentes grupos de chamadas de sistema, é preciso familiaridade com o ambiente de trabalho de edição, compilação e execução de programas a partir do shell. Para tanto, é preciso conhecer a ativação e o controle de processos diretamente no shell, entendendo questões de execução em fore e background, redirecionamento de entrada e saída de dados das operações de leitura e escrita no terminal realizadas pelos processos, e o tratamento de sinais.

Os arquivos de suporte desta unidade não são documentos detalhados, mas devem ajudar a entender e familiarizar-se com o tratamento de programas via shell.

É certo que existem ambientes integrados de desenvolvimento para programas em C usando interfaces gráficas, incluindo até IDEs como Eclipse e Netbeans (+ codeblocks, kdevelop, anjuta, + ...) para Linux. Para firmarmos os conceitos, contudo, vamos procurar usar ferramentas mais básicas acessíveis via shell, como o editor de texto vi, a compilação manual de programas com o gcc e o uso do utilitário make.

Tendo entendido o uso desses programas, passamos à fase de experimentações, usando programas exemplo.

Vale lembrar que o manual on-line nos sistemas Unix é a melhor fonte de informações para comandos, chamadas de sistema, utilitários, etc. Assim, para cada programa estudado, é importante ter ao menos 3 janelas de shell abertas: uma para a edição do programa com vi (coragem!), uma para consultar as páginas de manual das diversas funções de biblioteca C e, principalmente, das chamadas de sistema usadas nos programas, e outra para compilar e executar o programa.

Os programas possuem alguns comentários internos. Não são completos mas ajudam a pensar sobre o que é relevante observar em cada caso.

Sugestão: crie um diretório para armazenar os programas da disciplina.

Leia o Leia-me! e estude os programas e suas chamadas de sistema e funções da biblioteca C.

Mãos à obra! 

Hélio

O que é preciso saber com esta unidade:

- editar programas com editor vi
- compilar programas com gcc usando chamadas em linha de comando
- identificar warnings e erros de compilação e saber corrigi-los com - consultas ao manual e ajustes de caminhos de busca do compilador e do linker 
- gerar biblioteca de funções para link estático e dinâmico
- criar Makefiles e compilar e manter grupos de programa com make
- passar parâmetros para o programa principal e acessar variáveis de ambiente
- conhecer chamadas de sistema e o tratamento de valores de retorno em casos de sucesso e erro
- terminar a execução de processos com valores de retorno apropriado em suscesso e erro

---
## vi / vim

vi  / vim (vi improved)

(Para quem quiser aprender sobre o vim online, há um programa interessante, com operações passo-a-passo, chamado vimtutor. Para usar basta executá-lo numa sessão de shell.)

2 modos de operação: modo de comando e modo de inserção.
Há várias formas para ativar o modo de inserção. Estando no modo de inserção, pressione <*Esc*> para voltar ao modo de comando. 

**Edição de arquivo:**

$ vi arq     edita arquivo arq

**Movimentação do CURSOR em modo de comando:**

h  movimenta à esquerda
j  vai para a linha de baixo
k  vai para a linha de cima
l  movimenta à direita
b  vai para o começo da palavra anterior
w  vai para o início da próxima palavra
e  vai para o fim da palavra atual
$  vai para o fim da linha
0  vai para o começo da linha
:n vai para linha n
G    vai para o fim do arquivo
:$   vai para o fim do arquivo
setas? funcionam em algumas versões do vi, como vim


**Movimentação da TELA em modo de comando:**

^f  move uma tela abaixo (forward)
^b  move uma tela acima (backward)
^d  move meia tela para baixo (down / forward)
^u  move meia tela para cima (up / back)
^l  redesenha a tela


**Inserção de texto:**

a  insere à direita do cursor
A  insere no fim da linha
i  insere à esquerda do cursor
I  insere no começo da linha
o  insere na linha de baixo
O  insere na linha de cima
Esc  retorna ao modo de comando


**Edição (alteração/replacement) de texto:**

r     substitui (replaces) o caracter sob o cursor
R    substitui caracteres a partir do cursor, até que <*Esc*> seja pressionado
cw    troca palavra à direita do cursor (change word)
[n]cw troca n palavras à direita do cursor. Ex: 3cw
C     substitui os caracteres até o final na linha
cc    substitui a linha atual, a partir do início
[n]cc substitui n linhas, começando da linha atual. Ex: 4cc
Esc   retorna ao modo de comando


**Remoção de texto:**

x     remove caracter sob o cursor
[n]x  remove n caracteres à direita do cursor. Ex: 5x
dd    remove a linha atual
[n]dd remove n linhas a partir da atual. Ex: 3dd
dw    remove uma palavra à direita do cursor
[n]dw remove n palavras à direita do cursor. Ex: 2dw
D     apaga até o fim da linha
J     junta (joins) a linha de baixo com a linha atual


**Para localizar uma string:**

Esc
/string   busca próxima ocorrência da string
?string   busca ocorrência anterior da string, voltando no arquivo
n             repete busca anterior (para baixo ou para cima)


**Repetindo o último comando:**

.        repete a última operação (inserção, remoção, substituição, etc.)


**Copiando dados para o buffer interno:**

Y       copia 1 linha para o buffer
[n]Y  copia n linhas para o buffer. Ex: 5Y
p        cola (paste) as informações do buffer na próxima linha
P        cola (paste) as informações do buffer na linha anterior


**Inserindo (lendo/reading) um arquivo para a posição atual do cursor:**

:r arq


**Ajustando a aparência do editor:**

:set number        ativa exibição dos números de linha
:set nonumber   desativa exibição dos números de linha
:syntax on           ativa o reconhecimento da sintaxe do arquivo (.c, .html, etc.)
:syntax off           desativa o reconhecimento da sintaxe do arquivo
:set tabstop=x   controla o tamanho do espaço deixado pelo Tab
:set all                  consulta ajustes ativos


OBS: configurações podem ser salvas em ~/.virc (ou ~/.vimrc, para vim)


**Alterando o arquivo sendo editado:**

:e novo_arq     fecha o arquivo atual (se não alterado) e abre novo_arq para edição


**Para sair do vi:**

Esc
:w                           salva com o nome atual
:w novo_nome   salva como novo_nome
:wq                         salva e sai
:x                             salva e sai
:q                            sai sem salvar (se não houve alterações)
:q!                          sai sem salvar (mesmo se houve alterações)


**Pânico?**

Sai sem salvar: <*Esc*>:q! 

---
## gcc

**Compilando programas em linha de comando com gcc.**

Compilador: cc / gcc        // man gcc :-)


Uso:
gcc prog.c [-o prog] [bib.o] [-Iinc_dir] [-Llib_dir] [-llink_bib]

Ex:

- gcc prog.c                 // compila, faz link e salva código executável com o nome a.out
- gcc prog.c -o prog         // compila, faz link e salva o arquivo com o nome prog
- gcc -c prog.c              // compila apenas, gerando prog.o
- gcc prog.c -lm             // compila, faz link incluindo a biblioteca libm; gera a.out, a não ser que se use -o nome...

---
## cpp
Comandos do pré-processador (cpp)
```
man cpp               // C Preprocessor

#include              // #include<unistd.h>  (*)

#define               // #define _OPENMP
#ifdef / #endif       // #ifdef _OPENMP
```

```
#if defined (_OPENMP) && defined (VERBOSE)
...
#else
...
#endif
```

(*) Localização dos cabeçalhos (includes):

```
#include <xxx.h>  // biblioteca padrão,  em /usr/include
#include “xxx.h”    // diretório local, ou especificado com -I
```

---
## link e bibliotecas

Na fase de geração de código na compilação, o linker precisa conectar as bibliotecas usadas no programa sendo gerado, resolvendo questões de endereçamento das funções, variáveis, etc.

Os códigos das funções cujo código se encontra na biblioteca C padrão (libc ou glibc) são ligados automaticamente, já que essa biblioteca é essencial para todos os programas. 

Já para ligar os arquivos de outras bibliotecas usadas é preciso avisar o compilador em linha de comando. Isso é feito com o parâmeto -l e o nome da biblioteca, omitindo-se o prefixo lib. 

Veja a página de manual da função sqrt, por exemplo. Ali há uma indicação para "Link with -lm". 

Os arquivos das bibliotecas de código já compilado são comumente salvos em /lib e em /usr/lib. Caso seja preciso usar bibliotecas salvas em outros diretórios, é possível usar o parâmetro -L em linha de comando para especificar o diretório.

**Link e bibliotecas na fase de compilação**

gcc ... -lbib              // inclui biblioteca libbib.a  (*)
gcc ... -Llib_dir        // especifica caminho de busca

**(*) Localização das bibliotecas:**

Link estático:     /usr/lib (também libs dinâmicas adicionais)
Link dinâmico:  /lib, /usr/lib, (/etc/ld.so.conf)

**Resolução de endereços de funções em bibliotecas dinâmicas**

Quando o programa é compilado para uso de  bibliotecas de link dinâmico (*.so), algumas referências a objetos (funções e variáveis) dentro dos códigos das bibliotecas são resolvidas no momento do carregamento dos programas. Esse trabalho é feito pelo programa loader do SO, comumente o programa ld-linux.so. 

Os diretórios a partir dos quais são buscadas as bibliotecas necessárias são comumente definidos pelo arquivo /etc/ld.so.conf. Além disso, o usuário pode definir uma variável de ambiente chamada LD_LIBRARY_PATH, que especifica outros diretórios de busca para bibliotecas dinâmicas, como o diretório atual, por exemplo.

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

Por padrão, a compilação com gcc seleciona o link dinâmico para a biblioteca libc e outras eventuais bibliotecas padrão. O comando ldd exibe informações sobre dependências de bibliotecas dinâmicas  de um programa e indica um possível mapeamento de memórias para seus códigos no carregamento do programa indicado. Caso alguma biblioteca não possa ser localizada para mapeamento, isso comumente pode ser resolvido fazendo ajustes em LD_LIBRARY_PATH.

ldd: exibe dependências de bibliotecas dinâmicas   // man ldd
ldconfig: configura ajustes para links dinâmicos       // man ldconfig

**Programas com código estático**

O uso de bibliotecas dinâmicas gera uma economia significativa no uso de espaço do sistema de arquivos, uma vez que esses códigos não precisam ser salvos nos arquivos executáveis. Além disso, eles são carregados na memória apenas uma vez e, como não são alterados em tempo de execução, podem ser compartilhados também na memória.

Caso seja desejável compilar um programa com ligação estática das bibliotecas, usa-se o parâmetro -static.

gcc ... -static    // previne ligação com bibliotecas dinâmicas

gcc ... -shared  // produz objeto compartilhado que pode ser ”linkado” com outros objetos para formar um programa.

---
## make
Quando há vários programas relacionados a compilar, saber o que deve ser compilado e o que não precisa ser recompilado pode ser uma tarefa árdua e ineficiente. Para ajudar nessa tarefa, pode-se usar o utilitário make.

make usa informações de um arquivo de configuração (GNUmakefile, makefile, Makefile, ou outro especificado) para manter (compilar, linear, mover, copiar, remover, ...) grupos de programas. 

As ações realizadas pelo make são baseadas em regras e na data de última modificação de cada um dos arquivos de dependência. De maneira resumida, make executa comandos definidos no  Makefile para atualizar um ou mais targets, tipicamente programas.

Makefile   (arquivo texto)

**DEFINIÇÕES**
target:  componentes
<*Tab*>  regra            
pode haver quantas linhas com regras  forem necessárias, desde que comecem com <*tab*>

Ex:
```
DIR=/usr/local

OPT=-Wall
PROGS=prog teste

# targets

all:  prog teste

clean:                 # nome do target deve começar na 1a coluna
    rm -f $(PROGS)     # linhas abaixo do target indicam ações; 

install:
    cp $(PROGS) $(DIR)/bin

prog: prog.c bib.o
    gcc $(OPT) prog.c bib.o -o prog

bib.o: bib.c
    gcc $(OPT) -c bib.c

teste: teste.c
    gcc $(OPT) teste.c -o teste
```
 
**Para usar o comando make com esse makefile, poderia-se digitar:**
```
$ make prog
$ make teste prog
$ make clean
$ make        // executa os comandos do primeiro "target" encontrado no Makefile; neste caso, all
```

---
## debugging
```
gcc -W__     // define nível de warnings.
Ex: -Wall

gcc -g         //  gera programa instrumentado para depuração

gcc -glevel

man gcc
    / Warning Options
    / Debugging Options
```

**Depurando a execução de programas com gdb**

(ftp://ftp.gnu.org/old-gnu/Manuals/gdb/html_chapter/gdb_toc.html)

```
gdb prog
(gdb) help         // !

// Definindo breakpoints
(gdb) break        // Set breakpoint at specified location.
(gdb) break main   // exemplo

// Executando o programa 
(gdb) run        // Start debugged program.  You may specify arguments to give it.
(gdb) start      // Run the debugged program until the beginning of the main procedure.
(gdb) nexti      // Step program, proceeding through subroutine calls.
(gdb) n          //   "
(gdb) nexti      // Step one instruction, but proceed through subroutine calls.
(gdb) ni         //   "
(gdb) step       // Step program until it reaches a different source line.
(gbd) s          //   "
(gdb) step i     // Step one instruction exactly
(gdb) si         //   "
(gdb) kill       // Kill execution of program being debugged.

// Exibindo informações
(gdb) disassemble     // Disassemble a specified section of memory
(gdb) dis             //   "
(gdb) disass printf   // ex: mostra código da função printf
(gdb) info registers  // List of integer registers and their contents, for selected stack frame.
(gdb) i r             //   " 
(gdb) i r rax         // lista conteúdo do registrador a 
(gdb) info stack      // Print backtrace of all stack frames, or innermost COUNT frames.
(gdb) i stack         //   "
(gdb) where           //   "
(gdb) backtrace / bt  //   "
(gdb) info proc mappings  // list of mapped memory regions
(gdb) info variables  // All global and static variable names, or those matching REGEXP.
(gdb) info functions  // All function names, or those matching REGEXP.

(gdb) quit            // termina a execução do depurador gdb
```

---
## Usando syscalls

Embora os comportamentos esperados das chamadas de sistema sejam definidos por padrões como POSIX e BSD, a implementação interna das chamadas é específica a cada SO.
Nos documentações dos padrões há também uma especificação para as interfaces de chamadas de sistema, incluindo os parâmetros e valores de retorno, considerando chamadas em linguagem C.

De maneira geral, as funções das interfaces das chamadas de sistema retornam o valor 0 em caso de sucesso, e -1 em caso de erro. Neste caso, é possível consultar o código de erro através da variável errno.
Funções como perror(), strerror() e strerror_r() também podem ser usadas para a obtenção da mensagem de erro correspondente ao erro ocorrido na chamada de sistema mais recente.

**Tratamento de erro:**
```
#include <errno.h>

errno

perror( )

strerror( ) / strerror_r( )```