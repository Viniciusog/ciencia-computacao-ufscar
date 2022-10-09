# Conhecendo o Linux (e todos os Unix-like)...
##### Professor: Hélio Crestana Guardia
##### Universidade Federal de São Carlos

---

### Conhecendo o Linux

Neste curso, vamos usar GNU/Linux como plataforma para o estudo de sistemas operacionais. Linux é um sistema operacional (SO) usado em uma grande variedade de dispositivos, de smartphones e TVs até em supercomputadores formados de grandes aglomerados (clusters) de equipamentos.

Especificamente, vamos observar alguns grupos de chamadas de sistema, examinando os serviços tipicamente oferecidos pelos SOs. Mais do que isso, vamos também procurar pensar, investigar e ver na prática como esse SO trata das questões conceituais previstas para ambientes computacionais multiusuários e multitarefas. 

Linux é um exemplo de sistema Unix-like, que procura adequar-se aos padrões Unix, definidos por Single Unix Specification, mas que é padronizado pelas definições Linux Standard Base. Esse conjunto de padrões define a estrutura de um sistema Linux, incluindo, entre outros aspectos, a hierarquia do sistema de arquivos, o conjunto de programas utilitários e as chamadas de sistema oferecidas.

Por tratar-se de uma plataforma aberta e aderente a padrões, Linux, entre outros SOs, permite investigarmos os serviços tipicamente oferecidos por um SO e também examinarmos como esses serviços são implementados, estudando seu código fonte.

Linux em si é o núcleo do sistema operacional, ou kernel. Isso inclui os programas de boot e as bibliotecas usadas em tempo de execução. Só o núcleo do SO, contudo, não torna um sistema computacional completamente útil para o usuário. Afinal, para que o SO possa oferecer serviços (via chamadas de sistema) aos programas, é preciso que exista um mecanismo para iniciarmos os programas que queremos executar! Assim, é comum precisarmos ao menos de um shell, como o bash, ou o dash, de programas utilitários e de ferramentas variadas. Esses conjuntos de programas são organizados em distribuições Linux, que atendem a diferentes fins. 

Entre as distribuições abertas, destacam-se Ubuntu e outras derivadas, que procuram utilizar sempre versões  atualizadas dos pacotes que fornece, além de preocupar-se em simplificar sua utilização. As distribuições mais direcionadas ao usuário final também têm suporte a uma grande variedade de dispositivos, o que as torna aptas a reconhecer e configurar drivers de vídeo e rede, entre outros, de maneira simples. Outras distribuições Linux de destaque incluem Debian, Fedora, OpenSuse, e CentOS, que é uma distribuição baseada em RedHat, com enfoque corporativo.  

Para começar os estudos, precisamos acesso a  um sistema com Linux. Opções para isso incluem executar uma versão sem instalação (live), instalar uma versão do Linux em uma máquina virtual sobre seu sistema operacional padrão ou, bem interessante, instalar Linux como seu SO padrão!

Já tem acesso a um sistema?! Vamos praticar, então!

Bons estudos,

Hélio


**O que é preciso saber com esta unidade:**

login e interação com sistemas Linux/Unix, usando interface gráfica e shell
conhecer a estrutura de um sistema de arquivos *nix
manipular arquivos e diretórios com utilitários disponíveis via shell
manipular permissões e outros atributos associados às entradas no sistema de arquivos (também via shell)
criar processos com execução em fore e background, realizar redirecionamentos de E/S, tratar prioridades
identificar processos em execução e o consumo de recursos de CPU, memória e sistema de arquivos
enviar sinais para parar, continuar, interromper e terminar processos


PS: para quem quiser saber um pouco mais sobre o histórico de GNU e Linux, seguem links para as mensagens iniciais sobre os desenvolvimentos dessas plataformas.

    https://www.gnu.org/gnu/initial-announcement.en.html
    https://www.cs.cmu.edu/~awb/linux.history.html

PS2: quer conhecer filosofias do projeto original do Unix? Veja 

    The UNIX Time-Sharing System. Dennis M. Ritchie and Ken Thompson Bell Laboratories
    (https://people.eecs.berkeley.edu/~brewer/cs262/unix.pdf)

---
#### Interface gráfica    

Efetuando-se o login numa interface gráfica, o usuário passa a interagir com o sistema Linux através de um ambiente de janelas. Entre as opções de configuração do ambiente gráfico, que existem às dezenas, algumas das mais comuns são GNOME, KDE e UNITY(LightDM).

Tipicamente, os gerenciadores do ambiente gráfico (window managers) utilizam o conceito de janelas associadas às aplicações, para onde são direcionadas as operações de entrada e saída de dados. Janelas são dimensionáveis e podem ser sobrepostas, maximizadas e minimizadas. Mecanismos existem para selecionar a janela ativa, que recebe os eventos de teclado e mouse, tipicamente em função da posição do mouse ou do click de algum de seus botões. 

Janelas podem ter bordas variáveis, botões de controle (para minimização, maximização e encerramento da aplicação associada, além de regiões de controle de redimensionamento, tipicamente nos cantos das bordas. Dentro de uma janela é possível ter áreas de apresentação para desenhos e textos, áreas em que o usuário pode fornecer dados, além de botões. De maneira geral, cabe ao desenvolvedor de uma aplicação associada a uma janela determinar as ações associadas aos botões e eventos pré-definidos de controle de janela ou associados aos elementos que a janela contém.

Além de diferirem no formato e nas funcionalidades associadas às janelas, gerentes de interface gráfica (Display Managers) possuem elementos gráficos comumente presentes na tela, como barras de controle de aplicações e ícones associados a recursos de armazenamento e dispositivos.

As funcionalidades associadas ao pressionamento dos botões do mouse na área de trabalho também podem variar, tipicamente servindo para oferecer acesso a menus para manipulação de janelas ou aplicações.

Normalmente, todo ambiente gráfico costuma ter ao menos uma aplicação associada ao acesso e gerenciamento ao sistema de arquivos (file manager), editores de texto, navegadores Web e janelas de terminal associadas ao shell definido para a conta do usuário. Uma infinidade de utilitários com interfaces gráficas existem para sistemas Linux e costumam estar disponíveis nas variadas distribuições.

Programas gerenciadores de pacotes (grupos de programas) permitem a adição, remoção e atualização de programas i instalados no sistema local, e costumam ser fornecidos pelas distribuições e pelos gerenciadores de ambientes gráficos.

Gerenciadores da interface gráfica também costumam ter suporte facilitado para o uso de unidades de armazenamento removíveis. Uma particularidade no acesso a sistemas de arquivos em dispositivos removíveis é a necessidade de "desmontar” seus sistemas de arquivo antes que eles possam ser removidos com segurança. Isto ocorre pois o sistema operacional costuma manter buffers dos arquivos abertos em memória, de forma que nem todos os acessos aos arquivos geram a gravação imediata dos dados nos dispositivos. A montagem do sistema de arquivos em dispositivos é tipicamente feita de forma automática, mas a desmontagem deve ser feita manualmente, forçando a atualização dos dados no dispositivo.

Para encerrar uma sessão gráfica é preciso executar um procedimento de logout. Normalmente, há opções em alguma barra de menus que possibilita esse procedimento, além das opções de desligar e reiniciar o computador.

Também por motivos de consistência do sistema de arquivos, é importante selecionar um procedimento de desligamento via software antes de desligar o computador.

---
#### SHELL

**Conectando-se ao sistema: login**

O acesso a um sistema Linux depende da identificação de um nome de usuário e da senha correspondente, num procedimento de login. Enquanto o usuário root tem direito total sobre todos os recursos do sistema, os demais usuários têm acesso para leitura de grande parte dos arquivos, podem executar a maioria das aplicações, e têm direito de escrita somente sobre seus respectivos diretórios de trabalho (/home/fulano) e área temporária (/tmp).

Caso o ambiente gráfico tenha sido instalado, acompanhado dos gerenciadores do display (xdm, gdm ou kdm, por exemplo), a opção de login através de uma interface gráfica é selecionada automaticamente. Independentemente de o modo gráfico estar configurado, é possível executar-se o procedimento de login em modo texto.

**Login em modo texto**

No Linux, a combinação de teclas [<ctrl>]<alt><Fn> (n={1,2,.., 7}) dá acesso a 7 terminais virtuais através dos quais pode-se executar o procedimento de login numa interface de texto com acesso direto a um shell. Em sistemas em que a interface gráfica foi instalada, ela comumente pode ser acessada no primeiro terminal virtual (<alt><F1>).

Um shell é um programa interpretador de comandos, que tem a finalidade de controlar a ativação e manipulação de programas determinados pelo usuário. Comandos podem ser passados para o shell de maneira interativa ou através de programas (scripts).

Diversas versões de shell podem estar instaladas num sistema, sendo listadas no arquivo /etc/shells. Os shells mais comuns são sh, bash, csh, ksh, tcsh, zsh e dash. As diferenças entre esses programas podem ser notadas tanto no tratamento dos comandos interativos quanto na “linguagem” usada para escrever os scripts.

Comandos úteis para a linguagem de scripts incluem, por exemplo análise de expressões, iterações, decisões e desvios.

Bash é talvez o shell mais utilizado atualmente. Informações sobre sua configuração e seus comandos internos podem ser obtidas digitando-se help diretamente no prompt.

**OBS 1:** ao digitar comandos no shell, há diferenças no uso de letras maiúsculas e minúsculas. Comandos, em geral, são todos definidos com letras minúsculas. Variáveis de ambiente comumente contêm nomes apenas com letras maiúsculas.

**OBS 2:** nas documentações, é comum usar-se $ cmd para indicar a execução do comando cmd no shell. $ indica o prompt de shell de um  usuário comum, ou seja, trata-se de comandos que qualquer usuário pode executar. Comandos que devem ser executados com privilégio de root normalmente são indicados com # cmd.

**OBS 3:** $ cmd1 ; cmd2 <enter> indica dois comandos na mesma linha (pode haver mais). “;” indica separação de comandos na mesma linha.

**OBS 4:** $ .... \ <enter> (barra invertida antes de digitar <enter>) indica para o shell que, embora o comando está se estendendo para uma nova linha, ele ainda não foi concluído. “\” é usado como último caracter ao final de cada linha nesses casos, exceto na última.

**OBS 5:** ~ representa a área (HOME) de um usuário. Por exemplo, ~fulano refere-se ao HOME do usuário fulano. Quando um nome de usuário não é especificado, como em ~/progs , assume-se como referência o diretório home do usuário corrente, mais os diretóris especificados. Ex: $ ls ~fulano/pub  lista o conteúdo do diretório pub, localizado na área (HOME) do usuário fulano.

**Variáveis de ambiente**

Variáveis  podem ser utilizadas nos shells para armazenar informações úteis sobre o usuário e sobre suas preferências de comandos, além de várias outras configurações relevantes para a sessão e para os programas que serão executados.

Exemplo de variáveis incluem: HOME, SHELL, USER, PATH, etc.

A variável PATH, por exemplo, define os diretórios onde serão buscados os programas solicitados para execução.

Além de servirem para o controle do funcionamento do shell (shell variables), variáveis podem ser tornadas visíveis para os programas iniciados a partir do shell. Isso é feito "exportando-as", o que as tornam variáveis de ambiente (environment variables).  

A sintaxe para as configurações de variáveis do shell e de ambient depende do shell utilizado. No bash, é possível fazer como ilustrado a seguir:

```
bash:                       // exemplo de ajuste do PATH.  $ indica o prompt do shell

$ PATH=$PATH:$HOME/bin      // define a variável para o shell
$ export PATH               // exporta variável, tornando-a visível para
                            // programas executados a partir do shell
ou
$ export PATH=$PATH:$HOME/bin     // definição e exportação feitas com um único comando
```


Uma lista completa das variáveis definidas numa sessão de shell pode ser exibida com o comando set. O comando env exibe as variáveis de ambientes exportadas aos programas nessa sessão de shell.

A referência ao conteúdo de uma variável do shell pode ser feito da seguinte forma:

$NomeVar   ou

${NomeVar}

O comando echo, que exibe texto no terminal, também pode ser usado para verificar o conteúdo de variáveis de ambiente específicas.

 

**set, unset, env, setenv, unsetenv, export:** funções do shell para ler e escrever variáveis de ambiente.

Para exibir-se o conteúdo de uma variável, do shell ou de ambiente, é possível usar o comando interno do shell chamado echo:

echo: exibe uma linha de texto.
Ex: $ echo teste; echo $USER; echo $PATH; echo ${PATH


**Configuração de parâmetros do terminal**

Além de definir variáveis de controle para a sessão de shell atual, há alguns comandos que permitem o ajuste de aspectos do funcionamento do terminal de entrada e saída para o usuário:

 

**stty:** exibe e ajusta configurações do terminal. Ex: $ stty –a   ;  stty erase ^H

**clear:** limpa a tela do terminal. Ex: $ clear


**Histórico de comandos e substituições**

Diversos comandos e recursos do shell, como o histórico (history) e apelidos (alias), oferecem facilidades para a ativação de comandos. 

**history:** manipula a lista interna de comandos realizados no shell.

Algumas variáveis de ambiente definem como o histórico será salvo:

- HISTSIZE : define o tamanho do histórico guardado;
- HISTFILE : indica o nome do arquivo para salvamento do histórico de comandos;
- HISTFILESIZE : define o número máximo de comandos salvos no arquivo de histórico.
Os comandos a seguir ilustram o uso do histórico de comandos salvo pelo shell:

>
     $ !! : repete o último comando digitado
     $ !num : repete o comando número num do histórico
     $ !cmd : repete o último comando iniciado com a palavra cmd.
     $ ^old^new : executa o último comando, substituindo a string old por new
 

Na interação com o shell, é possível ainda definir apelidos (ou filtros) para os comandos digitados. Isso é feito com o comando **alias**:

**alias**: exibe ou ajusta apelidos para comandos. **unalias** os remove. 

Ex: alias rm=’rm –i’        // indica para o shell que quando o comando rm for digitado deve-se executar  rm -i


**Configuração da sessão de shell**

Arquivos específicos presentes na área do usuário (~/) e no diretório de configurações do sistema (/etc) permitem a configuração das sessões de utilização de um shell.

Há dois tipos de sessão de shell :

sessão de login, iniciada a partir do procedimento de login texto ou via acesso remoto;
sessão interativa, iniciada numa janela da interface gráfica, por exemplo, ou a partir de outra sessão de shell.
Para o programa shell bash, os seguintes arquivos de configuração são relevantes.

Para um shell de login:

/etc/profile               // configurações definidas pelo root, válidas para todos os usuários
~/.bash_profile            // configurações específicas do usuário
~/.bash_login              // configurações específicas do usuário
~/.profile                 // configurações específicas do usuário
 
Quando uma sessão de shell de login termina, são executados os comandos listados em ~/.bash_logout.

Assim, vale observar que, se um usuário deseja fazer ajustes para toda sessão interativa de shell, é comum usar-se o arquivo ~/.bashrc:

~/.bashrc   : configurações definidas pelo usuário. Pode conter referência a um arquivo de configuração em /etc/bashrc ou /etc/bash.bashrc.
Comandos úteis nos arquivos de configuração incluem: set, alias, stty, etc.

**Encerrando uma sessão de shell**

Uma sessão de login em modo texto é encerrada com o comando logout.

A combinação de teclas <ctrl><D>, normalmente definida como caracter indicador de fim de arquivo (EOF) via **stty**, também pode comumente ser usada para encerrar uma sessão de login. **Exit** termina uma sequência de comandos num shell ou encerra uma sessão de login.

- logout: comando interno do shell para encerrar uma sessão num computador
- exit: função interna do shell para encerrar um nível na sequência de operações sendo executadas ou um shell interativo. No shell de login tem o mesmo efeito de logout

---
#### Ajuda Online

A melhor fonte de informações em sistemas Linux/Unix é o manual on-line existente em todos os sistemas! Informações sobre o sistema, comandos utilitários, chamadas de sistema, funções das APIs instaladas, arquivos de configuração e muito mais, são comumente instaladas num sistema Unix na forma de páginas de manual. Digitando-se comandos diretamente na sessão do shell é possível acessar as suas funcionalidades.

**man:** comando de acesso às páginas do manual on-line do sistema.

**Seções:** (1) Comandos do usuário, (2) Chamadas do sistema, (3) Funções da biblioteca C, (4) Dispositivos e interfaces de rede, (5) Formatos de arquivos, (6) Jogos e demonstrativos, (7) Ambiente de trabalho, tabelas e macros troff, (8) Manutenção do sistema.

Páginas do manual são normalmente armazenadas como arquivos texto formatados para exibição com comandos roff, depois de descompactados. O arquivo /etc/man.config (ou /usr/lib/man.config) contém informações sobre os diretórios que contêm páginas de manual, o que também pode ser especificado pela variável de ambiente MANPATH.

Ex: man man, man 2 sleep, man -a passwd, man -k ...

**Daqui para frente, é bom ter ao menos dois shells ativos: um para pesquisar o comando com man, e outro para experimentá-lo!**

Whatis e apropos são outros comandos de ajuda, que exibem parte das informações comumente mostradas pelo comando man:

 

**whatis:** apresenta a descrição de comandos, tipicamente uma parte inicial da página de manual completa. Ex: whatis ls

**makewhatis:** cria a base de dados para o comando whatis. É normalmente executado periodicamente, de forma automática, no sistema.

**apropos:** mostra seções e páginas do manual que contém referências a um comando, pesquisando a base de dados do comando whatis

 
Já os comandos **whereis** e **which** ajudam na **localização** de comandos e arquivos:

**whereis**: fornece a localização de um comando executável, tipicamente buscando-o nos diretórios que costumam conter arquivos executáveis na hierarquia do sistema de arquivos Unix. Ex: whereis man

**which**: apresenta o nome (caminho) completo de um comando, caso ele estema definido em algum caminho de busca do shell corrente (PATH). Ex: which ls

Informações específicas sobre o bash podem ser obtidas com o comando help, digitado diretamente no prompt do shell. Particularmente, vale a pena examinar a relação de comandos internos (BUILTIN), o tratamento de sinais, a configuração do terminal, entre outros aspectos.

----
#### Utilitários comuns

Sistemas Unix-like possuem padronizações, como as especificadas por Single Unix Specification, que definem, entre outras coisas, um conjunto de programas utilitários comuns. 

**Utilitários para manipulação de arquivos e diretórios**

**ls:** mostra o conteúdo de diretórios. Ex: ```ls -l /home```
**pwd:** informa o nome do diretório corrente. Ex: ```pwd```
**cd:** muda o diretório de trabalho. Ex: ```cd /etc, cd .., cd ~/www, cd ../../local```
**cp:** copia arquivos. Ex: ```cp /tmp/arq ., cp -r dir1 ../dir2, cp arq1 arq2```
**mv:** move ou renomeia arquivos ou diretórios. Ex: ```mv /tmp/arq ., mv arq novo_nome```
**mkdir:** cria diretórios. Ex: ```mkdir dir, mkdir www pub tmp```
**rm:** remove arquivos. Ex: ```rm arq, rm -i arq, rm -f arq, rm -rf diret```
**rmdir:** remove diretórios. Ex: ```rmdir diret, rmdir dir1 dir2 /tmp/dir3```
**ln:** cria um link para um arquivo ou diretório. Ex: ```ln -s /bin/ls dir, ln -s /tmp tmp```
**cat:** lista o conteúdo de arquivos. Ex: ```cat /etc/fstab```
**more:** filtro de exibição de dados. Ex: ```more /etc/fstab```
**less:** filtro de exibição de dados. Ex: ```less /etc/fstab```
**cmp:** compara 2 arquivos. Ex: ```cmp arq1 arq1```
**diff:** exibe as diferenças entre 2 arquivos texto, linha por linha. Ex: ```diff arq1 arq2```
**find:** percorre uma hierarquia de diretórios. Ex: ```find . -name .doc -print,```
```find / -name \*.jpg -exec rm -f {} \;```
**grep:** imprime linhas que possuem um padrão especificado. Ex: ```grep root /etc/passwd```
**file:** determina o tipo de um arquivo (texto, binário, script do shell, etc.). Ex: ```file /bin/ls, file /etc/passwd```
**tail:** exibe a parte final de um arquivo. Ex: ```tail /var/log/messages, tail -20 /var/log/messages```
**head:** exibe as primeiras linhas de um arquivo. Ex: ```head /var/log/messages, head -20 /var/log/messages```
**cut:** seleciona partes de uma linha de texto. Ex: ```cut -c 10-20 /etc/passwd, cut -d: -f  5 /etc/passwd```
**wc:** contador de palavras, linhas e bytes. Ex: ```wc -l /etc/passwd```
**sort:** ordena linhas de arquivo texto. Ex: ```sort arq, sort -n -r arq```
**touch:** altera as datas de acesso e modificação de arquivos. Ex: ```touch *.h *.c```
**lsof:** lista arquivos abertos.

**Utilitários para a grupamento, conversão e compressão de arquivos**

**tar:** cria arquivos para tapes e adiciona ou remove arquivos. Ex: ```tar -tvf arq.tar, tar -cvf dir.tar dir, tar -xvf dir.tar, tar cvzf diret.tgz diret, tar xvzf diret.tgz```
**dd:** copia arquivos, podendo realizar conversões de formato. Ex: ```dd if=bootnet.img of=/dev/fd0```. Pode acessar dispositivos diretamente, sem passar pelo sistema de arquivos, mas requer privilégio de root. 
**cpio:** copia arquivos de/para dispositivos de E/S
**uuencode / uudecode:** codifica um arquivo binário para uma representação que pode ser enviada por e-mail. Uudecode decodifica o arquivo.
**compress / uncompress:** comprime e descomprime dados. Ex: ```compress log, uncompress log.Z```
**gzip / gunzip:** comprime ou expande arquivos. Ex: ```gzip arq.ext, gunzip arq.ext.gz```
**zip / unzip:** empacota e comprime / descomprime arquivos. Ex: ```zip arq.ext, unzip arq.ext.zip```
**bzip2 / bunzip2:** comprime / descomprime arquivos. Ex: ```bzip2 arq.ext, bunzip2 arq.ext.bz2```

**Gerenciamento de partições e sistemas de arquivo**

Assim como em outros sistemas operacionais, Linux permite a manipulação e o acesso a diversas partições nos discos. O utilitário **fdisk** é utilizado para essas manipulações. O nome do dispositivo a ser manipulado é especificado como parâmetro (e.g. **/dev/hda, /dev/hdb, ...**). Um sistema de arquivos deve ser criado, formatando-o com o comando mkfs, em cada partição que se deseja utilizar (formatação).

**fdisk:** manipula tabelas de partições de discos rígidos. Ex. ```fdisk /dev/hda```
**du:** exibe estatísticas da utilização do disco. Ex: ```du -sk .```
**df:** exibe informações sobre o espaço livre no disco. Ex: ```df -k``` 
**quota:** informa limites estabelecidos e ocupação do disco pelo usuário. Ex: ```quota -v```  
**mkfs:** constrói sistemas de arquivos em partições. Ex: ```mkfs -t ext4 /dev/hda2, mkfs -t msdos /dev/fd0```
**fsck:** verifica e repara sistemas de arquivos. Ex: ```fsck /dev/hda3```
**mkswap (linux):** cria uma área de swap no Linux. Ex: ```mkswap /dev/hda5```
**swapon / swapoff:** ativa / desativa arquivos e dispositivos de memória virtual e swap
**mount / umount:** monta / desmonta sistemas de arquivos. Ex: ```mount /dev/sda2 /home```
**showmount:** exibe informações sobre os sistemas de arquivo exportados via NFS por um servidor
**tune2fs:** ajusta parâmetros de um sistema de arquivos ext2. Ex: ```tune2fs -l /dev/hda3, tune2fs -j /dev/hda2```
