# Processos
## Professor: Hélio Crestana Guardia
## Universidade Federal de São Carlos
---

## Definições

À medida que foi desejável usar os computadores para execução [simultânea] de diversos programas, foi preciso criar mecanismos para representar e controlar cada programa. Para tanto, os SOs criaram uma abstração que é o conceito de processo. De maneira resumida, **processo** é um termo usado para indicar um programa em execução.

Mas, por quê pode haver vários programas em execução?

Considerando um computador pessoal de um estudante de computação, quais programas podem estar sendo executados?

- um programa navegador WWW com cerca de uma dezena de abas abertas. Apenas uma aba estará em primeiro plano, recebendo a atenção eventual do usuário, mas várias delas estarão sendo atualizadas em segundo plano, à medida que recebem dados e em função do parâmetro "refresh" nos documentos HTML, por exemplo, ou em função do código (javascript) que executam;
- uma outra janela do navegador WWW conectada a algum servidor de streaming. Informações contendo trechos de vídeo e áudio são recebidas constantemente no formato da codificação utilizada e são convertidas em sequências de imagens numa taxa apropriada para visualização contínua. Como a janela está sobreposta por outra, ouve-se o som apenas. [ou]
- um programa de áudio para streaming, que está constantemente recebendo dados pela rede e gerando sinais para o controlador de som;
- um programa anti-vírus que filtra as operações de leitura e escrita em disco;
vários mini-aplicativos associados a redes sociais; a maioria parada à espera de dados com notificações encaminhadas por servidores remotos, eventualmente gerando a exibição de alguma janela ou áudio cada vez que uma notificação é recebida;
- algum programa para transferência de arquivos no modelo torrent, também executando em segundo plano, mas enviando e recebendo dados de/para uma série de outros computadores remotos;
- [um jogo MMORPG em tela cheia, usando todos os núcleos da GPU para manter o vídeo contínuo, com a localização precisa dos avatares e realizando as ações locais e remotas em tempo real;]
- Ah, algum IDE (ambiente integrado para desenvolvimento de programas) onde está sendo editado o programa a entregar amanhã... Talvez haja várias abas abertas, se o código for modularizado, mas apenas uma delas estará em edição num dado momento, muito eventualmente... :-)

Que tal abrir o programa "gerenciador de tarefas" examinar o que está em execução? Além dos programas mencionados, serão visíveis vários programas relacionados a serviços e ao funcionamento do SO. Isso ocorre pois comumente o projeto do SO tem partes de suas funcionalidades executadas na forma de processos também, fora do núcleo. Vale observar que esses programas vão entrar em execução apenas eventualmente, comumente em função da ocorrência de eventos específicos.

Bem, lógica semelhante vale para o smartphone, exceto que o programa "telefone" nunca é usado :-)

Talvez a conclusão seja que em dispositivos computacionais pessoais há vários programas ativos, comumente bloqueados à espera do recebimento de dados e da ocorrência de eventos, e alguns programas prontos para execução, que periodicamente vão receber frações de uso do processador.

Já num computador servidor, voltado à execução de programas, o cenário é outro. Pode haver vários programas prontos para executar, cabendo ao SO gerenciar o uso dos recursos para que todos sejam executados de maneira eficiente. Raramente há interação com usuários, sendo que dados de entrada podem vir de arquivos. A saída de dados também comumente é direcionada a arquivos. 

Como já mencionado, as técnicas de **multiprogramação** (sobreposição de E/S e processamento) e de **compartilhamento de tempo** (time-sharing) são usadas pelo SO para alternar o uso do(s) processador(es).

Do ponto de vista do programador, contudo, as aplicações são criadas como se fossem ser executadas com o uso exclusivo dos recursos disponíveis no sistema computacional. Programas não precisam incluir código para explicitamente liberar o uso do processador periodicamente e nem quando precisam aguardar pela entrada ou saída de dados. 

Aqui talvez fique claro para quer serve o conceito de processo como programa em execução. Para poder manter vários programas ativos, o SO precisa fazer com que todos eles simplesmente executem. Se é necessário, ou desejável, manter vários programas em execução, alternando o uso do(s) processador(es) entre eles, alguns requisitos são:

- identificar logicamente cada processo;
manter informações de controle para cada processo (quais?);
- criar um mecanismo para direcionar um processador para executar código de um processo específico;
- limitar as áreas de memória que um processo acessa;
- criar mecanismos para retomar o controle do processador após tê-lo atribuído à execução de um processo;
- salvar o estado do hardware no momento em a execução de um processo for interrompida, para poder retoma-la posteriormente;
- criar mecanismos para oferecer serviços aos processos
- contabilizar o uso de recursos pelos processos
- manter informações sobre arquivos abertos e outros recursos em uso por um processo;
...

Em suma, o SO vai ter manter estruturas de dados na memória para armazenar as informações de controle de cada processo.

Em sistemas Linux, a estrutura de controle de processos é chamada de **task_struct.** 

Usando o mecanismo de processos e as estruturas de controle, ~~cada programa em execução terá a impressão de que está executando com uso dedicado do processador~~. Na verdade, quem tem a impressão que todos os programas estão sendo executados simultaneamente é o usuário! Do ponto de vista do programa, não é preciso ao programador preocupar-se em incluir nada específico no código para que ele seja eventualmente parado e continuado. Tudo vai acontecer como se as instruções fossem executadas de maneira ininterrupta. 

É claro que há programas em que a questão do tempo de execução é crítica, mas isso será tratado posteriormente, ao estudarmos mecanismos de seleção de processos para execução.

---
## Criação de processos

Se um processo é um programa em execução, talvez valha a pena começarmos a discussão sobre a criação de um processo pensando no conteúdo de um arquivo executável.

O que é um arquivo executável?  Qual é a estrutura deste arquivo que permite ao SO criar uma entidade em execução?

Quando compilamos um programa, as sequências de instruções de alto nível que usamos são convertidas em sequências de instruções do repertório de instruções do processador alvo. Bibliotecas de funções usadas no código podem ter sido previamente compiladas, gerando sequências de instruções do processador alvo também. O gerador de código define então, alguma forma de agrupar todos os códigos estáticos numa sequência de blocos e resolver as chamadas de função em desvios para os endereços apropriados desses blocos. Desconsideremos por enquanto o uso de bibliotecas de referência dinâmica. 

Programas têm ainda referências sobre variáveis estáticas e globais e indicações sobre a quantidade de memória necessária para elas no carregamento do programa. Puxa, muitos detalhes aqui; trataremos mais profundamente dessas questões na unidade de gerenciamento de memória. 

Resumidamente, um arquivo de programa executável contém códigos, dados constantes e informações de controle que vão permitir ao SO criar um processo a partir de seu conteúdo.

**Quando um processo é criado?**

Retomando o boot do sistema computacional, vemos que inicialmente o programa da BIOS é executado com o processador em modo real e endereçamento direto da memória. À medida que o SO é carregado, faz as inicializações e cria as estruturas de controle necessárias, ele pode passar o processador ao modo de operação protegido, que inclui suporte para a execução de múltiplas tarefas. A partir daí, o SO pode criar seus próprios processos, associados a atividades que estão fora do núcleo, implementadas como processos, ou tarefas, de maneira geral.

Nas configurações do SO existem listas de programas servidores que devem ser carregados na inicialização do sistema, dando origem a vários processos. Software instalado pelo usuário também pode gerar a ativação de programas automaticamente na fase inicial do sistema. 

Após inicializado, o SO pode disponibilizar alguma interface de identificação e login do usuário. Alguns programas vão estar configurados para carregamento automático no início da sessão do usuário, que pode então iniciar programas via interface gráfica. Caso esteja interagindo via uma interface texto, caberá ao programa shell interpretador de comandos receber as solicitações do usuário e solicitar a criação de processos. 

Alguns eventos também podem ocasionar a criação de novos processos, comumente por processos que já estão em execução à espera da ocorrência desses eventos.

É comum que SOs tenham mecanismos para programar a execução de processos em instantes específicos (at), e mesmo que programas sejam executados periodicamente, a cada hora, dia, semana ou mês (cron).

Programas em execução também podem gerar a criação de novos processos por razões variadas. Por exemplo, um servidor WWW pode gerar a criação de um novo processo cada vez que uma conexão é estabelecida por um cliente remoto. No lado de um computador de usuário, por sua vez, cada nova aba aberta pode levar à criação de um novo processo.

Em todos os casos, a criação de processo sempre vai estar associada a uma **solicitação explícita** ao SO para que ele faça isso. A forma de criação dos processos, os parâmetros e outras informações de controle podem variar entre os SOs.

Em SOs baseados em Unix, por exemplo, que seguem especificações de padrões como POSIX, a criação de um novo processo é feita com a chamada de sistema fork(). Para tratar esta chamada, que não tem parâmetros, o SO cria um novo processo fazendo uma cópia do processo atual. Esse novo processo, considerado um processo filho daquele que o criou, passa a ser executado na instrução seguinte à chamada fork. Como os processos pai e filho executam o mesmo código, é comum que o programador insira um comando de decisão logo após a chamada fork, para que cada um dos processos (pai e filho) faça ações diferentes.

Em geral, o processo filho criado faz uma outra chamada de sistema logo a seguir: execve(). Essa chamada pede ao SO para sobrepor o código corrente (e toda a configuração do processo) pelo código e pelas configurações definidas em um arquivo executável especificado como parâmetro da chamada. 

Neste ponto, já dá para começar a intuir como um programa shell funciona: lê o comando digitado pelo usuário, faz uma chamada de sistema fork e, no processo filho, faz uma chamada de sistema execve para sobrepor sua imagem de processo a partir do arquivo executável indicado pelo usuário! (é claro que tem muito mais detalhes nessa estória:)

Em sistemas Windows, a chamada de sistema para criação de um novo processo é CreateProcess(). Como se vê na documentação, a abordagem é diferente, uma vez que o nome do programa (arquivo executável) é fornecido como parâmetro. Ou seja, faz-se uma chamada ao SO já indicando o programa que deve ser usado para a criação do processo, ao invés de duplicar o processo corrente e fazer a substituição posterior. 

Em todos os casos, cada novo processo terá recursos específicos alocados pelo SO, incluindo um novo descritor de processo, áreas de memória para código e dados, informações de arquivos abertos, informações sobre o contexto de execução, etc. Alguns desses recursos, como algumas áreas de memória, podem eventualmente ser compartilhados pelo SO entre processos relacionados, como veremos posteriormente. 

---
## Término de processo

Se já sabemos como um processo é criado, falta pensar em como terminá-lo.

Usando a linguagem C, é comum terminar um programa retornando um valor inteiro ao final da execução da função main(). De acordo com as especificações padrão da linguagem, o retorno desta função é equivalente à chamada da função exit(). Na prática, o compilador acaba inserindo um código ao final do programa, de forma que, ao retornar da função main() é feita uma chamada à função exit().

O valor de retorno previsto é EXIT_SUCESS, para os casos em que o programa termina normalmente, e EXIT_FAILURE, para terminação mal-sucedida. O retorno de outros valores não é padronizado e, caso ocorram, seus significados e usos são dependentes da implementação. Ainda segundo o padrão, a função main deve ter um retorno explícito, para evitar comportamentos não definidos.

Em sistemas Unix, a função exit() comumente realiza operações de controle, que podem ser programadas pelo usuário usando a função atexit(),  e faz uma chamada de sistema à syscall _exit(). Já em sistemas Windows, ocorre uma chamada à função ExitProcess(). Vale observar que algumas bibliotecas de programação em sistemas Windows também oferecem suporte às chamadas de sistema POSIX e afins, mas talvez esse não seja o modo padrão de programação nesses sistemas.

Em ambos os casos, supõe-se que o processo concluiu sua execução e está fazendo uma **chamada explícita ao SO para ser terminado.** 

Também é possível que a execução de um processo termine devido a uma situação de erro fatal. Esse é o caso, por exemplo, se houver uma tentativa de divisão por zero no código, no caso em que a operação a ser executada tem erro ou não seja permitida, ou em tentativas de acesso a áreas de memória inválidas ou às quais o processo não tem permissão. Os mecanismos de detecção e notificação nesses casos são dependentes do processador e do SO.

Uma outra condição que pode levar ao término do processo é o recebimento de uma **notificação** gerada por outro processo. Em sistemas Unix é possível enviar sinais entre processos, através da chamada de sistema kill(). De maneira geral, essa chamada de sistema permite que um processo (do mesmo usuário ou do super-usuário) envie um sinal para outro processo. Diferentes sinais existem, com diferentes efeitos. Alguns deles, como os sinais SIGINT, SIGTERM e SIGKILL, comumente fazem com que a execução do processo que os receber seja terminada. 

Em sistemas Windows há um serviço chamado TerminateProcess(), que gera o término do processo indicado na chamada. É possível supor que quando ocorre um pedido para terminar um processo usando o programa Gerenciador de Tarefas ocorra uma chamada como essa. Nesses sistemas, programas associados a janelas normalmente definem rotinas para tratamento de eventos específicos. À medida que eventos de interesse do processo ocorrem, esse processo recebe mensagens de notificação específica, que vão ocasionar a execução automática de rotinas pré-determinadas.

Em todos os casos de término de processo, é de se esperar que o SO faça a **liberação dos recursos** alocados para esse processo, como estruturas de controle e área de memória, além da própria estrutura de representação do processo.

---
### Estados de processos

Relembrando a evolução dos SOs, a técnica de spool inicialmente procurava sobrepor o uso do processador para execução de um programa com a fase de carregamento de outro programa; dados de outro programa, já terminado, poderiam estar ao mesmo tempo sendo gravados da memória para uma fita de saída.

Na multiprogramação, o SO aproveita a relativa lentidão das transferências envolvendo o disco, por exemplo, para direcionar o uso do processador do processo que solicitou uma operação de E/S para outro que está em condição de ser executado.

Já na técnica de compartilhamento de tempo (time-sharing), o SO fica periodicamente alternando o uso do processador para a execução de vários processos aptos a executar.

O que podemos observar em todos esses casos é que o estado de um processo pode variar ao longo de sua existência. Há situações em que um processo não está pronto para execução e outras em que poderia estar sendo executado, mas o processador está sendo usado para a execução de outro processo.

De maneira geral, ao longo de sua existência, um processo pode estar em diferentes estados: 

- Em execução: quando um processador está executando suas instruções;
- Pronto: em condição de ser executado, mas o processador está sendo usado para executar outro processo;
- Bloqueado: não está em condição de execução pois aguarda algum evento ou ação que o desbloqueie. 

Processos compostos basicamente por instruções do processador comumente ficam alternando entre os estados de pronto e em execução, e vice-versa. Isso ocorre cada vez que o mecanismo de compartilhamento de tempo é usado para alternar o uso do processador. 

Já processos que precisam de dados de E/S podem acabar sendo temporariamente bloqueados.

Há várias situações que podem levar um processo a ser bloqueado. Por exemplo, suponha que um processo precisa que o usuário forneça um valor e, para tanto, emite uma chamada de sistema pedindo ao SO que leia dados do terminal. Até que o usuário digite os dados e o SO possa repassá-los ao processo, a execução deste processo não pode prosseguir.

Neste caso, o estado do processo é mudado para bloqueado. Além disso, a estrutura de dados usada pelo SO para representar esse processo é removida da fila dos processos prontos. É claro que, por razões de otimização de código, essa "remoção" da fila não implica mover dados de uma região de memória para outra. O SO apenas ajusta ponteiros de ligação de filas, encadeando os campos de ligação do descritor desse processo para a ligação em outra fila.

Quase sempre que um processo precisa aguardar pela leitura ou escrita de dados, como essas operações podem ser demoradas, o SO ativa os controladores de dispositivos apropriados para fazerem a transferência necessária e bloqueia o processo solicitante até que a operação seja concluída.

Mas, quando ocorre o desbloqueio e a volta do processo ao estado (e à fila) de pronto?

Dispositivos de E/S comumente usam interrupções ao processador para indicar que concluíram uma operação solicitada. Quando a interrupção ocorre, o processador (salva o PC e) desvia o fluxo de execução para a rotina de tratamento desta interrupção (cujo endereço foi obtido do vetor de interrupções). Como essa rotina é código do SO, o que ocorre é que o SO assume o controle da CPU; agora o processador estará executando a rotina do SO para tratamento da interrupção. 

Sabendo que essa interrupção indica que os dados solicitados pelo processo agora estão disponíveis, o SO copia os dados do local onde o controlador os colocou e os replica na área de memória indicada pelo processo na syscall de leitura. Esse processo agora está apto a voltar à execução, de forma que o SO muda seu estado para pronto e reinsere o descritor desse processo na fila de [processos] prontos.

Bloqueios de processos, que os tiram da fila de processos prontos, também podem ocorrer em função do uso de primitivas do SO oferecidas para comunicação e sincronização entre processos. 

E a transição de um processo do estado de pronto para em execução, quando ocorre? 

Relembrando do mecanismo de time-sharing, sabemos que o SO usa um gerador de interrupções periódicas para retornar o controle do processador e redirecioná-lo à execução de outro processo. A escolha de qual dos processos prontos deve ser o próximo a ser executado é chamada de **escalonamento**, que também é assunto deste capítulo.

Agora, que tal abrir novamente o programa "Monitor do Sistema", ou "Gerenciador de Tarefas" ou "Activity Monitor" e examinar os processos novamente?!

Quantos processos existem no sistema? Quais são seus estados? Por quê há processos bloqueados? O que será que esperam?

Já é possível perceber que o SO é mesmo um grande gerenciador de recursos e prestador de serviços. Programas ativados automaticamente na inicialização do SO e programas ativados pelos usuários vão gerar processos, que ficam competindo pelo uso do(s) processador(es) e dos serviços do SO.

---
## Representação de processos

Como já discutido, processos são programas em execução.

Cada processo sabe que não pode executar instruções específicas que alteram o controle do funcionamento do processador ou que realizam a interação com controladores de dispositivos. Independentemente disso, é mais fácil e seguro usar rotinas de serviço do SO!

**OBS:** de que maneira é possível impedir que programas executem certas instruções? Usando os anéis de privilégio do processador. Instruções de controle do processamento e de E/S só são permitidas no anel 0, enquanto os programas executam no anel 3. Assim, a única forma de os programas realizarem certas atividades é pedindo ao SO, cujas instruções são executadas no anel 0.

Cada processo é composto de sequências de instruções, escritas como se fossem ser executadas com o uso exclusivo do processador. Cabe ao SO implementar mecanismos para criar processos e compartilhar o uso do(s) processador(es) de maneira eficiente para a execução de todos os processos. 

Como o processador é alternado para a execução de instruções de todos os processos prontos, o SO precisa manter informações  de controle de cada um dos processos, incluindo seus estados e o estado dos registradores do processador no instante em que cada processo deixou de ser executado. 

A estrutura de controle de cada processo é comumente chamada de Bloco de Controle de Processo (BCP - ou Process Control Block) e é basicamente uma estrutura de dados, entre tantas outras, na área de memória do SO. Cada SO, contudo, define sua própria estrutura para a representação de processos.

No sistema Linux, usa-se uma estrutura para representação de tarefas, chamada de task_struct. Em sistemas Windows, há outra estrutura que inclui informações de cada processo. Algumas informações sobre estruturas opacas do SO Windows podem ser vistas em [1,2].

De maneira geral, além de particularidades de cada SO, uma estrutura de controle de processo inclui:

- Identificador do processo
- identificador do processo pai deste processo e possíveis outros relacionamentos hierárquicos com outros processos
- Identificador do usuário e de possível grupo associado à execução do processo
- Estado do processo
- Estado dos registradores do hardware
- Valor do contador de programa
- Estruturas para tratamento dos sinais
- Informações de contabilização do uso de recursos
- Alarmes e temporizadores do processo
...
- Diretório raiz e diretório corrente
- Vetor de informações dos arquivos abertos
...
- Ponteiro para a área de memória com o código
- Ponteiro para áreas de dados
- Endereço da base e do topo da pilha
- Informações sobre outras áreas de memória
...

**Contextos de execução**

Cada vez que um processo vai deixar de ser executado, o SO precisa realizar um procedimento chamado de troca de contexto. Contexto, neste caso, refere-se basicamente ao estado dos registradores do hardware no momento em que um processo vai sair de execução; ou seja, quando o processador, que executava instruções deste processo, vai ser direcionado à execução de instruções de outro processo.

Assim, na troca do processo em execução, é feito o salvamento do contexto do processo que sai. Um novo processo é selecionado pelo escalonador do SO e o contexto de execução deste processo é restaurado no hardware. 

A troca de contexto não é uma atividade simples e requer ações do processador e do SO. 

Supondo que o processador está executando instruções de um dado processo. Isso significa que o registrador PC (contador de programa) do processador aponta para a área de memória onde estão as instruções deste processo. O registrador ponteiro de pilha (ESP) aponta para a área de memória reservada para a pilha deste processo, e os demais registradores de uso geral do processador contêm valores definidos ao longo da execução deste processo.

Como então o SO entra em ação e promove uma troca de contexto?

Há algumas possibilidades para que o processador seja desviado para executar código do SO.

**[1]** Pode ocorrer uma interrupção externa, que é um evento completamente independente. Ao aceitar a interrupção, o processador irá salvar o valor do PC (comumente na pilha) e usar o número da interrupção (informado pelo controlador de interrupção) como um índice para consultar o vetor de interrupções. Na posição correspondente ao número da interrupção no vetor de interrupções estará o novo valor que deve ser atribuído ao PC. O SO pôs ali o endereço de sua rotina para tratamento desta int e, assim, o processador passa a executar código do SO.

**[2]** O dispositivo de timer foi anteriormente programado pelo SO para gerar interrupções periódicas. Decorrido o intervalo programado, este dispositivo gera uma interrupção e, da maneira como descrita no item 1, o processador é desviado para executar uma rotina do SO.
**[3]** processo em execução precisa de um serviço do SO e emite uma chamada de sistema.
Se, para isso, for usada a instrução de interrupção, o procedimento é semelhante aos casos 1 e 2.
Se a chamada for feita via instrução do processador específica para syscall, o processador salva o valor do PC (neste caso, em espaço reservado para isso) e atribui um novo valor ao PC, obtido de um registrador específico. Bem, o SO deve ter colocado ali o endereço de entrada de suas rotinas de tratamento de syscall, de forma que o processador é desviado para executar código do SO.
**[4]** Ocorre um **erro** ou uma **falta** na tentativa de execução da instrução corrente. Neste caso, o procedimento é semelhante aos casos 1 e 2.
Como se pode observar, o processador salvou automaticamente o valor do PC (contador de programa ou ponteiro de instruções), antes de substituir seu valor por algum endereço de rotina do SO. Alguma rotina do SO agora está em execução. Vale lembrar que junto com a mudança do PC ocorreu uma mudança para o anel de privilégio 0.

Antes de poder usar os registradores, a rotina do SO comumente **salva** seus valores na pilha do anel de privilégio corrente (0). Outras informações de controle sobre o processo que estava em execução são salvas no Bloco de Controle desse processo e, assim, fez-se o salvamento de seu contexto de execução!

SO pode prestar os serviços devidos e assim que acabar vai selecionar um processo para execução. Afinal, SO é um prestador de serviço eficiente e, tendo cumprido seu papel, vai direcionar o processador para a execução de código de algum processo o mais rapidamente possível.

Usando critérios e mecanismos que discutiremos posteriormente, o escalonador seleciona um processo pronto para execução. Pode ser o mesmo, se a interrupção foi rápida, ou algum outro processo. É preciso agora restaurar seu contexto de execução, para que tudo continue como se nenhuma parada tivesse ocorrido.

A restauração de um contexto envolve ajuste de ponteiros de memória (como estudaremos posteriormente), configurações de informações de controle no processador, restauração dos valores dos registradores de uso geral, salvos anteriormente, e direcionamento do processador para executar esse processo. Junto com esse desvio do PC, ocorre uma nova mudança no anel de privilégio, que é recolocado em 3 (na arquitetura x86 e afins). 

Puxa, quanta coisa! Faz sentido, pelo menos?!
Bons estudos!

Hélio

[1] https://docs.microsoft.com/en-us/windows-hardware/drivers/kernel/eprocess. Acesso em 2/4/2020. 
>"... The EPROCESS structure is an opaque structure that serves as the process object for a process.... The ETHREAD structure is an opaque structure that serves as the thread object for a thread...."

[2] https://www.microsoftpressstore.com/articles/article.aspx?p=2233328. Acesso em 2/4/2020.
>"... Each Windows process is represented by an executive process (EPROCESS) block. Besides containing many attributes relating to a process, an EPROCESS block contains and points to a number of other related data structures. For example, each process has one or more threads represented by executive thread (ETHREAD) blocks. (Thread data structures are explained in the section Thread Internals later in this chapter.) The EPROCESS block and its related data structures exist in system address space, with the exception of the process environment block (PEB), which exists in the process address space (because it contains information that needs to be accessed by user-mode code)..."

---