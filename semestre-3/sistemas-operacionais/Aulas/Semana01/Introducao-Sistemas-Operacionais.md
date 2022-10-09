# Introdução aos Sistemas Operacionais
##### Professor: Hélio Crestana Guardia
##### Universidade Federal de São Carlos
---

#### Definições
O que é e para que serve um sistema operacional (SO)?

Basta ligar um sistema computacional, como um computador de mesa, um notebook, um tablet, smartphone, ou mesmo um smartwatch, para que um SO entre em ação.

Na prática, o SO normalmente não é o primeiro programa a ser executado quando um sistema computacional é ligado, mas ele é o programa que vai tomar conta da máquina e permitir que nós e os nossos programas a utilizemos.

Quase todo sistema computacional tem um SO, que vai estar sempre em estado de execução, embora nem sempre o(s) processador(es) esteja(m) executando suas instruções. 

Idealmente, um SO deve atuar como um programa servidor discreto, de uso intuitivo, rápido e quase imperceptível, que nos dá acesso fácil, eficiente e seguro ao sistema computacional. Ah, ainda é preciso fazer isso sem gastar energia desnecessária, para que as baterias durem o máximo possível!

Muitas pessoas nem prestam atenção ao SO, exceto quando ele não funciona direito :-)  

Por outro lado, para quem quer (ou precisa :) estudar SOs, esses tantos atributos (discreto, intuitivo, rápido, fácil, eficiente, seguro, confiável, econômico, etc.) talvez dêem ideia da complexidade de se criar um. 

De maneira resumida, um sistema operacional pode ser considerado por 2 aspectos:

- é um programa de controle, que gerencia os recursos disponíveis no sistema computacional,
- é uma interface simplificada, com abstrações, para uso dos recursos pelos programas.

Ser um gerente de recursos significa fazer cada recurso funcionar para realizar as ações desejadas e dividir o uso desses recursos entre diversos programas clientes.

Para fazer um recurso, como um disco rígido (HD) ou uma impressora, funcionar, é preciso enviar instruções e sinais de controle para os controladores físicos desses dispositivos e receber e processar sinais de controle e informações geradas por esses dispositivos.

No caso de uma impressora, isso significa transmitir a ela os comandos para movimentação das partes mecânicas e os dados a serem impressos. Para dispositivos de entrada, como o teclado, por exemplo, é preciso receber do controlador os valores que representam o pressionamento e a liberação de teclas e transformar esses valores em códigos que representam as teclas pressionadas.

Como é comum haver mais de um programas em execução num sistema computacional, o gerenciamento de recursos ainda precisa tratar dos seus compartilhamentos. Seja alternando em função do tempo ou de alguma ordem de prioridade, o SO pode permitir que diferentes programas usem os recursos.

Contudo, o uso dos recursos pelos programas não é feito de maneira direta, permitindo que cada programa envie comandos de controle e dados para os controladores.

O SO oferece uma interface abstrata, simplificada para o uso dos recursos. Isso significa que o SO abstrai os detalhes de funcionamento dos dispositivos de hardware e oferece aos programas uma visão de máquina virtual (*), mais simples de usar. 

Por exemplo, o SO permite que programas salvem dados em arquivos em disco. Para fazer isso, os programas não precisam conhecer detalhes de qual dispositivo de armazenamento está sendo usado e quais são os comandos que precisam ser enviados ao controlador deste dispositivo para indicar onde os dados serão salvos. O programa não precisa nem saber qual é o formato do sistema de arquivos usados, ou mesmo se os arquivos estão sendo salvos num dispositivo local ou em algum servidor remoto "em nuvem".

Pois assim são os SOs, fáceis de usar e eficientes, mas complexos de implementar!

Bons estudos,

Hélio

(*) posteriormente, veremos que o próprio SO pode ser implantado sobre uma máquina virtual...

___

#### Histórico de SOs

Como surgiram e como evoluíram os Sistemas Operacionais?

Como menciona Tanenbaum, na seção 1.2, (SOs Modernos), a evolução dos SOs não ocorreu de forma completamente estanque e progressiva. Assim, destacam-se a seguir apenas alguns aspectos marcantes de suas evoluções.

Os primeiros sistemas computacionais não tinham um ambiente de apoio à programação e à execução de programas. Nesses sistemas, havia apenas um mecanismo para carregar na memória os códigos binários que representavam as instruções e seus parâmetros e, feito isso, para iniciar a execução desse programa.

Puxa, que falta faziam um Sistema Operacional, uma linguagem de alto nível e um compilador! (mas ninguém sabia disso ainda :-)

Para simplificar o uso do computador, programas passaram a ser gravados em cartões perfurados e podiam ser lidos automaticamente, sem que fosse preciso programar cada instrução diretamente na memória do computador. Para tanto, foi incorporada uma unidade de leitura de cartões como dispositivo de entrada no computador. 

Posteriormente, incorporou-se ao sistema computacional um mecanismo de impressão. Assim, a execução dos programas passou a ter 3 fases bem definidas: entrada via cartões, processamento, e saída para a impressora. Um novo aprimoramento para a execução dos programas foi o agrupamento sequencial de vários programas a executar numa sequência de cartões.

Para isso, criou-se uma unidade de entrada de dados desacoplada do computador. Cada conjunto de cartões que formava um programa era lido em sequência e copiado para uma fita magnética. Foram criados um programa de controle de jobs e uma linguagem de comando com instruções para definir o que era o início de um programa, onde ele terminava, onde começavam dados de entrada para uso durante a execução deste programa, se houvesse, e um comando de fim de job.

A fita contendo um conjunto de programas era levada ao computador, que lia cada um desses programas e os colocava sequencialmente em execução. Um aprimoramento foi o fato de um programa poder estar sendo carregado enquanto outro já estava em execução, previamente carregado na memória, e outro, já concluído estivesse gravando dados numa fita magnética de saída. Criou-se aí um conceito chamado spool (simultaneous peripheral operation on line), relacionado ao fato de dispositivos periféricos, como a unidade de fita com programas de entrada e a fita com os dados de saída operavam simultaneamente à execução de programas. 

A evolução seguinte consistiu em dividir os espaços de memória para conter mais de um programas em condição de execução de cada vez. A alternância entre eles ocorria quando algum deles precisava esperar por alguma condição, como ler dados de entrada ou imprimir dados de saída (E/S). Mecanismos para endereçamento de memória relativo e proteção entre as áreas foram criados pelos fabricantes dos processadores e seus usos eram coordenados pelos SOs.

Como as operações de entrada e saída de dados sempre foram relativamente mais demoradas do que a execução de instruções pelo processador, o SO introduziu uma técnica chamada multiprogramação. Se o programa que estivesse em execução fizesse uma solicitação para ler ou escrever dados de E/S, o SO iniciava a operação do controlador de leitura, ou escrita, que iriam copiar os dados necessários de/para a memória. Enquanto isso, o SO direcionava o processador para executar instruções de outro programa na memória.

Uma vez que já havia vários programas na memória, a próxima grande mudança foi relacionada à alternância entre eles. Ao invés de trocar o uso do processador apenas quando o programa corrente precisava de entrada e saída, passou-se a usar um dispositivo de tempo, que gerava interrupções periódicas. A cada interrupção, o processador era desviado para a execução de código do SO, que assumia o controle. O estado do programa corrente era salvo, outro programa pronto na memória era selecionado para execução, seu estado era restaurado no hardware e o processador era direcionado para sua execução. Esse mecanismo de compartilhamento do tempo de uso do processador era chamado de time-sharing. 

As técnicas de manutenção de vários programas na memória e os mecanismos para apoiar a alternância do uso do processador levaram ao conceito de sistemas multi-usuários e multitarefa. Ou seja, passou a ser possível ter vários usuários conectados a múltiplos terminais de entrada e saída de dados (monitores e teclados) no mesmo sistema computacional, cada um podendo ter vários programas em execução. 

Como dá para perceber, os SOs foram evoluindo ao longo do tempo, possibilitando a execução de vários programas. É claro que a evolução dos sistemas computacionais é resultado de esforços combinados dos desenvolvedores de processadores, de controladores de entrada e saída (E/S) e de sistemas operacionais, identificando demandas e elaborando mecanismos e estratégias apropriadas para o uso mais eficiente e simplificado dos recursos pelos programas.

Ao longo do caminho da evolução dos sistemas computacionais, diferentes tipos de computadores e sistemas foram desenvolvidos, incluindo computadores para usos gerais e específicos, computadores pessoais e grandes sistemas compartilhados. Tradicionalmente, contudo, os sistemas operacionais eram feitos sob medida para o hardware em que executavam.

Outro aspecto marcante na história dos SOs foi o surgimento do sistema Unix, que trouxe muitas inovações. Um aspecto fundamental do seu projeto foi a criação de uma linguagem de alto nível (C) para a escrita do SO. Tudo que fosse possível era escrito em comandos de alto nível, usando a linguagem de montagem do processador alvo apenas para aspectos muito específicos. Assim, passou a ser mais fácil trabalhar no desenvolvimento do SO, agora escrito em linguagem C, e possível "portá-lo" para outras plataformas em que existisse um compilador e gerador de código dessa linguagem.

Vários outros aspectos marcaram o desenvolvimento desse SO, incluindo o acesso fornecido ao seu código fonte para a academia (Universidade de Berkeley). À medida que passou a haver vários grupos trabalhando em versões do mesmo SO, começaram a surgir padrões, que definiam os serviços do SO, suas interfaces abstrações e comportamentos esperados, além dos programas utilitários. 

O surgimento do projeto GNU trouxe outra grande mudança para o mundo dos sistemas operacionais. Esse projeto deu origem a um conjunto de ferramentas de software livre, como compiladores, programas utilitários e um sistema operacional, todos disponíveis em seus códigos fonte, abertos para quem possa fazer uso deles. 

Impulsionado por esse projeto e pela experiência com um SO de cunho acadêmico, foi criado o sistema operacional Linux sobre a plataforma GNU para o ambiente dos computadores pessoais. Esse sistema baseou-se em padrões abertos do mundo Unix e inovou ao criar um modelo de desenvolvimento colaborativo, aproveitando a plataforma de transmissão e comunicação oferecida pela Internet. Outros sistemas operacionais abertos baseados em padrões Unix também surgiram para o ambiente dos PCs.

Muitas otimizações têm sido introduzidas nas estratégias e no desenvolvimento dos sistemas operacionais. Considerando o modelo do funcionamento dos computadores, baseado na arquitetura de Von Neumann, e as técnicas atualmente empregadas nos processadores para o apoio à execução segura de múltiplas tarefas, algumas estratégias têm sido comuns aos SOs atuais:

- suporte multitarefa: permitir a execução de diversos programas simultaneamente, normalmente alternando o uso do(s) processador(es) entre eles com técnicas de multiprogramação e compartilhamento de tempo;

- interação com controladores baseada em técnicas de acesso direto à memória (DMA) e interrupções.

---

#### Tipos de SOs

Como SOs diferem em função dos recursos gerenciados e dos usos desses recursos?

Desde a criação dos primeiros computadores até os dias atuais, sistemas computacionais evoluíram de equipamentos grandes e dedicados à execução de um programa de cada vez, a dispositivos portáteis e capazes de executar muitos programas ao mesmo tempo.

Considerando o que atualmente é chamado de Internet das Coisas (IoT - Internet of Things), vê-se que até pequenos objetos têm incorporado circuitos contendo processadores, memória e interfaces de comunicação em rede. Algum tipo de sistema gerente dos recursos deve haver nesses dispositivos.

Carros autônomos também são uma realidade, certamente contando com uma infraestrutura computacional bastante sofisticada. Nesse caso, é claro perceber que não basta apenas executar programas, mas são necessárias garantias que os programas e as ações resultantes de seus processamentos serão executadas dentro de condições de segurança e de tempo bem rígidas.

E o que falar dos smartphones, tão disseminados? Quais peculiaridades podem ser destacadas nesses sistemas?
Dadas as funcionalidades oferecidas pelos programas usados nesses dispositivos, é possível que muitos mencionem a duração da carga da bateria como um dos requisitos fundamentais! Mas isso é uma questão ao alcance do SO?

É claro que o fornecimento de energia para o funcionamento do processamento, das transmissões e da exibição na tela do dispositivo é uma questão física. Por outro lado, cabe ao SO permitir que diferentes programas estejam em execução simultaneamente, um usando a tela para interação com o usuário e outros executando em segundo plano, aguardando eventos e mensagens e realizando comunicações, por exemplo. Também cabe ao SO, agindo como um malabarista na atribuição do uso do(s) processador(es), determinar quando cada programa é executado e até mesmo reduzir a velocidade e o consumo de energia quando há pouco a fazer.

De maneira geral, é comum que todo sistema computacional tenha algum tipo de sistema operacional, com características que atendam às demandas de uso desses dispositivos. Em suma, SOs podem diferir em função dos ambientes gerenciados.

O SO vai estar presente nesses dispositivos para (a) gerenciar o funcionamento dos recursos físicos (processador, memória e unidades de armazenamento persistente, interfaces de entrada e saída, etc.), (b) simplificar o uso dos recursos, oferecendo abstrações (como processos e arquivos) para que as aplicações realizem seus objetivos.

O resultado da presença do SO é que os programas podem ser escritos em linguagens de alto nível, sem se precupar com detalhes do sistema computacional e concentrados nos serviços e nas funcionalidades que querem prover! 

---

#### Processador e execução de instruções

Quais são e para que servem os recursos típicos de um sistema computacional?

Relembrando as aulas de arquiteturas de computadores, vem em mente: processador(es) e execução de instruções, memória RAM, barramento para interligação de processador(es) e memória(s), diferentes controladores de dispositivos de armazenamento, como SATA, SCSI e USB, monitores e interfaces de vídeo, dispositivos de entrada, barramentos para interligação dos controladores ao(s) processador(es) e memória(s).

O conhecimento de detalhes da arquitetura e do funcionamento de cada um desses grandes componentes e de aspectos de suas interligações é relevante para entender estratégias de implementação dos SOs. Isso inclui, por exemplo, o ciclo de execução de instruções, anéis de privilégios dos processadores e conjuntos de instruções, modos de endereçamento da memória, interrupções e traps de acesso ao SO e interações com controladores de dispositivos. 

Examinando aspectos do funcionamento de processadores Intel X86, por exemplo, vê-se até que há apoio específico de processadores para a implementação de sistemas operacionais que suportem a execução simultânea de múltiplas tarefas. O mesmo vale para processadores AMD 64 (capítulo 3).

Aspectos relacionados ao funcionamento dos dispositivos de entrada e saída serão tratados em capítulo específico deste curso.

Mas como funciona um sistema computacional?

**Arquitetura de Von Neumann**

De maneira geral, um **processador** funciona na forma de um **ciclo** de **busca** de instrução de uma posição de memória definida pelo conteúdo de um registrador específico, e execução dessa instrução internamente.

Para tanto, a maioria dos computadores é organizada de acordo com uma lógica derivada da arquitetura de Von Neumann em que a memória é usada para armazenar programas e dados. Para ser executada pelo processador, uma instrução deve ser copiada da memória para um registrador interno da CPU (IR).

O objetivo do processador é executar instruções na sequência em que se encontram na memória. É claro, contudo, que a própria execução de uma instrução pode gerar o desvio do ponteiro de instruções para outras regiões da memória.

As instruções que um processador executa podem ser cálculos, transferências de valores envolvendo registradores e/ou posições de memória, ou leitura e escrita em barramentos de memória, para interação com controladores de dispositivos.

Essas instruções fazem parte do repertório de instruções do processador, como pode ser visto nos manuais de processadores Intel e AMD, por exemplo.

Logicamente, o ciclo de busca e execução (fetch-execute) de um processador pode ser representado da seguinte forma:

```
loop {
    RI <- MEM [ PC ]      // busca instrução da memória, se não puder obtê-la do cache
    PC <- PC +1           // incrementa de acordo com o tamanho da palavra; +8 p/ 64 bits
    Exec RI               // decodifica e executa a instrução, podendo requerer a busca de operandos
        INT ou exceção ?  // trata interrupção, se houver
   }
```
   _Figura 1: Algoritmo que representa, de maneira simplificada, o ciclo de funcionamento de um processador._

Na prática, processadores têm um pipeline interno (comumente, têm vários pipelines!), que sobrepõe atividades como busca, decodificação, acesso à memória e execução, realiza a busca antecipada de dados, etc. Em suma, há muitas otimizações e complicações no tratamento das instruções em processadores modernos. Assim, fiquemos com a lógica acima por ora.

Um aspecto importante a observar nesse ciclo é o funcionamento do cache. Dados endereçados pelo processador não são buscados byte a byte da memória, mas sempre em blocos do tamanho da linha de cache do processador, tipicamente 64 bytes de cada vez. Como acessos consecutivos tendem a ocorrer na mesma região de memória, o que caracteriza localidade (espacial ou temporal), é comum que os dados buscados depois de um acesso recente à memória estejam presentes no cache, de onde podem ser obtidos mais rapidamente.

Por exemplo, suponha que ocorre uma operação de leitura da posição X da memória. Para processadores 64 bits, ao invés de trazer 8 bytes para um buffer interno do processador, são trazidos 64 bytes, que é o tamanho típico de cada linha de cache. Se uma instrução seguinte tentar ler o conteúdo da palavra X+8, esses dados já podem ser providos para o processador diretamente do cache, de forma rápida e sem ter que gerar um acesso efetivo à memória. As próximas 6 palavras de 64 bits também vão estar lá, na mesma linha de cache, caso sejam solicitadas em breve.

O uso do cache proporciona melhor desempenho na busca de instruções e também faz com que o barramento de acesso à memória acabe ficando livre para acesso direto via DMA por outros controladores, como veremos posteriormente.

Por fim, qual é a principal conclusão aqui? Que um processador opera num ciclo contínuo de busca e execução de instruções.

As instruções a serem executadas devem estar na memória e a próxima instrução a executar é aquela na posição de memória apontada por um registrador interno, normalmente chamado de contador de programas. A execução de instruções como JMP (para desvio) e CALL (para chamada de função), muda o valor do registrador ponteiro de instruções, fazendo com que o processador passe a executar código contido em outra região da memória.

A ocorrência de interrupções, como veremos, também gera um desvio do ponteiro de instruções para endereços previamente salvos numa região específica da memória.

Para o processador, não faz diferença se a instrução sendo executada é de código de um programa ou de código do SO. É certo que existem algumas instruções privilegiadas (*), que só são permitidas em anéis de privilégio específico, o que trataremos posteriormente.

(*) Como se vê em Intel X86 System Instruction Summary

.

**Interrupções e Exceções**

Retornando à operação interna do processador, observa-se que o ciclo de busca e execução de **instruções** só é alterado na ocorrência de interrupções. Uma interrupção é um sinal ao processador, que permite que a execução de instruções seja desviada automaticamente para uma rotina de tratamento pré-definida.

Uma rotina de tratamento de interrupção é uma sequência de instruções que devem ser executadas em modo privilegiado. Cada rotina é projetada para identificar e responder à causa de uma interrupção específica e depois fazer com que o processador retorne à execução do software interrompido.

Como seria de se esperar, as rotinas de tratamento de interrupção são códigos projetados pelo SO! 

Interrupções podem ser geradas por eventos externos, ou podem ocorrer internamente, em decorrência de uma exceção na tentativa de executar uma instrução.

Interrupções externas são geradas por controladores de dispositivos para chamar a atenção do processador e forçar a execução de código para tratar a ocorrência de algum evento específico. Por exemplo, um controlador de teclado pode gerar uma interrupção para indicar ao processador que uma tecla foi pressionada. Um controlador de rede pode fazer o mesmo para indicar que um pacote foi recebido. Um controlador de disco pode gerar uma interrupção para indicar que um bloco de dados solicitados pelo SO já foi lido do disco e está disponível para uso, ou para indicar que já gravou no disco um bloco de dados solicitado.

No ciclo de funcionamento do processador mostrado na Figura 1, a ocorrência de uma interrupção externa é testada na linha 4. Ou seja, depois de o processador buscar e concluir a execução da instrução corrente.

Em geral, o processador tem apenas um canal para receber notificações de interrupções externas. Assim, comumente existe um dispositivo controlador de interrupções, que recebe as notificações de interrupção geradas pelos controladores e as repassa, uma a uma, ao processador. Em processadores x86 Intel, por exemplo, esse controlador de interrupções é chamado I/O APIC.

>[From the ntel Programmer's guide:] Any external interrupt that is delivered to the processor by means of the INTR pin or through the local APIC is called a maskable hardware interrupt. Maskable hardware interrupts that can be delivered through the INTR pin include all IA-32 architecture defined interrupt vectors from 0 through 255; those that can be delivered through the local APIC include interrupt vectors 16 through 255. 

Uma interrupção também pode ser gerada por uma instrução específica do repertório do processador: INT n. No algoritmo que representa o ciclo do processador, essa interrupção é identificada na linha 3, ao executar a instrução INT.

> [From the Intel Programmer's guide:] The INT n instruction permits interrupts to be generated from within software by supplying an interrupt vector number as an operand. For example, the INT 35 instruction forces an implicit call to the interrupt handler for interrupt 35.

Interrupções também podem ocorrer internamente ao processador, em decorrência de uma exceção na tentativa de execução de instruções. Exceções caracterizam interrupções síncronas e estão associadas à impossibilidade de executar uma instrução, como numa tentativa de divisão por zero, na tentativa de acesso a uma posição inválida da memória, no caso de uma instrução inexistente ou com parâmetros incorretos, ou numa falta de página de memória.

>[From Intel Programmer's guide:] The processor generates one or more exceptions when it detects program errors during the execution in an application program or the operating system or executive. Intel 64 and IA-32 architectures define a vector number for each processor-detectable exception. Exceptions are classified as faults, traps, and aborts

No algoritmo do ciclo do processador na Figura 1, há 2 situações que podem levar a exceções. Na linha 3, da execução da instrução, pode ocorrer de a instrução ser uma divisão por 0. Também pode ser que, por erro, o opcode da operação é inválido, ou seja, não corresponde a nenhuma instrução, ou a instrução tem parâmetros inconsistentes. Também é possível que a instrução corrente faça referência a uma posição inválida da memória, que está fora da área de memória do programa corrente, ou que ele não tem permissão para acessar. 

Como veremos ao estudar gerenciamento de memória, também é possível que o endereço referenciado numa instrução corresponda a uma página não presente na memória. Isso também gera uma exceção. 

Examinando a linha 1 do algoritmo, vê-se que também é possível que uma exceção ocorra na busca da instrução corrente, por erro no endereço, nas permissões ou por falta na presença da página de memória referenciada. 

**Tratamento de interrupções (e exceções)**

Na ocorrência de uma interrupção, externa, instrução ou exceção, o processador deverá passar à execução de uma rotina de tratamento apropriada. Além disso, a mudança de endereço de execução (identificado pelo contador de programa) nas exceções e interrupções causa uma mudança do processador para o modo kernel (anel de privilégio 0), em que o sistema operacional realiza algum tratamento antes de retornar o uso do processador para o processo interrompido.

Obs: como o tratamento do processador para interrupções e exceções é praticamente o mesmo com relação ao desvio do fluxo de execução, será mencionado apenas tratamento de interrupções daqui em diante. 

Na ocorrência de uma interrupção, o processador irá suspender a execução da sequência de instruções que vinha executando e será desviado para a execução de uma rotina de tratamento apropriada. Para conseguir retomar a execução do código interrompido posteriormente, como se nada tivesse acontecido, é preciso antes salvar o estado do processador, que corresponde aos valores nos registradores. 

Assim, ao ocorrer uma exceção na execução da instrução corrente, ou ao detectar que a linha de interrupção externa está ativa depois de executar a instrução corrente, o próprio processador começa o salvamento de seu estado atual, copiando para a pilha o valor do registrador de Flags e dos registradores CS e EIP (push EFLAGS, push CS, push EIP), que indicam o endereço da próxima instrução a executar e o status da execução das instruções mais recentes.  

Esse salvamento é feito numa área de memória reservada para a pilha modo kernel da tarefa atual. Vale saber que, para cada programa, o SO dever reservar uma área de memória para a pilha em cada um dos possíveis anéis de execução. Tipicamente, os SOs usam apenas os anéis 0 e 3. Assim, deve haver 2 áreas de pilha para cada programa. Uma delas, a do anel 3, é manipulável pelo programa, com PUSHes, POPs, CALLs e afins; a do nível 0 é usada somente durante a execução de código do SO e o programa nem tem acesso.

A mudança para uso da pilha no nível 0 ocorre quando há uma interrupção e o ponteiro de instruções muda para apontar para o endereço da rotina de tratamento apropriada. Além de indicar o endereço da próxima instrução a executar, esse registrador de endereço contém bits de controle, incluindo 2 que indicam o anel de privilégio (0,1,2 ou 3) em que as instruções agora deverão ser executadas.

Resumidamente, para que o endereço da próxima instrução a executar da tarefa corrente não seja perdido, o processador salva o conteúdo do registrador de endereço de execução antes de substituí-lo pelo endereço da rotina de tratamento estabelecida pelo SO. Esse  salvamento do endereço da instrução atual possibilita a continuação posterior da tarefa corrente, exceto em situações em que ela deva ser terminada.

Depois de salvar o endereço da próxima instrução da tarefa atual, o processador precisa ser desviado para a execução da rotina de tratamento específica. Para tanto, existe uma posição da memória que é chamada de vetor de interrupções (IDT), onde devem estar os endereços de cada uma das rotinas de tratamento de interrupção. A localização do IDT na memória (endereço e tamanho) é definida por um registrador na CPU (IDTR).

**Criação do vetor de interrupções**

Já dá para perceber que vai caber ao SO criar as rotinas de tratamento de cada uma das interrupções possíveis, instalar as rotinas na memória, reservar uma área de memória para o vetor de interrupções (IDT), inserir no IDT os endereços e outras informações relevantes sobre as rotinas e ajustar o endereço do IDT num registrador interno do processador. 

O conteúdo do IDT é preenchido pelo SO, normalmente na fase de boot, quando carrega as rotinas de tratamento para a memória. Na ocorrência de uma interrupção, o processador usa, então, o número da interrupção ou exceção como um índice para o vetor de endereços de interrupção, de onde obtém os novos valores para CS e EIP (ou RIP), que caracterizam o PC na plataforma X86. O processador retoma então seu ciclo de busca e execução de instruções e estará agora executando instruções da rotina de tratamento da interrupção, ou exceção, ocorrida.

>[From Intel programmer's guide:] The interrupt descriptor table (IDT) associates each exception or interrupt vector with a gate descriptor for the procedure or task used to service the associated exception or interrupt. Like the GDT and LDTs, the IDT is an array of 8-byte descriptors (in protected mode). Unlike the GDT, the first entry of the IDT may contain a descriptor. To form an index into the IDT, the processor scales the exception or interrupt vector by eight (the number of bytes in a gate descriptor). Because there are only 256 interrupt or exception vectors, the IDT need not contain more than 256 descriptors. It can contain fewer than 256 descriptors, because descriptors are required only for the interrupt and exception vectors that may occur. All empty descriptor slots in the IDT should have the present flag for the descriptor set to 0.

As entradas no vetor de interrupções (IDT para processadores x86), apontam para rotinas de tratamento de interrupções, exceções e traps. Ou seja, o salvamento do PC atual e a busca por um novo endereço para passar à execução da rotina de tratamento ocorrem praticamente da mesma maneira para os 3 casos.

Os números das interrupções variam de 0 a 255, sendo que a faixa de 0 a 31 é reservada pelos desenvolvedores do processador para exceções e interrupções. As posições de 32 a 255 são designadas a interrupções definidas pelo usuário (na verdade, pelo SO) e são geralmente atribuídas às interrupções geradas por dispositivos de E/S externos. A interrupção 0x80 (128) tem sido usada como uma das formas para chamadas de sistema no Linux no modo 32bits.

Assim, **uma interrupção faz com que o processador seja desviado para a execução do SO, ou seja, o SO reassume o controle da CPU sempre que acontece uma interrupção!**

Como já mencionado  o próprio **processador salva** na pilha corrente o valor contido no contador de programa antes de substituir o valor desse registrador. Caso contrário, não seria possível saber qual seria a próxima instrução a executar e retornar à execução do programa interrompido após o tratamento da interrupção.

E os demais registradores do processador, que estavam em uso pelo programa interrompido? Sim, também é preciso salvar seus valores antes que a própria rotina de tratamento os utilize, o que geraria a perda de seus conteúdos anteriores.

O salvamento dos valores dos registradores é feito pela rotina de tratamento da interrupção, normalmente salvando seus valores na área de pilha atual, por rapidez. Vale ressaltar que o SO vai ter que reservar áreas de memória para a pilha de cada programa, uma pilha cada anel de privilégio usado (ao menos 3 e 0), para poder salvar os conteúdos dos demais registradores antes de usá-los em seu código.

Como talvez já seja possível perceber, o mecanismo de interrupções e os salvamentos dos estados dos registradores, além de outras informações que o SO deve tratar, vão permitir que o SO eventualmente interrompa a execução de um programa, selecione outro para execução, restaure seu estado anterior no processador e direcione o processador para a execução deste novo programa. Esse assunto é chamado de troca de contexto e será tratado mais especificamente na próxima unidade de estudo.

Pensando na retomada da execução da tarefa interrompida ou de alguma outra tarefa selecionada para execução, pode-se concluir que a rotina de tratamento deve terminar seu trabalho executando a instrução IRET, que restaura da pilha os valores de EIP, CS e EFLAGS, ou seja, recoloca no PC o endereço daquela que seria a próxima instrução a executar, se a interrupção não tivesse ocorrido.

Num sistema Linux, é possível examinar a atribuição e a ocorrência de interrupções exibindo-se o conteúdo do arquivo /proc/interrupts.

---
### Processadores: modos de execução e anéis de privilégio 

Algumas das estratégias providas por processadores para apoiar a execução concorrente de múltiplos programas são os conceitos de **modo de operação** e **anéis de privilégio.**

CPUs podem ter diferentes modos de operação, chamados de processor modes. Esses modos visam a prover restrições sobre o acesso à memória e sobre as operações do repertório de instruções do processador que podem ser executadas pelos programas. 

A arquitetura Intel IA-32, por exemplo, oferece 3 **modos de operação**: protected, real-address e system management.

- Modo real-address: ativado quando o processador é iniciado ou ressetado, esse modo é compatível com CPUs x86. O endereçamento de memória é feito de forma segmentada, usando 20 bits, e não há restrição de acesso direto à toda a memória (1 MB). Também não há restrições para o acesso aos endereços de E/S e ao hardware. Assim, não há proteção de memória, suporte a multitarefa ou níveis de privilégio. 
- Modo protegido (protected mode ou protected virtual address mode): é um modo de execução que permite o uso de memória virtual, paginação e multi-tarefa de forma segura, tendo sido projetado para possibilitar o controle do sistema operacional sobre os programas de aplicação. A ativação deste modo de execução, contudo, só pode ser feita depois que o sistema ajuste tabelas de descritores apropriadas e habilite o bit de controle de proteção (Protection Enable - PE) em um registrador de controle (CR0).
- System management mode: este modo provê um mecanismo para implementação de um modelo de segurança. Neste modo, o processador muda para um espaço de endereçamento separado, salvando o contexto básico do programa em execução. 
Processadores AMD 64 bits têm modos de funcionamento equivalentes.

Um aspecto importante a notar na existência desses diferentes modos de operação está relacionado ao suporte à execução de múltiplos programas ao mesmo tempo. De maneira resumida, ainda quando eram usados para a execução de um único programa, ou quando havia o SO como suporte e apenas um programa era colocado em execução de cada vez, os processadores operavam no modo real, usando apenas mecanismos para relocação das referências aos endereços de memória.

À medida que foi-se tornando interessante, e necessário, usar o sistema computacional para executar várias tarefas ao mesmo tempo, alternando o uso do processador entre vários programas mantidos na memória, foi preciso criar outros modos de operação nos processadores, para apoiar o compartilhamento seguro da memória e previnir interferências entre os programas.

Entretanto, o funcionamento dos modos de operação protegidos requerem o apoio do SO, para criar e manter estruturas de controle na memória, alterando informações em registradores específicos do processador de acordo com o programa que for ser executado a cada momento. Como essas estrutura não existem a priori, quando o computador é ligado, processadores normalmente iniciam suas operações em modo real e, à medida que o SO é carregado e cria as estruturas de controle, o próprio SO pode alterar o modo de operação do processador para o modo protegido.

Antes de alterar o modo de funcionamento do processador x86, por exemplo, o SO precisa fazer várias configurações, incluindo criar um vetor de tratamento de interrupções e tabelas de descritores de segmentos de memória.

**Anéis de privilégio** (Ou: One ring to rule them all :-)

Operando no modo protegido, há ainda diferentes níveis de privilégio (privilege levels), também chamados de protection rings. Na arquitetura IA-32, os mecanismos de proteção usam 4 níveis de privilégio, de 0 a 3, sendo que números maiores correspondem a menos privilégio. O nível 0, mais privilegiado, é normalmente usado para interação direta com o hardware.

A diferença básica causada ao processador pelo anel de privilégio ativo é a permissão ou não de executar certas instruções. Há instruções que só podem ser executadas em anéis de privilégio menores que um certo valor. Resumidamente, nas arquiteturas x86 e AMD 64, por exemplo, todas as instruções podem ser executada no anel 0, algumas não podem ser executadas nos anéis 1 e 2, e há um conjunto que não pode ser executado no anel 3.

Mecanismos especiais em cada processador são providos para promover a mudança para um nível mais privilegiado de forma controlada. 

De maneira geral, quando operando em processadores x86, um SO usa apenas dois desses níveis de privilégio, 0 e 3, que são usados para a execução de códigos do kernel (0=kernel mode) e para a execução de aplicações (3=user mode).

Como códigos de aplicação executando em user mode (anel 3) não têm acesso a certas funcionalidades do hardware, há um mecanismo para a chamada de código do kernel, que é usado nas chamadas de sistema. 

Quando o mecanismo de níveis de privilégio está ativo na arquitetura x86/ia64, por exemplo, um campo chamado IOPL, definido através de alguns bits do registrador EFLAGS, controla o acesso ao espaço de E/S pelas instruções específicas para isso. Isso permite que o Sistema Operacional defina o nível de privilégio necessário para executar operações de E/S. Em geral, esse privilégio só é concedido aos níveis 0 e 1, de forma que apenas o SO pode executar essas operações. Chamadas de sistema apropriadas devem ser oferecidas para os serviços de E/S providos pelo SO.

Além dos bits de privilégio dos FLAGS, o campo de I/O Port Permission no TSS determina a possibilidade do programa corrente executar acessos às portas de E/S.

Exemplos de instruções privilegiadas para E/S incluem: IN, INS, OUT, OUTS, CLI (clear interrupt-enable flag), and STI (set interrupt-enable flag). Tentativas de executar essas instruções sem o privilégio devido causam exceções (general protection exception).

---
#### Boot: carregamento inicial do SO
Se o funcionamento de um processador é baseado num ciclo contínuo de busca e execução de instruções, como funciona o boot, ou seja, o carregamento inicial do sistema operacional? 

O ciclo de busca e execução de instruções do processador é válido desde o instante  em que o computador é ligado. Isso significa que para o boot do computador é preciso que já exista algum programa a executar na memória. Como a memória RAM é volátil (*) e vai estar zerada quando o computador for ligado, apela-se para a ajuda da BIOS. Trata-se de um firmware mantido numa memória não volátil, mas que é endereçada como RAM. Assim, no boot, é **forçado um valor** (https://en.wikipedia.org/wiki/Reset_vector) para o registrador ponteiro de instruções (Program Counter - PC), que é um endereço que aponta ao programa básico de entrada e saída, mantido tipicamente numa memória flash (ou alguma outra tecnologia não volátil). 

- Vale saber que também existe uma tecnologia chamada NVRAM (Non-volatile RAM), que tem sido explorada para armazenamento de configurações em sistemas computacionais. Seu uso tende a ser cada vez mais explorado pelos sistemas computacionais e pelos SOs.

Já sabemos que o endereço do programa da BIOS é atribuído ao registrador PC do processador quando o computador é ligado. Assim, o primeiro programa executado é o programa que estiver armazenado na BIOS. Sua primeira missão é realizar um teste dos recursos e equipamentos conectados, chamado power-on self-test (POST). Entre as atividades do POST incluem-se o teste de registradores internos da CPU, a verificação do código da BIOS, o teste de componentes como controladores DMA, de timer e de interrupções. Há verificação da memória, da interface de vídeo e de dispositivo de entrada, como o teclado. Também ocorre uma verificação de barramentos e dispositivos conectados e uma organização dos dispositivos selecionados / habilitados para o carregamento do SO.

- Aspectos sobre o endereçamento de áreas de memória e interação com controladores de dispositivos serão tratados mais detalhadamente em unidade futura.

Contudo, será que o programa da BIOS (ou UEFI) sabe onde estão os arquivos no SO no disco? Conhece diferentes formatos de sistema de arquivos? Saberia identificar o nome dos arquivos do SO a carregar, mesmo com atualizações e mudanças de versões?

A solução adotada pelo programa da BIOS para o boot é mais simples, tornando-o "agnóstico" em relação ao SO armazenado em disco. Cabe ao programa da BIOS apenas carregar para a memória o conteúdo de um bloco de dados específico do disco, o primeiro setor, chamado Master Boot Record (MBR). A determinação de qual dispositivo será usado para o boot depende de configurações da BIOS. 

Na arquitetura do PC, o conteúdo deste bloco é carregado para a posição 0x7C00 [citation needed! - estou procurando...]  

Uma vez carregado o conteúdo do bloco para a memória, cabe ao programa da BIOS verificar seu conteúdo antes de transferir o contador de programa da CPU para a sua execução. Na arquitetura x86 / AMD64, por exemplo, isso é feito verificando se os 2 últimos bytes do bloco contêm um valor específico, chamado Boot loader signature (AA55H). Se o valor ali armazenado for diferente disso, significa que o bloco carregado não contém um boot loader, e é preciso tentar carregar um bloco de próximo dispositivo de boot configurado. Esse pode ser identificado como a primeira partição ativa identificada na tabela de partições, ou o primeiro setor de outra unidade de armazenamento. 

Caso tenha conseguido carregar um bloco de boot válido, o programa em execução (BIOS) transfere a execução para essa área, ou seja, ajusta o PC para o endereço 0x7C00, no caso dos computadores pessoais.

É claro que um programa de boot de um SO não cabe em apenas 1 bloco de dados (512 bytes, menos o espaço para a tabela de partições, 64 bytes, e os 2 bytes da assinatura = 446). Assim, o boot é feito através do encadeamento de carregamento e chamada de vários blocos de código. No bloco inicial de boot carregado pela BIOS há um novo programa carregador de boot. Chamado de first-stage boot loader, esse código, que é dependente da versão do SO usado, vai promover o carregamento de uma outra parte de seu código e, a partir daí, vai ser carregado o SO padrão configurado ou espera-se que o usuário decida qual SO carregar. Para tanto, o programa de boot de segundo estágio deve conhecer detalhes do sistema de arquivos onde os arquivos de boot estão armazenados.

O segundo estágio do boot é feito por programas auxiliares dos sistemas operacionais. Em sistemas Linux isso é feito pelo programa GRUB, mas já foi feito pelo LILO. Em sistemas Windows, usava-se o NTLDR, passando as novas versões a usar o BOOTMGR. 

Detalhes sobre a estrutura do boot de um sistema Linux podem ser vistos na documentação do kernel.

Também é possível fazer o carregamento dos arquivos de boot do SO a partir da rede... vejam PXE, DHCP e TFTP...

.

Mais uma consideração a fazer aqui é que os procedimentos descritos até então refletem o funcionamento de processadores para os computadores pessoais. É claro que há ainda muitas particularidades do funcionamento desses processadores não tratadas aqui. Além disso, outros sistemas computacionais e processadores têm outras particularidades. Alguma lógica parecida com os procedimentos descritos aqui deverá existir nesses sistemas, contudo.


[1] https://developer.ibm.com/articles/l-linuxboot/
[2] https://en.wikipedia.org/wiki/Linux_startup_process 
[3] https://en.wikipedia.org/wiki/BIOS_interrupt_call 
[4] https://www.intel.com/content/dam/www/public/us/en/documents/research/2011-vol15-iss-1-intel-technology-journal.pdf
[5] https://wiki.osdev.org/UEFI 
[6] https://manybutfinite.com/post/how-computers-boot-up/

**UEFI vs. legacy BIOS**

A common misconception is that UEFI is a replacement for BIOS. In reality, both legacy motherboards and UEFI-based motherboards come with BIOS ROMs, which contain firmware that performs the initial power-on configuration of the system before loading some third-party code into memory and jumping to it. The differences between legacy BIOS firmware and UEFI BIOS firmware are where they find that code, how they prepare the system before jumping to it, and what convenience functions they provide for the code to call while running.

**Boot mechanism**

A legacy BIOS loads a 512 byte flat binary blob from the MBR of the boot device into memory at physical address 7C00 and jumps to it. The bootloader cannot return back to BIOS. UEFI firmware loads an arbitrary sized UEFI application (a relocatable PE executable file) from a FAT partition on a GPT-partitioned boot device to some address selected at run-time. Then it calls that application's main entry point. The application can return control to the firmware, which will continue searching for another boot device or bring up a diagnostic menu.

---
#### Abstrações providas por SOs para o uso dos sistemas computacionais

Para simplificar o uso dos recursos de um sistema computacional, SOs fornecem algumas abstrações, relacionadas à execução de programas e ao armazenamento de dados.

De maneira geral, o papel de um Sistema Operacional pode ser resumido a dois aspectos principais:

- Gerenciar o funcionamento dos recursos disponíveis no sistema, incluindo processadores, memória, unidades de armazenamento, de comunicação em rede e de interação com o usuário,
- Oferecer serviços para uso de recursos virtuais, com abstrações de aspectos relacionados aos recursos físicos envolvidos e provendo o uso compartilhado, eficiente e seguro entre os programas.

Entre as abstrações providas pelo SO aos processos, pode-se destacar:

- Processos e threads
- Espaço de endereçamento
- Arquivos e diretórios
- IPC e Sockets
- Processos e threads

Processadores trabalham num ciclo contínuo de busca e execução de instruções. Assim, qualquer atividade a executar, como os programas de aplicação, são compostos de sequências de instruções do repertório de instruções do processador onde serão executados.

Por razões de simplicidade e facilidade de programação, contudo, programas são comumente escritos em linguagem de alto nível e posteriormente convertidos em código executável para a arquitetura e o sistema operacional alvo. Como trataremos posteriormente, o acesso aos recursos do SO num programa em alto nível, ocorre na forma de chamadas de função de uma biblioteca.

Cada SO e cada sistema computacional tem aspectos específicos em relação ao código gerado para execução. Cabe ao compilador e ao mecanismo de geração de código criar uma estrutura apropriada para execução no computador alvo.

De maneira geral, todo SO apresenta o conceito de processo, que é uma abstração para representar um programa em execução. Associado a cada processo, é possível ainda ter várias linhas de execução (threads).

Aspectos da criação e do gerenciamento de **processos** e threads serão tratados em detalhes posteriormente.

**Espaços de endereçamento**

Sob o ponto de vista dos programas, a memória RAM disponível no computador é vista apenas como um conjunto de áreas que eles podem referenciar. Assim, cada programa não faz referências diretas aos endereços da memória física, mas a posições específicas dentro de suas áreas de memória em seu **espaço de endereçamento**.

De maneira geral, as áreas de memória de um processo são: código, dados e pilha.

A área de código contém as instruções do processo, os códigos das bibliotecas compartilhadas indicadas pelo compilador e solicitadas em seu carregamento, os códigos das chamadas de sistema solicitadas do SO. É claro que outras áreas do SO também devem acessíveis durante a execução de cada processo, como as rotinas de tratamento de interrupção e outros códigos associados, mas os processos não precisam preocupar-se com isso.

Do ponto de vista dos dados, um processo sabe que há uma área onde estão as variáveis globais e estáticas e uma área onde são posicionadas variáveis alocadas dinamicamente (heap). Também há uma área de pilha, usada para salvamentos de informações temporárias e para a passagem de parâmetros e o salvamento de endereços de retorno em chamadas de funções e desvios de código.

Outras áreas de memória podem ser alocadas explicitamente por processos que têm demandas específicas, via mmap ou shmget/attach.

Mas como será que o SO oferece essas abstrações? 
De maneira resumida, gerenciando as áreas de memória física (RAM) do sistema, atribuindo páginas aos processos sob demanda, e apoiando o funcionamento dos mecanismos do hardware associados à tradução de endereços lógicos em físicos. Assim, há um isolamento entre as áreas de memória dos processos e todas as referências à memória feitas pelos programas tratam de endereços virtuais.

Detalhes sobre o gerenciamento de memória serão tratados em capítulo específico.

**Arquivos e diretórios**

Arquivos são uma abstração provida pelo SO para que processos possam armazenar informações de maneira não volátil (persistente, sem apagar-se quando o computador é desligado).

Usando arquivos e diretórios, processos podem escrever e ler informações, sem preocupar-se com os inúmeros aspectos envolvidos no uso de unidades de armazenamento:

interação com controladores de dispositivos e conhecimento de procotolos específicos
organização dos espaços de armazenamento nos dispositivos (sistema de arquivo)
organização dos dados em blocos para leitura e escrita (uso de dispositivos de bloco)
Para os programas, basta solicitar ao SO para abrir (ou criar) e ler e escrever em arquivos.

**IPC e Sockets**

Programas em execução, representados na forma de processos (e threads), têm áreas de memória lógica isoladas umas das outras. Assim, para comunicação entre processos, o SO precisa oferecer mecanismos específicos.

Comunicações eventualmente são necessárias para passagem de informação e sincronização e podem ocorrer através de diferentes mecanismos providos pelos SOs. 

Esses mecanismos são chamados de mecanismos de IPC (Inter Process Communication), e incluem estruturas como pipes, semáforos, sockets e até áreas de memória compartilhada.

O mecanismo de sockets, por exemplo, permite a criação de um ponto lógico de comunicação entre processos, que podem estar no mesmo sistema ou mesmo em computadores diferentes, como ocorre na Internet. Diferentes protocolos de comunicação (TCP/IP, IPX,X.25, ...) e diferentes tipos de comunicação (com e sem conexão e controles de transmissão) podem ser associados a um socket.

Com isso, aspectos associados desde os protocolos de comunicação e as trocas de mensagens de controle são abstraídos pelo SO, assim como toda a interação com as interfaces de comunicação envolvidas.

Detalhes de estruturas de comunicação entre processos, incluindo descrições dos mecanismos, suas funcionalidades e mesmo sobre a lógica de utilização para diferentes tipos de aplicação serão tratados em capítulo dedicado.

---
#### Interação com o SO

Como é a interação dos usuários com um SO e dos programas com o SO?

Em sistemas computacionais atuais, usuários comumente interagem com o sistema operacional através de uma interface gráfica, às vezes usando comandos de voz, ou através da digitação de comandos para um programa shell (interpretador de comandos).

Porém, todos os programas de aplicação, e mesmo o shell e os programas da interface gráfica, interagem com o SO através da chamada de funções de serviço, denominadas System Calls (ou syscalls). 

Contexto:

- Processadores apenas executam instruções, sem se importar se são parte do código do SO ou de um ou outro programa de aplicação;
- SO é código, composto de instruções do repertório de instruções do sistema computacional que gerencia;
- SO gerencia a alternância do uso do(s) processador(es) para execução das suas instruções e das instruções dos programas;
- SO gerencia o uso dos espaços de memória, mantendo cada programa em áreas distintas;
Alguns dispositivos físicos do computador, como discos, teclados, monitores, etc, têm circuitos controladores físicos associados (onboard ou conectados a algum barramento do computador);
- SO gerencia o funcionamento dos recursos físicos, como discos, teclados, monitores de vídeo, interfaces de rede, etc., enviando comandos para os controladores desses dispositivos via barramentos (ou áreas específicas de memória);
- Processadores comumente têm mais de um anel de privilégio de execução; a execução de algumas instruções do processador só é permitida em alguns anéis de privilégio;
- Código do SO executa em anel com maior privilégio e pode usar todas as instruções do processador;
- Quando SO atribui o uso do processador para execução de instruções de programas, o processador é colocado em anel sem privilégio, de forma que algumas instruções não poderão ser usadas pelos programas;
- As instruções do processador para enviar comandos e enviar e receber dados de/para os controladores físicos dos dispositivos são privilegiadas e não podem ser usadas pelos programas, só pelo SO (em anel de maior privilégio);
- Programas precisam do SO para fazer operações de entrada e saída de dados!
- Programas precisam do SO para usar outros recursos abstratos que ele oferece, que tornam o uso do computador e a programação mais simples e eficiente!

**Chamadas de sistema**, system calls ou syscalls, são os nomes dados às solicitações dos serviços oferecidos por um sistema operacional aos programas. Serviços típicos de um SO incluem aqueles que oferecem acesso a dispositivos, como as operações de entrada e saída (I/O) e de acesso ao sistema de arquivos, e mecanismos para criação, gerenciamento e comunicação entre processos. 

Com as chamadas de sistema, o SO serve de intermediário para as ações que requerem privilégio de execução, como as instruções para acesso ao barramento (in e out) e aquelas usadas para o controle de interrupção (cli e sti). Essas são algumas instruções que não podem ser executadas no anel de privilégio 3 do processador, usado para a execução de processos de usuário. Além disso, ao oferecer os serviços, o SO pode promover a utilização compartilhada dos recursos, de forma eficiente, segura e justa.

Do ponto de vista dos programas que querem usar os serviços do SO, as chamadas de sistema (syscalls) são usadas como se fossem chamadas de bibliotecas de funções (APIs). Em sistemas compatíveis com os padrões Unix, por exemplo, as chamadas das syscalls são definidas através de uma interface em linguagem C. O uso dessa interface em alto nível favorece a portabilidade dos programas, cujo código fonte pode ser compilado para diferentes arquiteturas e SOs.

Apesar das chamadas de sistema nos programas ocorrem como chamadas de funções de uma APi, os códigos dos serviços do SO não são disponibilizados na forma de uma biblioteca, que seria ligada ao código das aplicações. Os códigos de serviço do SO, ou seja, das syscalls, são carregados para a memória na fase de boot e ficam disponíveis para uso pelos programas em tempo de execução apenas.

Nas bibliotecas (APIs) com as chamadas de sistema, como a libc em sistemas Unix, ou glibc em sistemas Gnu/Linux, existe apenas um código chamado de wrapper function (um invólucro) que faz uma interface, um desvio, para o código efetivo do SO quando o programa estiver sendo executado.

Cabe a essas funções em alto nível (wrapper functions) fazer ajustes necessários e realizar o acesso (desvio do processamento) ao kernel de forma adequada à plataforma de hardware e SO disponíveis. Normalmente, a implementação da função intermediária apenas faz uma cópia dos parâmetros da chamada da função em C para registradores do processador e invoca a chamada de sistema via uma instrução de interrupção ou via instruções desenvolvidas pelos processadores para chamada explícita ao kernel. Essas instruções, denominadas syscall e sysenter,  estão presentes em processadores Intel e AMD, por exemplo. Cabe à função de alto nível (wrapper) decidir qual mecanismo de chamada será utilizado para desviar o processador para a execução da rotina apropriada do código do SO.

Um aspecto importante a observar aqui é como ocorre a localização do código de cada chamada de sistema quando ela é invocada. Se pensarmos o código de cada syscall como uma função, de que maneira a wrapper function sabe qual é o endereço do código dessa função na memória para fazer um desvio do processador até ela durante a execução do programa que faz a chamada?

Na arquitetura x86, dos processadores Intel e AMD, por exemplo, há duas formas principais para o desvio: a instrução SYSCALL, para instruções 64 bits, e a instrução INT no modo 32 bits. No modo 32 bits há também uma instrução SYSENTER, que pode ser usada para desvio ao SO, de forma semelhante ao realizado com a instrução SYSCALL.

De maneira resumida, quando um programa faz uma chamada de sistema, o SO entra em ação através de um desvio do contador de programa do processador. Ocorre como se o programa executasse uma instrução CALL do processador, usada para chamada de função. O problema é que o programa, ou mesmo a interface da chamada de sistema (wrapper) não sabe qual é o endereço do código desejado no SO na memória... Mesmo se soubesse e colocasse o endereço gravado no código do programa, esse programa deixaria de funcionar se houvesse alguma mudança do SO e o endereço da função desejada fosse alterado.

A solução é fazer algum desvio indexado, ou seja, baseado em algum local onde o SO vai colocar o endereço de acesso às syscalls.

**1. Chamada de sistema via instrução INT do processador (modo 32 bits)**

A ideia é fazer algo parecido com uma chamada de função: CALL xxx. Para executar essa instrução, o processador salva o valor atual do contador de programa (PC) na pilha e atribui o endereço xxx ao PC. Assim, o processador passa agora a executar código na nova área da memória. 

Do mesmo modo que no tratamento de interrupções geradas por dispositivos externos, há uma instrução do processador quer permite a geração de uma interrupção por software. Incluída no código do programa, a instrução INT num vai gerar o salvamento do valor atual do contador de programa na pilha antes de alterar seu valor. Isso é feito pelo próprio processador, tipicamente copiando os valores atuais do ponteiro de programa na pilha da tarefa atual.

Usando agora o número da interrupção informado como parâmetro da instrução, num, o processador consulta uma área de memória chamada vetor de interrupções (IDT - Interrupt Description Table) para obter um novos valores para os FLAGS e para o contador de programa (PC). Pronto, o processador volta ao ciclo de busca e execução de instruções, agora desviado para a rotina de tratamento dessa interrupção, nesse caso o código das syscalls.

Vale atentar que esse desvio indexado foi tratado pelo próprio processador, executando a instrução INT. Só quando o processador começar a executar as instruções do novo local da memória é que o SO vai passar a ser executado.

Para que essa forma de desvio ao SO funcione, o SO deve (a) ter criado uma rotina de tratamento da chamada de sistema, (b) instalado essa rotina na memória, (c) colocado o endereço dessa rotina numa posição específica do vetor de interrupções (IDT).

**2. Chamada de sistema via instrução SYSCALL do processador (modo 64 bits)**

Relembrando, o programa em execução precisa fazer um desvio ao código de serviço do SO em tempo de execução, sem saber o endereço desse código na memória.

Do modo equivalente ao uso da instrução INT, na chamada de sistema via instrução SYSCALL, a execução dessa instrução pelo processador faz com que o o valor do registrador RIP (PC, na arquitetura 64 bits) seja salvo e seja substituído pelo endereço da rotina de entrada do SO. O endereço a ser atribuído ao RIP, contudo, agora é obtido a partir de uma espécie de registrador interno da CPU, cujo valor foi preenchido pelo SO. 

Como o endereço para desvio ao código do SO é obtido de registradores internos ao processador, ao invés de ter que acessar uma posição indexada da memória, (no caso da instrução INT), a forma de chamada do SO via instrução SYSCALL é mais rápida!

Para que essa forma de desvio ao SO funcione, o SO deve (a) ter criado uma rotina de tratamento da chamada de sistema, (b) instalado essa rotina na memória, (c) colocado o endereço dessa rotina em registradores específicos do processador.

Normalmente, na fase inicial (boot), o SO carrega sua rotina de tratamento das chamadas de sistema para a memória e ajusta seu endereço no vetor de interrupções na memória e nos registradores de endereço específicos. Assim, sempre que uma chamada de sistema é feita, seja através da instrução de interrupção ou das instruções syscall / sysenter, o SO entra em ação porque o valor dos registradores [FLAGS,] CS e EIP (ou RIP) são salvos e alterados para o endereço do SO (de sua rotina de tratamento).

Processadores Intel e AMD têm instruções logicamente equivalentes para chamada de sistema rápida: sysenter e syscall. Em processadores Intel, syscall é o modo padrão de acesso ao kernel no modo x86-64. Sysenter é usado no modo 32 bits. O uso da chamada via int 0x80 não é mais o modo preferido de acesso, já que a maior parte dos sistemas tem usado o modo 64 bits e o desvio pela instrução SYSCALL é mais rápido.

Em sistemas Linux, aplicações que queiram fazer chamadas de sistema podem invocar VDSO, que é uma biblioteca mapeada no espaço de endereçamento de todo processo. Cabe a essa forma de acesso tratar dos detalhes mais complexos da chamada via syscall ou sysenter.

Vale observar que a área do código do SO onde estão as rotinas das chamadas de sistema devem estar mapeada no espaço de endereçamento de todos os programas

**Ajuste do anel de privilégio do processador para execução do SO**

Outro aspecto relevante da chamada de sistema é o ajuste do nível de execução para o o anel 0 (mais privilegiado). Isso ocorre ao desviar-se o processador da execução da aplicação para a execução do código do SO.

Para tanto, bits de controle nos descritores de segmento do código do SO indicam o anel 0 de privilégio. Também o ponteiro da pilha é substituído por um ponteiro para uma área específica para esse nível de execução.

Como se vê, o SO precisa reservar uma área de pilha para cada anel de privilégio para cada tarefa.

Resumidamente, quando um programa faz uma chamada de sistema, o processador, que vinha executando instruções de um programa, é desviado para a execução de instruções do SO. Além da mudança no PC e no registrador de pilha (Stack), há uma mudança no anel de privilégio do processador, que agora vai poder executar qualquer instrução do seu repertório que houver no código do SO.

**Retornando de uma syscall**

De que maneira o SO retorna o processador à execução de código do programa que o chamou, após concluir a syscall?

Como vimos, as instruções de desvio ao SO geram a mudança do contador de programa, da pilha e do anel de privilégio do processador. Ao concluir o serviço solicitado, o SO deve retornar o processador à execução do programa que o solicitou, no anel sem privilégio (ou passar o processador a outro programa, como veremos posteriormente), 

Supondo que o serviço solicitado ao SO foi concluído rapidamente, o SO pode direcionar o processador à continuação da execução das instruções do programa solicitante. Para tanto, é preciso restaurar a pilha, voltar o PC para apontar para a área de código do programa, e retornar o anel de privilégio apropriado. Há instruções do processador que ajudam a fazer isso. 

Pronto, SO sai de cena! Como vemos, embora o SO esteja sempre presente na memória e pronto para execução, suas partes normalmente só são colocadas em execução quando são necessárias. Caso contrário, o(s) processador(es)  vai(vão) estar em uso executando instruções dos programas! 

Outro aspecto importante a notar é que quando se diz "o SO faz isso, ou aquilo..." significa apenas que "o processador, executando código do SO, executa instruções que causam isso, ou aquilo...". Afinal, o SO é código, código de serviço.

Retomando a atenção para o código da interface em alto nível das chamadas de sistema (wrapper functions), o valor de retorno das chamadas de sistema em C que forem bem sucedidas varia mas, em geral, é 0 (zero). Quando não são bem sucedidas, a maior parte das chamadas de sistema retorna um valor de erro negativo. Neste caso, a função equivalente em C da chamada de sistema copia o valor absoluto do código de erro na variável errno(3) e retorna o valor -1 para o programa que executou a chamada. Funções da biblioteca C, como perror(3) e strerror(3), podem ser usadas nos programas para a tradução de um código de erro numa mensagem apropriada.

**Syscalls em Linux**

A implementação das funções de acesso às chamadas de sistema é feita pela biblioteca libc, ou glibc, em sistemas GNU/Linux. A biblioteca glibc ainda permite o acesso direto às chamadas de sistema, sem fazer a intermediação típica das chamadas (wrapping). Para tanto, é implementada uma função chamada syscall, que permite especificar o número da chamada de sistema e os parâmetros relevantes. A função syscall é útil principalmente quando se deseja usar uma chamada de sistema ainda não implementada pela versão da glibc disponível na distribuição Linux em uso.

Um outro aspecto interessante das interfaces de chamada de sistema é a otimização do acesso em algumas chamadas de sistema frequentes e que envolvem apenas a leitura de informações mantidas pelo kernel. Esse é o caso, por exemplo, das chamadas gettimeofday(2), clock_gettime(2), getcpu(2) e time(2). Uma estratégia para realizar a chamada gettimeofday, por exemplo, de forma rápida consiste em fazer o kernel manter as informações sobre o horário atual em uma localização fixa da memória, que é mapeada no espaço de endereçamento de todos os processos. Desta forma, a interface em alto nível da chamada de sistema pode apenas ler o valor e retorná-lo ao processo, sem gerar uma mudança do processador para modo kernel. Da mesma maneira, algumas outras chamadas de sistema poderiam ser implementadas apenas através de acesso à memória. No Linux, essas implementações de chamadas de sistema que evitam a mudança do modo de execução do processador para o kernel space (nível 0) eram tratadas na biblioteca vsyscalls e passaram a ser implementadas na biblioteca vdso (Virtual Dynamic Shared Object). Ambas são mapeadas para o espaço de endereçamento de cada processo quando ele é carregado para execução.

---
#### Serviços do SO para os programas

Quais são os serviços típicos oferecidos pelos SOs aos programas? Como esses serviços são usados?

O conjunto de chamadas de sistema pode variar de acordo com o SO. Sistemas operacionais que permitem a criação nativa de programas com interfaces gráficas, podem ainda oferecer outros conjuntos de chamadas de sistema para a manipulação de janelas e outros aspectos. Isso acontece em sistemas Windows, por exemplo (https://docs.microsoft.com/en-us/windows/win32/apiindex/windows-api-list). Nem todas essas chamadas de serviço, contudo, vão gerar a transição do código do programa para rotinas de serviço do SO em tempo de execução. Muitas dessas chamadas correspondem a códigos que são tratados no próprio programa de aplicação, ligados ali com a inserção de códigos na fase de compilação / ligação da geração do código executável.

Uma lista de chamadas de um sistema operacional MacOS pode ser vista aqui: https://sigsegv.pl/osx-bsd-syscalls/, ou aqui: https://opensource.apple.com/source/xnu/xnu-1504.3.12/bsd/kern/syscalls.master.

Já as syscalls do sistema Linux podem ser consultados diretamente no repositório fonte do código: https://github.com/torvalds/linux/blob/master/arch/x86/entry/syscalls/syscall_64.tbl.

De maneira geral, em sistemas compatíveis com padrões POSIX, as chamadas de sistema são organizadas em grupos, que incluem suporte para: acesso e manipulação de arquivos e diretórios, comunicação em rede, criação e sinalização de processos, comunicação e sincronização entre processos, manipulação de espaços de memória, manipulação de informações de tempo, entre outras.

Em sistemas Gnu/Linux, uma lista ampla das syscalls pode ser vista no [manual](https://man7.org/linux/man-pages/man2/syscalls.2.html) online ($ man syscalls).

---
#### Estrutura de SOs

SOs têm muitos recursos a gerenciar e muitos serviços a prestar. Como são organizados os seus códigos e como funcionam suas partes?

Recapitulando alguns aspectos que estudamos, sabemos que o SO tem as seguintes partes/funcionalidades:

- Tratamento de interrupções
- Chamadas de sistema
- Controladores de dispositivos físicos
- Suporte para gerenciamento de memória, processador(es), unidades de armazenamento, dispositivos de entrada e saída, interfaces de rede, ...
- Software para auto-carregamento na fase de boot e configuração do computador
- ...

Outro aspecto que talvez já esteja claro é que, embora seja um gerente de recursos e prestador de serviços, o SO comumente só entra em execução quando é necessário. Ou seja, um processador só é direcionado à execução de códigos do SO quando há algo específico  a ser feito.

Há diferentes formas de organizar o código do SO.

De forma semelhante a um grande programa de aplicação, é possível pensar que o SO seja desenvolvido contendo várias bibliotecas de códigos para tratar aspectos específicos e várias bibliotecas de suporte. Teoricamente, qualquer trecho de código do SO poderia referenciar diretamente quase todas as funções disponibilizadas pelas suas bibliotecas. Alguma função principal do programa seria responsável pelas inicializações e configurações, passando o SO à espera de eventos que o ponham a trabalhar à espera de eventos e chamadas de serviço.

Para gerar um código utilizável do SO, todo o código relacionado às inicializações, configurações e posteriores tratamentos de eventos seria compilado e ligado num único arquivo executável. A esse formato de SO composto de um programa único é dado o nome de sistema **monolítico**.

Alguns SOs monolíticos oferecem ainda o conceito de **módulos do núcleo** (kernel modules), cujos códigos podem ser carregados e descarregados dinamicamente em tempo de execução, sem ser necessário reiniciar o SO para que suas funcionalidades sejam adicionadas e removidas do SO. Diferentes funcionalidades podem ser configuradas como módulos, desde que seja possível alterar as estruturas do SO em tempo de execução. 

Também no modelo monolítico, é possível que o código fonte seja logicamente **organizado em camadas** de abstrações. Cada camada é encarregada de gerenciar alguns tipos de recursos e oferecer abstrações e funções de mais alto nível à camada imediatamente acima.

Levando ao extremo o modelo de camadas, é possível pensar no projeto de um SO minimalista, com poucas camadas e com uma infraestrutura robusta para criação de processos e comunicação e sincronização desses processos. Todas as funcionalidades previstas para o SO no gerenciamento de recursos e na oferta de serviços são implementadas como processos, que utilizam os recursos providos pelo núcleo mínimo do SO. Esse modelo de implementação de SO com um núcleo mínimo é chamado de **microkernel (micronúcleo).**

Por exemplo, controladores de dispositivos podem ser implementados como processos numa camada mais baixa. Numa camada acima, poderia haver processos relacionados à implementação do suporte para sistemas de arquivos. Numa camada mais alta ainda, poderia haver processos que implementam serviços que serão oferecidos aos processos de aplicação.

Todos os processos, inclusive aqueles que implementam serviços do SO são executados no anel de privilégio 3 do processador e, portanto, não têm acesso direto aos controladores físicos dos dispositivos. Assim, qualquer um deles deverá solicitar serviços básicos do núcleo para realizar suas atividades. Ou, ainda, processos numa camada acima da camada de processos tratadores de dispositivos, como os processos ligados à implementação de sistema de arquivo, usam serviços do microkernel para comunicar-se e solicitar serviços dos processos de nivel mais baixo. 

Como o SO isola todos os processos, é mais fácil verificar permissões e controles de acesso, prevenindo erros. Por outro lado, talvez a definição precisa das interfaces e das camadas, mantendo o isolamento entre camadas e entre processos, torne o desenvolvimento do SO bastante complexo. 

A ideia de ter funcionalidades do SO implementadas na forma de processos servidores também pode ser explorada para o SO como um todo. Para tanto, um SO pode ser implementado como um núcleo com uma camada básica associada à interação com os controladores de dispositivos, e com serviços para criar processos e permitir comunicações entre eles na forma de solicitações de serviço. Esse modelo de implementação do SO é chamado de modelo **cliente-servidor.**

Funcionalidades do SO agrupadas e implementadas na forma de processos servidores. Cada processo servidor define uma interface que pode ser acessada pelos demais processos que requeiram seus serviços. Para um processo do SO acessar serviços providos por outro processo basta emitir uma solicitação identificando o serviço e os parâmetros relevantes. Cabe a um mecanismo de comunicação entre processos provido pelo SO intermediar as interações entre esses processos, repassando dados nas solicitações e respostas entre eles.
