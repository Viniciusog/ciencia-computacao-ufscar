# Syscalls
## Professor: Hélio Crestana Guardia
## Universidade Federal de São Carlos
---

## Escalonamento de tarefas

Nesta unidade, trataremos das seguintes questões:

- O que é escalonamento de tarefas?
- Quando ocorre?
- Como essa atividade é implementada no SO?
- Quais aspectos são (podem ser) considerados no escalonamento?
- Há diferença no escalonamento de processos e threads?
- Como já percebemos, num computador pessoal, é comum que existam poucas tarefas prontas para execução em um dado momento, que é aquela com a qual o usuário está interagindo. Outras tantas tarefas existentes estão bloqueadas à espera de dados e eventos na maior parte do tempo.

Nesse caso, parece não haver grandes dificuldades para o escalonador do SO em selecionar a próxima tarefa a executar.

Num computador servidor, contudo, em que há várias tarefas prontas para execução, e vários usuários ansiosos pelos resultados que essas tarefas vão gerar, parece mais evidente a importância do escalonador.

Processos e threads são entidades criadas pelo SO para possibilitar a execução de blocos de código que compartilham os recursos de um computador. Usando o conceito de contexto de execução, associado principalmente ao estado dos registradores do hardware na execução de uma tarefa (processo ou thread), o SO consegue promover a alternância dessas entidades no uso do(s) processador(es). O acesso a outros recursos, como unidades de armazenamento, é tipicamente oferecido por demanda.

De maneira geral, sabemos que o SO promove o compartilhamento eficiente do uso dos recursos sobrepondo as ações dos controladores de dispositivos nas operações de entrada e saída com a execução de instruções pelo(s) processador(es). Chamada de  multiprogramação, essa técnica evita que o processador fique ocioso aguardando a conclusão de uma transferência de dados realizada por um controlador de E/S. Para tanto, o SO instrui o controlador do dispositivo a fazer a leitura ou escrita necessária e direciona o processador para a execução de código de outra tarefa pronta.

Usando técnicas de acesso direto à memória (DMA), um controlador consegue transferir dados lidos de um dispositivo, através de um barramento, para a memória, e também enviar para um dispositivo dados lidos de áreas de memória usadas como buffers pelo SO. Ao finalizar a transferência, o controlador do dispositivo pode gerar uma interrupção ao processador, que serve para desviar a execução de instruções para uma rotina de tratamento do SO.

Outra forma de compartilhar o uso de um processador são as fatias de tempo. Um dispositivo de timer programável (programmable interrupt timer - PIT) presente na motherboard é usado pelo SO para a geração periódica de interrupções. Com essas interrupções, o SO retoma o controle da CPU em intervalos regulares, independentemente do fluxo de instruções do processo atual. Cabe ao SO determinar a frequência de ocorrência dessas interrupções, de acordo com a precisão dos eventos de temporização tratados. 

Definido que uma tarefa deve deixar a CPU momentaneamente, é preciso selecionar a próxima a ocupá-la. Essa seleção é chamada escalonamento de curto prazo de tarefas, ou simplesmente escalonamento (scheduling).

Se processos podem deixar a CPU antes de suas conclusões para dar lugar a outros, tem-se um mecanismo de escalonamento denominado preemptivo. Em sistemas não preemptivos, uma tarefa é executada até ser concluída ou até explicitamente liberar a CPU.

Diferentes critérios podem ser usados pelo escalonador para a seleção da próxima tarefa a executar:

- throughput: vazão, ou seja, o número de processos que completam suas execuções por período de tempo;
- Latência: tempo entre a submissão e a conclusão de um processo (turnaround time) ou tempo entre a submissão e a geração de um resultado (response time);
- Fairness: justiça no uso balanceado do(s) processador, evitando que tarefas tenham suas execuções preteridas (deferred) indefinidamente;
Cumprimento de prazos: garantia de que a execução de tarefas críticas ocorre dentro dos prazos previstos;
Maximização da ocupação dos recursos: 
...

Além disso, é comum ter que tratar prioridades estáticas associadas às tarefas.

Em sistemas computacionais associados ao controle de ambientes externos, como nos sistemas de tempo real, há ainda restrições de prazos para a conclusão da execução de tarefas (deadline). 

Talvez valha ressaltar que, num sistema operacional que não ofereça suporte a threads, o escalonamento faz a seleção do próximo processo a executar. Num sistema que oferece threads, um processo pode ser visto como uma entidade abstrata, sendo que suas threads vão competir pelo uso do(s) processador(es) com as demais threads. 

Em sistemas com suporte a threads, pode haver casos em que o escalonador selecione processos para execução, sendo que as fatias de tempo atribuídas a cada processo são divididas entre suas threads. 

Em sistemas Linux, contudo, como vimos, as entidades executáveis são denominadas tarefas, que podem corresponder logicamente a processos ou threads, dependendo de quais recursos compartilham com outras tarefas. O escalonamento no Linux é feito em função das tarefas existentes, independentemente de seus compartilhamentos.

---
## Escalonamento
**Quando ocorre o escalonamento?**

O que ocorreria se o SO atribuísse o uso do processador para executar instruções de uma única tarefa, até que ela concluísse sua execução? 

Se essa tarefa for composta só por instruções do processador, sem necessidade de E/S, o processador vai ficar ocupado e vai concluir essa tarefa o mais rapidamente possível. Mas, e outras tarefas que também estão prontas para executar?

Se essa tarefa precisar de E/S, ela vai fazer chamadas ao SO para prover esses serviços. O processador vai ser desviado para executar código de serviço do SO, que vai instruir algum controlador de E/S requerido e ficar esperando a transferência necessária ser concluída. O SO ficaria executando um laço de consulta do controlador, usando o processador para fazer nada de útil. Um desperdício! Quando a transferência for concluída, o SO pode repassar os dados à tarefa que os solicitou e redirecionar o processador para a execução de instruções dessa tarefa. 

Parece claro que, se há várias tarefas carregadas na memória e prontas para executar, vale a pena aproveitar toda espera por operações de E/S das tarefas para redirecionar o processador para a execução de instruções de outra tarefa.

Além disso, com várias tarefas prontas, é possível que os usuários fiquem mais satisfeitos se todas estiverem evoluindo, mesmo que em momentos alternados.

Pois o SO leva esses aspectos em consideração, de forma que frequentemente é necessário tomar decisões de escalonamento, ou seja, decidir qual deve ser a próxima tarefa a executar.

Assim, o escalonamento ocorre:

- Quando a tarefa corrente termina (pede ao SO para terminar: _exit());
- Quando a tarefa corrente precisa aguardar por E/S (pede ao SO, que ativa o controlador e, para não deixar o processador à toa, direciona-o para outra tarefa);
- Quando uma interrupção é gerada ao processador, que passa a executar código do SO, que percebe que agora há uma tarefa mais importante a executar do que aquela que estava em execução (preempção);
- Quando o dispositivo de timer gera uma interrupção, indicando ao SO que a tarefa atual já recebeu sua fatia de tempo de uso do processador e é hora de atribuí-lo a outra tarefa (preempção);
- Quando a tarefa corrente, voluntariamente (!!!) retorna o processador ao SO, para que ele o atribua a outra tarefa (sched_yield()).
Em todos os casos, vai haver uma troca de contexto. O SO salva o contexto de execução da tarefa que está deixando o processador, seleciona a próxima tarefa, restaura o contexto de execução dessa tarefa tal qual no momento em que sua execução foi interrompida, e direciona o processador para a execução de instruções desta tarefa selecionada. 

Já dá para perceber que a troca de contexto é uma ação custosa. Assim, é preciso que o tempo em que cada tarefa passa em execução seja relativamente bem maior do que o tempo gasto com a troca de contexto.

---
## Políticas de escalonamento

Levando em consideração os aspectos já indicados sobre o escalonamento de tarefas, há diferentes políticas que podem ser utilizadas pelo SO. É possível até que um SO utilize diferentes políticas para diferentes tipos de tarefas.

Algumas políticas são mais apropriadas para sistemas de processamento de tarefas em lotes, como os descritos a seguir.

**FIFO:** primeiro a chegar, primeiro a ser servido (First Come, First Served)

Trata-se de um algoritmo não preemptivo, usado normalmente em sistemas de processamento em lote. 

**Tarefa mais curta primeiro (Shortest Job First)**

Para esse algoritmo, é preciso conhecer o tempo de execução previsto para cada tarefa, e é preciso que todas as tarefas sejam conhecidas no momento da decisão. 

**Tempo restante mais curto (Shortest Remaining Time First)**

Esse algoritmo é uma versão preemptiva do algoritmo tarefa mais curta primeiro. Também requer o conhecimento prévio dos tempos de execução previstos para as tarefas. 

Quando uma nova tarefa é inserida no sistema, o escalonador verifica se seu tempo de execução é menor que o tempo restante da tarefa corrente. Caso seja, há uma preempção e essa nova tarefa é posta em execução.

Pode acontecer também de a tarefa corrente ser bloqueada por alguma condição, o que também ativa o escalonador para escolher a próxima entre as demais.

.

Em sistemas interativos, como os computadores pessoais e servidores, é comum o uso de escalonadores mais dinâmicos. 

**Chaveamento circular (Round-Robin)**

Nesse algoritmo, a atribuição do uso do processador é feita por períodos de tempo, chamados de fatias de tempo (time-slices). Assim, cada tarefa colocada em execução vai ter suas instruções executadas até que saia por algum motivo ou até que sua fatia de tempo expire. Neste caso, o contexto da tarefa é salvo e ela volta ao fim da fila de tarefas.

Vale observar que, para implementar essa política, o SO precisa usar um dispositivo temporizador que consiga gerar interrupções após o período de tempo desejado, fazendo com que o processador seja desviado da tarefa corrente para uma rotina de tratamento do SO.

A duração da fatia de tempo é uma questão crítica. Se for muito curta, o tempo com troca de contexto pode significar uma sobrecarga muito grande no uso do processador (que passaria mais temp fazendo operações de controle do que executando instruções das tarefas). Se for muito longo, cada tarefa demorará demais para receber o uso do processador, o que pode ocasionar pouca interatividade com o usuário em algumas tarefas.

Supondo que uma troca de contexto dure 1 ms e a fatia de tempo demore 100 ms. A proporção parece boa, mas pode depender do número de tarefas prontas. Se houver 100 tarefas, cada uma vai demorar muito para receber o uso do processador entre uma rodada e outra de escalonamento.

**Escalonamento por prioridades**

O uso de prioridades, estáticas e dinâmicas, pode ser usado como critério para seleção de tarefas para execução. A existência de algum mecanismo de preempção, contudo, pode ser desejável para evitar que tarefas de prioridade mais baixa nunca sejam executadas.

**Múltiplas Filas**

Levando em consideração as prioridades das tarefas, essa política usa várias filas, uma para cada valor possível de prioridade. Cabe ao escalonador selecionar uma tarefa pronta da fila de maior prioridade. Dentro dessa fila, as tarefas podem ser alternadas da mesma forma que o round-robin. Ou seja, há uma alternância entre as tarefas de mesma prioridade. 

Um problema potencial desta política é a possibilidade de tarefas menos prioritária não serem executadas. Assim, há estratégias em que uma tarefa que recebeu uma fatia de tempo, ao voltar para a fila, vá para a fila de prioridade imediatamente inferior. Dentro de cada fila, vale algo como round-robin. Em algum momento, todas as tarefas estarão na fila de mais baixa prioridade, competindo igualmente.

Inúmeras variações do mecanismo de prioridade dinâmica são possíveis.

**Escalonamento garantido**

A ideia do escalonamento garantido é prover uma fração igualitária do uso do(s) processador(es) para cada tarefa. Para tanto, é preciso saber: (a) quantas tarefas existem, (b) qual é o tempo de vida de cada tarefa, (c) quanto tempo de CPU cada tarefa já recebeu.

Para manter essas informações, além de saber quantas tarefas existem, o SO precisa registrar o instante de criação de cada tarefa. É preciso ainda contabilizar o uso de CPU por cada tarefa, o que não é uma tarefa simples. Isso significa que o SO deve registrar o instante exato em que vai atribuir o processador para a execução de instruções de uma tarefa. Ao retomar o controle do processador, o SO deve novamente identificar o instante atual, o que permite que calcule quanto tempo de CPU essa tarefa recebeu. Esse valor deve então ser somado aos tempos de execução anteriores dessa tarefa.

A relação tempo_de_CPU / tempo_de_vida indica a porcentagem de uso de CPU de uma tarefa.

Isso significa que o escalonador deve ordenar as tarefas de acordo com a distância do seu percentual de uso em relação à média do sistema! 

**Escalonamento por loteria**

Nessa proposta, a seleção das tarefas é feita usando uma distribuição de probabilidade. Para tanto, o espaço amostral de valores possíveis de serem sorteados é dividido entre as tarefas de acordo com suas importâncias. Pronto.

Quando é preciso selecionar uma tarefa, faz-se o sorteio. Ao longo do tempo, cada tarefa deve ser sorteada um número de vezes proporcional à sua importância. 

**Escalonamento por fração justa**

Essa política é semelhante ao escalonamento garantido. Ao invés de levar em consideração apenas o número de tarefas, considera-se o número de usuários. O objetivo é cada usuário receba uma fração justa do tempo de processamento. 

Por outro lado, para usuários com poucas tarefas, cada uma deve receber mais tempo do que as tarefas de um usuário que tem muitas delas!

.

**Escalonamento em sistemas de Tempo Real**

Um sistema computacional de tempo real, ou simplesmente sistema de tempo real, é um sistema em que as tarefas têm restrições de tempo para suas execuções.

Aplicados comumente para o controle de alguma atividade externa, sistemas de tempo real podem ser críticos ou não-críticos. Os sistemas de tempo real crítico são aqueles em que as consequências do não cumprimento de prazos de execução são severas. Exemplos incluem o controle de sistemas de saúde, de transporte ou industriais.

Já nos sistemas de tempo real não-crítico, o cumprimento de prazos das tarefas é desejável, mas falhas não são catastróficas! Exemplos incluem a manipulação de sinais de áudio e vídeo recreativos, por exemplo.

Tarefas em sistemas de tempo real têm um tempo de execução previsto, determinado como se suas instruções fossem executadas sem interrupção. Além disso, cada tarefa pode ser periódica ou esporádica.

Tarefas periódicas são ativadas em intervalos regulares, como no caso de uma tarefa responsável por medir a temperatura de um sistema externo. Já as esporádicas ocorrem em função de eventos. Nos dois casos, os prazos para execução das tarefas (deadlines) indicam em quanto tempo as execuções de seus códigos devem ser concluídas após serem ativadas.

Para o escalonamento em sistemas de tempo real, há ainda uma questão de viabilidade, ou seja, se é possível garantir que todas as ocorrências das tarefas serão concluídas dentro dos prazos, sem perdas de deadlines.

Para tanto, é preciso determinar se a soma dos coeficientes de utilização do processador pelas tarefas é menor ou igual a 1. Nessa conta, considera-se os intervalos entre ocorrências de tarefas periódicas e os piores casos, ou seja, as máximas ocorrências possíveis das tarefas esporádicas.

```
m
∑  Ci / Pi  ≤ 1
i=1
```

Ou seja, para ser viável, ou escalonável, é preciso que a soma das taxas de utilização das tarefas não exceda a capacidade de execução do sistema.

Respeitada essa característica das tarefas, há diferentes políticas ótimas para escalonamento em sistemas de tempo real. Em alguns casos, os cálculos das prioridades são estáticos e, em outros, dinâmicos. Algumas políticas para escalonamento em sistemas de tempo real incluem:

- Earliest (ou shortest) deadline first: tarefa com prazo mais próximo primeiro 

- Least slack: tarefa com menor folga (entre prazo e tempo de execução restante) primeiro

- Rate monotonic: é um algoritmo estático, com prioridades inversamente proporcionais aos períodos; menor período implica maior prioridade.

---
## Escalonamento no Linux
O escalonamento no sistema Linux já ocorreu de diferentes formas ao longo do tempo. De todo modo, os mecanismos sempre procuraram atender as especificações POSIX relacionadas.

A política atual é chamada de CFS (Completely Fair Schedule), e sua operação principal pode ser vista na função schedule().

Há várias situações em que essa função é chamada. Alguns exemplos incluem:

- No processamento de uma chamada de sistema bloqueante: exit_to_usermode_loop()
- Na espera por dados numa operação do pipe: wait_for_partner()
- Quando a tarefa corrente termina: do_exit()
- Quando a tarefa corrente recebe um sinal para ser parado: do_signal_stop()
- Quando a tarefa corrente faz uma chamada para dormir: alarm_do_nsleep()
- Cálculo da prioridade dinâmica

No escalonador atual do Linux, CFS (Completely Fair Scheduler), a prioridade dinâmica das tarefas é determinada em função do tempo de execução virtual de cada uma delas (vruntime).

Esse parâmetro é calculado na função update_curr().

Além do tempo de vida da tarefa, são computados os tempos em que uma tarefa passa na CPU, que permitem identificar seu percentual de execução e o tempo de prestação de serviço pelo SO: account_system_time(), account_user_time().https://elixir.bootlin.com/linux/latest/source/kernel/sched/core.c#L6483

---
## Tickless kernels
Ao retomar o controle do processador na ocorrência de uma interrupção do timer, além de verificar se há eventos agendados para tratar, o SO tem a chance de promover a alternância do uso deste processador. Para tanto, fatias de tempo (processor time slices) são definidas para as tarefas na forma e um número de time ticks do gerador de interrupções periódicas.

A cada interrupção do timer, um contador associado ao tempo de execução de uma tarefa é decrementado. Zerado o contador, isso significa o fim da fatia de tempo desta tarefa na CPU.

Há várias questões, contudo, que tornam o **uso de interrupções periódicas não apropriado**. Inicialmente, a escolha da frequência das interrupções deve ser considerada. Intervalos mais curtos permitem maior precisão nos eventos de temporização mas, por outro lado, geram elevada sobrecarga com o processamento das interrupções. Além disso, interrupções periódicas impedem que o processador fique ocioso, mesmo quando não há nada efetivo a executar. Com isso, desperiça-se a chance de desativar o processador e economizar energia.

Assim, o modelo de interrupção periódica tem dado lugar a tickless kernels. Nesses SOs, como ocorre com Linux [1], uma interrupção do timer é programada especificamente para o próximo evento. Embora isso gere um aumento na complexidade do tratamento de eventos de temporização, há possibilidade de economia significativa de energia. Processadores que não têm tarefas prontas podem ser colocados em modo de inoperância com a instrução HALT (em sistemas x86-64). 

[1] https://www.kernel.org/doc/html/v5.0/admin-guide/pm/cpuidle.html#idle-cpus-and-tick